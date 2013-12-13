#ifndef PORO_H_INCLUDED
#define PORO_H_INCLUDED

#include "../const.h"
#include "Entity.h"
#include "../Sprite/EntitySprite.h"
#include "../Include/Collide.h"
#include "../Include/EntityInfo.h"
#include "../EventHandler/EventHandler.h"
#include "../EntityManager/EntityManager.h"
#include "Elodie.h"
#include "../Sound/SoundManager.h"

class SoundManager;

enum class PoroState { RUNNING };

class Poro : public Entity {
public:
    Poro();
    Poro(sf::Vector2f position);
    Poro(float x, float y);
    virtual ~Poro();

    void update(sf::Time deltaTime);

    EntitySprite* getSprite();
    Hitbox returnCurrentHitbox();
    void checkArea(std::map< std::string, Entity* >& entities);
    void takeDamage(int damage, bool ignore);
    void doStuff(EventHandler* const& event, std::vector< std::vector<TileSprite*> > const& tiles, std::map< std::string, Entity* >& entities, sf::Time animate);
    void pause();
    void play();
protected:

private:
    void init(float x, float y);
    int damage = 0;
    SoundManager* soundManager;

    EntitySprite* sprite;

   PoroState state;

    std::map< PoroState, std::string > ANIMATIONS;
};

#endif // PORO_H_INCLUDED
