// 2048.h
#ifndef GAME_H
#define GAME_H

#define SIZE 4

extern int board[SIZE][SIZE];
extern int score;
extern int highScore;

void loadHighScore();
void saveHighScore();
void addRandom();
void printBoard();
int move(char direction);
int checkWin();
int checkGameOver();

#endif