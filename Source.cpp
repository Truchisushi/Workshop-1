/*
Authors	: Adam Lindberg, Daniel Trochez
Date	:	2018-02-02

*/


#include <iostream>
#include <time.h>
#include "Solver.h"
#include "Board.h"

int const sample_size = 1000;
int scores[sample_size];

//void print_board(int board[4][4]);

int main() {
	int move_type = -1;

	Solver solver;
	Board board;
	int scores_sum = 0;
	//board.print_board();

	for (int i = 0; i < sample_size; i++) {
		board.initialize();

		while (1) {
			if (board.can_move()) { //If AI can still move, AI continues
			//std::cin >> move_type; //REPLACE this with AI later

				board.do_move(solver.random_move());

				//board.print_board();
			}
			else { //If AI cannot move, the game has ended
				//std::cout << "Score: " << board.get_score() << std::endl;
				scores_sum += board.get_score();

				break;
			}
		}
	}

	std::cout << "Average score: " << (scores_sum / sample_size) << std::endl;

	while (1) {};
}
