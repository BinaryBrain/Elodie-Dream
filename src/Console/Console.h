#ifndef CONSOLE_H
#define CONSOLE_H

#include <SFML/Graphics.hpp>

#include "../env.h"
#include "../const.h"
#include "../font.h"
#include "../Game/GameView.h"
#include "../Displayable/Displayable.h"

/**
* The class used to display infos to the player in game. Shows as a black layer with some transparency
* and white text.
*/
class Console: public Displayable
{
public:
    static const int NLINES;

    Console(GameView& view);
    virtual ~Console();

    void clearAndWrite(std::string m);
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

    void display();

    void setNextState(GameState state);
    GameState getNextState();

private:

    sf::RectangleShape background;
    std::vector<std::string> lines;
    std::vector<std::vector<std::string> > pages;

    float startX;
    float startY;

    float sizeX = 1280;
    float sizeY = 200;

    float marginX = 50;
    float marginY = 20;
    unsigned int currentPage = 0;
    unsigned int totalPages = 0;

    std::vector<sf::Text> currentPageText;
    sf::ConvexShape up;
    sf::ConvexShape down;

    GameState nextState = GameState::INOVERWORLD;

    std::vector<size_t> getStringIndexes(std::string str, std::string sub);
    std::vector<std::string> split(std::string str, char delim);
    std::string toString(int n);
    void pushAll(std::vector<std::vector<std::string> > const& tabFrom, std::vector<std::vector<std::string> >& tabTo);
};

#endif // CONSOLE_H
