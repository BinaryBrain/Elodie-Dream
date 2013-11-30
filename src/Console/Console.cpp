#include "Console.h"

Console::Console(float viewX, float viewY) {
    this->viewX = viewX;
    this->viewY = viewY;

    font->loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");
}

Console::~Console() {
    //dtor
}

void Console::addSentence(std::string sentence) {
    pages = makePages(cutShort(sentence, " ", sizeX-4*marginX), linesPerPage);
}

void Console::setContent(std::vector<std::string> lines) {
    this->lines = lines;
}

std::vector<std::string> Console::cutShort(std::string str, std::string sub, int maxWidth) {
    std::vector<size_t> indexes = getStringIndexes(str, sub);
    indexes.insert(indexes.begin(), 0);

    sf::Text* text = new sf::Text("", *font);
    std::vector<std::string> lines;
    std::string buffer(sub); // tricky temporary space at the beginning :3

    for (unsigned int i(0); i<indexes.size(); ++i) {
        int length(indexes[i+1] - indexes[i]);
        buffer += str.substr(indexes[i], length);
        text->setString(buffer);

        if (text->getLocalBounds().width/1.8 > maxWidth) { // don't know why getLocalBounds() doesn't work properly :/
            lines.push_back(buffer);
            buffer = "";
        }
    }

    lines.push_back(buffer);

    // removing spaces at the beginning of each line \o/
    for (unsigned int i(0); i<lines.size(); ++i) {
        lines[i].erase(0,sub.length());
    }

    delete text;
    text = NULL;

    return lines;
}

std::vector<std::string> Console::rearrange(std::vector<std::string> lines) {
    std::vector<std::string> splited;
    std::vector<std::string> cutShorted;
    std::vector<std::string> toReturn;

    for(unsigned int i(0); i<lines.size(); ++i) {
        splited = split(lines[i], '\n');
        for(unsigned int j(0); j<splited.size(); ++j) {
            cutShorted = cutShort(splited[j], " ", sizeX-marginX);
            for(unsigned int k(0); k<cutShorted.size(); ++k) {
                toReturn.push_back(cutShorted[k]);
            }
        }
    }
    return toReturn;
}

std::vector<std::vector<std::string> > Console::makePages(std::vector<std::string> lines, int linesPerPage) {
    std::vector<std::vector<std::string> > pages;
    std::vector<std::string> line;
    int counter(0);
    int pageNum(0);

    lines = rearrange(lines);

    for (unsigned int i(0); i<lines.size(); ++i) {
        if(counter == 0) {
            pages.push_back(line);
        }

        if(counter < linesPerPage) {
            pages[pageNum].push_back(lines[i]);
            ++counter;
        }
        else {
            counter = 0;
            ++pageNum;
        }
    }

    return pages;
}

void Console::previousPage() {
    if(currentPage > 0) {
        --currentPage;
        setCurrentPage(currentPage);
    }
    std::cout << "Up pressed "<< currentPage << std::endl;
}

void Console::nextPage() {
    if(currentPage < pages.size()-1) {
        ++currentPage;
        setCurrentPage(currentPage);
    }
    std::cout << "Down pressed "<< currentPage << std::endl;
}

void Console::clear() {
    lines.clear();
    pages.clear();
}

void Console::setCurrentPage(int newPage) {
    float startX(viewX-sizeX);
    float startY(viewY-sizeY);

    currentPage = newPage;
    currentPageText.clear();
    for(unsigned int i(0); i < pages[currentPage].size(); ++i) {
        sf::Text newText(pages[currentPage][i], *font);
        newText.setCharacterSize(15);
        newText.setColor(sf::Color::White);
        newText.setPosition(startX+marginX, startY+marginY+20*i);
        currentPageText.push_back(newText);
     }
     std::cout << "Number of pages: "<< pages.size() << std::endl;
}

void Console::display(GameView* view) {

    float viewX(view->getWindow()->getSize().x);
    float viewY(view->getWindow()->getSize().y);

    float startX(viewX-sizeX);
    float startY(viewY-sizeY);

    background.setSize(sf::Vector2f(sizeX, sizeX));
    background.setOutlineColor(sf::Color::Black);
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0x7f));
    background.setOutlineThickness(3);
    background.setPosition(startX, startY);

    view->addDrawable(ViewLayer::CONSOLE, &background);

    for(unsigned int i(0); i < currentPageText.size(); ++i) {
        view->addDrawable(ViewLayer::CONSOLE, &(currentPageText[i]));
    }
}

void Console::setNextState(GameState state){
    nextState = state;
}

GameState Console::getNextState() {
    return nextState;
}

std::vector<size_t> Console::getStringIndexes(std::string str, std::string sub) {
    std::vector<size_t> indexes;
    size_t index = str.find(sub, 0);
    while(index != std::string::npos) { // npos: last element of a size_t
        indexes.push_back(index);
        index = str.find(sub,index+1);
    }
    return indexes;
}

std::vector<std::string> Console::split(std::string str, char delim) {
    std::vector<std::string> strings;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delim)) {
        strings.push_back(item);
    }
    return strings;
}
