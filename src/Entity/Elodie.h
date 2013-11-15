#ifndef ELODIE_H
#define ELODIE_H

#include "Entity.h"
#include "../Sprite/ElodieSprite.h"
#include "../Item/Item.h"

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
    virtual ~Elodie();


    /**
    * \brief Used to get Elodie's position.
    *
    * \return A Vector2f, m_position.
    */
    sf::Vector2f* getPosition();


    /**
    * \brief Makes Elodie stand.
    */
    void stand();

    /**
    * \brief Handles the direction in which Elodie must go.
    */
    void move();

    /**
    * \brief Makes Elodie walk down.
    */
    void walkDown();

    /**
    * \brief Makes Elodie walk up.
    */
    void walkUp();

    /**
    * \brief Makes Elodie walk right.
    */
    void walkRight();

    /**
    * \brief Makes Elodie walk left.
    */
    void walkLeft();

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

    int centerX = 21;
    int centerY = 32;

    float toMove = 0;
    float speed = 0.3;
    bool goingUp = false;
    bool goingDown = false;
    bool goingRight = false;
    bool goingLeft = false;

    int immersionLevel = 100;
    int nightmareLevel = 50; // Max: 100

    std::vector<Item> stuff;
};

#endif // ELODIE_H
