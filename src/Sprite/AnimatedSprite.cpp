////////////////////////////////////////////////////////////
//
// Copyright (C) 2013 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "AnimatedSprite.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(sf::Time frameTime, bool paused, bool looped)
{
    this->frameTime = frameTime;
    this->paused = paused;
    this->looped = looped;

    animation = NULL;

    previousFrame = -1;
    currentFrame = 0;
    texture = NULL;
}

void AnimatedSprite::setAnimation(const Animation& animation)
{
    this->animation = &animation;
    texture = this->animation->getSpriteSheet();

    previousFrame = -1;
    currentFrame = 0;
    setFrame(currentFrame);
}

void AnimatedSprite::setFrameTime(sf::Time time)
{
    frameTime = time;
}

void AnimatedSprite::play()
{
    paused = false;
}

void AnimatedSprite::pause()
{
    paused = true;
}

void AnimatedSprite::stop()
{
    paused = true;

    previousFrame = -1;
    currentFrame = 0;
    setFrame(currentFrame);
}

void AnimatedSprite::setLooped(bool looped)
{
    this->looped = looped;
}

void AnimatedSprite::setColor(const sf::Color& color)
{
    // Update the vertices' color
    vertices[0].color = color;
    vertices[1].color = color;
    vertices[2].color = color;
    vertices[3].color = color;
}

const Animation* AnimatedSprite::getAnimation() const
{
    return animation;
}

size_t AnimatedSprite::getCurrentFrame()
{
    return currentFrame;
}

size_t AnimatedSprite::getPreviousFrame()
{
    return previousFrame;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
    sf::IntRect rect = animation->getFrame(currentFrame);

    float width = static_cast<float>(std::abs(rect.width));
    float height = static_cast<float>(std::abs(rect.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

bool AnimatedSprite::isLooped() const
{
    return looped;
}

bool AnimatedSprite::isPlaying() const
{
    return !paused;
}

sf::Time AnimatedSprite::getFrameTime() const
{
    return frameTime;
}

void AnimatedSprite::setFrame(size_t, bool resetTime)
{
    if(animation)
    {
        //calculate new vertex positions and texture coordiantes
        sf::IntRect rect = animation->getFrame(currentFrame);

        vertices[0].position = sf::Vector2f(0.f, 0.f);
        vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
        vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
        vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

        float left = static_cast<float>(rect.left) + 0.0001f;
        float right = left + static_cast<float>(rect.width);
        float top = static_cast<float>(rect.top);
        float bottom = top + static_cast<float>(rect.height);

        vertices[0].texCoords = sf::Vector2f(left, top);
        vertices[1].texCoords = sf::Vector2f(left, bottom);
        vertices[2].texCoords = sf::Vector2f(right, bottom);
        vertices[3].texCoords = sf::Vector2f(right, top);
    }

    if(resetTime)
        this->currentTime = sf::Time::Zero;
}

void AnimatedSprite::update(sf::Time deltaTime)
{
    // if not paused and we have a valid animation
    if(!paused && animation)
    {
        previousFrame = currentFrame;

        // add delta time
        currentTime += deltaTime;
        // if current time is bigger then the frame time advance one frame
        if(currentTime >= frameTime)
        {
            // reset time, but keep the remainder
            currentTime = sf::microseconds(currentTime.asMicroseconds() % frameTime.asMicroseconds());
            // get next Frame index
            if(currentFrame + 1 < animation->getSize())
            {
                currentFrame++;
            }
            else
            {
                // animation has ended
                currentFrame = 0; // reset to start

                if(!looped)
                {
                    paused = true;
                }

            }

            // set the current frame, not reseting the time
            setFrame(currentFrame, false);
        }
    }
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (animation && texture)
    {
        states.transform *= getTransform();
        states.texture = texture;
        target.draw(vertices, 4, sf::Quads, states);
    }
}
