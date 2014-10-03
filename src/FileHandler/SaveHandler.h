#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <fstream>
#include <cstdio>
#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/prettywriter.h"	// for stringify JSON
#include "rapidjson/filestream.h"	// wrapper of C stream for prettywriter as output
#include "../env.h"

#include "../Json/JsonParser.h"
#include "../Json/JsonStringifier.h"
#include "../Json/JsonAccessor.h"
#include "FileHandler.h"

class SaveHandler {
public:
    static SaveHandler* getInstance();

    void setPath(std::string path);
    JsonStringifier* getStringifier();

    void save();
    std::string load();

    void clearStringifier();

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
    std::vector<int> encrypt(std::string p, std::string key);
    /**
    * \brief Decrypts a string from a vector of int, using a key.
    * \param tmp The string to decrypt.
    * \param key The key used to decrypt.
    * \return A string, the int vector decrypted.
    */
    std::string decrypt(std::vector<int> tmp, std::string key);

    std::string path;
    JsonStringifier* stringifier;
    JsonAccessor* accessor;
};

#endif // SAVEHANDLER_H
