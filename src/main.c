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
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "gui.h"
#include "constants.h"

SDL_Surface *screen;
SDL_Event event;
TTF_Font *police;
SDL_Surface* menu;
SDL_Surface *instruction;
SDL_Color yellow = {249, 240, 57}, white = {255, 255, 255};

/**
 * \fn BoardSize optionAction(SDL_Surface* screen, SDL_Surface* menu)
 * \brief Display the option menu
 * \details Display the option menu where you can choose between 3 size of board
 * \param screen The screen to draw on
 * \param menu The menu background surface
 * \return BoardSize The selected size
 */
BoardSize optionAction(SDL_Surface* screen, SDL_Surface* menu) {

    Title* titles = malloc(3*sizeof(Title));
    titles[0] =  guiCreateTitle(200, 250, PLAY, "SMALL", white, police);
    titles[1] =  guiCreateTitle(180, 330, INSTRUCTION, "MEDIUM", white, police);
    titles[2] =  guiCreateTitle(200, 410, OPTION, "LARGE", white, police);
    Title title;
    int state = 0;
    while (true)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return MEDIUM;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        state--;
                        break;
                    case SDLK_DOWN:
                        state++;
                        break;
                    case SDLK_RETURN:
                        title = guiGetSelectedItem(titles, 4);
                        switch (title->value) {
                            case PLAY:
                                return SMALL;
                                break;

                            case INSTRUCTION:
                                return MEDIUM;
                                break;

                            case OPTION:
                                return LARGE;
                                break;
                            default:
                                break;
                        }
                        break;

                    default:
                        break;
                }
                break;
        }

        //screen = SDL_SetVideoMode(MENU_SIZE_X, MENU_SIZE_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
        guiApplySurface(0, 0, menu, screen, NULL);

        guiSetSelectedTitle(titles, 3, state);
        guiDrawTitles(screen, titles, 3, yellow);

        SDL_Flip(screen);
    }
}



/**
 * \fn void instructionAction(SDL_Surface* screen, SDL_Surface* menu)
 * \brief Display the insctruction menu
 * \details Display the option menu where you can read insctructions
 * \param screen The screen to draw on
 * \param menu The menu background surface
 */
void instructionAction(SDL_Surface* screen, SDL_Surface* menu) {

    bool inWhile = true;
    while (inWhile)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                inWhile = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_RETURN:
                        inWhile = false;
                        break;
                    default:
                        break;
                }
                break;
        }
        guiApplySurface(0, 0, menu, screen, NULL);
        SDL_Flip(screen);
    }
}



/**
 * \fn int main(int argc, char *argv[])
 * \brief Display the main menu
 * \details Display the main menu where you can play, choose option or quit
 */
int main(int argc, char *argv[])
{
    BoardSize boardSize = MEDIUM;
    int continuer = 1;
    int idWinner;
    //char *titles[4] = {"JOUER", "HIGHSCORE", "OPTION", "QUITTER"};

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    screen = SDL_SetVideoMode(MENU_SIZE_X, MENU_SIZE_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption("Larasnake", NULL);
    police = TTF_OpenFont("./images/font/Black-Ops-2-Font-Julethekiller.ttf", MENU_POLICE_SIZE);
    menu = guiLoadImage("./images/gui/menu.png");
    instruction = guiLoadImage("./images/gui/instructions.png");

    /************************/
   /**      SOUND PART    **/
  /************************/

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialization of the Mixer API
    {
       printf("%s", Mix_GetError());
    }
    Mix_Music *musiqueMenu = Mix_LoadMUS("./sound/musiqueMenu.mp3"); //music of the game
    Mix_PlayMusic(musiqueMenu, -1); //loop music
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2); //half of the maximum sound


    /************************/
   /**                    **/
  /************************/
    Title* titles = malloc(4*sizeof(Title));
    titles[0] =  guiCreateTitle(200, 190, PLAY, "JOUER", white, police);
    titles[1] =  guiCreateTitle(100, 270, INSTRUCTION, "INSTRUCTION", white, police);
    titles[2] =  guiCreateTitle(190, 350, OPTION, "OPTION", white, police);
    titles[3] =  guiCreateTitle(180, 500, QUIT, "QUITTER", white, police);

    Title title;
    int state = 0;
    while (continuer)
    {
        if(!Mix_PlayingMusic())
        {
           Mix_PlayMusic(musiqueMenu, -1); //loop music only if it doesn't already loop
        }

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        state--;
                        break;
                    case SDLK_DOWN:
                        state++;
                        break;
                    case SDLK_RETURN:
                        title = guiGetSelectedItem(titles, 4);
                        switch (title->value) {
                            case PLAY:
                                idWinner = guiPlay(boardSize);
                                guiEndScreen(screen, boardSize, &event, idWinner);
                                break;

                            case INSTRUCTION:
                                instructionAction(screen, instruction);
                                break;

                            case OPTION:
                                boardSize = optionAction(screen, menu);
                                break;

                            case QUIT:
                                continuer = 0;
                                break;
                        }
                        break;

                    default:
                        break;
                }
                break;
        }

        screen = SDL_SetVideoMode(MENU_SIZE_X, MENU_SIZE_Y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
        guiApplySurface(0, 0, menu, screen, NULL);

        guiSetSelectedTitle(titles, 4, state);
        guiDrawTitles(screen, titles, 4, yellow);

        SDL_Flip(screen);
    }

    TTF_CloseFont(police);
    TTF_Quit();
    Mix_FreeMusic(musiqueMenu); //free the musicMenu
    Mix_CloseAudio(); // close audio
    //SDL_FreeSurface(texte);
    SDL_Quit();

    return EXIT_SUCCESS;
}
