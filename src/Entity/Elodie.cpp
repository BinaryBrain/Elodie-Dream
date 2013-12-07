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
        {ElodieState::FALLING, "falling"}
    };

    JsonAccessor json = JsonAccessor();
    json.load(ENTITIES_JSON_PATH+"/"+ENTITYNAME_ELODIE+".json");
    infos = json.getEntityInfo();

    state = ElodieState::WALKING;
    speed.x = 300;

    sprite = new ElodieSprite(infos);
    setEntitySprite(sprite);
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
    this->walk();
    goingDown = true;
}
void Elodie::setWalkUp() {
    this->walk();
    goingUp = true;
}
void Elodie::setWalkRight() {
    this->walk();
    goingRight = true;
}
void Elodie::setWalkLeft() {
    this->walk();
    goingLeft = true;
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



void Elodie::walk() {
    sprite->walk();
}

//What's in doStuff right now is only for testing purpose. Lot of stuff to do here.
void Elodie::doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, sf::Time animate) {
    timer += animate.asSeconds();
    if (timer > 3) {
        timer = 0;
        immersionLevel = immersionLevel == 100 ? 100 : immersionLevel + 25;
    }
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

    if (sprite->getCurrentStance() == ANIMATIONS[ElodieState::STANDING])
        this->walk();

    if (collideTiles.left["surface"] && collideTiles.right["surface"]) {
        speed.x = 0;
    } else if ((collideTiles.right["surface"] && speed.x > 0) || (collideTiles.left["surface"] && speed.x < 0)) {
        if (speed.x <= 0)
            speed.x = 300;
        else
            speed.x = -300;
        immersionLevel = immersionLevel == 0 ? 0 : immersionLevel-25;
    }

    if (collideTiles.bottom["surface"] && speed.y >= 0) {
        speed.y = 0;

        if(state == ElodieState::FALLING) {
            state = ElodieState::WALKING;
        }
    } else {
        computeGravity(animate);
        state = ElodieState::FALLING;
    }

    if (event->keyIsPressed(sf::Keyboard::Space) && state == ElodieState::WALKING) {
        speed.y = -400; // TODO Put in const file
        state = ElodieState::FALLING;
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

void Elodie::setPosition(sf::Vector2f pos){
    sprite->setPosition(pos);
    setHitboxes(infos, sprite->getPosition());
}

void Elodie::setPosition(float x, float y){
    setPosition(sf::Vector2f(x,y));
    setHitboxes(infos, sprite->getPosition());
}
