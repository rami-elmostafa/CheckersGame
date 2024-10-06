#ifndef UTILITY_H
#define UTILITY_H

#define U64 unsigned long long

U64 SetBit(U64 value, int position);
U64 ClearBit(U64 value, int position);
void InitializeBoard(U64* board);
void PrintBoard(U64* board);
void MovePiece(U64* board, int player, int from, int to);

#endif // UTILITY_H