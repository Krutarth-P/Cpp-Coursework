//
//  gameState.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.

#include "tictactoe.h"
#include "gameState.h"



// Return the clicked row (0..boardSize-1)

int gameState::get_clickedRow() {
    return clickedRow;
}
// Return the clicked column (0..boardSize-1)

int gameState::get_clickedColumn() {
    return clickedColumn;
}

// Set the clicked row to value (0..boardSize-1)
// An invalid value is ignored and no action is taken

void gameState::set_clickedRow(int value) {
    if (value >= 0 && value < 3)
        clickedRow = value;
}

// Set the clicked column (0..boardSize-1)
// An invalid value is ignored and no action is taken

void gameState::set_clickedColumn(int value) {
    if (value >= 0 && value < 3)
        clickedColumn = value;
}

// Get the moveValid value

bool gameState::get_moveValid() {
    return moveValid;
}

// Set the moveValid variable to value

void gameState::set_moveValid(bool value) {
    moveValid = value;
}

// Get the gameOver value

bool gameState::get_gameOver() {
    return gameOver;
}

// Set the gameOver variable to value

void gameState::set_gameOver(bool value) {
    gameOver = value;
}

// Get the winCode

int gameState::get_winCode() {
    return winCode;
}

// Set the winCode to value
// An invalid value is ignored and no action is taken

void gameState::set_winCode(int value) {
    if (value >= 0 && value < 9)
        winCode = value;
}

// Get the value of turn

bool gameState::get_turn() {
    return turn;
}

// Set the value of turn

void gameState::set_turn(bool value) {
    turn = value;
}

// Get the game board value at the board location at row and col
// This method checks that row, col and value are valid and if not it
// returns Empty

int gameState::get_gameBoard(int row, int col) {
    if ((gameBoard[row][col] == -1 || gameBoard[row][col] == 0 || gameBoard[row][col] == 1)&&(row >= 0 && row < 3)&&(col >= 0 && col < 3)) {
        return gameBoard[row][col];
    } else
        return Empty;
}

// Set the game board value at the board location at row and col to value
// This method checks that row, col and value are valid and if not it
// performs no action

void gameState::set_gameBoard(int row, int col, int value) {
    if ((value == -1 || value == 0 || value == 1)&&(row >= 0 && row < 3)&&(col >= 0 && col < 3))
        gameBoard[row][col] = value;
} 