//
// Created by omar on 12/02/23.
//

#ifndef PEC_MEN_POWERUP_H
#define PEC_MEN_POWERUP_H
#include <SDL.h>
#include <utility>
#include "entity.h"
#include "constants.h"

class PowerUp : public Entity{

protected:
    // TODO : IS powerup Active ?
    powerUps type_ {};

public:
    PowerUp(const pair<int, int> &coordinates, int size, SDL_Rect image, int points, powerUps type);
    PowerUp();
};


#endif //PEC_MEN_POWERUP_H
