#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <iostream>
#include "EventHandler.h"

using std::vector;

/**
* \brief The constructor of EventHandler.
*
* \param[in] window The RenderWindow of SFML on which we do different things.
*/
EventHandler::EventHandler(sf::RenderWindow* window): m_window(window)
{
    m_window->setKeyRepeatEnabled(false);
}

/**
* \brief The destructor of EventHandler.
*/
EventHandler::~EventHandler()
{
    // TODO: Check if there is something to delete when the game is closed
}

/**
* \brief Used to push all the content of one tab to another one.
*
* \param[in] tabFrom A vector of eventInput, the data to pass.
* \param[out] tabTo A vector of eventInput in which the data will be put.
*/
static void pushAll(vector<eventInput> const& tabFrom, vector<eventInput>& tabTo)
{
    for (unsigned int i(0); i < tabFrom.size(); ++i)
        tabTo.push_back(tabFrom[i]);
}

/**
* \brief Used to push all the contents of one tab to another one.
*
* \param[in] tabFrom A vector of eventMouse, the data to pass.
* \param[out] tabTo A vector of eventMouse, in which the data will be put.
*/
static void pushAll(vector<eventMouse> const& tabFrom, vector<eventMouse>& tabTo)
{
    for (unsigned int i(0); i < tabFrom.size(); ++i)
        tabTo.push_back(tabFrom[i]);
}

/**
* \brief Returns the position of an element if he's in the vector and -1 otherwise.
*
* \param[in] tab A vector of eventInput in which we will search.
* \param[in] code The code to find in tab.
* \return An int, the position of the code in the tab (or -1 if not found).
*/
static int inVector(vector<eventInput> const& tab, int code)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].code == code)
            return i;
    }
    return -1;
}

/**
* \brief Returns the position of an element if he's in the vector and -1 otherwise.
*
* \param[in] tab A vector of eventMouse in which we will search.
* \param[in] code The code to find in tab.
* \return An int, the position of the code in the tab (or -1 if not found).
*/
static int inVector(vector<eventMouse> const& tab, int code)
{
    for (int i(0); i < (int)tab.size(); ++i)
    {
        if (tab[i].code == code)
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

/**
* \brief Deletes an element from a vector based on the code given in the parameters.
*
* \param[in, out] tab A vector of eventInput, from which elements will be deleted.
* \param[in] code The code used to known which elements to remove.
*/
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

/**
* \brief Deletes an element from a vector based on the code given in the parameters.
*
* \param[in, out] tab A vector of eventMouse, from which elements will be deleted.
* \param[in] code The code used to known which elements to remove.
*/
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

/**
* \brief Returns all the code that are in the given tab.
*
* \param[in] tab A vector of eventInput, from which elements will be taken.
* \return A vector of int containing the code for each element in tab.
*/
static vector<int> codeContent(vector<eventInput> const& tab)
{
   vector<int> ret;

    for(unsigned int i(0); i < tab.size(); ++i)
        ret.push_back(tab[i].code);

    return ret;
}

/**
* \brief Returns the eventMouse corresponding to the code.
*
* \param[in] tab The vector of eventMouse in which we will search.
* \param[in] code The code used to know which eventMouse to return.
* \return The eventMouse corresponding to the code.
*
* If there is an eventMouse corresponding to the code in tab, it is returned.
* Else if the eventMouse is not in tab, an empty struct is returned (maybe change it to an exception later).
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

/**
* \brief Checks if the code is in the given tab.
*
* \param[in] tab A vector of evenInput in which we will search.
* \param[in] code The code (int) we want to search.
* \return A boolean describing if the code was found.
*/
static bool checkIn(vector<eventInput> const& tab, int code)
{
   return (inVector(tab, code) >= 0);
}

/**
* \brief Checks for each code in codes if it is in tab, and returns true in this case.
*
* \param[in] tab A vector of evenInput in which we will search.
* \param[in] codes The vector of int which contains elements we want to search.
* \return A boolean describing if the code was found.
*/
static bool checkIn(vector<eventInput> const& tab, vector<int> codes)
{
    for (int i(0); i < (int)codes.size(); ++i)
    {
        if (inVector(tab, codes[i]) >= 0)
            return true;
    }
    return false;
}

/**
* \brief Checks if the code is in the given tab.
*
* \param[in] tab A vector of eventMouse in which we will search.
* \param[in] code The code we want to search.
* \return A boolean describing if the code was found.
*/
static bool checkIn(vector<eventMouse> const& tab, int code)
{
    return (inVector(tab, code) >= 0);
}

/**
* \brief Calculates which events have occured and stocks then in the right vector.
*
* Has to be called at each turn of the game.
* It calculates which events have occured and stock then in the right vector.
* It's important to call it before trying to use any other function of EventHandler.
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

/**
* \brief Returns the codes obtained from m_keyPressed.
*
* \return A vector of int which contains the codes of m_keyPressed.
*/
vector<int> EventHandler::keyPressed()
{
    return codeContent(m_keyPressed);
}

/**
* \brief Checks if the code is in m_keyIsPressed.
* \param[in] code The code we want to search.
*
* \return A boolean which describes if code was found.
*/
bool EventHandler::keyIsPressed(int code)
{
    return checkIn(m_keyPressed, code);
}

/**
* \brief Checks if a code in codes is in m_keyPressed.
* \param[in] codes The code we want to search.
*
* \return A boolean which describes if a code was found.
*/
bool EventHandler::keyIsPressed(vector<int> codes)
{
    return checkIn(m_keyPressed, codes);
}


/**
* \brief Returns the codes obtained from m_keyHold.
*
* \return A vector of int which contains the codes of m_keyHold.
*/
vector<int> EventHandler::keyHold()
{
    return codeContent(m_keyHold);
}

/**
* \brief Checks if the code is in m_keyHold.
* \param[in] code The code we want to search.
*
* \return A boolean which describes if code was found.
*/
bool EventHandler::keyIsHold(int code)
{
    return checkIn(m_keyHold, code);
}

/**
* \brief Checks if a code in codes is in m_keyHold.
* \param[in] codes The code we want to search.
*
* \return A boolean which describes if a code was found.
*/
bool EventHandler::keyIsHold(vector<int> codes)
{
    return checkIn(m_keyHold, codes);
}


/**
* \brief Returns the codes obtained from m_keyReleased.
*
* \return A vector of int which contains the codes of m_keyReleased.
*/
vector<int> EventHandler::keyReleased()
{
    return codeContent(m_keyReleased);
}

/**
* \brief Checks if the code is in m_keyReleased.
* \param[in] code The code we want to search.
*
* \return A boolean which describes if code was found.
*/
bool EventHandler::keyIsReleased(int code)
{
    return checkIn(m_keyReleased, code);
}

/**
* \brief Checks if a code in codes is in m_keyReleased.
* \param[in] codes The code we want to search.
*
* \return A boolean which describes if a code was found.
*/
bool EventHandler::keyIsReleased(vector<int> codes)
{
    return checkIn(m_keyReleased, codes);
}


/**
* \brief Checks if the code is in m_mousePressed.
* \param[in] code The code we want to search.
*
* \return A boolean which describes if code was found.
*/
bool EventHandler::mouseIsPressed(int code)
{
    return checkIn(m_mousePressed, code);
}

/**
* \brief Gets the eventMouse for code in m_mousePressed.
* \param[in] code The code we want to use to find the eventMouse.
*
* \return An eventMouse corresponding to the code.
*/
eventMouse EventHandler::mouseInfoPressed(int code)
{
    return getInfoByCode(m_mousePressed, code);
}


/**
* \brief Checks if the code is in m_mouseHold.
* \param[in] code The code we want to search.
*
* \return A boolean which describes if code was found.
*/
bool EventHandler::mouseIsHold(int code)
{
    return checkIn(m_mouseHold, code);
}

/**
* \brief Gets the eventMouse for code in m_mouseHold.
* \param[in] code The code we want to use to find the eventMouse.
*
* \return An eventMouse corresponding to the code.
*/
eventMouse EventHandler::mouseInfoHold(int code)
{
    return getInfoByCode(m_mouseHold, code);
}


/**
* \brief Checks if the code is in mouseIsReleased.
* \param[in] code The code we want to search.
*
* \return A boolean which describes if code was found.
*/
bool EventHandler::mouseIsReleased(int code)
{
    return checkIn(m_mouseReleased, code);
}

/**
* \brief Gets the eventMouse for code in m_mouseReleased.
* \param[in] code The code we want to use to find the eventMouse.
*
* \return An eventMouse corresponding to the code.
*/
eventMouse EventHandler::mouseInfoReleased(int code)
{
    return getInfoByCode(m_mouseReleased, code);
}

/**
* \brief Returns the code obtained from m_mouseWheel.
*
* \return An int, the code of m_mouseWheel.
*/
int EventHandler::mouseIsWheeled()
{
    return m_mouseWheel.code;
}

/**
* \brief Returns the eventMouse obtained from m_mouseWheel.
*
* \return An eventMouse corresponding to the code of m_mouseWheel.
*/
eventMouse EventHandler::mouseInfoWheeled()
{
    eventMouse emptyStruct;
    if (m_mouseWheel.code)
        return m_mouseWheel;
    else
        return emptyStruct;
}
