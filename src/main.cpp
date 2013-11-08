#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

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
    Game game;

    // Conf test
    JsonAccessor language = JsonAccessor();
    language.load("assets/config/languages/FR.lang");

    // Strings test
    cout << language.getString("Intro") << endl;
    cout << language.getString("Dev") << endl;
    cout << language.getString("End") << endl;

/*
    sf::Texture texture;
    if(!texture.loadFromFile("assets/img/sprite.jpg")) {
        return EXIT_FAILURE;
    }

    // push frames
    Animation walkingAnimation;
    walkingAnimation.setSpriteSheet(texture);

    walkingAnimation.addFrame(sf::IntRect(85, 0, 48, 64));
    walkingAnimation.addFrame(sf::IntRect(85+50, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+100, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+157, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+202, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+246, 0, 46, 64));
    walkingAnimation.addFrame(sf::IntRect(85+290, 0, 46, 64));

    Animation standingAnimation;
    standingAnimation.setSpriteSheet(texture);
    standingAnimation.addFrame(sf::IntRect(0, 0, 43, 64));

    // set up AnimatesSprite
    AnimatedSprite animatedSprite(sf::seconds(0.1));
    animatedSprite.setAnimation(standingAnimation);

    animatedSprite.setPosition(100, 300);
*/

    game.run();

    return 0;
}
