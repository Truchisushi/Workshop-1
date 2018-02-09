
/*
Authors	: Adam Lindberg, Daniel Trochez
Date	:	2018-02-02

*/
#include "Board.h"
#include <iostream>
#include <time.h>


Board::Board()
{
}





bool Board::new_tile() {
	int potential_tiles = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] == 0) potential_tiles++;
		}
	}

	srand(clock());
	int pos, v;
	pos = rand() % potential_tiles;

	// 90% for 2 10% for 4.
	v = rand() % 100 < 89 ? 2 : 4;

	int zero_nr = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] == 0) {
				if (zero_nr == pos) {
					tiles[i][j] = v;
					return 1;
				}
				else zero_nr++;
			}
		}
	}

	return 0;
}

bool Board::can_move() {
	//Test if there are no free tiles.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] == 0) return 1;
		}
	}

	//Test if there are two adjacent tiles that are the same:
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j < 3) { //Check to the right
				if (tiles[i][j] == tiles[i][j + 1]) return 1;
			}
			if (i < 3) { //check down
				if (tiles[i][j] == tiles[i + 1][j]) return 1;
			}

		}
	}
	return 0;
}

int Board::get_best_tile() {
	int best_tile = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] > best_tile) best_tile = tiles[i][j];
		}
	}
	return best_tile;
}

int Board::get_score() {
	return score;
}

void Board::initialize() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tiles[i][j] = 0;
			old_tiles[i][j] = 0;
		}
	}
	score = 0;

	srand(clock());
	int pos1, pos2, v1, v2, r1, c1, r2, c2;
	pos1 = rand() % 16;
	pos2 = rand() % 15;
	pos2 = pos2 < pos1 ? pos2 : pos2 + 1;

	r1 = pos1 / 4;
	c1 = pos1 % 4;
	r2 = pos2 / 4;
	c2 = pos2 % 4;

	// 90% for 2 10% for 4.
	v1 = rand() % 100 < 89 ? 2 : 4;
	v2 = rand() % 100 < 89 ? 2 : 4;

	tiles[r1][c1] = v1;
	tiles[r2][c2] = v2;

	//std::cout << "(" << r1 << ", " << c1 << ")   (" << r2 << ", " << c2 << ")\n";

}

void Board::do_move(int move_type) {
	int start_board[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			start_board[i][j] = tiles[i][j];
			old_tiles[i][j] = tiles[i][j];
			tiles[i][j] = 0;
		}
	}


	if (move_type == 1) //up
		transpose(start_board);
	else if (move_type == 2) //right
		reverse(start_board);
	else if (move_type == 3) //down 
	{
		transpose(start_board);
		reverse(start_board);
	}
	//for left, no transposition or mirroring is required

	for (int row = 0; row < 4; ++row) {
		int out_col = 0; //column to output
		int col = 0;
		while (col < 4) {
			int next_col = col + 1;

			int current_cell = start_board[row][col];
			if (current_cell == 0) {
				col++;
				continue; //go to beginning of while.
			}
			if (col == 3) {
				tiles[row][out_col] = current_cell;
				break; //we have come to the last column, just update tiles and exit
			}

			int next_cell = start_board[row][next_col];

			while (next_cell == 0 && next_col < 3) {
				next_col++;
				next_cell = start_board[row][next_col];
			}

			if (next_cell == current_cell) { // they are the same.
				tiles[row][out_col] = current_cell + next_cell;
				score += (current_cell + next_cell);
				out_col++;
				col = next_col + 1;
			}
			else {
				tiles[row][out_col] = current_cell;
				out_col++;
				col = next_col;
			}
		}
	}

	if (move_type == 1) transpose(tiles);
	if (move_type == 2) reverse(tiles);
	if (move_type == 3) {
		reverse(tiles);
		transpose(tiles);
	}

	bool board_changed = 0;

	//Check if the board has actually changed
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (old_tiles[i][j] != tiles[i][j]) {
				board_changed = 1;
				break;
			}
		}
	}

	//Add a new tile if the board has changed
	if (board_changed == 1) new_tile();
}

//transpose the board so that the rows become columns and columns become rows. 
//this is hardcoded for this exact problem
void Board::transpose(int board[4][4]) {
	int temp;
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			temp = board[i][j];
			board[i][j] = board[j][i];
			board[j][i] = temp;
		}
	}
}

//reverse the rows. This is hardcoded for this exact problem
void Board::reverse(int board[4][4]) {
	int temp;
	for (int i = 0; i < 4; ++i) { //each row.
		for (int j = 0; j < 2; ++j) {
			temp = board[i][j];
			board[i][j] = board[i][3 - j];
			board[i][3 - j] = temp;
		}
	}

}

void Board::print_board() {
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			std::cout << tiles[row][col] << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

int Board::test_move(int move_type) {
	int current_score = score;
	//std::cout << "In test move, before!\n\n";
	//print_board();
	do_move(move_type);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tiles[i][j] = old_tiles[i][j];
		}
	}

	//std::cout << "In test move, after!\n\n";
	//print_board();

	int score_dif = score - current_score;
	score = current_score;
	return score_dif;
}



Board::~Board()
{
}
