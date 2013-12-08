#ifndef SHEEP_H_INCLUDED
#define SHEEP_H_INCLUDED

#include "../../const.h"
#include "../Entity.h"
#include "../../Sprite/EnemySprite/SheepSprite.h"
#include "../../Include/Collide.h"
#include "../../Include/EntityInfo.h"
#include "../../EventHandler/EventHandler.h"
#include "../../EntityManager/EntityManager.h"
#include "../Elodie.h"

enum class SheepState { STANDING };

class Sheep : public Entity {
public:
    Sheep();
    Sheep(sf::Vector2f position);
    Sheep(float x, float y);
    virtual ~Sheep();

    void update(sf::Time deltaTime);

    SheepSprite* getSprite();
    Hitbox returnCurrentHitbox();
    void doAttack(std::map< std::string, Entity* >& entities);
    void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate);
    void pause();
    void play();
protected:

private:
    void init(float x, float y);

    SheepSprite* sprite;

    SheepState state;

    std::map< SheepState, std::string > ANIMATIONS;
};

#endif // SHEEP_H_INCLUDED
