#include "Puzzle.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

int main() {

    int n = 4;
    int **board = new int*[n];
    for(int i = 0; i < n; i++){
        board[i] = new int[n];
    }
    board[0][0] = 15;
    board[0][1] = 14;
    board[0][2] = 8;
    board[0][3] = 12;
    board[1][0] = 10;
    board[1][1] = 11;
    board[1][2] = 9;
    board[1][3] = 13;
    board[2][0] = 2;
    board[2][1] = 6;
    board[2][2] = 5;
    board[2][3] = 1;
    board[3][0] = 3;
    board[3][1] = 7;
    board[3][2] = 4;
    board[3][3] = 0;

    State *state = new State(n, nullptr, board);
    State *goal = state->generateGoal();

    Puzzle *p = new Puzzle(state, goal);


    p->solve();
    
    return 0;
}