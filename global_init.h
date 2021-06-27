// to check error (ASSERT)

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

//..........................................//

typedef unsigned long long U64;

#define board_square 120
#define MAX_GAME_MOVES 2048

#define START_FEN "rnbqknnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

// w -> white, b->black
enum { empty, w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king, b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king };

// colors for pieces
enum { white, black, both };   // both means all pawn together

// for columns , just for y co-ordinate
enum { file_a, file_b,  file_c, file_d, file_e, file_f, file_g, file_h, file_none };

// for rows, just for x co-ordinate
enum { rank_1, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_none };

// giving movalble boundary ( 8*8 ) a value 
enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFF_BOARD
};


// castling  IN bits form 0 0 0 0, each bit tells which castle is permissible
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };


// store position history in this structure
typedef struct {

	int move;
	int castle_perm;
	int en_pas;
	int fifty_move;
	U64 pos_key;	

} undo;


typedef struct {
	
	int pieces[board_square];          // size of whole board
	U64 pawns[3];          //64 bits shows 64 square board position, if a bit is set 1 that means on that position a pawn is present of color of given index of array 

	int king_sq[2];    //pos at which we hold both king 

	int side;  // current side to move(black or white)

	int en_pas;

	int fifty_move;     // only that much moves are given in the game to one bot, otherwise it will be draw 

	int ply;   // how much half moves in current search 
 	int his_ply; // in total game how much half moves are made

	int castle_perm;   // tells about castling permission

	U64 pos_key;    // unique to check position

	int piece_num[13];   // how much pieces we have (node + 12 pieces = 13)
	int big_piece[3];      // king
	int maj_piece[3];	//rooks, queen
	int min_piece[3];       // bishop, knights

	undo history[MAX_GAME_MOVES];        // max moves to store 

	int piece_list[13][10];   // array stores all pieces position	


} board;


// MACROS

#define FR2SQ(f, r) ( (21 + (f) ) + ( (r) * 10 ) )      // 120 based index is returned if rank(0-7) and file (0-7) is given 

#define SQ64(sq120) (sq120tosq64[sq120])   // function call using micro to get 64 indexed value of board

#define SQ120(sq64) (sq64tosq120[sq64])   // function call using micro to get 120 indexed value of board

#define clear_bit(bb, sq) ((bb) &= clear_mask[sq])    // on given position there will be 0 in clear_mask[sq], after doing & operation that will be unset 1 & 0 = 0

#define set_bit(bb, sq) ((bb) |= set_mask[sq])		// on given position there will be 1 in set_mask[sq], after doing | operation that will be set 1 | 0 = 0


// GLOBALS

int sq120tosq64[board_square];             // store value of board in 64 indexed base
int sq64tosq120[64];					// store value of board in 120 indexed base

U64 clear_mask[64];                 // store 0 on given pos

U64 set_mask[64];               // store 1 on given pos

U64 piece_keys[13][120];      // every piece has a unique around the whole board

U64 castle_keys[16];        // 16 keys(0-15) for castling 

U64 side_key;   //tells which move is it

extern char pce_char[];
extern char side_char[];
extern char rank_char[];
extern char file_char[];


// FUNCTIONS

// init.cpp
void all_init();     // initialize board values

// bit_board.cpp
 
void print_bit_board(U64 bb);      // printing board (bit manipulation)

int count_bits(U64 bb);   // calculates number of pawns (set bits)

int pop_bit(U64 *bb);   // unset lowest bit

// hashkey.cpp
U64 generate_pos_key(const board* pos);

// board.cpp
void reset_board(board* pos);
int Parse_FEN(char *fen, board* pos);
void print_board(const board* pos);




























