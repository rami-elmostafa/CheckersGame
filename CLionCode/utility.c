#include "utility.h"
#include <stdio.h>
#include <string.h>

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

    if (direction == DOWN) {
        if (rowDiff == 1 && (colDiff == -1 || colDiff == 1)) {
            return 1; // Valid move
        }
    } else { // direction == UP
        if (rowDiff == -1 && (colDiff == -1 || colDiff == 1)) {
            return 1; // Valid move
        }
    }

    return 0; // Invalid move
}

// Implement logic to update the game state after each move // Switch turns, check for game-ending conditions, etc.
void UpdateGameState(U64* board, int currentPlayer) {

}

//Removes a piece from the opponent's bitboard when captured. This method updates the opponent's bitboard to reflect the capture.
void CapturePiece(U64* board, int position) {
    board[position] = 0;
}






// Moves a piece from one position to another
void MovePiece(U64* board, int player, const char* from, const char* to) {
    int fromIndex = ConvertInputToIndex(from);
    int toIndex = ConvertInputToIndex(to);

    if (fromIndex == -1 || toIndex == -1) {
        printf("Invalid input\n");
        return;
    }

    if (IsLegalMove(board, player, fromIndex, toIndex)) {
        board[player] = ClearBit(board[player], fromIndex);
        board[player] = SetBit(board[player], toIndex);
    } else {
        printf("Illegal move\n");
    }
}