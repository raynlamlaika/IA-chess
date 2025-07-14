#include "all.hpp"

int evaluateBoard(Piece board[8][8]) {
    int score = 0;
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece p = board[r][c];
            switch(p) {
                case WP: score += 100; break;
                case WN: score += 320; break;
                case WB: score += 330; break;
                case WR: score += 500; break;
                case WQ: score += 900; break;
                case WK: score += 20000; break;
                case BP: score -= 100; break;
                case BN: score -= 320; break;
                case BB: score -= 330; break;
                case BR: score -= 500; break;
                case BQ: score -= 900; break;
                case BK: score -= 20000; break;
                default: break;
            }
        }
    }
    return score;
}




void evaluateBoardThread(Piece board[8][8], int& score) {
    score = evaluateBoard(board); // this is your existing function
}