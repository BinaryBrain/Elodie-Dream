#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <string>

#include <SFML/Audio.hpp>

#include "../env.h"
#include "../const.h"

class SoundManager {
public:
    SoundManager();
    virtual ~SoundManager();

    sf::SoundBuffer* getSoundBuffer(SoundType type);
    std::string getPath(SoundType type);

    void play(sf::SoundBuffer* buffer);
    void play(SoundType type);
protected:
private:
    std::map< SoundType, sf::SoundBuffer* > soundBuffers;
    std::map< SoundType, std::string > SOUND_TYPE;
};

#endif // SOUNDSYSTEM_H
