#include "../include/wukong_engine.h"
#include "../include/move_search.h"

// main driver
int main()
{
    // parse FEN string
    parse_fen("4k3/8/8/8/R2K4/8/7r/8 b - - 6 6");
    print_board();
    print_values();


    // run perft driverx
    //perft_test(2);


    printf("minimax algorithm gives value : %d \n", minimax(3, side));

    
    return 0;
}