#ifndef ALL_HPP
# define ALL_HPP

#include <iostream>
#include <string>


enum Piece 
{
    EMPTY = 0,
    WP, WN, WB, WR, WQ, WK,
    BP, BN, BB, BR, BQ, BK
};

void initBoard(Piece board[8][8]);
void printBoard(Piece board[8][8]);
bool makeMove(Piece board[8][8], const std::string& move);
bool isLegalMove(Piece board[8][8], int fromRow, int fromCol, int toRow, int toCol);



#endif