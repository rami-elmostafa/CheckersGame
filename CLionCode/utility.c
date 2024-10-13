#include "utility.h"

#include <stdlib.h> // For exit
#include <stdio.h>
#include <string.h>

U64 board[2];     // Standard pieces
U64 kings[2];     // King pieces

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
void InitializeBoard(U64* board, U64* kings) {
    // Initialize the regular pieces
    board[PLAYER1] = 0ULL; // Player 1
    board[PLAYER2] = 0ULL; // Player 2
    // Initialize the king pieces
    kings[PLAYER1] = 0ULL;
    kings[PLAYER2] = 0ULL;
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
// Prints the current state of the board
void PrintBoard(U64* board, U64* kings) {
    for (int i = 0; i < 8; i++) {
        printf("%d ", i); // Row headers
        for (int j = 0; j < 8; j++) {
            int index = i * 8 + j;
            if (board[PLAYER1] & (1ULL << index)) {
                // If it's a king piece
                if (kings[PLAYER1] & (1ULL << index)) {
                    printf("R^ ");  // King piece for player 1
                } else {
                    printf("R ");   // Regular piece for player 1
                }
            } else if (board[PLAYER2] & (1ULL << index)) {
                // If it's a king piece
                if (kings[PLAYER2] & (1ULL << index)) {
                    printf("B^ ");  // King piece for player 2
                } else {
                    printf("B ");   // Regular piece for player 2
                }
            } else {
                printf(". ");  // Print '.' for empty spaces
            }
        }
        printf("\n"); // New line after each row
    }
    printf("  A B C D E F G H\n"); // Column headers
}


// Checks if the move is diagonal and valid
// Checks if the move is diagonal and valid
int IsLegalMove(U64* board, U64* kings, int player, int start, int end) {
    // Basic move validation
    if (end < 0 || end >= 64 || start < 0 || start >= 64) {
        return 0; // Out of bounds
    }

    // Check if the starting position has a piece (regular or king)
    if (!(board[player] & (1ULL << start)) && !(kings[player] & (1ULL << start))) {
        return 0; // No piece at the start
    }

    // Check if the end position is empty
    if (board[PLAYER1] & (1ULL << end) || board[PLAYER2] & (1ULL << end)) {
        return 0; // End position is not empty
    }

    // Calculate row and column differences
    int rowDiff = (end / 8) - (start / 8);
    int colDiff = (end % 8) - (start % 8);

    // Regular move for regular pieces
    if ((player == PLAYER1 && rowDiff == 1 && (colDiff == -1 || colDiff == 1)) || // Down moves
        (player == PLAYER2 && rowDiff == -1 && (colDiff == -1 || colDiff == 1))) { // Up moves
        return 1; // Valid move for regular pieces
    }

    // Moves for kings (both directions)
    if (abs(rowDiff) == 1 && (colDiff == -1 || colDiff == 1)) {
        return 1; // Valid diagonal move for kings
    }

    // Capture move for regular pieces
    if ((player == PLAYER1 && rowDiff == 2 && (colDiff == -2 || colDiff == 2)) ||
        (player == PLAYER2 && rowDiff == -2 && (colDiff == -2 || colDiff == 2))) {
        int middle = start + (rowDiff / 2) * 8 + (colDiff / 2);
        if ((board[PLAYER1] & (1ULL << middle)) || (board[PLAYER2] & (1ULL << middle))) {
            return 1; // Valid capturing move
        }
    }

    // Capture move for kings
    if (abs(rowDiff) == 2 && (colDiff == -2 || colDiff == 2)) {
        int middle = start + (rowDiff / 2) * 8 + (colDiff / 2);
        if ((board[PLAYER1] & (1ULL << middle)) || (board[PLAYER2] & (1ULL << middle))) {
            return 1; // Valid capturing move for kings
        }
    }

    // Additional capture logic for kings (one square ahead or behind)
    if (abs(rowDiff) == 1 && abs(colDiff) == 0) {
        int middle = start + (rowDiff * 8);
        if ((player == PLAYER1 && (board[PLAYER2] & (1ULL << middle))) ||
            (player == PLAYER2 && (board[PLAYER1] & (1ULL << middle)))) {
            return 1; // Valid capture for kings (forward or backward)
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
void CapturePiece(U64* board,int player, int position) {
    // Logic to capture a piece
    board[PLAYER1] = ClearBit(board[PLAYER1], position);
    board[PLAYER2] = ClearBit(board[PLAYER2], position);
}

// Moves a piece from one position to another
int MovePiece(U64* board, U64* kings, int player, const char* from, const char* to) {
    int fromIndex = ConvertInputToIndex(from);
    int toIndex = ConvertInputToIndex(to);

    // Check for invalid input
    if (fromIndex == -1 || toIndex == -1) {
        printf("Invalid input\n");
        return 0; // Indicate failure
    }

    // Check if the move is legal
    if (!IsLegalMove(board, kings, player, fromIndex, toIndex)) {
        printf("Illegal move\n");
        return 0; // Indicate failure
    }

    // Move the piece
    board[player] = ClearBit(board[player], fromIndex);
    board[player] = SetBit(board[player], toIndex);

    // Check for capturing
    int middle = (fromIndex + toIndex) / 2;
    if (player == PLAYER1 && (middle >= 8 && (board[PLAYER2] & (1ULL << middle)))) {
        CapturePiece(board, PLAYER2, middle);
    } else if (player == PLAYER2 && (middle < 56 && (board[PLAYER1] & (1ULL << middle)))) {
        CapturePiece(board, PLAYER1, middle);
    }

    // Check for king promotion
    if ((player == PLAYER1 && toIndex >= 56) || (player == PLAYER2 && toIndex < 8)) {
        PromoteToKing(board, kings, player, toIndex);
    }

    printf("Moved from %s to %s.", from, to);

    return 1; // Indicate success
}
void PromoteToKing(U64* board, U64* kings, int player, int position) {
    if (player == PLAYER1 && position >= 56) { // Rows 0-7 for Player 1
        kings[PLAYER1] = SetBit(kings[PLAYER1], position);
        // No need to clear the regular piece from the board
    } else if (player == PLAYER2 && position < 8) { // Rows 56-63 for Player 2
        kings[PLAYER2] = SetBit(kings[PLAYER2], position);
        // No need to clear the regular piece from the board
    }
    printf("Promoting piece at position %d for Player %d\n", position, player + 1);
}