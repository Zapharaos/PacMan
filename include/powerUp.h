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
    powerUps type ;
    SDL_Rect sprite;
public:

    PowerUp();

    PowerUp(const powerUps &type, const SDL_Rect &sprite);

    [[nodiscard]] const powerUps &getType() const;

    void setType(const powerUps type);

    [[nodiscard]] const SDL_Rect &getSprite() const;

    void setSprite(const SDL_Rect sprite);

    virtual ~PowerUp();


};


#endif //PEC_MEN_POWERUP_H
