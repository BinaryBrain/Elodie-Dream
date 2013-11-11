#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>

typedef struct {
    int code;
    std::time_t time;
} eventInput;

typedef struct {
    int code;
    int x;
    int y;
    std::time_t time;
} eventMouse;

class EventHandler {
public:
    EventHandler(sf::RenderWindow* window);
    virtual ~EventHandler();
    void listening();

    std::vector<int> keyPressed();
    bool keyIsPressed(int code);
    bool keyIsPressed(std::vector<int> code);

    std::vector<int> keyHold();
    bool keyIsHold(int code);
    bool keyIsHold(std::vector<int> code);

    std::vector<int> keyReleased();
    bool keyIsReleased(int code);
    bool keyIsReleased(std::vector<int> code);

    bool mouseIsPressed(int code);
    eventMouse mouseInfoPressed(int code);

    bool mouseIsHold(int code);
    eventMouse mouseInfoHold(int code);

    bool mouseIsReleased(int code);
    eventMouse mouseInfoReleased(int code);

    int mouseIsWheeled();
    eventMouse mouseInfoWheeled();
private:
    std::vector<eventInput> m_keyPressed, m_keyHold, m_keyReleased;
    std::vector<eventMouse> m_mousePressed, m_mouseHold, m_mouseReleased;
    eventMouse m_mouseWheel;
    sf::RenderWindow* m_window;
};

#endif // EVENT_H_INCLUDED
