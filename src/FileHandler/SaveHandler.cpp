#include "../const.h"
#include "../Utils/Utils.h"
#include "SaveHandler.h"

const unsigned int SaveHandler::NUMSLOTS = 5;

SaveHandler::SaveHandler() {

}

SaveHandler::~SaveHandler() {

}

// Gets the instance of the SaveHandler
SaveHandler& SaveHandler::getInstance() {
  static SaveHandler instance;
  return instance;
}

bool SaveHandler::isSlotFree(const std::string& slot) {
    return !FileHandler::fileExists("save/" + slot + ".save");
}

std::string SaveHandler::nextFreeSlot() {
    for (unsigned int i = 1; i <= NUMSLOTS; i++) {
        std::string slot = MENU_SLOT_PREFIX_LABEL + Utils::itos(i);
        if (isSlotFree(slot)) {
            return slot;
        }
    }
    return "";
}

std::string SaveHandler::computeLevelName(int levelNumber) {
    if (levelNumber == 0) {
        return "Tutorial";
    } else {
        return "Level " + Utils::itos(levelNumber);
    }
}

JsonStringifier& SaveHandler::getStringifier() {
    return stringifier;
}

void SaveHandler::clearStringifier() {
    stringifier.reset();
}

void SaveHandler::saveEncryptedContentTo(const std::string& path) {
    std::string stringified = stringifier.getStringifiedDoc();

    // saves the encrypted content to the file
    std::vector<int> tmp = encrypt(stringified, "key");
    std::ofstream myfile;
    myfile.open(path);
    for (size_t i = 0; i < tmp.size(); ++i) {
        myfile << tmp[i] << std::endl;
    }
    myfile.close();
}

std::string SaveHandler::getDecryptedContentFrom(const std::string& path) {
    // loads the file, decrypts the content
    std::vector<int> tmp;
    std::ifstream infile;
    infile.open(path);
    int acc;
    while (infile >> acc) {
        tmp.push_back(acc);
    }
    infile.close();
    std::string json = decrypt(tmp, "key");

    // in case the file is not here -> no parse error
    if (json == "") {
        json = "{}";
    }

    return json;
}

std::vector<int> SaveHandler::encrypt(const std::string& p, const std::string& key) {
    std::vector<int> tmp;
    for (size_t i = 0; i < p.length(); ++i) {
        tmp.push_back((int)p[i]^key[i%key.length()]);
    }
    return tmp;
}

std::string SaveHandler::decrypt(std::vector<int> tmp, const std::string& key) {
    std::string p = "";
    for (size_t i = 0; i < tmp.size(); ++i) {
        p += ((char)tmp[i])^key[i%key.length()];
    }
    return p;
}
