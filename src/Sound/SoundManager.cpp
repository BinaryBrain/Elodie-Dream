#include "SoundManager.h"

SoundManager::SoundManager() {
    SOUND_TYPE = {
        { SoundType::PUNCH, SOUND_TYPE_PUNCH }
    };
}

SoundManager::~SoundManager() {
    for(std::map< SoundType, sf::SoundBuffer* >::iterator bufferPair = soundBuffers.begin(); bufferPair != soundBuffers.end(); bufferPair++) {
        sf::SoundBuffer* buffer = bufferPair->second;
        if(buffer) {
            delete buffer;
        }
    }
}

sf::SoundBuffer* SoundManager::getSoundBuffer(SoundType type) {
    if(!soundBuffers[type]) {
        sf::SoundBuffer* buffer = new sf::SoundBuffer();
        if(!buffer->loadFromFile(getPath(type))) {
            // TODO handle error
        } else {
            soundBuffers[type] = buffer;
        }
    }

    return soundBuffers[type];
}

std::string SoundManager::getPath(SoundType type) {
    return SOUNDS_PATH+"/"+SOUND_TYPE[type];
}

void SoundManager::play(sf::SoundBuffer* buffer) {
    sf::Sound* sound = new sf::Sound();
    sound->setBuffer(*buffer);
    sound->play();
    // TODO destroy it!
}

void SoundManager::play(SoundType type) {
    sf::SoundBuffer* buffer = getSoundBuffer(type);
    play(buffer);
}
