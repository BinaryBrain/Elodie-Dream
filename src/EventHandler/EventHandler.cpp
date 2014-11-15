#include "EventHandler.h"

EventHandler::EventHandler(sf::RenderWindow& window) : _window(window)
{
    _window.setKeyRepeatEnabled(false);
}

EventHandler::~EventHandler()
{
}

void EventHandler::pushAll(const std::vector<eventInput>& tabFrom, std::vector<eventInput>& tabTo)
{
    for (unsigned int i = 0; i < tabFrom.size(); ++i)
    {
        tabTo.push_back(tabFrom[i]);
    }
}

void EventHandler::pushAll(const std::vector<eventMouse>& tabFrom, std::vector<eventMouse>& tabTo)
{
    for (unsigned int i = 0; i < tabFrom.size(); ++i)
    {
        tabTo.push_back(tabFrom[i]);
    }
}

int EventHandler::inVector(const std::vector<eventInput>& tab, int code) const
{
    for (unsigned int i = 0; i < tab.size(); ++i)
    {
        if (tab[i].code == code)
        {
            return (i);
        }
    }
    return (-1);
}

int EventHandler::inVector(const std::vector<eventMouse>& tab, int code) const
{
    for (unsigned int i = 0; i < tab.size(); ++i)
    {
        if (tab[i].code == code)
        {
            return (i);
        }
    }
    return (-1);
}

/*void EventHandler::extractByTime(std::vector<eventInput>& tab, time_t curTime)
  {
  for (unsigned int i = 0; i < tab.size(); ++i)
  {
  if (tab[i].time != curTime)
  tab.erase(tab.begin() + i);
  }
}*/

void EventHandler::extractByCode(std::vector<eventInput>& tab, int code)
{
    for (unsigned int i = 0; i < tab.size(); ++i)
    {
        if (tab[i].code == code)
        {
            tab.erase(tab.begin() + i);
            return ;
        }
    }
}

void EventHandler::extractByCode(std::vector<eventMouse>& tab, int code)
{
    for (unsigned int i = 0; i < tab.size(); ++i)
    {
        if (tab[i].code == code)
        {
            tab.erase(tab.begin() + i);
            return ;
        }
    }
}

std::vector<int> EventHandler::codeContent(const std::vector<eventInput>& tab) const
{
    std::vector<int> ret;

    for(unsigned int i = 0; i < tab.size(); ++i)
    {
        ret.push_back(tab[i].code);
    }
    return (ret);
}

eventMouse EventHandler::getInfoByCode(const std::vector<eventMouse>& tab, int code) const
{
    eventMouse emptyStruct;

    for (unsigned int i = 0; i < tab.size(); ++i)
    {
        if (tab[i].code == code)
        {
            return (tab[i]);
        }
    }
    return (emptyStruct);
}

bool EventHandler::checkIn(const std::vector<eventInput>& tab, int code) const
{
    return (inVector(tab, code) >= 0);
}

bool EventHandler::checkIn(const std::vector<eventInput>& tab, const std::vector<int>& codes) const
{
    for (unsigned int i = 0; i < codes.size(); ++i)
    {
        if (inVector(tab, codes[i]) >= 0)
        {
            return (true);
        }
    }
    return (false);
}

bool EventHandler::checkIn(const std::vector<eventMouse>& tab, int code) const
{
    return (inVector(tab, code) >= 0);
}

void EventHandler::listening()
{
    sf::Event event;
    time_t curTime;

    time(&curTime);
    pushAll(_keyPressedVector, _keyHoldVector);
    pushAll(_mousePressedVector, _mouseHoldVector);
    _keyPressedVector.clear();
    _keyReleasedVector.clear();
    _mousePressedVector.clear();
    _mouseReleasedVector.clear();
    _mouseWheel.code = 0;
    _prevFocus = _focus;
    while (_window.pollEvent(event))
    {
        eventInput newInput;
        eventMouse newMouse;

        switch (event.type)
        {
        case sf::Event::Closed:
            _window.close();
            break;

        case sf::Event::LostFocus:
            _focus = false;
            break;

        case sf::Event::GainedFocus:
            _focus = true;
            break;

        case sf::Event::KeyPressed:
            if (inVector(_keyPressedVector, event.key.code) < 0 ||
                    inVector(_keyHoldVector, event.key.code) < 0)
            {
                newInput.code = event.key.code;
                newInput.time = curTime;
                _keyPressedVector.push_back(newInput);
            }
            break;

        case sf::Event::KeyReleased:
            extractByCode(_keyPressedVector, event.key.code);
            extractByCode(_keyHoldVector, event.key.code);
            newInput.code = event.key.code;
            newInput.time = curTime;
            _keyReleasedVector.push_back(newInput);
            break;

        case sf::Event::MouseWheelMoved:
            _mouseWheel.code = event.mouseWheel.delta;
            _mouseWheel.x = event.mouseWheel.x;
            _mouseWheel.y = event.mouseWheel.y;
            _mouseWheel.time = curTime;
            break;

        case sf::Event::MouseButtonPressed:
            if (inVector(_mousePressedVector, event.key.code) < 0 ||
                    inVector(_mouseHoldVector, event.key.code) < 0)
            {
                newMouse.code = event.mouseButton.button;
                newMouse.x = event.mouseButton.x;
                newMouse.y = event.mouseButton.y;
                newMouse.time = curTime;
                _mousePressedVector.push_back(newMouse);
            }
            break;

        case sf::Event::MouseButtonReleased:
            extractByCode(_mousePressedVector, event.mouseButton.button);
            extractByCode(_mouseHoldVector, event.mouseButton.button);
            newMouse.code = event.mouseButton.button;
            newMouse.x = event.mouseButton.x;
            newMouse.y = event.mouseButton.y;
            newMouse.time = curTime;
            _mouseReleasedVector.push_back(newMouse);
            break;

        case sf::Event::MouseMoved:
            break;

        default:
            break;
        }
    }
}

std::vector<int> EventHandler::keyPressed() const
{
    return (codeContent(_keyPressedVector));
}

bool EventHandler::keyIsPressed(int code) const
{
    return (checkIn(_keyPressedVector, code));
}

bool EventHandler::keyIsPressed(const std::vector<int>& codes) const
{
    return (checkIn(_keyPressedVector, codes));
}


std::vector<int> EventHandler::keyHold() const
{
    return (codeContent(_keyHoldVector));
}

bool EventHandler::keyIsHold(int code) const
{
    return (checkIn(_keyHoldVector, code));
}

bool EventHandler::keyIsHold(const std::vector<int>& codes) const
{
    return (checkIn(_keyHoldVector, codes));
}


std::vector<int> EventHandler::keyReleased() const
{
    return (codeContent(_keyReleasedVector));
}

bool EventHandler::keyIsReleased(int code) const
{
    return (checkIn(_keyReleasedVector, code));
}

bool EventHandler::keyIsReleased(const std::vector<int>& codes) const
{
    return (checkIn(_keyReleasedVector, codes));
}


bool EventHandler::mouseIsPressed(int code) const
{
    return (checkIn(_mousePressedVector, code));
}

eventMouse EventHandler::mouseInfoPressed(int code) const
{
    return (getInfoByCode(_mousePressedVector, code));
}


bool EventHandler::mouseIsHold(int code) const
{
    return (checkIn(_mouseHoldVector, code));
}

eventMouse EventHandler::mouseInfoHold(int code) const
{
    return (getInfoByCode(_mouseHoldVector, code));
}


bool EventHandler::mouseIsReleased(int code) const
{
    return (checkIn(_mouseReleasedVector, code));
}

eventMouse EventHandler::mouseInfoReleased(int code) const
{
    return (getInfoByCode(_mouseReleasedVector, code));
}


int EventHandler::mouseIsWheeled() const
{
    return (_mouseWheel.code);
}

eventMouse EventHandler::mouseInfoWheeled() const
{
    eventMouse emptyStruct;

    if (_mouseWheel.code)
    {
        return (_mouseWheel);
    }
    return (emptyStruct);
}

bool EventHandler::hasFocus() const
{
    return (_focus);
}

bool EventHandler::gainedFocus() const
{
    return (_prevFocus != _focus && _focus == true);
}

bool EventHandler::lostFocus() const
{
    return (_prevFocus != _focus && _focus == false);
}
