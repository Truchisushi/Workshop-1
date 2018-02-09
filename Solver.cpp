#include "Solver.h"
#include <time.h>
#include <random>



Solver::Solver()
{
}

int Solver::random_move()
{
	srand(clock());
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


Solver::~Solver()
{
}
