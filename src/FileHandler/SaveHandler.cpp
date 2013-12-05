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
    std::string keyGameState = "gamestate";
    GameState gameState = Game::getInstance()->getState();
    stringifier.add(keyGameState, (int)gameState);

    std::string keyCurrentEnv = "currentenv";
    int currentEnv = Game::getInstance()->getOverworld()->getCurrentEnv();
    stringifier.add(keyCurrentEnv, currentEnv);

    std::string stringified(stringifier.getStringifiedDoc());
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
    int gameState = accessor.getInt("gamestate");
    int currentEnv = accessor.getInt("currentenv");
    std::cout << "Retrieved gamestate: " << gameState << std::endl;
    std::cout << "Retrieved currentenv: " << currentEnv << std::endl;


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
