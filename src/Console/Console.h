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
    Console(float viewX, float viewY);
    virtual ~Console();

    void addParagraph(std::string paragraph);

    // Cuts a string in multiple strings if the string's text is longer than maxWidth
    std::vector<std::string> cutShort(std::string str, std::string sub, int maxWidth);
    std::vector<std::string> rearrange(std::vector<std::string> lines);
    std::vector<std::vector<std::string> > makePages(std::vector<std::string> lines, int linesPerPage);

    void setCurrentPage(int newPage);
    void prepareCurrentPage();

    void previousPage();
    void nextPage();

    std::vector<std::vector<std::string> > getPages();
    void setPages(std::vector<std::vector<std::string> > pages);
    void insertPage(std::vector<std::string> page, int index);
    void deletePage(int n);
    void clear();

    void display(GameView* view);

    void setNextState(GameState state);
    GameState getNextState();

private:
    sf::Font* font = new sf::Font();

    sf::RectangleShape background;
    std::vector<std::string> lines;
    std::vector<std::vector<std::string> > pages;

    float viewX;
    float viewY;

    //default values
    float sizeX = 1280;
    float sizeY = 200;
    int linesPerPage = 3;

    float marginX = 50;
    float marginY = 20;
    unsigned int currentPage = 0;
    int totalPages = 0;

    std::vector<sf::Text> currentPageText;
    GameState nextState = GameState::INOVERWORLD;

    std::vector<size_t> getStringIndexes(std::string str, std::string sub);
    std::vector<std::string> split(std::string str, char delim);
    std::string toString(int n);
    void pushAll(std::vector<std::vector<std::string> > const& tabFrom, std::vector<std::vector<std::string> >& tabTo);
};

#endif // CONSOLE_H
