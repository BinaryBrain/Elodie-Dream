#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <string>

#include <SFML/Audio.hpp>

#include "../env.h"
#include "../const.h"
#include "../Game/Game.h"

class SoundManager
{
public:
    static SoundManager& getInstance();

    sf::SoundBuffer* getRandomSoundBuffer(SoundType type);
    std::string getPath(SoundType type, int n);

    void cleanUnusedSounds();

    void play(sf::SoundBuffer* buffer, int volume = 100);
    void play(SoundType type);
protected:
private:
    SoundManager();
    ~SoundManager();

    SoundManager(const SoundManager&);
    SoundManager& operator= (SoundManager const&);

    std::map< SoundType, std::map< int, sf::SoundBuffer* > > soundBuffers;
    std::map< SoundType, std::pair< std::string, int > > SOUND_TYPE;
    std::vector< sf::Sound* > sounds;
};

#endif // SOUNDSYSTEM_H
