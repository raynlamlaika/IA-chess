#include "all.hpp"


// Function to print the board
void printBoard(Piece board[8][8]) 
{
    for (int r = 7; r >= 0; --r) {  // Print from rank 8 to 1
        std::cout << (r + 1) << " ";
        for (int c = 0; c < 8; ++c) {
            switch (board[r][c]) {
                case WP: std::cout << "P "; break;
                case WN: std::cout << "N "; break;
                case WB: std::cout << "B "; break;
                case WR: std::cout << "R "; break;
                case WQ: std::cout << "Q "; break;
                case WK: std::cout << "K "; break;
                case BP: std::cout << "p "; break;
                case BN: std::cout << "n "; break;
                case BB: std::cout << "b "; break;
                case BR: std::cout << "r "; break;
                case BQ: std::cout << "q "; break;
                case BK: std::cout << "k "; break;
                case EMPTY: std::cout << ". "; break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h\n";
}

// Initialize the board with starting position
void initBoard(Piece board[8][8]) 
{
    // Clear board
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = EMPTY;

    // White pieces
    board[0][0] = WR; board[0][1] = WN; board[0][2] = WB; board[0][3] = WQ;
    board[0][4] = WK; board[0][5] = WB; board[0][6] = WN; board[0][7] = WR;
    for (int c = 0; c < 8; ++c)
        board[1][c] = WP;

    // Black pieces
    board[7][0] = BR; board[7][1] = BN; board[7][2] = BB; board[7][3] = BQ;
    board[7][4] = BK; board[7][5] = BB; board[7][6] = BN; board[7][7] = BR;
    for (int c = 0; c < 8; ++c)
        board[6][c] = BP;
}

// Converts a square notation like "e2" to board coordinates (row, col)
bool notationToCoords(const std::string& square, int& row, int& col) 
{
    if (square.length() != 2) return false;
    col = square[0] - 'a';
    row = square[1] - '1';
    if (col < 0 || col > 7 || row < 0 || row > 7) return false;
    return true;
}

// Make a move if valid (no move legality checking for now)
bool makeMove(Piece board[8][8], const std::string& move) 
{
    if (move.length() != 4) return false;
    int fromRow, fromCol, toRow, toCol;

    if (!notationToCoords(move.substr(0,2), fromRow, fromCol)) return false;
    if (!notationToCoords(move.substr(2,2), toRow, toCol)) return false;

    // Move the piece
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = EMPTY;
    return true;
}

