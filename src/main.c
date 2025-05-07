#include "wukong_engine.h"

// main driver
int main()
{
    // parse FEN string
    parse_fen("3k4/8/8/5r2/4R3/8/8/3K4 b - - 0 1");
    print_board();
    print_values();


    
    // run perft driver
    perft_test(2);

    printf("minimax algorithm gives value : %d \n", side);

    
    return 0;
}