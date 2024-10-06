#include <stdio.h>
#include "utility.h"

int main() {
    U64 board[2];
    InitializeBoard(board);
    PrintBoard(board);

    printf("\nAttempting to move player 1's piece from 9 to 10...\n");
    MovePiece(board, 0, 2, 25);


    PrintBoard(board);
    return 0;
}