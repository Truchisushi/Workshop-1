#include "Solver.h"
#include <time.h>
#include <random>
#include <iostream>



Solver::Solver()
{
}

int Solver::random_move()
{
	int move;
	move = rand() % 4;

	return move;
}

int Solver::greedy_move(Board * board)
{
	//Test all move_types (0, 1, 2, 3)
	//test 1
	int dif1=0, dif2 = 0, best_move = 0;
	for (int move = 0; move < 4; ++move) {
		dif2 = board->test_move(move);
		if (dif2 > dif1) {
			dif1 = dif2;
			best_move = move;
		}
			
	}

	if (dif1 == 0) return random_move();
	else return best_move;
}

int Solver::corner_moves(Board * board, bool advanced)
{
	int dif = 0;

	if (board->last_move == 3) {
		if (board->test_move(0, 1)) return 0; //Try left move
		else if (board->test_move(3, 1)) return 3; //Try down move
	}
	else {
		if (board->test_move(3, 1)) return 3; //Try down move
		else if (board->test_move(0, 1)) return 0; //Try left move
	}


	if (advanced == 0) {
		if (board->test_move(2, 1)) return 2;
		else return 1;
	}
	else { //advanced continuation
		bool bot_occupied = 1;
		bool left_occupied = 1;

		//Check if all bottom tiles are occupied
		for (int i = 0; i < 4; i++) {
			if (board->tiles[3][i] == 0) {
				bot_occupied = 0;
				break;
			}
		}
		//Check if all left tiles are occupied
		/*for (int i = 0; i < 4; i++) {
			if (board->tiles[i][0] != 0) left_occupied = 1;
		}*/

		if (bot_occupied) { //Don't move up if all bottom tiles are occupied. Move right instead.
			if (board->test_move(2, 1)) return 2;
			else return 1;
		}
		else {
			if (board->test_move(1, 1)) return 1; //Move up
			else return 2;
		}
	}
}


Solver::~Solver()
{
}
