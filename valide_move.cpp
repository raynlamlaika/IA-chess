#include "all.hpp"

bool isWhitePiece(Piece p) {
    return (p >= WP && p <= WK);
}

bool isBlackPiece(Piece p) {
    return (p >= BP && p <= BK);
}


bool isLegalPawnMove(Piece board[8][8], int fromRow, int fromCol, int toRow, int toCol, bool isWhite) {
    int direction = isWhite ? 1 : -1;
    int startRow = isWhite ? 1 : 6;

    Piece target = board[toRow][toCol];

    if (toCol == fromCol && toRow == fromRow + direction && target == EMPTY)
        return true;

    if (toCol == fromCol && fromRow == startRow && toRow == fromRow + 2 * direction &&
        board[fromRow + direction][fromCol] == EMPTY && target == EMPTY)
        return true;

    if ((toCol == fromCol + 1 || toCol == fromCol - 1) && toRow == fromRow + direction &&
        target != EMPTY)
        return true;

    return false;
}

bool isLegalMove(Piece board[8][8], std::string move) {
    if (move.length() != 4) return false;

    int fromRow, fromCol, toRow, toCol;
    if (!notationToCoords(move.substr(0,2), fromRow, fromCol)) return false;
    if (!notationToCoords(move.substr(2,2), toRow, toCol)) return false;

    Piece piece = board[fromRow][fromCol];
    if (piece == EMPTY) return false;

    bool isWhite = isWhitePiece(piece);
    bool isBlack = isBlackPiece(piece);
    if (!isWhite && !isBlack) return false; // invalid piece

    Piece target = board[toRow][toCol];
    // Cannot capture own piece
    if (isWhite && isWhitePiece(target)) return false;
    if (isBlack && isBlackPiece(target)) return false;

    // Now dispatch piece-specific legality
    switch(piece) {
        case WP:
            return isLegalPawnMove(board, fromRow, fromCol, toRow, toCol, true);
        case BP:
            return isLegalPawnMove(board, fromRow, fromCol, toRow, toCol, false);
        // Add other pieces here
        default:
            return false; // For now reject other pieces
    }
}
