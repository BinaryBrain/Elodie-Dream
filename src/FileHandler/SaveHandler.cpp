#include "SaveHandler.h"

// Initialisation of the singleton to NULL
SaveHandler* SaveHandler::shInstance = NULL;

SaveHandler::SaveHandler() {
    stringifier = new JsonStringifier();
    accessor = new JsonAccessor();
}

SaveHandler::~SaveHandler() {
    delete stringifier;
    delete accessor;
    stringifier = NULL;
    accessor = NULL;
}

// Gets the instance of the game
SaveHandler* SaveHandler::getInstance() {
    if(!shInstance) shInstance = new SaveHandler();
    return shInstance;
}

void SaveHandler::setPath(std::string path) {
    this->path = path;
}

JsonStringifier* SaveHandler::getStringifier() {
    return stringifier;
}

void SaveHandler::save() {
    std::string stringified(stringifier->getStringifiedDoc());

    // saves the encrypted stringified json to the file
    std::vector<int> tmp = encrypt(stringified, "key");
    std::ofstream myfile;
    myfile.open(path);
    for (size_t i = 0; i < tmp.size(); ++i) {
        myfile << tmp[i] << std::endl;
    }
    myfile.close();
}

bool SaveHandler::isSlotFree(std::string slot) {
    return !Utils::fileExists("save/"+slot+".save");
}

std::string SaveHandler::nextFreeSlot() {
    for(unsigned int i = 1; i <= 3; i++) { // TODO add 3 as a const
        if(isSlotFree("Slot "+Utils::itos(i))) {
            return "Slot "+Utils::itos(i);
        }
    }

    return "";
}

std::string SaveHandler::load() {
    // loads the file, decrypts the json inside
    std::vector<int> tmp;
    std::ifstream infile;
    infile.open(path);
    int acc;
    while(infile>>acc) {
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

void SaveHandler::clearStringifier() {
    delete stringifier;
    stringifier = new JsonStringifier();
}

std::vector<int> SaveHandler::encrypt(std::string p, std::string key) {
    std::vector<int> tmp;
    for(size_t i = 0; i < p.length(); ++i) {
        tmp.push_back((int)p[i]^key[i%key.length()]);
    }
    return tmp;
}

std::string SaveHandler::decrypt(std::vector<int> tmp, std::string key) {
    std::string p = "";
    for(size_t i = 0; i < tmp.size(); ++i) {
        p += ((char)tmp[i])^key[i%key.length()];
    }
    return p;
}
