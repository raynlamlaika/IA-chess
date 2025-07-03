#include  "all.hpp"

int main() 
{
    Piece board[8][8];
    initBoard(board);

    printBoard(board);

    std::string move;
    while (true)
    {
        std::cout << "Enter your move (e.g. e2e4): ";
        if (!getline(std::cin, move))
            exit(1);
        if (move == "quit") break;
        if (isLegalMove(board, move))
        {
            if (makeMove(board, move))
            {
                printBoard(board);

            } 
        }
        else 
            std::cout << "Invalid move format!" << std::endl;
    }
    return 0;
}
