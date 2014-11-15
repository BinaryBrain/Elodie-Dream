#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>

/**
 * The structure representing inputs events.
 */
typedef struct
{
    int code;
    std::time_t time;
} eventInput;

/**
 * The structure representing mouse events.
 */
typedef struct
{
    int code;
    int x;
    int y;
    std::time_t time;
} eventMouse;

/**
 * The class handling input and mouse events.
 */
class EventHandler
{
public:

    /**
     * \brief The constructor of EventHandler.
     *
     * \param[in] window The RenderWindow of SFML on which we do different things.
     */
    EventHandler(sf::RenderWindow& window);
    /**
     * \brief The destructor of EventHandler.
     */
    virtual ~EventHandler();

    /**
     * \brief Calculates which events have occured and stocks then in the right vector.
     *
     * Has to be called at each turn of the game.
     * It calculates which events have occured and stock then in the right vector.
     * It's important to call it before trying to use any other function of EventHandler.
     */
    void listening();

    /**
     * \brief Returns the codes obtained from keyPressedVector.
     *
     * \return A vector of int which contains the codes of keyPressedVector.
     */
    std::vector<int> keyPressed() const;
    /**
     * \brief Checks if the code is in keyIsPressedVector.
     * \param[in] code The code we want to search.
     *
     * \return A boolean which describes if code was found.
     */
    bool keyIsPressed(int code) const;
    /**
     * \brief Checks if a code in codes is in keyPressedVector.
     * \param[in] codes The code we want to search.
     *
     * \return A boolean which describes if a code was found.
     */
    bool keyIsPressed(const std::vector<int>& codes) const;

    /**
     * \brief Returns the codes obtained from keyHoldVector.
     *
     * \return A vector of int which contains the codes of keyHoldVector.
     */
    std::vector<int> keyHold() const;
    /**
     * \brief Checks if the code is in keyHoldVector.
     * \param[in] code The code we want to search.
     *
     * \return A boolean which describes if code was found.
     */
    bool keyIsHold(int code) const;
    /**
     * \brief Checks if a code in codes is in keyHoldVector.
     * \param[in] codes The code we want to search.
     *
     * \return A boolean which describes if a code was found.
     */
    bool keyIsHold(const std::vector<int>& codes) const;

    /**
     * \brief Returns the codes obtained from keyReleasedVector.
     *
     * \return A vector of int which contains the codes of keyReleasedVector.
     */
    std::vector<int> keyReleased() const;
    /**
     * \brief Checks if the code is in keyReleasedVector.
     * \param[in] code The code we want to search.
     *
     * \return A boolean which describes if code was found.
     */
    bool keyIsReleased(int code) const;
    /**
     * \brief Checks if a code in codes is in keyReleasedVector.
     * \param[in] codes The code we want to search.
     *
     * \return A boolean which describes if a code was found.
     */
    bool keyIsReleased(const std::vector<int>& codes) const;

    /**
     * \brief Checks if the code is in mousePressedVector.
     * \param[in] code The code we want to search.
     *
     * \return A boolean which describes if code was found.
     */
    bool mouseIsPressed(int code) const;
    /**
     * \brief Gets the eventMouse for code in mousePressedVector.
     * \param[in] code The code we want to use to find the eventMouse.
     *
     * \return An eventMouse corresponding to the code.
     */
    eventMouse mouseInfoPressed(int code) const;

    /**
     * \brief Checks if the code is in mouseHoldVector.
     * \param[in] code The code we want to search.
     *
     * \return A boolean which describes if code was found.
     */
    bool mouseIsHold(int code) const;
    /**
     * \brief Gets the eventMouse for code in mouseHoldVector.
     * \param[in] code The code we want to use to find the eventMouse.
     *
     * \return An eventMouse corresponding to the code.
     */
    eventMouse mouseInfoHold(int code) const;

    /**
     * \brief Checks if the code is in mouseIsReleasedVector.
     * \param[in] code The code we want to search.
     *
     * \return A boolean which describes if code was found.
     */
    bool mouseIsReleased(int code) const;
    /**
     * \brief Gets the eventMouse for code in mouseIsReleasedVector.
     * \param[in] code The code we want to use to find the eventMouse.
     *
     * \return An eventMouse corresponding to the code.
     */
    eventMouse mouseInfoReleased(int code) const;

    /**
     * \brief Returns the code obtained from mouseWheel.
     *
     * \return An int, the code of mouseWheel.
     */
    int mouseIsWheeled() const;
    /**
     * \brief Returns the eventMouse obtained from mouseWheel.
     *
     * \return An eventMouse corresponding to the code of mouseWheel.
     */
    eventMouse mouseInfoWheeled() const;

    bool hasFocus() const;
    bool gainedFocus() const;
    bool lostFocus() const;

private:
    /**
     * \brief Used to push all the content of one tab to another one.
     *
     * \param[in] tabFrom A vector of eventInput, the data to pass.
     * \param[out] tabTo A vector of eventInput in which the data will be put.
     */
    void pushAll(const std::vector<eventInput>& tabFrom, std::vector<eventInput>& tabTo);

    /**
     * \brief Used to push all the contents of one tab to another one.
     *
     * \param[in] tabFrom A vector of eventMouse, the data to pass.
     * \param[out] tabTo A vector of eventMouse, in which the data will be put.
     */
    void pushAll(const std::vector<eventMouse>& tabFrom, std::vector<eventMouse>& tabTo);

    /**
     * \brief Returns the position of an element if he's in the vector and -1 otherwise.
     *
     * \param[in] tab A vector of eventInput in which we will search.
     * \param[in] code The code to find in tab.
     * \return An int, the position of the code in the tab (or -1 if not found).
     */
    int inVector(const std::vector<eventInput>& tab, int code) const;

    /**
     * \brief Returns the position of an element if he's in the vector and -1 otherwise.
     *
     * \param[in] tab A vector of eventMouse in which we will search.
     * \param[in] code The code to find in tab.
     * \return An int, the position of the code in the tab (or -1 if not found).
     */
    int inVector(const std::vector<eventMouse>& tab, int code) const;

    /**
     * \brief Deletes an element from a vector based on the code given in the parameters.
     *
     * \param[in, out] tab A vector of eventInput, from which elements will be deleted.
     * \param[in] code The code used to known which elements to remove.
     */
    void extractByCode(std::vector<eventInput>& tab, int code);

    /**
     * \brief Deletes an element from a vector based on the code given in the parameters.
     *
     * \param[in, out] tab A vector of eventMouse, from which elements will be deleted.
     * \param[in] code The code used to known which elements to remove.
     */
    void extractByCode(std::vector<eventMouse>& tab, int code);

    /**
     * \brief Returns all the code that are in the given tab.
     *
     * \param[in] tab A vector of eventInput, from which elements will be taken.
     * \return A vector of int containing the code for each element in tab.
     */
    std::vector<int> codeContent(const std::vector<eventInput>& tab) const;

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
    eventMouse getInfoByCode(const std::vector<eventMouse>& tab, int code) const;

    /**
     * \brief Checks if the code is in the given tab.
     *
     * \param[in] tab A vector of evenInput in which we will search.
     * \param[in] code The code (int) we want to search.
     * \return A boolean describing if the code was found.
     */
    bool checkIn(const std::vector<eventInput>& tab, int code) const;

    /**
     * \brief Checks for each code in codes if it is in tab, and returns true in this case.
     *
     * \param[in] tab A vector of evenInput in which we will search.
     * \param[in] codes The vector of int which contains elements we want to search.
     * \return A boolean describing if the code was found.
     */
    bool checkIn(const std::vector<eventInput>& tab, const std::vector<int>& codes) const;

    /**
     * \brief Checks if the code is in the given tab.
     *
     * \param[in] tab A vector of eventMouse in which we will search.
     * \param[in] code The code we want to search.
     * \return A boolean describing if the code was found.
     */
    bool checkIn(const std::vector<eventMouse>& tab, int code) const;

    std::vector<eventInput> _keyPressedVector, _keyHoldVector, _keyReleasedVector;
    std::vector<eventMouse> _mousePressedVector, _mouseHoldVector, _mouseReleasedVector;
    eventMouse _mouseWheel;
    bool _prevFocus = true;
    bool _focus = true;
    sf::RenderWindow& _window;
};

#endif // EVENT_H_INCLUDED
