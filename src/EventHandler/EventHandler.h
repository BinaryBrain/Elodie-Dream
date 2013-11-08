#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>

typedef struct {
    int code;
    std::time_t time;
} eventInput;

class EventHandler
{
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
private:
    std::vector<eventInput> m_keyPressed, m_keyHold, m_keyReleased, m_mousePressed, m_mouseReleased;
    int m_mouseWheel;
    sf::RenderWindow* m_window;
};

#endif // EVENT_H_INCLUDED
