#include "TileSprite.h"

TileSprite::TileSprite(TileType type) {
    this->type = type;
    this->side = 0;

    // TODO Change the path according to the type
    this->texture.loadFromFile("assets/img/sprites/tilesets/autotiles/ground1.png");

    this->setTexture(this->texture);
    // TODO Change the coords according to the type
    this->setTextureRect(sf::IntRect(32, 64, 32, 32));
}

TileSprite::~TileSprite() {

}

TileType TileSprite::getType() {
    return this->type;
}

int TileSprite::getSide() {
    return this->side;
}

void TileSprite::setSide(TileSide side) {
    this->setSide((int) side);

}

void TileSprite::addSide(TileSide side) {
    this->setSide(this->side | (int) side);
}

void TileSprite::setSide(int side) {
    this->side = side;

    if(this->side & (int) TileSide::TOP) {
        this->setTextureRect(sf::IntRect(32, 32, 32, 32));
    }

    if(this->side & (int) TileSide::LEFT) {
        this->setTextureRect(sf::IntRect(0, 64, 32, 32));
    }

    if(this->side & (int) TileSide::RIGHT) {
        this->setTextureRect(sf::IntRect(64, 64, 32, 32));
    }

    if(this->side & (int) TileSide::TOP && this->side & (int) TileSide::LEFT) {
        this->setTextureRect(sf::IntRect(0, 32, 32, 32));
    }

    if(this->side & (int) TileSide::TOP && this->side & (int) TileSide::RIGHT) {
        this->setTextureRect(sf::IntRect(64, 32, 32, 32));
    }
}
