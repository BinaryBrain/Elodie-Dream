#include <SFML/Graphics.hpp>
#include <fstream>

#include "env.h"
#include "Sprite/AnimatedSprite.h"
#include "EventHandler/EventHandler.h"
#include "Game/Game.h"
#include "Overworld/Overworld.h"
#include "Utils/Utils.h"
#include "font.h"

//Here for testing purpose. To remove later on
#include "EntityManager/EntityManager.h"

using std::cout;
using std::endl;


int main()
{
    FileHandler::createDirIfNotExisting("save");
    globalFont.loadFromFile(GLOBALFONT_PATH);

    if (false)
    {
        EntityManager& ToyBox = EntityManager::getInstance();
        EntityInfo* sheep = ToyBox.getEnemyInfo(EntityType::ENEMY, EntityName::SHEEP);
        std::cout << std::endl << "sheep" << std::endl;
        std::cout << "height: " << sheep->height << std::endl;
        std::cout << "width: " << sheep->width << std::endl;
        for(std::map< std::string, HitboxInfo >::iterator it = sheep->anim.begin(); it != sheep->anim.end(); ++it)
        {
            std::cout << it->first << std::endl;
            std::cout << it->second.row << std::endl;
            for (size_t i = 0; i < it->second.hitboxes.size(); ++i)
            {
                std::cout << it->second.hitboxes[i].left << " " << it->second.hitboxes[i].top << " " << it->second.hitboxes[i].width << " " << it->second.hitboxes[i].height << std::endl;
            }
        }
        delete sheep;
    }
    Game::getInstance().run();

    return 0;
}
