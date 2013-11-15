#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <iostream>
#include "EventHandler.h"

using std::vector;

EventHandler::EventHandler(sf::RenderWindow* window): m_window(window) {
    m_window->setKeyRepeatEnabled(false);
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
    pushAll(m_keyPressed, m_keyHold);
    pushAll(m_mousePressed, m_mouseHold);
    m_keyPressed.clear();
    m_keyReleased.clear();
    m_mousePressed.clear();
    m_mouseReleased.clear();
    m_mouseWheel.code = 0;
    while (m_window->pollEvent(event)) {
        eventInput newInput;
        eventMouse newMouse;

        switch (event.type) {
        case sf::Event::Closed:
            m_window->close();
            break;

        case sf::Event::KeyPressed:
            if (inVector(m_keyPressed, event.key.code) < 0 || inVector(m_keyHold, event.key.code) < 0) {
                newInput.code = event.key.code;
                newInput.time = curTime;
                m_keyPressed.push_back(newInput);
            }
            break;

        case sf::Event::KeyReleased:
            extractByCode(m_keyPressed, event.key.code);
            extractByCode(m_keyHold, event.key.code);
            newInput.code = event.key.code;
            newInput.time = curTime;
            m_keyReleased.push_back(newInput);
            break;

        case sf::Event::MouseWheelMoved:
            m_mouseWheel.code = event.mouseWheel.delta;
            m_mouseWheel.x = event.mouseWheel.x;
            m_mouseWheel.y = event.mouseWheel.y;
            m_mouseWheel.time = curTime;
            break;

        case sf::Event::MouseButtonPressed:
            if (inVector(m_mousePressed, event.key.code) < 0 || inVector(m_mouseHold, event.key.code) < 0) {
                newMouse.code = event.mouseButton.button;
                newMouse.x = event.mouseButton.x;
                newMouse.y = event.mouseButton.y;
                newMouse.time = curTime;
                m_mousePressed.push_back(newMouse);
            }
            break;

        case sf::Event::MouseButtonReleased:
            extractByCode(m_mousePressed, event.mouseButton.button);
            extractByCode(m_mouseHold, event.mouseButton.button);
            newMouse.code = event.mouseButton.button;
            newMouse.x = event.mouseButton.x;
            newMouse.y = event.mouseButton.y;
            newMouse.time = curTime;
            m_mouseReleased.push_back(newMouse);
            break;

        case sf::Event::MouseMoved:
            break;

        default:
            break;
        }
    }
}

vector<int> EventHandler::keyPressed() {
    return codeContent(m_keyPressed);
}

bool EventHandler::keyIsPressed(int code) {
    return checkIn(m_keyPressed, code);
}

bool EventHandler::keyIsPressed(vector<int> codes) {
    return checkIn(m_keyPressed, codes);
}


vector<int> EventHandler::keyHold() {
    return codeContent(m_keyHold);
}

bool EventHandler::keyIsHold(int code) {
    return checkIn(m_keyHold, code);
}

bool EventHandler::keyIsHold(vector<int> codes) {
    return checkIn(m_keyHold, codes);
}


vector<int> EventHandler::keyReleased() {
    return codeContent(m_keyReleased);
}

bool EventHandler::keyIsReleased(int code) {
    return checkIn(m_keyReleased, code);
}

bool EventHandler::keyIsReleased(vector<int> codes) {
    return checkIn(m_keyReleased, codes);
}


bool EventHandler::mouseIsPressed(int code) {
    return checkIn(m_mousePressed, code);
}

eventMouse EventHandler::mouseInfoPressed(int code) {
    return getInfoByCode(m_mousePressed, code);
}


bool EventHandler::mouseIsHold(int code) {
    return checkIn(m_mouseHold, code);
}

eventMouse EventHandler::mouseInfoHold(int code) {
    return getInfoByCode(m_mouseHold, code);
}


bool EventHandler::mouseIsReleased(int code) {
    return checkIn(m_mouseReleased, code);
}

eventMouse EventHandler::mouseInfoReleased(int code) {
    return getInfoByCode(m_mouseReleased, code);
}


int EventHandler::mouseIsWheeled() {
    return m_mouseWheel.code;
}

eventMouse EventHandler::mouseInfoWheeled() {
    eventMouse emptyStruct;
    if (m_mouseWheel.code)
        return m_mouseWheel;
    else
        return emptyStruct;
}
