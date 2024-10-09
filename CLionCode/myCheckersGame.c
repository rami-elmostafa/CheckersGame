#include <stdio.h>
#include "utility.h"

int main() {
    U64 board[2];
    InitializeBoard(board);
    PrintBoard(board);

    int currentPlayer = PLAYER1; // Start with Player 1
    char from[3], to[3]; // For storing user input

    while (1) {
        printf("\nPlayer %d's turn. Enter move (e.g., 'B2 B3'): ", currentPlayer + 1);
        scanf("%2s %2s", from, to); // Read two inputs for from and to positions

        if (MovePiece(board, currentPlayer, from, to)) {
            PrintBoard(board); // Print the board after the move
            UpdateGameState(board, &currentPlayer); // Update game state and switch players
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    return 0;
}