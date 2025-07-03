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
bool notationToCoords(const std::string& square, int& row, int& col);
bool isLegalMove(Piece board[8][8], std::string move);
#endif