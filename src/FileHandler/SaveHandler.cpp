#include "SaveHandler.h"

SaveHandler::SaveHandler() {

}

SaveHandler::~SaveHandler() {

}

void SaveHandler::setPath(std::string path) {
    this->path = path;
}

void SaveHandler::save() {
    JsonStringifier stringifier;

    // todo fin why there should be another string each time, not the same one which switches values
    std::string keyState = "gamestate";
    GameState state = Game::getInstance()->getState();
    stringifier.setInt(keyState, (int)state);

    std::string test = "test";
    std::string vie = "la vie!";
    stringifier.setString(test, vie);

    std::string toWrite(stringifier.getStringifiedDoc());
    FileHandler fh;
    std::cout << "Saved string: " << toWrite << std::endl;

    std::vector<int> tmp = encrypt(toWrite, "key");
    std::ofstream myfile;
    myfile.open (path);
    for (size_t i = 0; i < tmp.size(); ++i){
        myfile << tmp[i] << std::endl;
    }
    myfile.close();
}

void SaveHandler::load() {
    std::vector<int> tmp;
    std::ifstream infile;
    infile.open(path);
    int acc;
    while(infile>>acc){
        tmp.push_back(acc);
    }
    std::string test = decrypt(tmp, "key");
    std::cout << test << std::endl;
}

std::vector<int> SaveHandler::encrypt(std::string p, std::string key) {
    std::vector<int> tmp;
    for(size_t i = 0; i < p.length(); ++i){
        tmp.push_back((int)p[i]^key[i%key.length()]);
    }
    return tmp;
}

std::string SaveHandler::decrypt(std::vector<int> tmp, std::string key) {
    std::string p = "";
    for(size_t i = 0; i < tmp.size(); ++i){
        p += ((char)tmp[i])^key[i%key.length()];
    }
    std::cout << p <<std::endl;
    return p;
}
