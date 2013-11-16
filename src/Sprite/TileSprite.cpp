#include "TileSprite.h"

TileSprite::TileSprite(TileType type) {
    this->type = type;
    this->side = 0;

    // TODO Change the path according to the type
    this->texture.loadFromFile("assets/img/sprites/tilesets/autotiles/rock1extended.png");

    this->setTexture(this->texture);
    // TODO Change the coords according to the type
    this->setTextureRect(sf::IntRect(0, 0, 32, 32));
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

void TileSprite::filterSides() {
    if(this->side & (int) TileSide::TOP && this->side & (int) TileSide::TOP_LEFT)
        this->side = ~(~this->side | (int) TileSide::TOP_LEFT);
    if(this->side & (int) TileSide::TOP && this->side & (int) TileSide::TOP_RIGHT)
        this->side = ~(~this->side | (int) TileSide::TOP_RIGHT);


    if(this->side & (int) TileSide::BOTTOM && this->side & (int) TileSide::BOTTOM_LEFT)
        this->side = ~(~this->side | (int) TileSide::BOTTOM_LEFT);
    if(this->side & (int) TileSide::BOTTOM && this->side & (int) TileSide::BOTTOM_RIGHT)
        this->side = ~(~this->side | (int) TileSide::BOTTOM_RIGHT);

    if(this->side & (int) TileSide::RIGHT && this->side & (int) TileSide::TOP_RIGHT)
        this->side = ~(~this->side | (int) TileSide::TOP_RIGHT);
    if(this->side & (int) TileSide::RIGHT && this->side & (int) TileSide::BOTTOM_RIGHT)
        this->side = ~(~this->side | (int) TileSide::BOTTOM_RIGHT);

    if(this->side & (int) TileSide::LEFT && this->side & (int) TileSide::TOP_LEFT)
        this->side = ~(~this->side | (int) TileSide::TOP_LEFT);
    if(this->side & (int) TileSide::LEFT && this->side & (int) TileSide::BOTTOM_LEFT)
        this->side = ~(~this->side | (int) TileSide::BOTTOM_LEFT);
}

void TileSprite::setSide(int side) {
    this->side = side;

    this->filterSides();

    this->setTextureRect(sf::IntRect(0, 0, 32, 32));

    if(this->side == ((int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(4*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(0*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(4*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT))
        this->setTextureRect(sf::IntRect(2*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(6*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(2*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(6*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT))
        this->setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(5*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(1*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(5*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT))
        this->setTextureRect(sf::IntRect(3*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(7*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(3*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(7*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(0*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(2*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT | (int) TileSide::TOP_RIGHT))
        this->setTextureRect(sf::IntRect(1*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(3*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT))
        this->setTextureRect(sf::IntRect(0*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(1*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::TOP_LEFT))
        this->setTextureRect(sf::IntRect(2*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(3*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(0*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM))
        this->setTextureRect(sf::IntRect(4*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::TOP_RIGHT))
        this->setTextureRect(sf::IntRect(6*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::TOP_LEFT))
        this->setTextureRect(sf::IntRect(5*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT))
        this->setTextureRect(sf::IntRect(7*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(0*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::LEFT | (int) TileSide::TOP_RIGHT))
        this->setTextureRect(sf::IntRect(1*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::RIGHT))
        this->setTextureRect(sf::IntRect(6*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::RIGHT | (int) TileSide::TOP_LEFT))
        this->setTextureRect(sf::IntRect(7*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::RIGHT | (int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(4*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP))
        this->setTextureRect(sf::IntRect(4*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(5*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(6*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(7*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(2*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::LEFT | (int) TileSide::BOTTOM_RIGHT))
        this->setTextureRect(sf::IntRect(3*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::RIGHT))
        this->setTextureRect(sf::IntRect(4*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::RIGHT | (int) TileSide::BOTTOM_LEFT))
        this->setTextureRect(sf::IntRect(5*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::RIGHT | (int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(2*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM))
        this->setTextureRect(sf::IntRect(1*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM | (int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(3*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM | (int) TileSide::RIGHT))
        this->setTextureRect(sf::IntRect(5*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM | (int) TileSide::RIGHT | (int) TileSide::LEFT))
        this->setTextureRect(sf::IntRect(6*32, 5*32, 32, 32));
}
