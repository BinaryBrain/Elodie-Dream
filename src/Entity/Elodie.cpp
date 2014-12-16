#include "../Score/ScoreManager.h"
#include "../Sound/SoundManager.h"
#include "Elodie.h"

const std::map< int, std::string > Elodie::ANIMATIONS =
{
    {Elodie::State::STANDING, "standing"},
    {Elodie::State::WALKING, "running"},
    {Elodie::State::PUNCHING, "attacking"},
    {Elodie::State::FALLING, "falling"},
    {Elodie::State::JUMPING, "jumping"}
};

Elodie::Elodie() : Entity(Elodie::ANIMATIONS, Elodie::State::STANDING, {(float) moveSpeed, 0})
{
    JsonAccessor accessor = JsonAccessor();
    accessor.loadJsonFrom(ENTITIES_JSON_PATH+"/"+ENTITYNAME_ELODIE+".json");
    info = accessor.getEntityInfo();
    sprite = new ElodieSprite(info);
    spriteCast = dynamic_cast<ElodieSprite*>(sprite);
}

Elodie::Elodie(sf::Vector2f position) : Elodie()
{
    setPosition(position.x, position.y);
}

Elodie::Elodie(float x, float y) : Elodie(sf::Vector2f(x, y))
{
}

Elodie::~Elodie()
{
}

sf::Vector2f Elodie::getPosition()
{
    return sf::Vector2f(spriteCast->getPosition().x, spriteCast->getPosition().y);
}

void Elodie::stand()
{
    spriteCast->stand();
}

void Elodie::overworldMove(float seconds)
{
    if (!hasToMove())
    {
        noMoves();
        stand();
    }
    else
    {
        float rem = toMove - seconds*overworldSpeed.x;
        float delta;
        if (rem > 0)
        {
            toMove -= seconds*overworldSpeed.x;
            delta = seconds*overworldSpeed.x;
        }
        else
        {
            delta = toMove;
            toMove = 0;
        }
        if (goingDown)
        {
            spriteCast->move(0,delta);
        }
        else if (goingLeft)
        {
            spriteCast->move(-delta, 0);
        }
        else if (goingRight)
        {
            spriteCast->move(+delta, 0);
        }
        else if (goingUp)
        {
            spriteCast->move(0, -delta);
        }
        else
        {
            noMoves();
        }
    }
}

void Elodie::setWalkDown()
{
    spriteCast->changeStance(animations.at(Elodie::State::FALLING), sf::seconds(0.1f));
    goingDown = true;
}

void Elodie::setWalkUp()
{
    spriteCast->changeStance(animations.at(Elodie::State::JUMPING), sf::seconds(0.1f));
    goingUp = true;
}

void Elodie::setWalkRight()
{
    this->walk();
    goingRight = true;
    flipToRight();
}

void Elodie::setWalkLeft()
{
    this->walk();
    goingLeft = true;
    flipToLeft();
}

void Elodie::setDistanceToMove(float dist)
{
    toMove = dist;
}

bool Elodie::isMoving()
{
    return (goingDown or goingLeft or goingRight or goingUp);
}

bool Elodie::hasToMove()
{
    return toMove > 0;
}

void Elodie::noMoves()
{
    toMove = 0;
    goingDown = false;
    goingLeft = false;
    goingRight = false;
    goingUp = false;
}

int Elodie::getImmersionLevel()
{
    return immersionLevel;
}

int Elodie::getNightmareLevel()
{
    return nightmareLevel;
}

void Elodie::takeDamage(int damage, bool ignore)
{
    if (!damageCD && (state != Elodie::State::PUNCHING || ignore))
    {
        immersionLevel -= damage;
        ScoreManager& sm = ScoreManager::getInstance();
        sm.takeDamage(damage);
        if (immersionLevel < 0)
        {
            immersionLevel = 0;
        }
        damageCD = DAMAGE_CD;
        SoundManager::getInstance().play(SoundType::OUTCH);
    }
}

void Elodie::walk()
{
    spriteCast->walk();
}

void Elodie::punch(std::map< std::string, Entity* >& entities)
{
    for (std::map< std::string, Entity* >::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        if (it->first != "elodie")
        {
            if (isInFront(returnCurrentHitbox().getArea(),
                          it->second->returnCurrentHitbox().getArea(), direction))
            {
                it->second->takeDamage(1, true);
            }
        }
    }
}

void Elodie::changeAnimation(Collide collideTiles)
{
    unsigned int curFrame = spriteCast->getCurrentFrame();
    Elodie::State memState = static_cast<Elodie::State>(state);

    if (spriteCast->getCurrentStance() == animations.at(Elodie::State::STANDING) ||
            (state == Elodie::State::PUNCHING && curFrame == 3))
    {
        if (collideTiles.bottom["surface"])
        {
            changeState(Elodie::State::WALKING);
            this->walk();
        }
        else
        {
            if(speed.y > 0)
            {
                changeState(Elodie::State::FALLING);
            }
            else
            {
                changeState(Elodie::State::JUMPING);
            }
        }
    }

    if (collideTiles.bottom["surface"])
    {
        if (state != Elodie::State::PUNCHING)
        {
            changeState(Elodie::State::WALKING);
        }
        if (state == Elodie::State::STANDING)
        {
            changeState(Elodie::State::WALKING);
        }
        if (state == Elodie::State::WALKING && curFrame == 1 && spriteCast->getPreviousFrame() != curFrame)
        {
            SoundManager::getInstance().play(SoundType::FOOTSTEP_GROUND);
        }
    }
    else if (state != Elodie::State::PUNCHING)
    {
        if (speed.y > 0)
        {
            changeState(Elodie::State::FALLING);
        }
        else
        {
            changeState(Elodie::State::JUMPING);
        }
    }

    if (state != memState)
    {
        spriteCast->changeStance(animations.at(state), sf::seconds(0.1f));
    }
}

void Elodie::handleEvent(const EventHandler& event, EntityMap& entities, Collide collideTiles)
{
    if (event.keyIsPressed(sf::Keyboard::Space) &&
            (state == Elodie::State::WALKING || state == Elodie::State::STANDING ||
             (state == Elodie::State::PUNCHING && collideTiles.bottom["surface"])))
    {
        changeState(Elodie::State::JUMPING);
        speed.y = jumpSpeed;
        spriteCast->changeStance(animations.at(state), sf::seconds(0.1f));
    }
    else if (event.keyIsPressed(sf::Keyboard::A) && (attackTimer > attackCD))
    {
        attackTimer = 0;
        changeState(Elodie::State::PUNCHING);
    }
    else if (state == Elodie::State::PUNCHING)
    {
        punch(entities);
    }
}

//What's in doStuff right now is only for testing purpose. Lot of stuff to do here.
void Elodie::doStuff(const EventHandler& event, const std::vector< std::vector<TileSprite*> >& tiles,
                     EntityMap& entities, sf::Time animate)
{
    //Compute the gravity
    computeGravity(animate);

    //Check the collisions, set the new distances and do the move
    Collide collideTiles = collideWithTiles(tiles, animate.asSeconds());
    setDistance(collideTiles);
    move(animate.asSeconds()*(speed.x), animate.asSeconds()*speed.y);
    spriteCast->update(animate);

    //Change the sprite in accord with the speed
    changeAnimation(collideTiles);
    handleEvent(event, entities, collideTiles);

    if (0 == speed.x && !collideTiles.right["surface"])
    {
        speed.x = moveSpeed;
    }

    float dist = cameraPos.x - spriteCast->getPosition().x;

    if (dist > 0 && !collideTiles.right["surface"] && !buffed)
    {
        buffed = true;
        speed.x = moveSpeed + dist;
    }

    buffed = !collideTiles.right["surface"];

    if (buffed && dist <= 0)
    {
        buffed = false;
        speed.x = moveSpeed;
    }

    //Other stuff to do
    attackTimer += animate.asSeconds();
    pvTimer += animate.asSeconds();
    if (pvTimer > interRecoveryTime)
    {
        pvTimer = 0;
        immersionLevel = immersionLevel == 100 ? 100 : immersionLevel + 1;
    }
    if (damageCD)
    {
        --damageCD;
    }
    cameraPos.x += (moveSpeed)*animate.asSeconds();
    cameraPos.y = spriteCast->getPosition().y;
}

void Elodie::changeState(Elodie::State to)
{
    Elodie::State from = static_cast<Elodie::State>(state);
    state = to;

    if (from == Elodie::State::WALKING && to == Elodie::State::JUMPING)
    {
        speed.y = jumpSpeed;
        spriteCast->changeStance(animations.at(state), sf::seconds(0.1f));
    }
    else if (from == Elodie::State::FALLING && to == Elodie::State::WALKING)
    {
        SoundManager::getInstance().play(SoundType::FOOTSTEP_GROUND);
    }
    else if (from == Elodie::State::JUMPING && to == Elodie::State::WALKING)
    {
        SoundManager::getInstance().play(SoundType::FOOTSTEP_GROUND);
    }

    if (to == Elodie::State::PUNCHING)
    {
        spriteCast->changeStance(animations.at(state), sf::seconds(0.05f));
        SoundManager::getInstance().play(SoundType::WOOSH);
    }
}

void Elodie::reset()
{
    immersionLevel = 100;
    pvTimer = 0;
    attackTimer = 2;
    state = Elodie::State::WALKING;
    speed.x = moveSpeed;
    speed.y = 0;

    delete sprite;
    sprite = new ElodieSprite(info);
    spriteCast = dynamic_cast<ElodieSprite*>(sprite);

    setHitboxes(info, sprite->getPosition());
}

void Elodie::setPosition(sf::Vector2f pos)
{
    sprite->setPosition(pos);
    cameraPos.x = pos.x;
    cameraPos.y = pos.y;
    setHitboxes(info, sprite->getPosition());
}

void Elodie::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x,y));
    cameraPos.x = x;
    cameraPos.y = y;
    setHitboxes(info, sprite->getPosition());
}

sf::Vector2f Elodie::getCameraPos()
{
    return cameraPos;
}

sf::Vector2f& Elodie::getCameraPosRef()
{
    return cameraPos;
}

void Elodie::setJumpSpeed(int newJumpSpeed)
{
    jumpSpeed = newJumpSpeed < 0 ? newJumpSpeed : jumpSpeed;
}

void Elodie::setMoveSpeed(int newMoveSpeed)
{
    moveSpeed = newMoveSpeed > 0 ? newMoveSpeed : moveSpeed;
}

void Elodie::setInterRecoveryTime(float newInterRecoveryTime)
{
    interRecoveryTime = newInterRecoveryTime > 0 ? newInterRecoveryTime : interRecoveryTime;
}

void Elodie::setAttackCD(float newAttackCD)
{
    attackCD = newAttackCD > 0 ? newAttackCD : attackCD;
}
