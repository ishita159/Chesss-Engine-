#include<bits/stdc++.h>
using namespace std;
int Parse_FEN(const char *fen, board* pos)
{
	ASSERT(fen != NULL);   // fen is pointer to string FEN
	ASSERT(pos != NULL);  

	int rank = rank_8;
	int file = file_a;

	int piece = 0;    // to check which piece is this
	int count = 0;    // to count number of empty space
	
	int sq64 = 0;
	int sq120 = 0;

	reset_board(pos);

// parse through FEN strin 	
	while((rank >= rank_1) && *fen)
	{
		count = 1;       
		
		switch(*fen)
		{
			case 'p': piece = b_pawn;
						break;		
			case 'r': piece = b_rook;
						break;
			case 'n': piece = b_knight;
						break;		
			case 'b': piece = b_bishop;
						break;	
			case 'k': piece = b_king;
						break;
			case 'q': piece = b_queen;
						break;
			case 'P': piece = w_pawn;
						break;		
			case 'R': piece = w_rook;
						break;
			case 'N': piece = w_knight;
						break;		
			case 'B': piece = w_bishop;
						break;	
			case 'K': piece = w_king;
						break;
			case 'Q': piece = w_queen;
						break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				piece = empty;
				count = *fen - '0';    // char to int
				break;

			case '/':
			case ' ':
				rank--;
				file = file_a;
				fen++;
				continue;

			default:
					cout<<"FEN ERROR"<<endl;
					return -1;  
		}	

// if piece count is 1 then only piece else  space from  that position to number of count
		for(int i = 0; i < count; i++)
		{
			sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);

			if(piece != empty)
			{
				pos->pieces[sq120] = piece;
			} 
			file++;
		}
		fen++;
	}

	ASSERT(*fen == 'w' || *fen == 'b')

// setting position side who will play next
	pos->side = (*fen == 'w') ? white : black;
	fen += 2;

// checking castle permission	

	for(int i = 0; i < 4; i++)
	{
		if(*fen == ' ')
			break;

// using or operator , because castle_perm is 16 bit
		switch(*fen)
		{
			case 'K':	pos->castle_perm |=  WKCA;
						break;

			case 'Q':	pos->castle_perm |=  WQCA;
						break;

			case 'k':	pos->castle_perm |=  BKCA;
						break;		

			case 'q':	pos->castle_perm |=  BQCA;
						break;

			default:
					break;
		}
		fen++;
	}
	fen++;

	ASSERT(pos->castle_perm >= 0 && pos->castle_perm <= 15);

// checking en passant

	if(* fen != '-')
	{
		file = fen[0] - 'a';       // converting char to int
		rank = fen[1] - '1';

		ASSERT(file >= file_a  && file <= file_h);
		ASSERT(rank >= rank_1 && rank <= rank_8);

		pos->en_pas = FR2SQ(file, rank);
 
	}

// getting hash key from all of that given situation

	pos->pos_key = generate_pos_key(pos);

	return 0;

}


void reset_board(board* pos)
{

// first setting all board suare to off board

	for(int i = 0; i < board_square; i++)
		pos->pieces[i] = OFF_BOARD;

// setting all playable square to empty

	for(int i = 0; i < 64; i++)
		pos->pieces[SQ120(i)] = empty;

// reseting all pieces 

	for(int i = 0; i < 3; i++)
	{
		pos->big_piece[i] = 0;
		pos->maj_piece[i] = 0;
		pos->min_piece[i] = 0;
		pos->pawns[i] = 0ULL;
	}

// reseting all remaing pieces in between game (piece_num[13])

	for(int i = 0; i < 13; i++)
		pos->piece_num[i] = 0;

// reseting all other variable

	pos->king_sq[white] = pos->king_sq[black] = NO_SQ;

	pos->side = both;      // no side to play

	pos->en_pas = NO_SQ;

	pos->fifty_move = 0;

	pos->ply = 0;

	pos->his_ply = 0;

	pos->castle_perm = 0;

	pos->pos_key = 0ULL;

}

void print_board(const board* pos)
{
	int piece, sq;

// printing 64 bit board
	for(int i = rank_8; i >= rank_1; i--)
	{
		cout<<i+1<<" ";
	
		for(int j = file_a; j <= file_h; j++)
		{
			sq = FR2SQ(j, i);
			piece = pos->pieces[sq];
			printf("%3c",pce_char[piece]);
		}	
		cout<<endl;
	}

// printhing other stuff

	for(int i = file_a; i <= file_h; i++)
		printf("%3c", 'a' + i);

	cout<<endl;

	cout<<"side: "<<side_char[pos->side]<<endl;
	cout<<"en passant: "<<pos->en_pas<<endl;
	
// printing castle permission

	printf("castle: %c%c%c%c\n",
			pos->castle_perm & WKCA ? 'K' : '-',
			pos->castle_perm & WQCA ? 'Q' : '-',
			pos->castle_perm & BKCA ? 'k' : '-',
			pos->castle_perm & BQCA ? 'q' : '-');

	printf("pos key: %llX \n", pos->pos_key);

}

 




















