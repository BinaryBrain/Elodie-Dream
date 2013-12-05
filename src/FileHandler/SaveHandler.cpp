#include "SaveHandler.h"

SaveHandler::SaveHandler() {

}

SaveHandler::~SaveHandler() {

}

void SaveHandler::setPath(std::string path) {
    this->path = path;
}

void SaveHandler::addSave() {
    JsonStringifier stringifier;

    // todo fin why there should be another string each time, not the same one which switches values
    std::string keyState = "gamestate";
    GameState state = Game::getInstance()->getState();
    std::cout << "Original gamestate: " << (int)state << std::endl;
    stringifier.add(keyState, (int)state);

    std::string test = "test";
    std::string vie = "la vie!";
    stringifier.add(test, vie);

    std::string stringified(stringifier.getStringifiedDoc());
    FileHandler fh;
    std::cout << "Stringified json: " << stringified << std::endl;

    // save the encrypted stringified json to path
    std::vector<int> tmp = encrypt(stringified, "key");
    std::ofstream myfile;
    myfile.open(path);
    for (size_t i = 0; i < tmp.size(); ++i){
        myfile << tmp[i] << std::endl;
    }
    myfile.close();
}

void SaveHandler::applySaves() {

}

void SaveHandler::load() {
    std::vector<int> tmp;
    std::ifstream infile;
    infile.open(path);
    int acc;
    while(infile>>acc){
        tmp.push_back(acc);
    }
    infile.close();
    std::string json = decrypt(tmp, "key");

    std::ofstream tempJsonFile;
    std::string tempJsonFilePath = "save/temp.json";

    tempJsonFile.open(tempJsonFilePath);
    tempJsonFile << json << std::endl;
    tempJsonFile.close();

    JsonAccessor accessor;
    accessor.load(tempJsonFilePath);
    int state = accessor.getInt("gamestate");
    std::cout << "Retrieved gamestate: " << state << std::endl;


    if(remove(tempJsonFilePath.c_str()) != 0 ) {
        std::cerr << "Error deleting temporary json" << std::endl;
    }
    else {
        std::cout << "Temporary json successfully deleted." << std::endl;
    }

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
    return p;
}
