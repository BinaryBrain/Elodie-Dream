#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "env.h"

#include "Sprite/AnimatedSprite.h"
#include "EventHandler/EventHandler.h"
#include "JsonParser/JsonParser.h"
#include "JsonAccessor/JsonAccessor.h"
#include "Game/Game.h"
#include "Overworld/Overworld.h"

using std::cout;
using std::endl;

int main() {
    // Map Parsing test
    Game* game = Game::getInstance();

    // Conf test
    JsonAccessor language = JsonAccessor();
    language.load("assets/config/languages/FR.lang");

    // Strings test
    cout << language.getString("Intro") << endl;
    cout << language.getString("Dev") << endl;
    cout << language.getString("End") << endl;

    JsonAccessor sheep = JsonAccessor();
    sheep.load("assets/img/sprites/enemies/sheep.json");

    std::vector< std::vector<int>* >* tab = sheep.getInt2DVector("anim.hitbox");
    for (unsigned int i = 0; i < tab->size(); ++i) {
        for (unsigned int j = 0; j < (*tab)[i]->size(); ++j) {
            cout << (*(*tab)[i])[j] << endl;
        }
    }
    cout << sheep.getString("anim.name") << endl;
    cout << sheep.getString("anim.name") << endl;

    game->run();
    game->kill();

    return 0;
}
