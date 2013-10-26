#include <SFML/Graphics.hpp>
#include "src/Sprite/AnimatedSprite.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Animated Sprite Test", sf::Style::Default);

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

    // set up AnimatesSprite
    AnimatedSprite animatedSprite(sf::seconds(0.1));
    animatedSprite.setAnimation(walkingAnimation);

    animatedSprite.setPosition(100, 300);

    sf::Clock frameClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }

            // Screenshot
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
                sf::Image screen = window.capture();
                screen.saveToFile("screenshot.jpg");
            }
        }

        animatedSprite.update(frameClock.restart());
        animatedSprite.move(0.05, 0);

        if(animatedSprite.getPosition().x > window.getSize().x) {
            animatedSprite.setPosition(-50, animatedSprite.getPosition().y);
        }

        window.clear(sf::Color(0xFF, 0xFF, 0xFF));
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}
