#include "SaveHandler.h"

// Initialisation of the singleton to NULL
SaveHandler* SaveHandler::shInstance = NULL;

SaveHandler::SaveHandler() {
    buff = "";
}

SaveHandler::~SaveHandler() {

}

// Gets the instance of the SaveHandler
SaveHandler* SaveHandler::getInstance() {
    if(!shInstance) shInstance = new SaveHandler();
    return shInstance;
}

void SaveHandler::setPath(std::string path) {
    this->path = path;
}

void SaveHandler::save() {
    // saves the encrypted content to the file
    std::vector<int> tmp = encrypt(buff, "key");
    std::ofstream myfile;
    myfile.open(path);
    for (size_t i = 0; i < tmp.size(); ++i) {
        myfile << tmp[i] << std::endl;
    }
    myfile.close();
}

void SaveHandler::load() {
    // loads the file, decrypts the content
    std::vector<int> tmp;
    std::ifstream infile;
    infile.open(path);
    int acc;
    while(infile>>acc) {
        tmp.push_back(acc);
    }
    infile.close();
    buff = decrypt(tmp, "key");
}

void SaveHandler::clearBuff() {
    buff = "";
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

void SaveHandler::add(std::string s) {
    buff += (s + "\n");
}

void SaveHandler::add(int a) {
    buff += (Utils::itos(a) + "\n");
}

void SaveHandler::add(std::vector<int> v) {
    for (size_t i(0); i < v.size()-1; ++i) {
        buff += (Utils::itos(v[i]) + ",");
    }
    buff += (Utils::itos(v[v.size()-1]) + "\n");
}

std::string SaveHandler::readString() {
    std::pair<std::string,std::string> p = Utils::splitString(buff, "\n");
    buff = p.second;
    return p.first;
}

int SaveHandler::readInt() {
    std::pair<std::string,std::string> p = Utils::splitString(buff, "\n");
    int a = Utils::stoi(p.first);
    return a;
}

std::vector<int> SaveHandler::readIntVector() {
    std::vector<int> scores;
    std::string scoresLine = Utils::splitString(buff, "\n").first;
    // TODO

    return scores;
}
