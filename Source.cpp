
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

//static int move[4] = { -1, 1, -4, 4 };
void do_move(int move_type, int start_board[4][4], int end_board[4][4]);
void do_move2(int start_board[4][4], int end_board[4][4]);
void print_board(int board[4][4]);

void transpose(int board[4][4]);
void reverse(int board[4][4]);

int main() {
	int start_board[4][4] = { 0 };
	int end_board[4][4] = { 0 };
	int move_type = -1;

	//read in starting board input:
	for (int row = 0; row < 4; ++row)
		for(int col = 0; col < 4; ++col)
			std::cin >> start_board[row][col];

	std::cin >> move_type;

	if (move_type == 1) //up
	{ 
		transpose(start_board);
		do_move2( start_board, end_board);
		transpose(end_board);
	}
	else if (move_type == 2) // right
	{ 
		reverse(start_board);
		do_move2( start_board, end_board);
		reverse(end_board);
	}
	else if (move_type == 3) // down 
	{
		transpose(start_board);
		reverse(start_board);
		do_move2( start_board, end_board);
		reverse(end_board);
		transpose(end_board);
	}
	else // left
	{
		do_move2( start_board, end_board);

	}

	//print_board(start_board);
	//transpose(start_board);
	//print_board(start_board);
	//reverse(start_board);
	//print_board(start_board);
	//do_move(move_type, start_board, end_board);
	print_board(end_board);
}

void do_move(int move_type, int start_board[4][4], int end_board[4][4])
{
	//For now it only works going to the left:
	for (int row = 0; row < 4; ++row) {
		int col = 0;
		int out_col = 0;
		int out_row = row;
		int current_cell;
		int next_cell;

		while (col < 4) {

			current_cell = start_board[row][col];

			if (current_cell == 0) {
				col++;
			}
			else {
				col++;
				next_cell = start_board[row][col];

				if (current_cell == next_cell) { //if they are same, update output, increment output indices.
					end_board[out_row][out_col] = current_cell + next_cell;
					out_col++;
					col++;
				}
				else if(next_cell != 0) { // if they are different, update output, increment output.
					end_board[out_row][out_col] = current_cell;
					out_col++;
				}
			}
		}
	}	
	//print_board(end_board);
}

void do_move2(int start_board[4][4], int end_board[4][4]) {
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
				//std::cout << current_cell << std::endl;
				end_board[row][out_col] = current_cell;
				break; //we have come to the last column, just update end_board and exit
			}

			int next_cell = start_board[row][next_col];


			while (next_cell == 0 && next_col < 3) {
				next_col++;
				next_cell = start_board[row][next_col];
			}

			if (next_cell == current_cell) { // they are the same.
				end_board[row][out_col] = current_cell + next_cell;
				out_col++;
				col = next_col+1;
			}
			else {
				end_board[row][out_col] = current_cell;
				out_col++;
				col = next_col;
			}			
		}
	}
}

//transpose the board so that the rows become columns and columns become rows. 
//this is hardcoded for this exact problem
void transpose(int board[4][4]) {
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
void reverse(int board[4][4]) {
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