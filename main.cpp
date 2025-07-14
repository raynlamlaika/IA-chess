#include  "all.hpp"

int main() 
{
    Piece board[8][8];
    Piece copy[8][8];
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
                std::string iamove;
                printBoard(board);
                int evalScore = 0;
                memcpy(copy, board, sizeof(Piece)*64);
                std::thread t1 (evaluateBoardThread, copy, std::ref(evalScore));
                std::thread t2 (aiBestMoveThread, copy, /*whiteTurn=*/false, std::ref(iamove));
                t1.join();
                t2.join();
                
                // here willbe the ia move
                makeMove(board, iamove);
                std::cout << " the score is :" << evalScore << std::endl;
                printBoard(board);

            } 
        }
        else 
            std::cout << "Invalid move format!" << std::endl;
    }
    return 0;
}
