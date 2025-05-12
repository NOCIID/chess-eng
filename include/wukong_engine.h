#ifndef WUKONG_ENGINE_H
#define WUKONG_ENGINE_H

#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

// --- Enumerations and Constants ---

// Pieces
enum pieces { e, P, N, B, R, Q, K, p, n, b, r, q, k, o };


// decode promoted pieces
extern int promoted_pieces[];

// Sides
enum sides { white, black };

// Castling rights
enum castling { KC = 1, QC = 2, kc = 4, qc = 8 };

// Capture flags
enum capture_flags { all_moves, only_captures };

// Board squares (partial listing; ensure you define all needed, for example)
enum squares {
    a8 = 0,   b8, c8, d8, e8, f8, g8, h8,
    a7 = 16,  b7, c7, d7, e7, f7, g7, h7,
    a6 = 32,  b6, c6, d6, e6, f6, g6, h6,
    a5 = 48,  b5, c5, d5, e5, f5, g5, h5,
    a4 = 64,  b4, c4, d4, e4, f4, g4, h4,
    a3 = 80,  b3, c3, d3, e3, f3, g3, h3,
    a2 = 96,  b2, c2, d2, e2, f2, g2, h2,
    a1 = 112, b1, c1, d1, e1, f1, g1, h1, no_sq
};

// convert board square indexes to coordinates
extern char *square_to_coords[];



// --- Type Definitions ---

// Move list structure
typedef struct {
    int moves[256];
    int count;
} moves;


// --- Macros ---
// encode move
#define encode_move(source, target, piece, capture, pawn, enpassant, castling) \
(                          \
    (source) |             \
    (target << 7) |        \
    (piece << 14) |        \
    (capture << 18) |      \
    (pawn << 19) |         \
    (enpassant << 20) |    \
    (castling << 21)       \
)

// decode move's source square
#define get_move_source(move) (move & 0x7f)

// decode move's target square
#define get_move_target(move) ((move >> 7) & 0x7f)

// decode move's promoted piece
#define get_move_piece(move) ((move >> 14) & 0xf)

// decode move's capture flag
#define get_move_capture(move) ((move >> 18) & 0x1)

// decode move's double pawn push flag
#define get_move_pawn(move) ((move >> 19) & 0x1)

// decode move's enpassant flag
#define get_move_enpassant(move) ((move >> 20) & 0x1)

// decode move's castling flag
#define get_move_castling(move) ((move >> 21) & 0x1)

// --- Function Prototypes ---

// FEN parsing and board initialization
void reset_board(void);
void parse_fen(char *fen);

// Board printing and evaluation
void print_board(void);
void print_values(void);
int compute_board_value(void);

// Move generation and manipulation
void add_move(moves *move_list, int move);
void generate_moves(moves *move_list, int side);
int make_move(int move, int capture_flag, int side);

// Attack map function (for debugging)
int is_square_attacked(int square, int side);
void print_attacked_squares(int side);


// --- Global Variables ---
// (Declare these as extern since they are defined in wukong_engine.c)
extern int board[128];
extern int side;
extern int enpassant;
extern int castle;
extern int king_square[2];
extern long nodes;

#endif // WUKONG_ENGINE_H