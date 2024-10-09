#include "utility.h"

#include <stdlib.h> // For exit
#include <stdio.h>
#include <string.h>

#define ABS(x) ((x) < 0 ? -(x) : (x)) // Macro for absolute value
#define PLAYER1 0
#define PLAYER2 1

typedef enum { UP = -1, DOWN = 1 } Direction;

U64 SetBit(U64 value, int position) {
    return value | (1ULL << position);
}

U64 ClearBit(U64 value, int position) {
    return value & ~(1ULL << position);
}

// Initializes the board with pieces
void InitializeBoard(U64* board) {
    board[PLAYER1] = 0ULL; // Player 1
    board[PLAYER2] = 0ULL; // Player 2
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                board[PLAYER1] = SetBit(board[PLAYER1], (i * 8 + j)); // Player 1
            }
        }
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                board[PLAYER2] = SetBit(board[PLAYER2], (i * 8 + j)); // Player 2
            }
        }
    }
}

// Converts a column-row notation (e.g., "A0") to an index
int ConvertInputToIndex(const char* input) {
    if (strlen(input) != 2) return -1; // Invalid input length
    int column = input[0] - 'A'; // Convert 'A' to 0, 'B' to 1, etc.
    int row = input[1] - '0';     // Convert '0' to 0, '1' to 1, etc.

    if (column < 0 || column >= 8 || row < 0 || row >= 8) {
        return -1; // Out of bounds
    }
    return row * 8 + column; // Convert to bitboard index
}

// Prints the current state of the board
void PrintBoard(U64* board) {
    for (int i = 0; i < 8; i++) {
        printf("%d ", i); // Row headers
        for (int j = 0; j < 8; j++) {
            if (board[PLAYER1] & (1ULL << (i * 8 + j))) {
                printf("R ");  // Print Red for player 1
            } else if (board[PLAYER2] & (1ULL << (i * 8 + j))) {
                printf("B ");  // Print Black for player 2
            } else {
                printf(". ");  // Print '.' for empty spaces
            }
        }
        printf("\n"); // New line after each row
    }
    printf("  A B C D E F G H\n"); // Column headers
}

// Checks if the move is diagonal and valid
int IsLegalMove(U64* board, int player, int start, int end) {
    Direction direction = (player == PLAYER1) ? DOWN : UP; // Player 1 moves down, Player 2 moves up

    // Basic move validation
    if (end < 0 || end >= 64 || start < 0 || start >= 64) {
        return 0; // Out of bounds
    }

    // Check if the starting position has a piece
    if (!(board[player] & (1ULL << start))) {
        return 0; // No piece at the start
    }

    // Check if the end position is empty
    if (board[PLAYER1] & (1ULL << end) || board[PLAYER2] & (1ULL << end)) {
        return 0; // End position is not empty
    }

    // Check if moving diagonally (valid diagonal moves for checkers)
    int rowDiff = (end / 8) - (start / 8);
    int colDiff = (end % 8) - (start % 8);

    // Regular move
    if (direction == DOWN && rowDiff == 1 && (colDiff == -1 || colDiff == 1)) {
        return 1; // Valid move down
    } else if (direction == UP && rowDiff == -1 && (colDiff == -1 || colDiff == 1)) {
        return 1; // Valid move up
    }

    // Capture move
    if (direction == DOWN && rowDiff == 2 && (colDiff == -2 || colDiff == 2)) {
        int middle = start + (rowDiff / 2) * 8 + (colDiff / 2);
        if ((board[PLAYER1] & (1ULL << middle)) || (board[PLAYER2] & (1ULL << middle))) {
            return 1; // Valid capturing move
        }
    } else if (direction == UP && rowDiff == -2 && (colDiff == -2 || colDiff == 2)) {
        int middle = start + (rowDiff / 2) * 8 + (colDiff / 2);
        if ((board[PLAYER1] & (1ULL << middle)) || (board[PLAYER2] & (1ULL << middle))) {
            return 1; // Valid capturing move
        }
    }

    return 0; // Invalid move
}

// Logic to update the game state after each move
void UpdateGameState(U64* board, int* currentPlayer) {
    // Check for win conditions
    int player1Pieces = __builtin_popcountll(board[PLAYER1]); // Count pieces for Player 1
    int player2Pieces = __builtin_popcountll(board[PLAYER2]); // Count pieces for Player 2

    if (player1Pieces == 0) {
        printf("Player 2 wins!\n");
        exit(0); // Exit the game
    }
    if (player2Pieces == 0) {
        printf("Player 1 wins!\n");
        exit(0); // Exit the game
    }

    // Switch turns
    *currentPlayer = (*currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
}

// Removes a piece from the opponent's bitboard when captured
void CapturePiece(U64* board, int position) {
    // Logic to capture a piece
    board[PLAYER1] = ClearBit(board[PLAYER1], position);
    board[PLAYER2] = ClearBit(board[PLAYER2], position);
}

// Moves a piece from one position to another
int MovePiece(U64* board, int player, const char* from, const char* to) {
    int fromIndex = ConvertInputToIndex(from);
    int toIndex = ConvertInputToIndex(to);

    if (fromIndex == -1 || toIndex == -1) {
        printf("Invalid input\n");
        return 0; // Indicate failure
    }

    if (IsLegalMove(board, player, fromIndex, toIndex)) {
        // If capturing, remove the opponent's piece
        int middle = (fromIndex + toIndex) / 2; // Calculate the position of the captured piece
        if ((player == PLAYER1 && (board[PLAYER2] & (1ULL << middle))) ||
            (player == PLAYER2 && (board[PLAYER1] & (1ULL << middle)))) {
            CapturePiece(board, middle); // Capture the piece
            }

        board[player] = ClearBit(board[player], fromIndex);
        board[player] = SetBit(board[player], toIndex);
        return 1; // Indicate success
    } else {
        printf("Illegal move\n");
        return 0; // Indicate failure
    }
}