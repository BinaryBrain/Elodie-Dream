#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

/**
* The class used to display infos to the player in game. Shows as a black layer with some transparency
* and white text.
*/
class Console: public Displayable {
public:
    Console();
    virtual ~Console();

    void addSentence(std::string sentence);
    void setContent(std::vector<std::string> sentences);
    void clear();

    void display(GameView* view);

private:
    sf::Font* font = new sf::Font();

    sf::RectangleShape background;
    std::vector<std::string> sentences;
};

#endif // CONSOLE_H
