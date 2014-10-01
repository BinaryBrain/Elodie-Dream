#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <fstream>
#include <cstdio>
#include "../env.h"

#include "../Json/JsonAccessor.h"
#include "FileHandler.h"

/**
* The class used to manage saves. There should be only one SaveHandler.
* To create a save file, set the path with setPath(), add the things you want with the
* add() functions and use save() when you're done.
*
* To load a save, set the path of the file, use load() and then be sure to read what you
* added in the right order (when you saved).
*
* At the moment, the buffer is a simple string and the add functions push the data on a
* new line each time.
*/
class SaveHandler {
public:
    /**
    * \brief Gets the instance of the SaveHandler.
    */
    static SaveHandler* getInstance();
    /**
    * \brief Sets the path of the file. Should be used before save() and load().
    * \param path The path to set.
    */
    void setPath(std::string path);
    /**
    * \brief Saves the buffer to the save file after encrypting it.
    */
    void save();
    /**
    * \brief Loads the content save file to the buffer after decrypting it.
    */
    void load();
    /**
    * \brief Clears the buffer. Should be used before adding data to the buffer.
    */
    void clearBuff();

    /**
    * \brief Adds an int to the buffer.
    * \param a The int to add to the buffer.
    */
    void add(int a);
    /**
    * \brief Adds a string to the buffer.
    * \param s The string to add to the buffer.
    */
    void add(std::string s);
    /**
    * \brief Adds an int vector to the buffer.
    * \param v The int vector to add to the buffer.
    */
    void add(std::vector<int> v);

    /**
    * \brief Reads an int from the buffer.
    * \return The int wanted.
    */
    int readInt();
    /**
    * \brief Reads a string from the buffer.
    * \return The string wanted.
    */
    std::string readString();
    /**
    * \brief Reads an int vector from the buffer.
    * \return The int vector wanted.
    */
    std::vector<int> readIntVector();

private:
    /**
    * \brief The constructor of SaveHandler. Private for the Singleton pattern.
    */
    SaveHandler();
    /**
    * \brief The default destructor of SaveHandler.
    */
    virtual ~SaveHandler();

    static SaveHandler* shInstance;
    SaveHandler& operator= (SaveHandler const&); // Makes operator= private

    /**
    * \brief Encrypts a string to a vector of int, using a key.
    * \param p The string to encrypt.
    * \param key The key used to encrypt.
    * \return An int vector, the string encrypted.
    */
    std::vector<int> encrypt(std::string p, std::string key);
    /**
    * \brief Decrypts a string from a vector of int, using a key.
    * \param tmp The string to decrypt.
    * \param key The key used to decrypt.
    * \return A string, the int vector decrypted.
    */
    std::string decrypt(std::vector<int> tmp, std::string key);

    std::string path;
    std::string buff;
};

#endif // SAVEHANDLER_H
