#ifndef _GAME_H_
#define _GAME_H_

#define N           3

#define SCREEN_W    640
#define SCREEN_H    480

#define CELL_W      ((SCREEN_W) / (N))
#define CELL_H      ((SCREEN_H) / (N))

#define TRUE        1
#define FALSE       0

typedef enum _PlayerTurn {
    PLAYER_X_TURN, PLAYER_O_TURN
} PlayerTurn;

typedef struct _QuitState {
    unsigned quitState:1;
} QuitState;

typedef enum _StateBoard {
    PLAYER_X, PLAYER_O, EMPTY_CELL
} StateBoard;

typedef enum _StateGame {
    RUNNING, PLAYER_X_WON, PLAYER_O_WON, TIE
} StateGame;

typedef struct _Game {
    StateBoard  board[N * N];
    StateGame   state;
    PlayerTurn  playerTurn;
} Game;

#endif