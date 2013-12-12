#include "SoundManager.h"

SoundManager* SoundManager::soundManagerInstance = NULL;

SoundManager::SoundManager() {
    SOUND_TYPE = {
        { SoundType::PUNCH, { SOUND_TYPE_PUNCH, SOUND_TYPE_PUNCH_MAX } }, // The int is the number after the max file (2 => punch2.wav)
        { SoundType::SPIKES, { SOUND_TYPE_SPIKES, SOUND_TYPE_SPIKES_MAX } },
        { SoundType::SHEEP, { SOUND_TYPE_SHEEP, SOUND_TYPE_SHEEP_MAX } },
        { SoundType::FOOTSTEP_GROUND, { SOUND_TYPE_FOOTSTEP_GROUND, SOUND_TYPE_FOOTSTEP_GROUND_MAX } },
        { SoundType::FOOTSTEP_GRASS, { SOUND_TYPE_FOOTSTEP_GRASS, SOUND_TYPE_FOOTSTEP_GRASS_MAX } }
    };
}

SoundManager::~SoundManager() {
    for(std::map< SoundType, std::map < int, sf::SoundBuffer* > >::iterator bufferPair = soundBuffers.begin();
            bufferPair != soundBuffers.end(); bufferPair++) {
        for(std::map < int, sf::SoundBuffer* >::iterator buffer = bufferPair->second.begin(); buffer != bufferPair->second.end(); buffer++) {
            if(buffer->second) {
                delete buffer->second;
            }
        }
    }
}

// Gets the instance of the game
SoundManager* SoundManager::getInstance() {
    if(!soundManagerInstance) soundManagerInstance = new SoundManager();
    return soundManagerInstance;
}

void SoundManager::kill() {
    if(soundManagerInstance) {
        delete soundManagerInstance;
        soundManagerInstance = NULL;
    }
}

sf::SoundBuffer* SoundManager::getRandomSoundBuffer(SoundType type) {
    int n = 0;

    if(SOUND_TYPE[type].second != 0) {
        n = rand() % (SOUND_TYPE[type].second+1);
    }

    if(!soundBuffers[type][n]) {
        sf::SoundBuffer* buffer = new sf::SoundBuffer();
        if(!buffer->loadFromFile(getPath(type, n))) {
            // TODO handle error
            // Buffer should not be called
        } else {
            soundBuffers[type][n] = buffer;
        }
    }

    return soundBuffers[type][n];
}

std::string SoundManager::getPath(SoundType type, int n) {
    std::stringstream sstm;
    sstm << SOUNDS_PATH << "/" << SOUND_TYPE[type].first << n << ".wav";
    return sstm.str();
}

void SoundManager::play(sf::SoundBuffer* buffer) {
    Game* game = Game::getInstance();

    if(!game->isMute()) {
        sf::Sound* sound = new sf::Sound();
        sound->setBuffer(*buffer);
        sound->play();
        sounds.push_back(sound);
    }

    cleanUnusedSounds();
}

void SoundManager::play(SoundType type) {
    sf::SoundBuffer* buffer = getRandomSoundBuffer(type);
    play(buffer);
}

void SoundManager::cleanUnusedSounds() {
    for(unsigned int i = 0; i < sounds.size(); i++) {
        if(sounds[i]->getStatus() != sf::Sound::Status::Playing) {
            delete sounds[i];
            sounds.erase(sounds.begin()+i);
        }
    }
}
