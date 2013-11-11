#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <iostream>
#include "EventHandler.h"

using std::vector;

EventHandler::EventHandler(sf::RenderWindow* window): m_window(window)
{
    m_window->setKeyRepeatEnabled(false);
}

EventHandler::~EventHandler()
{
    //TODO: Check if there is something to delete when the game is closed
}

/*
** pushAll is used to push all the content of one tab to another one
** (used to pass all the data of m_*pressed to m_*hold)
*/
static void pushAll(vector<eventInput> const& tabFrom, vector<eventInput>& tabTo)
{
    for (unsigned int i(0); i < tabFrom.size(); ++i)
        tabTo.push_back(tabFrom[i]);
}

static void pushAll(vector<eventMouse> const& tabFrom, vector<eventMouse>& tabTo)
{
    for (unsigned int i(0); i < tabFrom.size(); ++i)
        tabTo.push_back(tabFrom[i]);
}

//inVector return the position of an element if he's in the vector and -1 otherwhise
static int inVector(vector<eventInput> const& tab, int val)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].code == val)
            return i;
    }
    return -1;
}

static int inVector(vector<eventMouse> const& tab, int val)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].code == val)
            return i;
    }
    return -1;
}

/*static void extractByTime(vector<eventInput>& tab, time_t curTime)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].time != curTime)
            tab.erase(tab.begin() + i);
    }
}*/

//extractByCode delete an element from a vector based on the code given in the parameters
static void extractByCode(vector<eventInput>& tab, int code)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].code == code) {
            tab.erase(tab.begin() + i);
            return ;
        }
    }
}

static void extractByCode(vector<eventMouse>& tab, int code)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].code == code) {
            tab.erase(tab.begin() + i);
            return ;
        }
    }
}

//codeContent return all the keycode that are in the given tab
static vector<int> codeContent(vector<eventInput> const& tab)
{
   vector<int> ret;

    for(unsigned int i(0); i < tab.size(); ++i)
        ret.push_back(tab[i].code);

    return ret;
}

/*
** getInfoByCode return the informations about the mousekey (code) given in the parameters
** If the mouseKey is not in the tab, an empty struct is returned (maybe change it to an exception later)
*/
static eventMouse getInfoByCode(vector<eventMouse> const &tab, int code)
{
    eventMouse emptyStruct;

    for(unsigned int i(0); i < tab.size(); ++i) {
        if (tab[i].code == code)
            return tab[i];
    }
    return emptyStruct;
}

//checkIn return true or false if the code(s) is/are in the given tab
static bool checkIn(vector<eventInput> const& tab, int code)
{
    if (inVector(tab, code) < 0)
        return false;
    return true;
}

static bool checkIn(vector<eventInput> const& tab, vector<int> code)
{
    for (int i(0); i < (int)code.size(); ++i)
    {
        if (inVector(tab, code[i]) >= 0)
            return true;
    }
    return false;
}

static bool checkIn(vector<eventMouse> const& tab, int code)
{
    if (inVector(tab, code) < 0)
        return false;
    return true;
}

/*
** EventHandler::listening() has to be called at each turn of the game.
** It calculates which events have occured and stock then in the right tab.
** It's important to call it before trying to use any other function of EventHandler
*/
void EventHandler::listening()
{
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
    while (m_window->pollEvent(event))
    {
        eventInput newInput;
        eventMouse newMouse;

        switch (event.type)
        {
            case sf::Event::Closed:
                m_window->close();
                break;

            case sf::Event::KeyPressed:
                if (inVector(m_keyPressed, event.key.code) < 0 || inVector(m_keyHold, event.key.code) < 0)
                {
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
                if (inVector(m_mousePressed, event.key.code) < 0 || inVector(m_mouseHold, event.key.code) < 0)
                {
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

vector<int> EventHandler::keyPressed()
{
    return codeContent(m_keyPressed);
}

bool EventHandler::keyIsPressed(int code)
{
    return checkIn(m_keyPressed, code);
}

bool EventHandler::keyIsPressed(vector<int> code)
{
    return checkIn(m_keyPressed, code);
}


vector<int> EventHandler::keyHold()
{
    return codeContent(m_keyHold);
}

bool EventHandler::keyIsHold(int code)
{
    return checkIn(m_keyHold, code);
}

bool EventHandler::keyIsHold(vector<int> code)
{
    return checkIn(m_keyHold, code);
}


vector<int> EventHandler::keyReleased()
{
    return codeContent(m_keyReleased);
}

bool EventHandler::keyIsReleased(int code)
{
    return checkIn(m_keyReleased, code);
}

bool EventHandler::keyIsReleased(vector<int> code)
{
    return checkIn(m_keyReleased, code);
}


bool EventHandler::mouseIsPressed(int code)
{
    return checkIn(m_mousePressed, code);
}

eventMouse EventHandler::mouseInfoPressed(int code)
{
    return getInfoByCode(m_mousePressed, code);
}


bool EventHandler::mouseIsHold(int code)
{
    return checkIn(m_mouseHold, code);
}

eventMouse EventHandler::mouseInfoHold(int code)
{
    return getInfoByCode(m_mouseHold, code);
}


bool EventHandler::mouseIsReleased(int code)
{
    return checkIn(m_mouseReleased, code);
}

eventMouse EventHandler::mouseInfoReleased(int code)
{
    return getInfoByCode(m_mouseReleased, code);
}


int EventHandler::mouseIsWheeled()
{
    return m_mouseWheel.code;
}

eventMouse EventHandler::mouseInfoWheeled()
{
    eventMouse emptyStruct;
    if (m_mouseWheel.code)
        return m_mouseWheel;
    else
        return emptyStruct;
}
