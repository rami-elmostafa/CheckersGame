#include <stdio.h>
#include "utility.h"

int main() {
    U64 board[2];
    U64 kings[2];
    InitializeBoard(board, kings);
    PrintBoard(board, kings);

    int currentPlayer = PLAYER1;
    char input[10];

    while (1) {
        printf("Player %d's turn. Enter move (e.g., 'B2 D4'): ", currentPlayer + 1);
        fgets(input, sizeof(input), stdin);

        // Split the input into from and to
        char from[3], to[3];
        sscanf(input, "%2s %2s", from, to);

        if (MovePiece(board, kings, currentPlayer, from, to)) { // Pass kings array
            PrintBoard(board, kings);
            UpdateGameState(board, &currentPlayer); // Use & to pass the address
        } else {
            printf("Invalid move. Try again.\n");
        }
    }

    return 0;
}