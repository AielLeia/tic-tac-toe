#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "game.h"
#include "event_manager.h"
#include "render_manager.h" 

int main ( int argc, char *argv[] ) {
    // Initialization of SDL's video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to load the sdl video subsystem: %s", SDL_GetError());
        exit( EXIT_FAILURE );
    }

    // Creation of the game window
    SDL_Window *game_win = SDL_CreateWindow(
        "Tic Tac Tao",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_W,
        SCREEN_H,
        SDL_WINDOW_SHOWN
    );
    if (game_win == NULL) {
        SDL_Log( "Failed to create the main game window: %s", SDL_GetError() );
        SDL_Quit();
        exit( EXIT_FAILURE );
    }

    // Creation of the main rendering of the game
    SDL_Renderer *game_ren = SDL_CreateRenderer(
        game_win,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (game_ren == NULL) {
        SDL_Log( "Failed to create the rendering of the game: %s", SDL_GetError() );
        SDL_DestroyWindow(game_win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    // Event struct
    SDL_Event e;
    QuitState quit = {FALSE};

    // Game
    Game game = {
        .board = {
            EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
            EMPTY_CELL, EMPTY_CELL, EMPTY_CELL,
            EMPTY_CELL, EMPTY_CELL, EMPTY_CELL
        },
        .state = TIE,
        .playerTurn = PLAYER_X_TURN
    };

    // Loop game
    while (!quit.quitState) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit.quitState = TRUE;
                break;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                on_clicked(
                    &game,
                    e.button.y / CELL_H,
                    e.button.x / CELL_W
                );
            }
        }
        SDL_SetRenderDrawColor(game_ren, 0, 0, 0, 255);
        SDL_RenderClear(game_ren);
        render( game_ren, &game );
        SDL_RenderPresent(game_ren);
    }

    SDL_DestroyRenderer(game_ren);
    SDL_DestroyWindow(game_win);
    SDL_Quit();
    return EXIT_SUCCESS;
}