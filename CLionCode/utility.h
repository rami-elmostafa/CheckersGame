#ifndef UTILITY_H
#define UTILITY_H

#define U64 unsigned long long
#define PLAYER1 0
#define PLAYER2 1
#define KING_MASK 0x8000000000000000 // Example bit for king representation


U64 SetBit(U64 value, int position);
U64 ClearBit(U64 value, int position);
void InitializeBoard(U64* board, U64* kings);
void PrintBoard(U64* board, U64* kings);
int MovePiece(U64* board, U64* kings,int player, const char* from, const char* to);
int IsLegalMove(U64* board,int player, int start, int end);
void UpdateGameState(U64* board, int* currentPlayer);
void CapturePiece(U64* board,int player, int position);

void PromoteToKing(U64* board,U64* kings, int player, int position);

#endif // UTILITY_H