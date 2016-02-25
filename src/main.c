#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include <stdint.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
//#include "plateau.h"
//#include "serpent.h"

// Pour tester:  gcc -o prog main.c `sdl-config --cflags --libs`

enum direction {left, right, up, down};
typedef enum direction direction;

int main(int argc, char *argv[])
{
    // Variables
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Rect positionZozor;
    SDL_Event event;
    int continuer = 1;
    int frameRate = 60; // FPS
    int frameMs = 1000 / frameRate; //calculate the length of each frame
    Uint32 lastMove=0;
    Uint32 startMs;
    Uint32 endMs;
    Uint32 delayMs;
    int moveTime = 500; // temps d'attente avant que le snake avance
    int moveTimer = 0;
    direction direction = up;

    // Init
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption("Larakis", NULL); // nom de la fenetre et icone
    zozor = SDL_LoadBMP("../images/test.bmp");
    positionZozor.x = ecran->w / 2 - zozor->w / 2; // On centre Zozor à l'écran
    positionZozor.y = (ecran->h / 2 - zozor->h / 2) - 200;
    SDL_EnableKeyRepeat(10, 10);

    // Game loop
    while (continuer)
    {
        startMs = SDL_GetTicks(); //when the frame starts
       
        // Gestion evenements
        SDL_PollEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP: // Flèche haut 1
                        direction=up;
                        break;
                    case SDLK_DOWN: // Flèche bas 2 
                        direction = down;
                        break;
                    case SDLK_RIGHT: // Flèche droite 3
                        direction=right;
                        break;
                    case SDLK_LEFT: // Flèche gauche 4
                        direction=left;
                        break;
                }
                break;
        }
        
        // Move
        moveTimer += SDL_GetTicks() - lastMove;   
        if (moveTimer >= moveTime) {
            switch(direction) {
                case up: // Flèche haut 1
                    positionZozor.y = positionZozor.y-30;
                    break;
                case down: // Flèche bas 2 
                    positionZozor.y = positionZozor.y+30;
                    break;
                case right: // Flèche droite 3
                    positionZozor.x = positionZozor.x+30;
                    break;
                case left: // Flèche gauche 4
                    positionZozor.x = positionZozor.x-30;
                    break;
            }
            moveTimer = 0 ;
        }
        lastMove = SDL_GetTicks();
        
        // Display
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        SDL_Flip(ecran);

        // FPS management
        endMs = SDL_GetTicks(); //when the frame calculations end
        delayMs = frameMs - (endMs - startMs); //how long to delay
        SDL_Delay(delayMs); //delay processing 
    }

    // End
    SDL_FreeSurface(zozor);
    SDL_Quit();
    return EXIT_SUCCESS;
}
