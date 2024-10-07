#include <stdio.h>
#include "utility.h"

int main() {
    U64 board[2];
    InitializeBoard(board);
    PrintBoard(board);

    printf("\nAttempting to move player 1's piece from B2 to A3...\n");
    MovePiece(board, 0, "B2", "B3");


    PrintBoard(board);
    return 0;
}