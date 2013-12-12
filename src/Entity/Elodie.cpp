#include "Elodie.h"

Elodie::Elodie() {
    init();
}

Elodie::Elodie(sf::Vector2f position) {
    init();
    setPosition(position.x, position.y);
}

Elodie::Elodie(float x, float y) {
    init();
    setPosition(x, y);
}

void Elodie::init() {
    ANIMATIONS = {
        {ElodieState::STANDING, "standing"},
        {ElodieState::WALKING, "running"},
        {ElodieState::PUNCHING, "attacking"},
        {ElodieState::FALLING, "falling"},
        {ElodieState::JUMPING, "jumping"}
    };

    JsonAccessor json = JsonAccessor();
    json.load(ENTITIES_JSON_PATH+"/"+ENTITYNAME_ELODIE+".json");
    info = json.getEntityInfo();

    state = ElodieState::STANDING;
    speed.x = ELODIE_SPEED;

    sprite = new ElodieSprite(info);
    setEntitySprite(sprite);

    soundManager = SoundManager::getInstance();
}

ElodieSprite* Elodie::getSprite() {
    return sprite;
}

Elodie::~Elodie() {
    delete sprite;
    delete info;
    sprite = NULL;
    info = NULL;
    setEntitySprite(NULL);
}

sf::Vector2f Elodie::getPosition() {
    return sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y);
}

void Elodie::stand() {
    sprite->stand();
}

void Elodie::overworldMove(float seconds) {
    if(!hasToMove()) {
        noMoves();
        stand();
    } else {
        float rem = toMove - seconds*overworldSpeed.x;
        float delta;
        if (rem > 0) {
            toMove -= seconds*overworldSpeed.x;
            delta = seconds*overworldSpeed.x;
        } else {
            delta = toMove;
            toMove = 0;
        }
        if (goingDown) {
            sprite->move(0,delta);
        } else if (goingLeft) {
            sprite->move(-delta, 0);
        } else if (goingRight) {
            sprite->move(+delta, 0);
        } else if (goingUp) {
            sprite->move(0, -delta);
        } else {
            noMoves();
        }
    }
}

void Elodie::setWalkDown() {
    sprite->changeStance(ANIMATIONS[ElodieState::FALLING], sf::seconds(0.1f));
    goingDown = true;
}
void Elodie::setWalkUp() {
    sprite->changeStance(ANIMATIONS[ElodieState::JUMPING], sf::seconds(0.1f));
    goingUp = true;
}
void Elodie::setWalkRight() {
    this->walk();
    goingRight = true;
    flipToRight();
}
void Elodie::setWalkLeft() {
    this->walk();
    goingLeft = true;
    flipToLeft();
}

void Elodie::setDistanceToMove(float dist) {
    toMove = dist;
}

bool Elodie::isMoving() {
    return goingDown or goingLeft or goingRight or goingUp;
}

bool Elodie::hasToMove() {
    return toMove > 0;
}

void Elodie::noMoves() {
    toMove = 0;
    goingDown = false;
    goingLeft = false;
    goingRight = false;
    goingUp = false;
}

void Elodie::update(sf::Time deltaTime) {
    sprite->update(deltaTime);
}

int Elodie::getImmersionLevel() {
    return immersionLevel;
}

int Elodie::getNightmareLevel() {
    return nightmareLevel;
}

void Elodie::takeDamage(int damage, bool ignore) {
    if (!damageCD && (state != ElodieState::PUNCHING || ignore)) {
        immersionLevel -= damage;
        if (immersionLevel < 0)
            immersionLevel = 0;
        damageCD = DAMAGE_CD;
    }
}

void Elodie::walk() {
    sprite->walk();
}

Hitbox Elodie::returnCurrentHitbox() {
    return getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame());
}

void Elodie::punch(std::map< std::string, Entity* >& entities) {
    for (std::map< std::string, Entity* >::iterator it = entities.begin(); it != entities.end(); ++it) {
        if (it->first != "elodie") {
            if (isInFront(returnCurrentHitbox().getArea(), it->second->returnCurrentHitbox().getArea(), direction)) {
                it->second->takeDamage(1, true);
            }
        }
    }
}

void Elodie::changeAnimation(Collide collideTiles) {
    unsigned int curFrame = sprite->getCurrentFrame();
    ElodieState memState = state;

    if (sprite->getCurrentStance() == ANIMATIONS[ElodieState::STANDING] ||
            (state == ElodieState::PUNCHING && curFrame == 3)) {
        if(collideTiles.bottom["surface"]) {
            changeState(ElodieState::WALKING);
            this->walk();
        } else {
            if(speed.y > 0) {
                changeState(ElodieState::FALLING);
            } else {
                changeState(ElodieState::JUMPING);
            }
        }
    }


    if (collideTiles.bottom["surface"]) {
        if (state != ElodieState::PUNCHING) {
            changeState(ElodieState::WALKING);
        }
        if (state == ElodieState::STANDING) {
            changeState(ElodieState::WALKING);
        }
        if (state == ElodieState::WALKING && curFrame == 1 && sprite->getPreviousFrame() != curFrame) {
            soundManager->play(SoundType::FOOTSTEP_GROUND);
        }
    } else if (state != ElodieState::PUNCHING) {
        if (speed.y > 0) {
            changeState(ElodieState::FALLING);
        } else {
            changeState(ElodieState::JUMPING);
        }
    }

    if (state != memState) {
        sprite->changeStance(ANIMATIONS[state], sf::seconds(0.1f));
    }
}

void Elodie::handleEvent(EventHandler* const& event, EntityMap& entities, Collide collideTiles) {
    if (event->keyIsPressed(sf::Keyboard::Space) &&
            (state == ElodieState::WALKING || state == ElodieState::STANDING ||
             (state == ElodieState::PUNCHING && collideTiles.bottom["surface"]))) {
        changeState(ElodieState::JUMPING);
        speed.y = ELODIE_JUMP;
        sprite->changeStance(ANIMATIONS[state], sf::seconds(0.1f));
    } else if (event->keyIsPressed(sf::Keyboard::A) && (attackTimer > ATTACK_COOLDOWN)) {
        attackTimer = 0;
        changeState(ElodieState::PUNCHING);
    } else if (state == ElodieState::PUNCHING) {
        punch(entities);
    }
}

//What's in doStuff right now is only for testing purpose. Lot of stuff to do here.
void Elodie::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, EntityMap& entities, sf::Time animate) {
    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    sprite->update(animate);

    //Change the sprite in accord with the speed
    changeAnimation(collideTiles);
    handleEvent(event, entities, collideTiles);

    if (0 == speed.x && !collideTiles.right["surface"]) {
        speed.x = ELODIE_SPEED;
    }

    float dist = cameraPos.x - sprite->getPosition().x;

    if (dist > 0 && !collideTiles.right["surface"] && !buffed) {
        buffed = true;
        speed.x = ELODIE_SPEED + dist;
    }

    buffed = !collideTiles.right["surface"];

    if (buffed && dist <= 0) {
        buffed = false;
        speed.x = ELODIE_SPEED;
    }

    //Other stuff to do
    attackTimer += animate.asSeconds();
    pvTimer += animate.asSeconds();
    if (pvTimer > INC_PV_TIMER) {
        pvTimer = 0;
        immersionLevel = immersionLevel == 100 ? 100 : immersionLevel + 1;
    }
    if (damageCD)
        --damageCD;
    cameraPos.x += ELODIE_SPEED*animate.asSeconds();
    cameraPos.y = sprite->getPosition().y;
}

void Elodie::changeState(ElodieState to) {
    ElodieState from = state;
    state = to;

    if(from == ElodieState::WALKING && to == ElodieState::JUMPING) {
        speed.y = ELODIE_JUMP;
        sprite->changeStance(ANIMATIONS[state], sf::seconds(0.1f));
    } else if(from == ElodieState::FALLING && to == ElodieState::WALKING) {
        soundManager->play(SoundType::FOOTSTEP_GROUND);
    } else if(from == ElodieState::JUMPING && to == ElodieState::WALKING) {
        soundManager->play(SoundType::FOOTSTEP_GROUND);
    }

    if(to == ElodieState::PUNCHING) {
        sprite->changeStance(ANIMATIONS[state], sf::seconds(0.05f));
        soundManager->play(SoundType::PUNCH);
    }
}

void Elodie::pause() {
    sprite->pause();
}

void Elodie::play() {
    sprite->play();
}

void Elodie::reset() {
    immersionLevel = 100;
    pvTimer = 0;
    attackTimer = 2;
    state = ElodieState::WALKING;
    speed.x = ELODIE_SPEED;

    setEntitySprite(sprite);

    setHitboxes(info, sprite->getPosition());
}

void Elodie::setPosition(sf::Vector2f pos) {
    sprite->setPosition(pos);
    cameraPos.x = pos.x;
    cameraPos.y = pos.y;
    setHitboxes(info, sprite->getPosition());
}

void Elodie::setPosition(float x, float y) {
    setPosition(sf::Vector2f(x,y));
    cameraPos.x = x;
    cameraPos.y = y;
    setHitboxes(info, sprite->getPosition());
}

sf::Vector2f Elodie::getCameraPos() {
    return cameraPos;
}

sf::Vector2f* Elodie::getCameraPosPtr() {
    return &cameraPos;
}
