#include "all.hpp"



// ----------------- Utilities -----------------

bool isInside(int r, int c) {
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}

bool isEnemy(Piece p, bool whiteTurn) {
    if (p == EMPTY) return false;
    bool isWhite = (p >= WP && p <= WK);
    return isWhite != whiteTurn;
}

std::string toMoveString(int fromRow, int fromCol, int toRow, int toCol) {
    return std::string(1, 'a' + fromCol) + std::to_string(fromRow + 1) +
           std::string(1, 'a' + toCol) + std::to_string(toRow + 1);
}

// ----------------- Pawn -----------------

void generatePawnMoves(Piece board[8][8], int row, int col, std::vector<std::string>& moves) {
    bool white = (board[row][col] == WP);
    int dir = white ? 1 : -1;
    int startRow = white ? 1 : 6;

    // Forward move
    if (isInside(row + dir, col) && board[row + dir][col] == EMPTY)
        moves.push_back(toMoveString(row, col, row + dir, col));

    // Double move from starting row
    if (row == startRow &&
        board[row + dir][col] == EMPTY &&
        board[row + 2 * dir][col] == EMPTY)
        moves.push_back(toMoveString(row, col, row + 2 * dir, col));

    // Captures
    for (int dc : {-1, 1}) {
        int c = col + dc;
        if (isInside(row + dir, c) && isEnemy(board[row + dir][c], white))
            moves.push_back(toMoveString(row, col, row + dir, c));
    }
}

// ----------------- Knight -----------------

void generateKnightMoves(Piece board[8][8], int row, int col, std::vector<std::string>& moves) {
    static const int dr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    static const int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    bool white = (board[row][col] >= WP && board[row][col] <= WK);

    for (int i = 0; i < 8; ++i) {
        int r = row + dr[i], c = col + dc[i];
        if (isInside(r, c) && (board[r][c] == EMPTY || isEnemy(board[r][c], white)))
            moves.push_back(toMoveString(row, col, r, c));
    }
}

// ----------------- King -----------------

void generateKingMoves(Piece board[8][8], int row, int col, std::vector<std::string>& moves) {
    static const int dr[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    static const int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    bool white = (board[row][col] >= WP && board[row][col] <= WK);

    for (int i = 0; i < 8; ++i) {
        int r = row + dr[i], c = col + dc[i];
        if (isInside(r, c) && (board[r][c] == EMPTY || isEnemy(board[r][c], white)))
            moves.push_back(toMoveString(row, col, r, c));
    }
}

// ----------------- Rook -----------------

void generateRookMoves(Piece board[8][8], int row, int col, std::vector<std::string>& moves) {
    static const int dr[4] = {1, -1, 0, 0};
    static const int dc[4] = {0, 0, 1, -1};
    bool white = (board[row][col] >= WP && board[row][col] <= WK);

    for (int d = 0; d < 4; ++d) {
        int r = row, c = col;
        while (true) {
            r += dr[d]; c += dc[d];
            if (!isInside(r, c)) break;
            if (board[r][c] == EMPTY)
                moves.push_back(toMoveString(row, col, r, c));
            else {
                if (isEnemy(board[r][c], white))
                    moves.push_back(toMoveString(row, col, r, c));
                break;
            }
        }
    }
}

// ----------------- Bishop -----------------

void generateBishopMoves(Piece board[8][8], int row, int col, std::vector<std::string>& moves) {
    static const int dr[4] = {1, 1, -1, -1};
    static const int dc[4] = {1, -1, 1, -1};
    bool white = (board[row][col] >= WP && board[row][col] <= WK);

    for (int d = 0; d < 4; ++d) {
        int r = row, c = col;
        while (true) {
            r += dr[d]; c += dc[d];
            if (!isInside(r, c)) break;
            if (board[r][c] == EMPTY)
                moves.push_back(toMoveString(row, col, r, c));
            else {
                if (isEnemy(board[r][c], white))
                    moves.push_back(toMoveString(row, col, r, c));
                break;
            }
        }
    }
}

// ----------------- Queen -----------------

void generateQueenMoves(Piece board[8][8], int row, int col, std::vector<std::string>& moves) {
    generateRookMoves(board, row, col, moves);
    generateBishopMoves(board, row, col, moves);
}

// ----------------- Master Function -----------------

std::vector<std::string> generateAllPseudoLegalMoves(Piece board[8][8], bool whiteTurn) {
    std::vector<std::string> moves;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece p = board[row][col];

            if (p == EMPTY) continue;
            bool isWhite = (p >= WP && p <= WK);
            if (isWhite != whiteTurn) continue;

            switch (p) {
                case WP: case BP:
                    generatePawnMoves(board, row, col, moves);
                    break;
                case WN: case BN:
                    generateKnightMoves(board, row, col, moves);
                    break;
                case WB: case BB:
                    generateBishopMoves(board, row, col, moves);
                    break;
                case WR: case BR:
                    generateRookMoves(board, row, col, moves);
                    break;
                case WQ: case BQ:
                    generateQueenMoves(board, row, col, moves);
                    break;
                case WK: case BK:
                    generateKingMoves(board, row, col, moves);
                    break;
                default:
                    break;
            }
        }
    }

    return moves;
}

void aiBestMoveThread(Piece board[8][8], bool whiteTurn, std::string& bestMoveOut) {
    std::vector<std::string> moves = generateAllPseudoLegalMoves(board, whiteTurn);
    
    int bestScore = whiteTurn ? -1000000 : 1000000;
    std::string bestMove = "";

    for (const std::string& move : moves) {
        Piece copy[8][8];
        memcpy(copy, board, sizeof(Piece) * 64);

        // Optional: add `isLegalMove(copy, move, whiteTurn)` if needed
        if (!makeMove(copy, move)) continue;

        int score = evaluateBoard(copy);

        if ((whiteTurn && score > bestScore) || (!whiteTurn && score < bestScore)) {
            bestScore = score;
            bestMove = move;
        }
    }

    bestMoveOut = bestMove;
}