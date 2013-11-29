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
    Console(int sizeX, int sizeY);
    virtual ~Console();

    void addSentence(std::string sentence);
    void setContent(std::vector<std::string> sentences);
    std::vector<std::string> makeLines(std::string str, std::string substr);
    std::vector<std::vector<std::string> > makePages(std::vector<std::string> lines, int linesPerPage);
    void setCurrentPage(int newPage, float viewX, float viewY);
    void clear();

    void display(GameView* view);

private:
    sf::Font* font = new sf::Font();

    sf::RectangleShape background;
    std::vector<std::string> lines;
    std::vector<std::vector<std::string> > pages;

    int sizeX;
    int sizeY;

    int linesPerPage = 7;
    int currentPage = 0;
    std::vector<sf::Text> currentPageText;

    std::vector<size_t> getStringIndexes(std::string str, std::string sub);
};

#endif // CONSOLE_H
