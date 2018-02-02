
#include <iostream>

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
	int tiles[4][4] = { { 2,4,2,4 },{ 8,16,8,16 },{ 32,64,32,64 },{ 128,256,128,256 } };
	void initialize();
	void do_move(int move_type);
	bool can_move();
	int get_score();
private:
	void transpose(int board[4][4]);
	void reverse(int board[4][4]);
};

void print_board(int board[4][4]);

int main() {
	int start_board[4][4] = { 0 };
	int end_board[4][4] = { 0 };
	int move_type = -1;

	Board board;

	while (1) {
		if (board.can_move()) { //If AI can still move, AI continues
			std::cin >> move_type; //REPLACE this with AI later

			board.do_move(move_type);

			print_board(board.tiles);
		}
		else { //If AI cannot move, the game has ended
			std::cout << "Score: " << board.get_score() << std::endl;

			break;
		}
	}

	while (1) {};
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
	int temp[4][4] = { { 2,4,2,4 }, { 8,16,8,16 }, { 32,64,32,64 }, { 128,256,128,256 } };
}

void Board::do_move(int move_type) {
	int start_board[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			start_board[i][j] = tiles[i][j];
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
				col = next_col+1;
			}
			else {
				tiles[row][out_col] = current_cell;
				out_col++;
				col = next_col;
			}			
		}
	}

	if(move_type == 1) transpose(tiles);
	if(move_type == 2) reverse(tiles);
	if(move_type == 3) {
		reverse(tiles);
		transpose(tiles);
	}
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

void print_board(int board[4][4]) {
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			std::cout << board[row][col] << " ";
		}
		std::cout << std::endl;
	}
}