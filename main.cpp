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
        std::cin >> move;
        if (move == "quit") break;
        if (makeMove(board, move))
        {
            // th model will be passed from here
            
            printBoard(board);
        } else {
            std::cout << "Invalid move format!" << std::endl;
        }
    }
    return 0;
}
