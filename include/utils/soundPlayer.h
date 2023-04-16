//
// Created by omar on 15/04/23.
//

#ifndef PACMAN_SOUNDPLAYER_H
#define PACMAN_SOUNDPLAYER_H

#include <SDL2/SDL.h>

class SoundPlayer{
public :
    enum class Sounds
    {
        kCredit,
        kDeath1,
        kDeath2,
        kEatFruit,
        kEatGhost,
        kExtend,
        kGameStart,
        kIntermission,
        kMunch1,
        kMunch2,
        kPowerPellet,
        kRetreating,
        kSiren1,
        kSiren2,
        kSiren3,
        kSiren4,
        kSiren5
    };

    SoundPlayer();

    virtual ~SoundPlayer();

    void playSound(const char* filename) const;
private :
    SDL_AudioDeviceID m_device;
    static void audioCallback(void* userdata, Uint8* stream, int len) {
        // do nothing
    }

};
#endif //PACMAN_SOUNDPLAYER_H
