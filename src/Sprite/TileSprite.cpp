#include "TileSprite.h"

TileSprite::TileSprite(TileType type)
{
    this->type = type;

    side = 0;

    setTextureRect(sf::IntRect(0, 0, 32, 32));
}

TileSprite::~TileSprite()
{

}

TileType TileSprite::getType()
{
    return type;
}

int TileSprite::getSide()
{
    return side;
}

void TileSprite::setSide(TileSide side)
{
    setSide((int) side);

}

void TileSprite::addSide(TileSide side)
{
    setSide(this->side | (int) side);
}

void TileSprite::filterSides()
{
    if(side & (int) TileSide::TOP)
    {
        side = ~(~side | (int) TileSide::TOP_LEFT);
        side = ~(~side | (int) TileSide::TOP_RIGHT);
    }

    if(side & (int) TileSide::BOTTOM)
    {
        side = ~(~side | (int) TileSide::BOTTOM_LEFT);
        side = ~(~side | (int) TileSide::BOTTOM_RIGHT);
    }

    if(side & (int) TileSide::RIGHT)
    {
        side = ~(~side | (int) TileSide::TOP_RIGHT);
        side = ~(~side | (int) TileSide::BOTTOM_RIGHT);
    }

    if(side & (int) TileSide::LEFT)
    {
        side = ~(~side | (int) TileSide::TOP_LEFT);
        side = ~(~side | (int) TileSide::BOTTOM_LEFT);
    }
}

void TileSprite::setSide(int side)
{
    this->side = side;

    filterSides();

    setTextureRect(sf::IntRect(0, 0, 32, 32));

    if(this->side == ((int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(4*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(0*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(4*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT))
        setTextureRect(sf::IntRect(2*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(6*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(2*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(6*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT))
        setTextureRect(sf::IntRect(1*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(5*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(1*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(5*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT))
        setTextureRect(sf::IntRect(3*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(7*32, 0*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(3*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(7*32, 1*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT))
        setTextureRect(sf::IntRect(0*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(2*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT | (int) TileSide::TOP_RIGHT))
        setTextureRect(sf::IntRect(1*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::LEFT | (int) TileSide::TOP_RIGHT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(3*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT))
        setTextureRect(sf::IntRect(0*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(1*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::TOP_LEFT))
        setTextureRect(sf::IntRect(2*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::TOP_LEFT | (int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(3*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::RIGHT | (int) TileSide::LEFT))
        setTextureRect(sf::IntRect(0*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM))
        setTextureRect(sf::IntRect(4*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::TOP_RIGHT))
        setTextureRect(sf::IntRect(6*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::TOP_LEFT))
        setTextureRect(sf::IntRect(5*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::TOP_LEFT | (int) TileSide::TOP_RIGHT))
        setTextureRect(sf::IntRect(7*32, 3*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::LEFT))
        setTextureRect(sf::IntRect(0*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::LEFT | (int) TileSide::TOP_RIGHT))
        setTextureRect(sf::IntRect(1*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::RIGHT))
        setTextureRect(sf::IntRect(6*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::RIGHT | (int) TileSide::TOP_LEFT))
        setTextureRect(sf::IntRect(7*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::BOTTOM | (int) TileSide::RIGHT | (int) TileSide::LEFT))
        setTextureRect(sf::IntRect(4*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP))
        setTextureRect(sf::IntRect(4*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(5*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(6*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM_LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(7*32, 2*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::LEFT))
        setTextureRect(sf::IntRect(2*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::LEFT | (int) TileSide::BOTTOM_RIGHT))
        setTextureRect(sf::IntRect(3*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::RIGHT))
        setTextureRect(sf::IntRect(4*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::RIGHT | (int) TileSide::BOTTOM_LEFT))
        setTextureRect(sf::IntRect(5*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::RIGHT | (int) TileSide::LEFT))
        setTextureRect(sf::IntRect(2*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM))
        setTextureRect(sf::IntRect(1*32, 4*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM | (int) TileSide::LEFT))
        setTextureRect(sf::IntRect(3*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM | (int) TileSide::RIGHT))
        setTextureRect(sf::IntRect(5*32, 5*32, 32, 32));
    else if(this->side == ((int) TileSide::TOP | (int) TileSide::BOTTOM | (int) TileSide::RIGHT | (int) TileSide::LEFT))
        setTextureRect(sf::IntRect(6*32, 5*32, 32, 32));
}
