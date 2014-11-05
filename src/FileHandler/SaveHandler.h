#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <fstream>
#include <cstdio>
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include "../env.h"

#include "../Json/JsonStringifier.h"
#include "FileHandler.h"

class SaveHandler {
public:
    static SaveHandler* getInstance();

    void setPath(const std::string& path);
    JsonStringifier* getStringifier();

    bool isSlotFree(const std::string& slot);
    std::string nextFreeSlot();

    void save();
    std::string load();

    void clearStringifier();
    std::string computeLDLName(int LDL);

private:
    SaveHandler();
    virtual ~SaveHandler();

    static SaveHandler* shInstance;
    SaveHandler& operator= (SaveHandler const&); // Makes operator= private

    /**
    * \brief Encrypts a string to a vector of int, using a key.
    * \param p The string to encrypt.
    * \param key The key used to encrypt.
    * \return An int vector, the string encrypted.
    */
    std::vector<int> encrypt(const std::string& p, const std::string& key);
    /**
    * \brief Decrypts a string from a vector of int, using a key.
    * \param tmp The string to decrypt.
    * \param key The key used to decrypt.
    * \return A string, the int vector decrypted.
    */
    std::string decrypt(std::vector<int> tmp, const std::string& key);

    std::string path;
    JsonStringifier* stringifier;
};

#endif // SAVEHANDLER_H
