#include "Console.h"

Console::Console(int sizeX, int sizeY) {
    font->loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");
    this->sizeX = sizeX;
    this->sizeY = sizeY;
}

Console::~Console() {
    //dtor
}

void Console::addSentence(std::string sentence) {
    pages = makePages(makeLines(sentence, " "), linesPerPage);
}

void Console::setContent(std::vector<std::string> lines) {
    this->lines = lines;
}

std::vector<std::string> Console::makeLines(std::string str, std::string substr) {
    std::vector<size_t> indexes = getStringIndexes(str, substr);
    indexes.insert(indexes.begin(), 0);

    sf::Text* text = new sf::Text("", *font);
    std::vector<std::string> lines;
    std::string buffer(substr); // tricky temporary space at the beginning :3

    for (unsigned int i(0); i<indexes.size(); ++i) {
        int length(indexes[i+1] - indexes[i]);
        buffer += str.substr(indexes[i], length);
        text->setString(buffer);

        if (text->getLocalBounds().width/1.8 > sizeX) { // don't know why getLocalBounds() doesn't work properly :/
            lines.push_back(buffer);
            buffer = "";
        }
    }

    lines.push_back(buffer);

    // removing spaces at the beginning of each line \o/
    for (unsigned int i(0); i<lines.size(); ++i) {
        lines[i].erase(0,substr.length());
    }

    delete text;
    return lines;
}

std::vector<std::vector<std::string> > Console::makePages(std::vector<std::string> lines, int linesPerPage) {
    std::vector<std::vector<std::string> > pages;
    std::vector<std::string> init;
    int counter(0);
    int pageNum(0);

    for (unsigned int i(0); i<lines.size(); ++i) {
        if(counter == 0) {
            pages.push_back(init);
        }

        if(counter <= linesPerPage) {
            pages[pageNum].push_back(lines[i]);
            ++counter;
        }
        else {
            counter = 0;
            ++pageNum;
        }
    }
    std::cout<<pages.size()<<std::endl;
    return pages;
}

void Console::clear() {
    lines.clear();
}

void Console::setCurrentPage(int newPage, float viewX, float viewY) {
    float startX(viewX-sizeX);
    float startY(viewY-sizeY);

    currentPage = newPage;
    currentPageText.clear();
    for(unsigned int i(0); i < pages[currentPage].size(); ++i) {
        sf::Text newText(pages[currentPage][i], *font);
        newText.setCharacterSize(15);
        newText.setColor(sf::Color::White);
        newText.setPosition(startX+50, startY+20+20*i);
        currentPageText.push_back(newText);
     }
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

std::vector<size_t> Console::getStringIndexes(std::string str, std::string sub) {
    std::vector<size_t> indexes;
    size_t index = str.find(sub, 0);
    while(index != std::string::npos) { // npos: last element of a size_t
        indexes.push_back(index);
        index = str.find(sub,index+1);
    }
    return indexes;
}
