#include "TileSprite.h"

TileSprite::TileSprite(TileType type) {
    this->type = type;

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
