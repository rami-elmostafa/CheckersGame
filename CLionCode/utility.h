#ifndef UTILITY_H
#define UTILITY_H

#define U64 unsigned long long
#define PLAYER1 0
#define PLAYER2 1


U64 SetBit(U64 value, int position);
U64 ClearBit(U64 value, int position);
void InitializeBoard(U64* board);
void PrintBoard(U64* board);
int MovePiece(U64* board, int player, const char* from, const char* to);
int IsLegalMove(U64* board,int player, int start, int end);
void UpdateGameState(U64* board, int* currentPlayer);
void CapturePiece(U64* board, int player, int position);

#endif // UTILITY_H