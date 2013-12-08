#include "Elodie.h"

Elodie::Elodie() {
    init();
}

Elodie::Elodie(sf::Vector2f position) {
    init();
    setPosition(position.x - centerX, position.y - centerY);
}

Elodie::Elodie(float x, float y) {
    init();
    setPosition(x - centerX, y - centerY);
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
    infos = json.getEntityInfo();

    state = ElodieState::WALKING;
    speed.x = 300;

    sprite = new ElodieSprite(infos);
    setEntitySprite(sprite);

    soundManager = SoundManager::getInstance();
}

ElodieSprite* Elodie::getSprite() {
    return sprite;
}

Elodie::~Elodie() {
    delete sprite;
    delete infos;
    sprite = NULL;
    infos = NULL;
    setEntitySprite(NULL);
}

sf::Vector2f Elodie::getPosition() {
    return sf::Vector2f(sprite->getPosition().x + centerX, sprite->getPosition().y + centerY);
}

void Elodie::stand() {
    sprite->stand();
}

void Elodie::overworldMove(float seconds) {
    if(!hasToMove()) {
        noMoves();
        stand();
    } else {
        toMove -= seconds*overworldSpeed.x;
        if (goingDown) {
            sprite->move(0, seconds*overworldSpeed.x);
        } else if (goingLeft) {
            sprite->move(-seconds*overworldSpeed.x, 0);
        } else if (goingRight) {
            sprite->move(+seconds*overworldSpeed.x, 0);
        } else if (goingUp) {
            sprite->move(0, -seconds*overworldSpeed.x);
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

void Elodie::takeDamage(int damage) {
    if (!damageCD) {
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

//What's in doStuff right now is only for testing purpose. Lot of stuff to do here.
void Elodie::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate) {
    /*timer += animate.asSeconds();
    if (timer > 3) {
        timer = 0;
        immersionLevel = immersionLevel == 100 ? 100 : immersionLevel + 25;
    }*/
    if (damageCD)
        --damageCD;
    Collide collideTiles = collideWithTiles(tiles, &speed, animate.asSeconds(), getCurrentHitbox(ANIMATIONS[state], sprite->getCurrentFrame()));

    if (speed.x < 0) {
        if (collideTiles.left["distance"])
            speed.x = -collideTiles.left["distance"];
        else
            speed.x = 300;
    } else {
        if (collideTiles.right["distance"])
            speed.x = collideTiles.right["distance"];
        else
            speed.x = -300;
    }

    if (speed.y < 0)
        speed.y = -collideTiles.top["distance"];
    else
        speed.y = collideTiles.bottom["distance"];

    //move HAS to be made juste after the collision. Because you have to move with the speed you have tested.
    //If you put move at the end, you'll have to check the collision 2 times
    move(animate.asSeconds()*speed.x, animate.asSeconds()*speed.y);

    sprite->update(animate);

    if (sprite->getCurrentStance() == ANIMATIONS[ElodieState::STANDING]) {
        this->walk();
    }
    ElodieState memState = state;

    if (collideTiles.left["surface"] && collideTiles.right["surface"]) {
        speed.x = 0;
    } else if ((collideTiles.right["surface"] && speed.x > 0) || (collideTiles.left["surface"] && speed.x < 0)) {
        if (speed.x <= 0)
            speed.x = 300;
        else
            speed.x = -300;
        //immersionLevel = immersionLevel == 0 ? 0 : immersionLevel-25;
    }

    if (collideTiles.bottom["surface"] && speed.y >= 0) {
        speed.y = 0;

        state = ElodieState::WALKING;

        if(state == ElodieState::FALLING) {
            state = ElodieState::WALKING;
            stateChanged(ElodieState::FALLING, ElodieState::WALKING);
        }
        else if(state == ElodieState::JUMPING) {
            state = ElodieState::WALKING;
        }

        unsigned int curFrame = sprite->getCurrentFrame();
        if((curFrame == 1 || curFrame == 3) && sprite->getPreviousFrame() != curFrame) {
            soundManager->play(SoundType::FOOTSTEP_GRASS);
        }
    } else {
        computeGravity(animate);
        if (speed.y > 0) {
            state = ElodieState::FALLING;
        } else {
            state = ElodieState::JUMPING;
        }
    }

    if (event->keyIsPressed(sf::Keyboard::Space) && state == ElodieState::WALKING) {
        speed.y = -400; // TODO Put in const file
        state = ElodieState::JUMPING;
        stateChanged(ElodieState::WALKING, ElodieState::JUMPING);
    }
    if (state != memState) {
        sprite->changeStance(ANIMATIONS[state], sf::seconds(0.1f));
    }
    if(speed.x < 0) {
        flipToLeft();
    } else {
        flipToRight();
    }
}

void Elodie::stateChanged(ElodieState from, ElodieState to) {
    if(from == ElodieState::FALLING && to == ElodieState::WALKING) {
        soundManager->play(SoundType::FOOTSTEP_GRASS);
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
    timer = 0;
    state = ElodieState::WALKING;
    speed.x = 300;

    setEntitySprite(sprite);

    setHitboxes(infos, sprite->getPosition());
}

void Elodie::setPosition(sf::Vector2f pos) {
    sprite->setPosition(pos);
    setHitboxes(infos, sprite->getPosition());
}

void Elodie::setPosition(float x, float y) {
    setPosition(sf::Vector2f(x,y));
    setHitboxes(infos, sprite->getPosition());
}

void Elodie::flipToLeft() {
    sprite->setOrigin(sf::Vector2f(0,0));
    sprite->setScale(1, 1);
}
void Elodie::flipToRight() {
    sprite->setOrigin(sf::Vector2f(64,0));
    sprite->setScale(-1, 1);
}
