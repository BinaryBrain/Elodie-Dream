#include <SFML/Graphics.hpp>
#include <vector>

#include "Sprite/AnimatedSprite.h"
#include "EventHandler/EventHandler.h"
#include "JsonParser/JsonParser.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Animated Sprite Test 2", sf::Style::Default);
    EventHandler e(window);

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

    sf::Clock frameClock;

    std::vector<int> esc;
    esc.push_back(sf::Keyboard::Escape);
    esc.push_back(sf::Keyboard::LShift);

    std::vector<int> movement;
    movement.push_back(sf::Keyboard::Left);
    movement.push_back(sf::Keyboard::Right);
    movement.push_back(sf::Keyboard::Up);
    movement.push_back(sf::Keyboard::Down);

    while (window.isOpen()) {
        e.listening();

        if (e.keyIsHold(esc))
            window.close();

        if (e.keyIsPressed(sf::Keyboard::F1)) {
            sf::Image screen = window.capture();
            screen.saveToFile("screenshot.jpg");
        }

        if (e.keyIsReleased(movement) && !e.keyIsHold(movement))
            animatedSprite.setAnimation(standingAnimation);
        if (e.keyIsPressed(movement) && !e.keyIsHold(movement))
            animatedSprite.setAnimation(walkingAnimation);

        if (e.keyIsHold(sf::Keyboard::Down))
            animatedSprite.move(0, +0.05);
        if (e.keyIsHold(sf::Keyboard::Up))
            animatedSprite.move(0, -0.05);
        if (e.keyIsHold(sf::Keyboard::Left))
            animatedSprite.move(-0.05, 0);
        if (e.keyIsHold(sf::Keyboard::Right))
            animatedSprite.move(+0.05, 0);

        animatedSprite.update(frameClock.restart());

        if(animatedSprite.getPosition().x > window.getSize().x) {
            animatedSprite.setPosition(-50, animatedSprite.getPosition().y);
        }

        window.clear(sf::Color(0xFF, 0xFF, 0xFF));
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}
