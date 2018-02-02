/*
	Authors	: Adam Lindberg, Daniel Trochez
	Date	:	2018-02-02

*/


#include <iostream>
#include <time.h>

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

class Board {
public:
	int tiles[4][4] = { 0 };
	void initialize();
	void do_move(int move_type);
	bool can_move();
	int get_score();
	void print_board();
private:
	int old_tiles[4][4] = { 0 }; //Used to see if a move actually changed anything on the board
	void transpose(int board[4][4]);
	void reverse(int board[4][4]);
	bool new_tile();
};

//void print_board(int board[4][4]);

int main() {
	int move_type = -1;

	Board board;
	board.initialize();
	board.print_board();

	
	while (1) {
		if (board.can_move()) { //If AI can still move, AI continues
			std::cin >> move_type; //REPLACE this with AI later

			board.do_move(move_type);

			board.print_board();
		}
		else { //If AI cannot move, the game has ended
			std::cout << "Score: " << board.get_score() << std::endl;

			break;
		}
	}

	while (1) {};
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] == 0) return 1;
		}
	}
	return 0;
}

int Board::get_score() {
	int best_tile = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tiles[i][j] > best_tile) best_tile = tiles[i][j];
		}
	}
	return best_tile;
}

void Board::initialize() {
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

