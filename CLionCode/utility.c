#include "utility.h"
#include <stdio.h>

U64 SetBit(U64 value, int position) {
    return value | (1ULL << position);
}

U64 ClearBit(U64 value, int position) {
    return value & ~(1ULL << position);
}

// Initializes the board with pieces
void InitializeBoard(U64* board) {
    board[0] = 0ULL; // Player 1
    board[1] = 0ULL; // Player 2
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                board[0] = SetBit(board[0], (i * 8 + j)); // Player 1
            }
        }
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                board[1] = SetBit(board[1], (i * 8 + j)); // Player 2
            }
        }
    }
}

// Prints the current state of the board
void PrintBoard(U64* board){
    printf("  0 1 2 3 4 5 6 7\n"); // Column headers
    for (int i = 0; i < 8; i++) {
        printf("%d ", i); // Row headers
        for (int j = 0; j < 8; j++) {
            int isRed = board[0] & (1ULL << (i * 8 + j)) ? 1 : 0;
            int isBlack = board[1] & (1ULL << (i * 8 + j)) ? 1 : 0;

            if (isRed) {
                printf("R ");  // Print Red for player 1
            } else if (isBlack) {
                printf("B ");  // Print Black for player 2
            } else {
                printf(". ");  // Print '.' for empty spaces
            }
        }
        printf("\n"); // New line after each row
    }
}

// Moves a piece from one position to another
void MovePiece(U64* board, int player, int from, int to) {
    board[player] = ClearBit(board[player], from);
    board[player] = SetBit(board[player], to);

}