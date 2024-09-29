#include "State.h"
#include <iostream>
#include <string>
//#include "Puzzle.h"
using namespace std;

int main() {
    int n = 4;

    int **board;
    board = new int*[n];
    for(int i = 0; i < n; i++){
        board[i] = new int[n]; // memoria para cada fila
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
    


    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    State *s = new State(n, nullptr, board);
    State *goal = s->generateGoal();

    cout << "Distancia de s a goal: " << s->manhattan(goal) << endl;
    cout << "Conflicto de s: " << s->conflict(goal) << endl;
    return 0;
    
}