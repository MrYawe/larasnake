#ifndef IA_H
#define IA_H

#include "board.h"
#include "snake.h"
#include "game.h"

Direction iaSurvive (Board *board, Snake *snake);
Direction iaJambon (Game game, Snake *snake);

#endif