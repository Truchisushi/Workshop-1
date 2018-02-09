/*
Board structure:

First Row							Second Row							Third Row					Fourth Row
[ [column1 column2 column3 column4] | [column1 column2 column3 column4] | [column1 column2 column3 column4] | [column1 column2 column3 column4] ]

index positions go from [0-3][0-3](4x4 positions in total).

First  row consists of indices: [0][0-3]
Second row consists of indices: [1][0-3]
Third  row consists of indices: [2][0-3]
Fourth row consists of indices: [3][0-3]

First  column consists of indices: [0-3][0]
Second column consists of indices: [0-3][1]
Third  column consists of indices: [0-3][2]
Fourth column consists of indices: [0-3][3]
*/

#pragma once


class Board {
public:
	Board();
	int tiles[4][4] = { 0 };
	void initialize();
	void do_move(int move_type);
	bool can_move();
	int get_score();
	int get_best_tile();
	void print_board();
	int test_move(int move_type);
	~Board();
private:
	int score = 0;
	int old_tiles[4][4] = { 0 }; //Used to see if a move actually changed anything on the board
	void transpose(int board[4][4]);
	void reverse(int board[4][4]);
	bool new_tile();
};
