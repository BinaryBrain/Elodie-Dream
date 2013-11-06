#include "Overworld.h"

Overworld::Overworld() {
    std::string filenames[4] = { "overworld1.png", "overworld2.png", "overworld3.png", "overworld4.png" };

    for(int i=0; i<4; i++) {
        sf::Texture* overworld = new sf::Texture;
        overworld->loadFromFile("assets/img/overworld/"+filenames[i]);
        overworldSprites.push_back(new sf::Sprite(*overworld));
    }

    this->currentState = UNIL;
}

Overworld::~Overworld() {
    for (std::vector<sf::Sprite*>::iterator sprite = this->overworldSprites.begin(); sprite != this->overworldSprites.end(); ++sprite) {
        delete *sprite;
    }
}

sf::Sprite* Overworld::getCurrentSprite() {
    return this->overworldSprites[this->currentState];
}

void Overworld::evolve() {
    switch(this->currentState) {
        case UNIL:
            this->currentState = CASTLE;
            break;
        case CASTLE:
            this->currentState = VOLCANO;
            break;
        case VOLCANO:
            this->currentState = FRELJORD;
            break;
        // FIXME Dev stuff
        case FRELJORD:
            this->currentState = UNIL;
            break;
        default:
            break;
    }
}
