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

    // Cuts a string in multiple strings if the string's text is longer than maxWidth
    std::vector<std::string> cutShort(std::string str, std::string sub, int maxWidth);
    std::vector<std::string> rearrange(std::vector<std::string> lines);
    std::vector<std::vector<std::string> > makePages(std::vector<std::string> lines, int linesPerPage);
    void setCurrentPage(int newPage, float viewX, float viewY);
    void previousPage();
    void nextPage();
    void clear();

    void display(GameView* view);

private:
    sf::Font* font = new sf::Font();

    sf::RectangleShape background;
    std::vector<std::string> lines;
    std::vector<std::vector<std::string> > pages;

    //default values
    int sizeX = 1280;
    int sizeY = 200;
    int linesPerPage = 7;

    int marginX = 50;
    int marginY = 20;
    unsigned int currentPage = 0;

    std::vector<sf::Text> currentPageText;

    std::vector<size_t> getStringIndexes(std::string str, std::string sub);
    std::vector<std::string> split(std::string str, char delim);
};

#endif // CONSOLE_H
