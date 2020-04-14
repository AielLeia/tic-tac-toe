#include <stdio.h>

#include "game.h"
#include "event_manager.h"

int check_player_won ( Game *game, StateBoard player ) {
    int row_count = 0;
    int column_count = 0;
    int dialo1_count = 0;
    int dialo2_count = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (game->board[i * N + j] == player) row_count++;
            if (game->board[j * N + i] == player) column_count++;
        }
        
        if (row_count >= N || column_count >= N) return TRUE;
        row_count = 0;
        column_count = 0;

        if (game->board[i * N + i] == player) dialo1_count++;
        if (game->board[i * N + N - i - 1] == player) dialo2_count++;
    }

    return dialo1_count >= N || dialo2_count >= N;
}

int count_cell(Game *game, StateBoard cell) {
    int counter = 0;
    for (int i = 0; i < N * N; i++) {
        if (game->board[i] == cell) counter++;
    }
    return counter;
}

void game_condition ( Game *game ) {
    if (check_player_won(game, PLAYER_X)) {
        game->state = PLAYER_X_WON;
    } else if (check_player_won(game, PLAYER_O)) {
        game->state = PLAYER_O_WON;
    } else if (count_cell(game, EMPTY_CELL) == 0) {
        game->state = TIE;
    }
}

void player_turn ( Game *game, int row, int column) {
    if (game->board[row * N + column] == EMPTY_CELL && game->playerTurn == PLAYER_X_TURN) {
        game->board[row * N + column] = PLAYER_X;
        game->playerTurn = PLAYER_O_TURN;
        game_condition(game);
    } else if (game->board[row * N + column] == EMPTY_CELL && game->playerTurn == PLAYER_O_TURN) {
        game->board[row * N + column] = PLAYER_O;
        game->playerTurn = PLAYER_X_TURN;
        game_condition(game);
    }
}

void reset_game(Game *game) {
    game->state = RUNNING;
    game->playerTurn = PLAYER_X_TURN;
    for (int i = 0; i < N * N; i++) {
        game->board[i] = EMPTY_CELL;
    }
}

void on_clicked(Game *game, int row, int column) {
    if (game->state == RUNNING) {
        player_turn(game, row, column);
    } else {
        reset_game(game);
    }
}
