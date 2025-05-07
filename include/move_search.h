#ifndef MOVE_SEARCH_H
#define MOVE_SEARCH_H

#include "wukong_engine.h"
#include "stack.h"

// ----- Enums & Constants & Global Variables --------//
extern int pieces_values[];

Stack* move_stack;

extern long nodes;


// Function prototypes
int get_time_ms(void);
void perft_driver(int depth);
void perft_test(int depth);
void print_values(void);
int compute_board_value(void);
int minimax(int depth, int side);
int minimax_driver(void);


#endif