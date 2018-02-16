#ifndef SOLVER_H
#define SOLVER_H
#include "Board.h"
class Solver
{
public:
	Solver();
	int random_move();
	int greedy_move(Board *);
	int corner_moves(Board *, bool advanced = 0);
	~Solver();
};

#endif


