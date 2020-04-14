#include "game.h"
#include "render_manager.h"

#include <math.h>
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"

const SDL_Color RUNNING_COLOR       = { .r = 255, .g = 255, .b = 255, .a = 255 };
const SDL_Color PLAYER_X_COLOR      = { .r = 255, .g = 50,  .b = 50,  .a = 255 };
const SDL_Color PLAYER_O_COLOR      = { .r = 50,  .g = 50,  .b = 255, .a = 255 };
const SDL_Color TIE_COLOR           = { .r = 150, .g = 150, .b = 150, .a = 255 };

void render_grid ( SDL_Renderer *renderer, const SDL_Color *color ) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

    for ( int i = 1; i < N; i++ ) {
        //  Vertical line
        SDL_RenderDrawLine(
            renderer,
            i * CELL_W, 0,
            i * CELL_W, SCREEN_H
        );

        // Horizontal line
        SDL_RenderDrawLine(
            renderer,
            0,        i * CELL_H,
            SCREEN_W, i * CELL_H
        );
    }
}

void render_o (SDL_Renderer *renderer, const int row, const int column, const SDL_Color *color) {
    const float half_box_side = fmin(CELL_W, CELL_H) * 0.25;
    const float center_x = CELL_W * 0.5 + column * CELL_W;
    const float center_y = CELL_H * 0.5 + row * CELL_H;

    filledCircleRGBA(
        renderer,
        center_x,
        center_y,
        half_box_side + 5,
        color->r,
        color->g,
        color->b,
        color->a
    );

    filledCircleRGBA(
        renderer,
        center_x,
        center_y,
        half_box_side - 5,
        0,
        0,
        0,
        255
    );
}

void render_x (SDL_Renderer *renderer, const int row, const int column, const SDL_Color *color) {
    const float half_box_side = fmin(CELL_W, CELL_H) * 0.25;
    const float center_x = CELL_W * 0.5 + column * CELL_W;
    const float center_y = CELL_H * 0.5 + row * CELL_H;
    thickLineRGBA(
        renderer,
        center_x - half_box_side,
        center_y - half_box_side,
        center_x + half_box_side,
        center_y + half_box_side,
        10,
        color->r, color->g, color->b, color->a
    );
     thickLineRGBA(
        renderer,
        center_x + half_box_side,
        center_y - half_box_side,
        center_x - half_box_side,
        center_y + half_box_side,
        10,
        color->r, color->g, color->b, color->a
    );
}

void render_board ( SDL_Renderer *renderer, const StateBoard *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            switch (board[i * N + j]) {
                case PLAYER_X:
                    render_x(renderer, i, j, player_x_color);
                    break;
                case PLAYER_O:
                    render_o(renderer, i, j, player_o_color);
                    break;
                default:
                    break;
            }
        }
    }
}

void running_state ( SDL_Renderer *renderer, const Game *game ) {
    render_grid( renderer, &RUNNING_COLOR );
    render_board(
        renderer,
        game->board,
        &PLAYER_X_COLOR,
        &PLAYER_O_COLOR
    );
} 

void game_end ( SDL_Renderer *renderer, const Game *game, const SDL_Color *color ) {
    render_grid( renderer, color );
    render_board(
        renderer,
        game->board,
        color,
        color
    );
} 


void render( SDL_Renderer *renderer, const Game *game ) {
    switch (game->state) {
        case RUNNING:
            running_state(renderer, game);
            break;
        case PLAYER_X_WON:
            game_end(renderer, game, &PLAYER_X_COLOR);
            break;
        case PLAYER_O_WON:
            game_end(renderer, game, &PLAYER_O_COLOR);
            break;
        case TIE:
            game_end(renderer, game, &TIE_COLOR);
            break;
        default:
            break;
    }
}   

