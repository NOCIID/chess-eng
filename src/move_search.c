#include "../include/wukong_engine.h"
#include "../include/move_search.h"
#include <string.h>
#include <sys/time.h>


long nodes = 0;

int pieces_values[] = {0, 1, 3, 3, 5, 9, 100, 1, 3, 3, 5, 9, 100, 0};

// get time in milliseconds
int get_time_ms()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

// perft driver
void perft_driver(int depth, int side)
{
    // escape condition
    if  (!depth)
    {
        // count current position
        nodes++;
        return;
    }

    // create move list variable
    moves move_list[1];
    
    // generate moves
    generate_moves(move_list, side);
    
    // loop over the generated moves
    for (int move_count = 0; move_count < move_list->count; move_count++)
    {
        // define board state variable copies
        int board_copy[128], king_square_copy[2];
        int side_copy, enpassant_copy, castle_copy;
        
        // copy board state
        memcpy(board_copy, board, 512);
        side_copy = side;
        enpassant_copy = enpassant;
        castle_copy = castle;
        memcpy(king_square_copy, king_square,8);
        
        // make only legal moves
        if (!make_move(move_list->moves[move_count], all_moves, side))
            // skip illegal move
            continue;
        
        // recursive call
        perft_driver(depth - 1, side);
        
        // restore board position
        memcpy(board, board_copy, 512);
        side = side_copy;
        enpassant = enpassant_copy;
        castle = castle_copy;
        memcpy(king_square, king_square_copy,8);
    }
}

// perft test
void perft_test(int depth, int side)
{
    printf("\n    Performance test:\n\n");
    
    // init start time
    int start_time = get_time_ms();

    // create move list variable
    moves move_list[1];
    
    // generate moves
    generate_moves(move_list, side);
    
    // loop over the generated moves
    for (int move_count = 0; move_count < move_list->count; move_count++)
    {
        // define board state variable copies
        int board_copy[128], king_square_copy[2];
        int side_copy, enpassant_copy, castle_copy;
        
        // copy board state
        memcpy(board_copy, board, 512);
        side_copy = side;
        enpassant_copy = enpassant;
        castle_copy = castle;
        memcpy(king_square_copy, king_square,8);
        
        // make only legal moves
        if (!make_move(move_list->moves[move_count], all_moves, side))
            // skip illegal move
            continue;
        
        // cummulative nodes
        long cum_nodes = nodes;
        
        // recursive call
        perft_driver(depth - 1, side);
        
        // old nodes
        long old_nodes = nodes - cum_nodes;
        
        // restore board position
        memcpy(board, board_copy, 512);
        side = side_copy;
        enpassant = enpassant_copy;
        castle = castle_copy;
        memcpy(king_square, king_square_copy,8);
        
        // print current move
        printf("    move %d: %s%s%c    %ld\n",
            move_count + 1,
            square_to_coords[get_move_source(move_list->moves[move_count])],
            square_to_coords[get_move_target(move_list->moves[move_count])],
            promoted_pieces[get_move_piece(move_list->moves[move_count])],
            old_nodes
        );
    }
    
    // print results
    printf("\n    Depth: %d", depth);
    printf("\n    Nodes: %ld", nodes);
    printf("\n     Time: %d ms\n\n", get_time_ms() - start_time);
}

// print the total pieces values for each sides
void print_values(){
    int w_piece_values = 0;
    int b_piece_values = 0;

    for (int square = 0; square < 120; square++){
        // if board is not empty
        if (!(square & 0x88)){
            if (board[square]){
                // if we have a white piece 
                if ((board[square] >= 1) && (board[square] <= 6)){
                    w_piece_values += pieces_values[board[square]];
                }
                // if we have a black piece
                else if ((board[square] >= 7) && (board[square] <= 12)){
                    b_piece_values += pieces_values[board[square]];
                }
            }
        }
    }
    printf("\nTotal white piece values : %d", w_piece_values);
    printf("\nTotal black piece values : %d\n\n", b_piece_values);
}


int compute_board_value(){
    int w_piece_values = 0;
    int b_piece_values = 0;

    for (int square = 0; square < 120; square++){
        // if board is not empty
        if (!(square & 0x88)){
            if (board[square]){
                // if we have a white piece 
                if ((board[square] >= 1) && (board[square] <= 6)){
                    w_piece_values += pieces_values[board[square]];
                }
                // if we have a black piece
                else if ((board[square] >= 7) && (board[square] <= 12)){
                    b_piece_values += pieces_values[board[square]];
                }
            }
        }
    }
    return w_piece_values - b_piece_values;
}

int minimax(int depth, int side){
    if (depth == 0){
        int value = compute_board_value();

        if (value) {
            printf("\n  value : %d and side : %d\n", value, side);
            print_board();

        }
        //printf("\n      side : %d", side);
        //print_board();
        return value;
    }
    
    moves move_list[1];
    generate_moves(move_list, side);

    // usually it should be the other way around but since the side gets changed in the make_move we flip it beforehand before it gets flipped (i know it makes no sense)
    int best_eval = (side == white) ? INT_MIN : INT_MAX;
    
    // loop over candidate moves
    for (int move_count = 0; move_count < move_list->count; move_count++){
        int move = move_list->moves[move_count];
        
        // save current state
        int board_copy[128], king_square_copy[2];
        int side_copy, enpassant_copy, castle_copy;
        memcpy(board_copy, board, 512);
        memcpy(king_square_copy, king_square, 8);
        side_copy = side;
        enpassant_copy = enpassant;
        castle_copy = castle;

        // apply move; if illegal, skip
        if (!make_move(move, all_moves, side))
            {
                continue;
            }

        
        // recursive search on the new position (side switched in make_move)
        int eval = minimax(depth - 1, side ^ 1);//(side == white) ? black : white);

        //printf("\n      side : %d", side);

        // update best eval depending on who is moving
        if (side == white)
            best_eval = (eval > best_eval) ? eval : best_eval;
        else
            best_eval = (eval < best_eval) ? eval : best_eval;
        
        // undo move: restore board state
        memcpy(board, board_copy, 512);
        memcpy(king_square, king_square_copy, 8);
        side = side_copy;
        enpassant = enpassant_copy;
        castle = castle_copy;
    }
    
    return best_eval;
}

int minimax_driver(){
    move_stack = create_stack(128);

    push(move_stack, 32);

    printf("\nmovestack : %d\n", peek(move_stack));
    return 0;
}