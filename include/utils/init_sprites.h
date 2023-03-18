//
// Created by mfrei on 18/03/2023.
//

#ifndef PACMAN_INIT_SPRITES_H
#define PACMAN_INIT_SPRITES_H

#include "constants.h"
#include "../display/sprite.h"
#include "../display/animation.h"

// PACMAN

const Sprite pacman_default{{constants::BMP_PACMAN_START_X, constants::BMP_PACMAN_START_Y, 14, 14}, {1 * 2, 1 * 2}, {14 * 2, 14 * 2}};
const Sprite pacman_left_1{{48, constants::BMP_PACMAN_START_Y, 13, 14}, {2 * 2,  1 * 2}, {13 * 2, 14 * 2}};
const Sprite pacman_left_2{{64, constants::BMP_PACMAN_START_Y, 9, 14}, {7 * 2, 1 * 2}, {9 * 2, 14 * 2}};
const Sprite pacman_right_1{{21, constants::BMP_PACMAN_START_Y, 13, 14}, {1 * 2, 1 * 2}, {13 * 2, 14 * 2}};
const Sprite pacman_right_2{{36, constants::BMP_PACMAN_START_Y, 9, 14}, {1 * 2, 1 * 2}, {9 * 2, 14 * 2}};
const Sprite pacman_up_1{{76, 91, 14, 13}, {1 * 2, 2 * 2}, {14 * 2, 13 * 2}};
const Sprite pacman_up_2{{93, 95, 14, 9}, {1 * 2, 7 * 2}, {14 * 2,9 * 2}};
const Sprite pacman_down_1{{110, 91, 14, 13}, {1 * 2, 1 * 2}, {14 * 2, 13 * 2}};
const Sprite pacman_down_2{{127, 95, 14, 9}, {1 * 2, 1 * 2}, {14 * 2, 9 * 2}};
const Sprite pacman_death_1{{4, 111, 16, 8}, {0, 0 * 2}, {16 * 2, 8 * 2}};
const Sprite pacman_death_2{{23, 113, 16, 6}, {0, 2 * 2}, {16 * 2, 6 * 2}};
const Sprite pacman_death_3{{42, 114, 16, 5}, {0, 3 * 2}, {16 * 2, 5 * 2}};
const Sprite pacman_death_4{{61, 114, 16, 5}, {0, 4 * 2}, {16 * 2, 5 * 2}};
const Sprite pacman_death_5{{80, 113, 16, 6}, {0, 4 * 2}, {16 * 2, 6 * 2}};
const Sprite pacman_death_6{{99, 112, 14, 6}, {1 * 2, 4 * 2}, {14 * 2, 6 * 2}};
const Sprite pacman_death_7{{116, 112, 10, 7}, {3 * 2, 4 * 2}, {10 * 2, 7 * 2}};
const Sprite pacman_death_8{{129, 112, 6, 7}, {5 * 2, 4 * 2}, {6 * 2, 7 * 2}};
const Sprite pacman_death_9{{138, 112, 2, 7}, {7 * 2, 4 * 2}, {2 * 2, 7 * 2}};
const Sprite pacman_death_10{{143, 109, 11, 10}, {3 * 2,  3 * 2}, {11 * 2, 10 * 2}};

const Animation pacman_left{{pacman_default, pacman_left_1, pacman_left_2}, true, constants::ENTITY_REFRESH_RATE};
const Animation pacman_right{{pacman_default, pacman_right_1, pacman_right_2}, true, constants::ENTITY_REFRESH_RATE};
const Animation pacman_up{{pacman_default, pacman_up_1, pacman_up_2}, true, constants::ENTITY_REFRESH_RATE};
const Animation pacman_down{{pacman_default, pacman_down_1, pacman_down_2}, true, constants::ENTITY_REFRESH_RATE};
const Animation pacman_death{{pacman_death_1, pacman_death_2, pacman_death_3, pacman_death_4, pacman_death_5, pacman_death_6,
                        pacman_death_7, pacman_death_8, pacman_death_9, pacman_death_10}, false, 7};

// FRUITS

const Sprite fruit_cherry_1{{290, 238, 12, 12}, {2 * 2, 2 * 2}, {12 * 2, 12 * 2}};
const Sprite fruit_cherry_2{{290, 258, 12, 12}, {1 * 2, 1 * 2}, {14 * 2, 14 * 2}};
const Sprite fruit_strawberry_1{{307, 238, 11, 12}, {2 * 2, 2 * 2}, {11 * 2, 12 * 2}};
const Sprite fruit_strawberry_2{{307, 258, 11, 12}, {1 * 2, 1 * 2}, {13 * 2, 14 * 2}};
const Sprite fruit_orange_1{{322, 238, 12, 12}, {2 * 2, 2 * 2}, {12 * 2, 12 * 2}};
const Sprite fruit_orange_2{{322, 258, 12, 12}, {1 * 2, 1 * 2}, {13 * 2, 14 * 2}};
const Sprite fruit_apple_1{{338, 238, 12, 12}, {2 * 2, 2 * 2}, {12 * 2, 12 * 2}};
const Sprite fruit_apple_2{{338, 258, 12, 12}, {1 * 2, 1 * 2}, {13 * 2, 14 * 2}};
const Sprite fruit_melon_1{{355, 236, 11, 14}, {2 * 2, 1 * 2}, {11 * 2, 14 * 2}};
const Sprite fruit_melon_2{{355, 256, 11, 14}, {1 * 2, 0}, {13 * 2, 15 * 2}};
const Sprite fruit_flagship_1{{371, 239, 11, 11}, {2 * 2, 2 * 2}, {11 * 2, 11 * 2}};
const Sprite fruit_flagship_2{{371, 259, 11, 11}, {1 * 2, 1 * 2}, {13 * 2, 13 * 2}};
const Sprite fruit_bell_1{{387, 237, 12, 13}, {2 * 2, 1 * 2}, {12 * 2, 13 * 2}};
const Sprite fruit_bell_2{{387, 257, 12, 13}, {1 * 2, 0}, {14 * 2, 15 * 2}};
const Sprite fruit_key_1{{405, 237, 7, 13}, {4 * 2, 1 * 2}, {7 * 2, 13 * 2}};
const Sprite fruit_key_2{{405, 257, 7, 13}, {3 * 2, 0}, {9 * 2, 15 * 2}};

// PELLET

const Sprite pellet{{constants::BMP_POINT_START_X, constants::BMP_POINT_START_Y, constants::BMP_POINT_SIZE, constants::BMP_POINT_SIZE},
              {3 * 2 * 2, 3 * 2 * 2}, {2 * 2 * 2, 2 * 2 * 2}};

const Sprite energizer{{constants::BMP_POWER_START_X, constants::BMP_POWER_START_Y, constants::BMP_POWER_SIZE, constants::BMP_POWER_SIZE},
                 {0,0},{7 * 2 * 2, 7 * 2 * 2}};

// MAP

const Sprite map_default{{constants::BMP_MAP_START_X, constants::BMP_MAP_START_Y,constants::BMP_MAP_WIDTH, constants::BMP_MAP_HEIGHT},
                   {0, 0}, {constants::BMP_MAP_WIDTH * 4,constants::BMP_MAP_HEIGHT * 4}};

const Sprite map_blink{{540, constants::BMP_MAP_START_Y, constants::BMP_MAP_WIDTH, constants::BMP_MAP_HEIGHT},
                 {0, 0}, {constants::BMP_MAP_WIDTH * 4,constants::BMP_MAP_HEIGHT * 4}};



#endif //PACMAN_INIT_SPRITES_H
