#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

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

enum class BonusState { STANDING };

class Bonus : public Entity {
public:
    Bonus();
    Bonus(sf::Vector2f position);
    Bonus(float x, float y);
    virtual ~Bonus();

    void update(sf::Time deltaTime);

    EntitySprite* getSprite();
    Hitbox returnCurrentHitbox();
    void getTaken(std::map< std::string, Entity* >& entities);
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

    BonusState state;

    std::map< BonusState, std::string > ANIMATIONS;
};

#endif // BONUS_H_INCLUDED
