#ifndef ELODIE_H
#define ELODIE_H

#include "../const.h"
#include "Entity.h"
#include "../Sprite/ElodieSprite.h"
#include "../Item/Item.h"
#include "../Include/Collide.h"
#include "../EventHandler/EventHandler.h"
#include "../Include/EntityInfo.h"
#include "../Sound/SoundManager.h"

class SoundManager;

enum class ElodieState {
    STANDING, WALKING, FALLING, PUNCHING, JUMPING
};

/**
* The class representing Elodie, an Entity.
*/
class Elodie : public Entity {
public:

    /**
    * \brief The default constructor of Elodie. Calls init().
    */
    Elodie();

    /**
    * \brief The constructor of Elodie with the position specified.
    *
    * \param[in] position A Vector2f, the position of Elodie.
    *
    * The constructor of Elodie with the position specified with a Vector2f. Calls init() and set the position.
    */
    Elodie(sf::Vector2f position);

    /**
    * \brief The constructor of Elodie with the position specified.
    *
    * \param[in] x An int, the position x of Elodie.
    * \param[in] y An int, the position y of Elodie.
    *
    * The constructor of Elodie with the position specified with 2 int. Calls init() and set the position.
    */
    Elodie(float x, float y);

    /**
    * \brief Used to get Elodie's sprite.
    *
    * \return An ElodieSprite, m_sprite.
    */
    ElodieSprite* getSprite();

    /**
    * \brief The destructor of Elodie.
    */
    Hitbox returnCurrentHitbox();
    void punch(std::map< std::string, Entity* >& entities);
    void changeAnimation(Collide collideTiles);
    void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, EntityMap& entities, sf::Time animate);
    virtual ~Elodie();

    /**
    * \brief Used to get Elodie's position.
    *
    * \return A Vector2f, m_position.
    */
    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f pos);

    void setPosition(float x, float y);

    /**
    * \brief Makes Elodie stand.
    */
    void stand();

    /**
    * \brief Handles the direction in which Elodie must go.
    */
    void overworldMove(float seconds);

    /**
    * \brief Makes Elodie walk down.
    */
    void setWalkDown();

    /**
    * \brief Makes Elodie walk up.
    */
    void setWalkUp();

    /**
    * \brief Makes Elodie walk right.
    */
    void setWalkRight();

    /**
    * \brief Makes Elodie walk left.
    */
    void setWalkLeft();

    /**
    * \brief Sets the distance Elodie must move.
    *
    * \param[in] dist A float, the distance Elodie must move.
    */
    void setDistanceToMove(float dist);

    /**
    * \brief Tells if Elodie is moving.
    */
    bool isMoving();
    /**
    * \brief Tells if Elodie has to move.
    */
    bool hasToMove();

    /**
    * \brief Makes Elodie stop.
    */
    void noMoves();

    /**
    * \brief Updates Elodie's sprite from deltaTime.
    *
    * \param[in] deltaTime The time the sprite must be updated.
    */
    void update(sf::Time deltaTime);


    /**
    * \brief Gets the immersion level of Elodie.
    *
    * \return An int, the value of the immersion level.
    */
    int getImmersionLevel();

    /**
    * \brief Gets the nightmare level of Elodie.
    *
    * \return An int, the value of the nightmare level.
    */
    int getNightmareLevel();
    void takeDamage(int damage, bool ignore);
    void changeState(ElodieState to);
    void reset();
    void pause();
    void play();
    void setSpeed(sf::Vector2f speed);
    sf::Vector2f getCameraPos();
    sf::Vector2f* getCameraPosPtr();
    void handleEvent(EventHandler* const& event, EntityMap& entities, Collide collideTiles);

protected:

private:
    /**
    * Sets Elodie's sprite to be a new ElodieSprite.
    */
    void init();
    /**
    * Makes Elodie's sprite walk.
    */
    void walk();

    ElodieSprite* sprite;

    ElodieState state;

    float toMove = 0;
    bool goingUp = false;
    bool goingDown = false;
    bool goingRight = false;
    bool goingLeft = false;

    sf::Vector2f overworldSpeed = { 300, 300 }; // TODO Put in a const.h file

    int immersionLevel = 100;
    int nightmareLevel = 50; // Max: 100

    float timer = 0;

    std::vector<Item> stuff;
    std::map< ElodieState, std::string > ANIMATIONS;

    SoundManager* soundManager;
    sf::Vector2f cameraPos;
    bool buffed = false;
    float buff = 0;
};

#endif // ELODIE_H
