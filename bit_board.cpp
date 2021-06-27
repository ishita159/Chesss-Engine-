// https://stackoverflow.com/questions/30680559/what-is-this-code-doing/40380973  read this link to understand all of this

// random table
const int bit_table[64] = 
{
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};



int pop_bit(U64 *bb) 
{
  U64 b = *bb ^ (*bb - 1);        // flip least significant bit and lower of them

  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));   //first fold with lower 32 bits (b & 0*ffffffff) then take xor with upper half 32 bit(b>>32) 

  *bb &= (*bb - 1);   // unset the lowest bit

  return bit_table[(fold * 0x783a9b23) >> 26];   
}




int count_bits(U64 bb)
{
	int count;
	for(count = 0; bb; count++, bb &= bb - 1);    // calculates number of set bits  bb &= bb-1 this line unset lowest bit 

	return count;

}

void print_bit_board(U64 bb)
{
	U64 shift = 1ULL;       // 000000.......0001
	int sq, sq64;

	for(int i = rank_8; i >= rank_1; i--)
	{
		for(int j = file_a; j <= file_h; j++)
		{
			sq = FR2SQ(j, i);       // 120 based
			sq64 = SQ64(sq);		// 64 based	
		
			if((shift << sq64) & bb)
				printf("x");
			else
				printf("-");

		}
		printf("\n");
	}

}
