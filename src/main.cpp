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


    game->run();
    game->kill();

    return 0;
}
