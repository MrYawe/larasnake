#ifndef IA_H
#define IA_H

/**
 * \file ia.h
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Headers of ia file
 * \details All header of the ia file functions
 */

#include "board.h"
#include "snake.h"
#include "game.h"

Direction iaRandom (Board board, Snake snake);
Direction iaSurvive (Board board, Snake snake);
Direction iaJambon (Game game, Snake snake);
Direction iaSurviveDepth(Board board, Snake snake);
void iaDirectionItem(Board board, Snake snake, int* tab);

#endif