/*
Authors	: Adam Lindberg, Daniel Trochez
Date	:	2018-02-02

*/


#include <iostream>
#include <time.h>
#include <math.h>
#include <algorithm>
#include "Solver.h"
#include "Board.h"

int const sample_size = 10;
int scores[sample_size];
double v = 0.0;
double sd = 0.0;

//double standard_dev();
double variance(double my);
double standard_deviation(double v);
int min_score(double my);
int max_score(double my);

//void print_board(int board[4][4]);

int main() {
	int move_type = -1;

	Solver solver;
	Board board;
	double scores_sum = 0;
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
				scores[i] = board.get_score();
				break;
			}
		}
	}

	std::cout << "Average score: " << (scores_sum / sample_size) << std::endl;
	std::cout << "Population Variance: " << variance(scores_sum / sample_size) << std::endl;
	std::cout << "Standard Deviation: " << standard_deviation(v) << std::endl;
	std::cout << "Min score: " << min_score(scores_sum / sample_size) << std::endl;
	std::cout << "Max score: " << max_score(scores_sum / sample_size) << std::endl;

	while (1) {};
}
//Population variance
int min_score(double my) {
	int m = my;

	for (int i = 0; i < sample_size; ++i) {
		m = std::min(m, scores[i]);
	}
	return m;
}

int max_score(double my) {
	int m = my;

	for (int i = 0; i < sample_size; ++i) {
		m = std::max(m, scores[i]);
	}
	return m;
}


double variance(double my) 
{
	for (int i = 0; i < sample_size; ++i) {
		v += (scores[i] - my)*(scores[i] - my);
	}
	v = v / sample_size;
	return v;
}

double standard_deviation(double v) {
	sd = std::sqrt(v);
	return sd;
}

