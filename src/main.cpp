#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>

#include "env.h"

#include "Sprite/AnimatedSprite.h"
#include "EventHandler/EventHandler.h"
#include "JsonParser/JsonParser.h"
#include "JsonAccessor/JsonAccessor.h"
#include "Game/Game.h"
#include "Overworld/Overworld.h"

using std::cout;
using std::endl;

int main() {
    // Map Parsing test
    std::ofstream myfile;
    myfile.open ("example.txt");
    std::string test = "Writing this to a file.\n";
    std::string key = "key";
    std::vector<int> tmp;
    for(size_t i = 0; i < test.length(); ++i){
        //test[i] = test[i]^key[i%key.length()];
        tmp.push_back((int)test[i]^key[i%key.length()]);
    }
    for (size_t i = 0; i < tmp.size(); ++i){
        myfile << tmp[i] << std::endl;
    }
    myfile.close();
    tmp.clear();
    std::ifstream infile;
    infile.open("example.txt");
    int acc;
    while(infile>>acc){
        tmp.push_back(acc);
    }
    test = "";
    for(size_t i = 0; i < tmp.size(); ++i){
        test += ((char)tmp[i])^key[i%key.length()];
    }
    std::cout << test <<std::endl;
    Game* game = Game::getInstance();

    if (false) {
        // Conf test
        JsonAccessor language = JsonAccessor();
        language.load("assets/config/languages/FR.lang");

        // Strings test
        cout << language.getString("Intro") << endl;
        cout << language.getString("Dev") << endl;
        cout << language.getString("End") << endl;

        JsonAccessor sheep = JsonAccessor();
        sheep.load("assets/img/sprites/enemies/sheep.json");

        std::vector< std::vector<int>* >* tab = sheep.getInt2DVector("anim.hitbox");
        for (unsigned int i = 0; i < tab->size(); ++i) {
            for (unsigned int j = 0; j < (*tab)[i]->size(); ++j) {
                cout << (*(*tab)[i])[j] << endl;
            }
        }
        cout << sheep.getString("anim name") << endl;
        cout << sheep.getString("anim name") << endl;
        cout << sheep.getString("anim name") << endl;
        cout << sheep.getString("anim name") << endl;
    }

    game->run();
    game->kill();

    return 0;
}
