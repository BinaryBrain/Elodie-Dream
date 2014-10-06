#include "EventHandler.h"

using std::vector;

EventHandler::EventHandler(sf::RenderWindow* window) {
    this->window = window;
    this->window->setKeyRepeatEnabled(false);
}

EventHandler::~EventHandler() {
    // TODO: Check if there is something to delete when the game is closed
}

void EventHandler::pushAll(vector<eventInput> const& tabFrom, vector<eventInput>& tabTo) {
    for (unsigned int i(0); i < tabFrom.size(); ++i)
        tabTo.push_back(tabFrom[i]);
}

void EventHandler::pushAll(vector<eventMouse> const& tabFrom, vector<eventMouse>& tabTo) {
    for (unsigned int i(0); i < tabFrom.size(); ++i)
        tabTo.push_back(tabFrom[i]);
}

int EventHandler::inVector(vector<eventInput> const& tab, int code) {
    for (int i(0); i < (int)tab.size(); ++i) {
        if (tab[i].code == code)
            return i;
    }
    return -1;
}

int EventHandler::inVector(vector<eventMouse> const& tab, int code) {
    for (int i(0); i < (int)tab.size(); ++i) {
        if (tab[i].code == code)
            return i;
    }
    return -1;
}

/*void EventHandler::extractByTime(vector<eventInput>& tab, time_t curTime)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].time != curTime)
            tab.erase(tab.begin() + i);
    }
}*/

void EventHandler::extractByCode(vector<eventInput>& tab, int code) {
    for (int i(0); i < (int)tab.size(); ++i) {
        if (tab[i].code == code) {
            tab.erase(tab.begin() + i);
            return ;
        }
    }
}

void EventHandler::extractByCode(vector<eventMouse>& tab, int code) {
    for (int i(0); i < (int)tab.size(); ++i) {
        if (tab[i].code == code) {
            tab.erase(tab.begin() + i);
            return ;
        }
    }
}

vector<int> EventHandler::codeContent(vector<eventInput> const& tab) {
    vector<int> ret;

    for(unsigned int i(0); i < tab.size(); ++i)
        ret.push_back(tab[i].code);

    return ret;
}

eventMouse EventHandler::getInfoByCode(vector<eventMouse> const &tab, int code) {
    eventMouse emptyStruct;

    for(unsigned int i(0); i < tab.size(); ++i) {
        if (tab[i].code == code)
            return tab[i];
    }
    return emptyStruct;
}

bool EventHandler::checkIn(vector<eventInput> const& tab, int code) {
    return (inVector(tab, code) >= 0);
}

bool EventHandler::checkIn(vector<eventInput> const& tab, vector<int> codes) {
    for (int i(0); i < (int)codes.size(); ++i) {
        if (inVector(tab, codes[i]) >= 0)
            return true;
    }
    return false;
}

bool EventHandler::checkIn(vector<eventMouse> const& tab, int code) {
    return (inVector(tab, code) >= 0);
}

void EventHandler::listening() {
    sf::Event event;
    time_t curTime;

    time(&curTime);
    pushAll(keyPressedVector, keyHoldVector);
    pushAll(mousePressedVector, mouseHoldVector);
    keyPressedVector.clear();
    keyReleasedVector.clear();
    mousePressedVector.clear();
    mouseReleasedVector.clear();
    mouseWheel.code = 0;
    prevFocus = focus;
    while (window->pollEvent(event)) {
        eventInput newInput;
        eventMouse newMouse;

        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::LostFocus:
            focus = false;
            break;

        case sf::Event::GainedFocus:
            focus = true;
            break;

        case sf::Event::KeyPressed:
            if (inVector(keyPressedVector, event.key.code) < 0 || inVector(keyHoldVector, event.key.code) < 0) {
                newInput.code = event.key.code;
                newInput.time = curTime;
                keyPressedVector.push_back(newInput);
            }
            break;

        case sf::Event::KeyReleased:
            extractByCode(keyPressedVector, event.key.code);
            extractByCode(keyHoldVector, event.key.code);
            newInput.code = event.key.code;
            newInput.time = curTime;
            keyReleasedVector.push_back(newInput);
            break;

        case sf::Event::MouseWheelMoved:
            mouseWheel.code = event.mouseWheel.delta;
            mouseWheel.x = event.mouseWheel.x;
            mouseWheel.y = event.mouseWheel.y;
            mouseWheel.time = curTime;
            break;

        case sf::Event::MouseButtonPressed:
            if (inVector(mousePressedVector, event.key.code) < 0 || inVector(mouseHoldVector, event.key.code) < 0) {
                newMouse.code = event.mouseButton.button;
                newMouse.x = event.mouseButton.x;
                newMouse.y = event.mouseButton.y;
                newMouse.time = curTime;
                mousePressedVector.push_back(newMouse);
            }
            break;

        case sf::Event::MouseButtonReleased:
            extractByCode(mousePressedVector, event.mouseButton.button);
            extractByCode(mouseHoldVector, event.mouseButton.button);
            newMouse.code = event.mouseButton.button;
            newMouse.x = event.mouseButton.x;
            newMouse.y = event.mouseButton.y;
            newMouse.time = curTime;
            mouseReleasedVector.push_back(newMouse);
            break;

        case sf::Event::MouseMoved:
            break;

        default:
            break;
        }
    }
}

vector<int> EventHandler::keyPressed() {
    return codeContent(keyPressedVector);
}

bool EventHandler::keyIsPressed(int code) {
    return checkIn(keyPressedVector, code);
}

bool EventHandler::keyIsPressed(vector<int> codes) {
    return checkIn(keyPressedVector, codes);
}


vector<int> EventHandler::keyHold() {
    return codeContent(keyHoldVector);
}

bool EventHandler::keyIsHold(int code) {
    return checkIn(keyHoldVector, code);
}

bool EventHandler::keyIsHold(vector<int> codes) {
    return checkIn(keyHoldVector, codes);
}


vector<int> EventHandler::keyReleased() {
    return codeContent(keyReleasedVector);
}

bool EventHandler::keyIsReleased(int code) {
    return checkIn(keyReleasedVector, code);
}

bool EventHandler::keyIsReleased(vector<int> codes) {
    return checkIn(keyReleasedVector, codes);
}


bool EventHandler::mouseIsPressed(int code) {
    return checkIn(mousePressedVector, code);
}

eventMouse EventHandler::mouseInfoPressed(int code) {
    return getInfoByCode(mousePressedVector, code);
}


bool EventHandler::mouseIsHold(int code) {
    return checkIn(mouseHoldVector, code);
}

eventMouse EventHandler::mouseInfoHold(int code) {
    return getInfoByCode(mouseHoldVector, code);
}


bool EventHandler::mouseIsReleased(int code) {
    return checkIn(mouseReleasedVector, code);
}

eventMouse EventHandler::mouseInfoReleased(int code) {
    return getInfoByCode(mouseReleasedVector, code);
}


int EventHandler::mouseIsWheeled() {
    return mouseWheel.code;
}

eventMouse EventHandler::mouseInfoWheeled() {
    eventMouse emptyStruct;
    if (mouseWheel.code)
        return mouseWheel;
    else
        return emptyStruct;
}

bool EventHandler::hasFocus() {
    return focus;
}

bool EventHandler::gainedFocus() {
    return (prevFocus != focus && focus == true);
}

bool EventHandler::lostFocus() {
    return (prevFocus != focus && focus == false);
}
