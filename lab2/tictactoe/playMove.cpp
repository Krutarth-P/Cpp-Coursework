//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include "tictactoe.h"
#include "gameState.h"

void playMove(gameState& game_state) {
    int draw = 1; //variable for draw condition
    int currentPlayer = ((game_state.get_turn() == true) ? X : O); //sets the player value to be used in gameBHoard


    if (game_state.get_gameOver() == true) {//dont run if game already over
        return;
    }

    for (int i = 0; i < 3; i++) {//check for draw
        for (int j = 0; j < 3; j++) {
            if (game_state.get_gameBoard(i, j) == Empty)
                draw = 0;
        }
    }

    if (game_state.get_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn()) == Empty) { //checks if a move is valid
        game_state.set_moveValid(true);
    } else {
        game_state.set_moveValid(false);
        return;
    }

    if (game_state.get_moveValid() == true) {//valid move actions

        game_state.set_gameBoard(game_state.get_clickedRow(), game_state.get_clickedColumn(), currentPlayer); //play/place the move

        if (game_state.get_gameBoard(0, 2) == currentPlayer &&
                game_state.get_gameBoard(1, 1) == currentPlayer &&
                game_state.get_gameBoard(2, 0) == currentPlayer) {//diagonal

            game_state.set_gameOver(true);
            game_state.set_winCode(8);

        } else if (game_state.get_gameBoard(0, 0) == currentPlayer &&
                game_state.get_gameBoard(1, 1) == currentPlayer &&
                game_state.get_gameBoard(2, 2) == currentPlayer) {//diagonal

            game_state.set_gameOver(true);
            game_state.set_winCode(7);



        } else if (game_state.get_gameBoard(0, 0) == currentPlayer &&
                game_state.get_gameBoard(1, 0) == currentPlayer &&
                game_state.get_gameBoard(2, 0) == currentPlayer) {//vertical column 0

            game_state.set_gameOver(true);
            game_state.set_winCode(4);

        } else if (game_state.get_gameBoard(0, 1) == currentPlayer &&
                game_state.get_gameBoard(1, 1) == currentPlayer &&
                game_state.get_gameBoard(2, 1) == currentPlayer) {//vertical column 1

            game_state.set_gameOver(true);
            game_state.set_winCode(5);

        } else if (game_state.get_gameBoard(0, 2) == currentPlayer &&
                game_state.get_gameBoard(1, 2) == currentPlayer &&
                game_state.get_gameBoard(2, 2) == currentPlayer) {//vertical column 2

            game_state.set_gameOver(true);
            game_state.set_winCode(6);

        } else if (game_state.get_gameBoard(0, 0) == currentPlayer &&
                game_state.get_gameBoard(0, 1) == currentPlayer &&
                game_state.get_gameBoard(0, 2) == currentPlayer) {//horizontal row 0

            game_state.set_gameOver(true);
            game_state.set_winCode(1);

        } else if (game_state.get_gameBoard(1, 0) == currentPlayer &&
                game_state.get_gameBoard(1, 1) == currentPlayer &&
                game_state.get_gameBoard(1, 2) == currentPlayer) {//horizontal row 1

            game_state.set_gameOver(true);
            game_state.set_winCode(2);

        } else if (game_state.get_gameBoard(2, 0) == currentPlayer &&
                game_state.get_gameBoard(2, 1) == currentPlayer &&
                game_state.get_gameBoard(2, 2) == currentPlayer) {//horizontal row 2

            game_state.set_gameOver(true);
            game_state.set_winCode(3);
            
        } else if (draw == 1) {//game draw condition

            game_state.set_gameOver(true);
            game_state.set_winCode(0);

        } else {//game not over condition

            game_state.set_gameOver(false);
            game_state.set_winCode(0);

        }

        if (game_state.get_turn() == true)
            game_state.set_turn(false);
        else
            game_state.set_turn(true);
    }
    return;
}

