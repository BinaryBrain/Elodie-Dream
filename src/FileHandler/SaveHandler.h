#ifndef SAVEHANDLER_H
#define SAVEHANDLER_H

#include <fstream>
#include <cstdio>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filestream.h"
#include "../env.h"
#include "../const.h"
#include "../Utils/Utils.h"

#include "../Json/JsonStringifier.h"
#include "FileHandler.h"

class SaveHandler
{
public:
    static const unsigned int NUMSLOTS;

    static const std::string VERSION_KEY;
    static const std::string DATE_KEY;
    static const std::string LDL_KEY;
    static const std::string SCORES_KEY;
    static const std::string MORESTATS_KEY;

    static const std::string SLOT_PREFIX_LABEL;

    static SaveHandler& getInstance();
    static bool isSlotFree(const std::string& slot);
    static std::string nextFreeSlot();
    static std::string computeLevelName(const std::vector<int>& LDL);

    JsonStringifier& getStringifier();
    void clearStringifier();

    void saveEncryptedContentTo(const std::string& path);
    std::string getDecryptedContentFrom(const std::string& path);

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

    JsonStringifier stringifier;
};

#endif // SAVEHANDLER_H
