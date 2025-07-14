#ifndef ALL_HPP
# define ALL_HPP

#include <cstring>

#include <iostream>
#include <string>
#include <string.h>
#include <thread>
#include <vector>
enum Piece 
{
    EMPTY = 0,
    WP, WN, WB, WR, WQ, WK,
    BP, BN, BB, BR, BQ, BK
};


std::vector<std::string> generateAllPseudoLegalMoves(Piece board[8][8], bool whiteTurn);
void aiBestMoveThread(Piece board[8][8], bool whiteTurn, std::string& bestMoveOut);
void evaluateBoardThread(Piece board[8][8], int& score);
int evaluateBoard(Piece board[8][8]);
void initBoard(Piece board[8][8]);
void printBoard(Piece board[8][8]);
bool makeMove(Piece board[8][8], const std::string& move);
bool notationToCoords(const std::string& square, int& row, int& col);
bool isLegalMove(Piece board[8][8], std::string move);
#endif