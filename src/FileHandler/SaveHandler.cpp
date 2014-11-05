#include "SaveHandler.h"

// Initialisation of the singleton to NULL
SaveHandler* SaveHandler::shInstance = NULL;

SaveHandler::SaveHandler() {
    stringifier = new JsonStringifier();
}

SaveHandler::~SaveHandler() {
    delete stringifier;
}

// Gets the instance of the SaveHandler
SaveHandler* SaveHandler::getInstance() {
    if(!shInstance) shInstance = new SaveHandler();
    return shInstance;
}

void SaveHandler::setPath(const std::string& path) {
    this->path = path;
}

JsonStringifier* SaveHandler::getStringifier() {
    return stringifier;
}

void SaveHandler::save() {
    std::string stringified(stringifier->getStringifiedDoc());

    // saves the encrypted content to the file
    std::vector<int> tmp = encrypt(stringified, "key");
    std::ofstream myfile;
    myfile.open(path);
    for (size_t i = 0; i < tmp.size(); ++i) {
        myfile << tmp[i] << std::endl;
    }
    myfile.close();
}

std::string SaveHandler::load() {
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
    if(json == "") {
        json = "{}";
    }

    return json;
}

bool SaveHandler::isSlotFree(const std::string& slot) {
    return !FileHandler::fileExists("save/" + slot + ".save");
}

std::string SaveHandler::nextFreeSlot() {
    for (int i = 1; i <= NUMSLOTS; i++) {
        std::string slot = MENU_SLOT_PREFIX_LABEL + Utils::itos(i);
        if(isSlotFree(slot)) {
            return slot;
        }
    }

    return "";
}

void SaveHandler::clearStringifier() {
    delete stringifier;
    stringifier = new JsonStringifier();
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
    for (std::size_t i = 0; i < tmp.size(); ++i) {
        p += ((char)tmp[i])^key[i%key.length()];
    }
    return p;
}

std::string SaveHandler::computeLDLName(int LDL) {
    if(LDL == 0) {
        return "Tutorial";
    } else {
        return "Level " + Utils::itos(LDL);
    }
}
