#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int board[SIZE][SIZE];

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
    system("clear");
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf(".    ");
            } else {
                printf("%-4d ", board[i][j]);
            }
        }
        printf("\n\n");
    }
}

void rotate() {
    int temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = board[SIZE - j - 1][i];
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

int main() {
    char input;
    
    srand(time(NULL));
    
    addRandom();
    addRandom();

    while (1) {
        printBoard();
        
        printf("Mutari: w a s d | Iesire: q\n");
        scanf(" %c", &input);
        
        if (input == 'q') break;
        
        if (move(input)) {
            addRandom();
        }
    }
    return 0;
}