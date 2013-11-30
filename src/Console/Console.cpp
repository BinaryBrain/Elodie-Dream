#include "Console.h"

Console::Console(float viewX, float viewY) {
    this->viewX = viewX;
    this->viewY = viewY;

    font->loadFromFile("assets/fonts/pf_tempesta_seven/pf_tempesta_seven.ttf");
}

Console::~Console() {
    //dtor
}

void Console::addParagraph(std::string paragraph) {
    pushAll(makePages(cutShort(paragraph, " ", sizeX-3*marginX), linesPerPage), pages);
    totalPages = pages.size();
    std::cout << "Number of lines: " << lines.size() << ", number of pages: " << pages.size() << std::endl;
}

std::vector<std::string> Console::cutShort(std::string str, std::string sub, int maxWidth) {
    std::vector<size_t> indexes = getStringIndexes(str, sub);
    indexes.insert(indexes.begin(), 0);

    sf::Text* text = new sf::Text("", *font);
    std::vector<std::string> lines;
    std::string buffer(sub); // tricky temporary sub at the beginning :3

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

    // removing sub at the beginning of each line \o/
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
    lines = rearrange(lines);
    int numPages(std::ceil(lines.size()/(double)linesPerPage));
    std::vector<std::vector<std::string> > pages(numPages);

    int counter(0);
    int pageNum(0);

    for(unsigned int i(0); i<lines.size(); ++i) {
        if(counter < linesPerPage) {
            ++counter;
        }
        else {
            counter = 0;
            ++pageNum;
        }
        pages[pageNum].push_back(lines[i]);
    }
    return pages;
}

void Console::previousPage() {
    if(currentPage > 0) {
        --currentPage;
        setCurrentPage(currentPage);
    }
}

void Console::nextPage() {
    if(currentPage < pages.size()-1) {
        ++currentPage;
        setCurrentPage(currentPage);
    }
}

std::vector<std::vector<std::string> > Console::getPages() {
    return pages;
}

void Console::setPages(std::vector<std::vector<std::string> > pages) {
    this->pages = pages;
}

void Console::insertPage(std::vector<std::string> page, int index) {
    pages.insert(pages.begin()+index, page);
    ++totalPages;
}

void Console::deletePage(int index) {
    pages.erase(pages.begin()+index);
    --totalPages;
}

void Console::clear() {
    lines.clear();
    pages.clear();
}

void Console::setCurrentPage(int newPage) {
    currentPage = newPage;
    prepareCurrentPage();
}

void Console::prepareCurrentPage() {
    float startX(viewX-sizeX);
    float startY(viewY-sizeY);

    currentPageText.clear();

    sf::Text newText("", *font);
    newText.setColor(sf::Color::White);

    // console lines
    for(unsigned int i(0); i < pages[currentPage].size(); ++i) {
        newText.setString(pages[currentPage][i]);
        newText.setCharacterSize(15);
        newText.setPosition(startX+marginX, startY+marginY+20*i);
        currentPageText.push_back(newText);
     }

    // progress number
    newText.setString(toString(currentPage+1) + "/" + toString(totalPages));
    newText.setCharacterSize(13);
    newText.setPosition(startX+sizeX-marginX, startY+sizeY-marginY);
    currentPageText.push_back(newText);
}

void Console::display(GameView* view) {

    float viewX(view->getWindow()->getSize().x);
    float viewY(view->getWindow()->getSize().y);

    float startX(viewX-sizeX);
    float startY(viewY-sizeY);

    background.setSize(sf::Vector2f(sizeX, sizeX));
    background.setOutlineColor(sf::Color::Black);
    background.setFillColor(sf::Color(0x00, 0x00, 0x00, 0xB3));
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

std::string Console::toString(int n) {
    std::ostringstream convert;
    convert << n;
    return convert.str();
}

void Console::pushAll(std::vector<std::vector<std::string> > const& tabFrom, std::vector<std::vector<std::string> >& tabTo) {
    for (unsigned int i(0); i < tabFrom.size(); ++i) {
        tabTo.push_back(tabFrom[i]);
    }
}
