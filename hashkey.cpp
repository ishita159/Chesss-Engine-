U64 generate_pos_key(const board* pos)
{
	int piece = empty;
	U64 final_key = 0;

// first find piece on the whole board then take xor to find final key
	for(int i = 0; i < board_square; i++)
	{
		piece = pos->pieces[i];
		if(piece != empty && piece != NO_SQ && piece != OFF_BOARD)      // checking if it is a piece
		{
			ASSERT(piece >= w_pawn && piece <= b_king);  // checking if it is a piece
			final_key ^= piece_keys[piece][i];
		}
	}

	if(pos->side == white)    // if it is white side then take xor to seperate from black side key
	{
		final_key ^= side_key; 
	}

// in case of en passant

	if(pos->en_pas != NO_SQ)
	{
		ASSERT(pos->en_pas >= 0 && pos->en_pas < board_square);
		final_key ^= piece_keys[empty][pos->en_pas];		
	}	

// in case of castling

	ASSERT(pos->castle_perm >=0 && pos->castle_perm <= 15)

	final_key ^= castle_keys[pos->castle_perm];

	return final_key;
}
