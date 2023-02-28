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
    powerUps type ;
    SDL_Rect sprite{};
public:
    PowerUp(const pair<int, int> &coordinates, const string &name, int points, powerUps type, const SDL_Rect &sprite);

    PowerUp(const pair<int, int> &coordinates, const string &name, powerUps type, const SDL_Rect &sprite);

    PowerUp();

    [[nodiscard]] powerUps getType() const;

    void setType(powerUps type);

    [[nodiscard]] const SDL_Rect &getSprite() const;

    void setSprite(const SDL_Rect &sprite);


};


#endif //PEC_MEN_POWERUP_H
