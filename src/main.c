/**
 * \file main.c
 * \author groupe Larakis
 * \version 1
 * \date 20/02/2016
 * \brief Represents the program
 * \details All the actions of the program
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "gui.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    guiPlay(MEDIUM); // SMALL MEDIUM LARGE

    return EXIT_SUCCESS;
}
