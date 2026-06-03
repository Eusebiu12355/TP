
#include <stdio.h>
#include <stdlib.h>
#include "2048.h"

int board[SIZE][SIZE];
int score = 0;
int highScore = 0;

void loadHighScore() {
    FILE *f = fopen("highscore.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d", &highScore);
        fclose(f);
    }
}

void saveHighScore() {
    FILE *f = fopen("highscore.txt", "w");
    if (f != NULL) {
        fprintf(f, "%d", highScore);
        fclose(f);
    }
}

void addRandom() {
    int empty[SIZE * SIZE][2];
    int count = 0;
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }
    
    if (count > 0) {
        int r = rand() % count;
        board[empty[r][0]][empty[r][1]] = (rand() % 10 == 0) ? 4 : 2;
    }
}

void printBoard() {
}

void rotate() {
    int temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = board[SIZE - 1 - j][i];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = temp[i][j];
        }
    }
}

int moveLeft() {
    int moved = 0;
    
    for (int i = 0; i < SIZE; i++) {
        int pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                if (j != pos) {
                    board[i][pos] = board[i][j];
                    board[i][j] = 0;
                    moved = 1;
                }
                pos++;
            }
        }
        
        for (int j = 0; j < SIZE - 1; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][j + 1] = 0;
                moved = 1;
            }
        }
        
        pos = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                if (j != pos) {
                    board[i][pos] = board[i][j];
                    board[i][j] = 0;
                }
                pos++;
            }
        }
    }
    return moved;
}

int move(char direction) {
    int moved = 0;
    int rotations = 0;
    
    if (direction == 'a') rotations = 0;
    else if (direction == 's') rotations = 1;
    else if (direction == 'd') rotations = 2;
    else if (direction == 'w') rotations = 3;
    else return 0;

    for (int i = 0; i < rotations; i++) rotate();
    moved = moveLeft();
    for (int i = 0; i < (4 - rotations) % 4; i++) rotate();
    
    return moved;
}

int checkWin() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2048) return 1;
        }
    }
    return 0;
}

int checkGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 0;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return 0;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return 0;
        }
    }
    return 1;
}