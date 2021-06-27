#include<bits/stdc++.h>
#include "global_init.h"
#include "init.cpp"
#include "bit_board.cpp"
#include "hashkey.cpp"
#include "board.cpp"
#include "data.cpp"
using namespace std;

#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"

int main()
{
	all_init();

	board b[1];

	Parse_FEN(START_FEN, b);
	print_board(b);

	Parse_FEN(FEN1, b);
	print_board(b);

	Parse_FEN(FEN2, b);
	print_board(b);

	Parse_FEN(FEN3, b);
	print_board(b);
		
	return 0;
}
