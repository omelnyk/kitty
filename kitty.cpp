#include <iostream>
#include <vector>
#include <algorithm>
#include "kitty_types.h"

using namespace std;

/**
 * Contains values variants for of the cells on the board
 */
typedef cell_variants board_variants[9][9];
 
/**
 * Returns number of the box the given cell belongs to
 */
int get_box_id(int x, int y)
{
	return (y / 3) * 3 + x / 3;
}

/**
 * Returns (x; y) coordinates a cell, identified by the number
 * of box that contains it (box_id) and it's relative number
 * in the box (cell_id)
 */
point get_box_cell(int box_id, int cell_id)
{
	point p;
	p.x = (box_id % 3) * 3 + (cell_id % 3);
	p.y = (box_id / 3) * 3 + (cell_id / 3);
	return p;
}

/**
 * Returns (x; y) coordinates of an empty cell with the fewest
 * value variants. If all cells are non-empty, returns a point
 * with coordinates (-1; -1)
 */
point most_certain_point(board puzzle, board_variants vars)
{
	point min(0, 0);
	bool found = false;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((puzzle[i][j] != 0))
			{
				continue;
			}
			if (!found)
			{
				min.x = i;
				min.y = j;
				found = true;
			}
			else if ((vars[i][j].unrestricted_count < vars[min.x][min.y].unrestricted_count))
			{
				min.x = i;
				min.y = j;
			}
		}
	}

	return min;
}

/**
 * Increases restrictions counter for the specifed
 * variant/value pair
 */
void restrict_value(cell_variants &var, int value)
{
	if (var.restrictions[value] == 0)
	{
		var.unrestricted_count--;
	}
	var.restrictions[value]++;
}

/**
 * Decreases restrictions counter for the specifed 
 * variant/value pair
 */
void unrestrict_value(cell_variants &var, int value)
{
	if (var.restrictions[value] - 1 == 0)
	{
		var.unrestricted_count++;
	}
	var.restrictions[value]--;
}

/**
 * Sets cell with coordinates (x, y) to specified value (value)
 * and updates possible board variants (vars) accordingly; value
 * must be not zero
 */
void set_cell(board puzzle, board_variants vars, int x, int y, int value)
{
	int box_id = get_box_id(x, y);

	puzzle[x][y] = value;

	for (int i = 0; i < 9; i++)
	{
		point p = get_box_cell(box_id, i);
		restrict_value(vars[x][i], value);
		restrict_value(vars[i][y], value);
		restrict_value(vars[p.x][p.y], value);
	}

	for (int i = 1; i < 10; i++)
	{
		restrict_value(vars[x][y], i);
	}
}

/**
 * Unsets cell with coordinates (x, y) and updates possible board
 * variants (vars) accordingly
 */
void unset_cell(board puzzle, board_variants vars, int x, int y)
{
	int box_id = get_box_id(x, y), value = puzzle[x][y];

	puzzle[x][y] = 0;

	for (int i = 0; i < 9; i++)
	{
		point p = get_box_cell(box_id, i);
		unrestrict_value(vars[x][i], value);
		unrestrict_value(vars[i][y], value);
		unrestrict_value(vars[p.x][p.y], value);
	}

	for (int i = 1; i < 10; i++)
	{
		unrestrict_value(vars[x][y], i);
	}
}

/**
 * Solves specified puzzle using a greedy recursive backtracking
 * algorithm; vars should be set to initial board status before
 * call
 */
bool backtrack(board puzzle, board_variants vars, int depth)
{
	point p = most_certain_point(puzzle, vars);
	vector<int> values;
	values.reserve(9);

	if (vars[p.x][p.y].unrestricted_count == 0)
	{
		return (puzzle[p.x][p.y] != 0);
	}

	for (int i = 1; i < 10; i++)
	{
		if (vars[p.x][p.y].restrictions[i] == 0)
		{
			values.push_back(i);
		}
	}

	sort(values.begin(), values.end());

	for (int i = 0; i < values.size(); i++)
	{
		set_cell(puzzle, vars, p.x, p.y, values[i]);
		if (backtrack(puzzle, vars, depth + 1))
		{
			return true;
		}
		unset_cell(puzzle, vars, p.x, p.y);
	}

	return false;
}

/**
 * Solves the problem specified by the first argument and
 * stores its solution in the second argument. Return value
 * indicates whether solution was found. If the problem has
 * no solution, content of the second argument is undefined.
 */
bool solve(board problem, board solution)
{
	board_variants vars;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			solution[i][j] = 0;
			vars[i][j].unrestricted_count = 9;
			for (int k = 0; k < 10; k++)
			{
				vars[i][j].restrictions[k] = 0;
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (problem[i][j] != 0)
			{
				set_cell(solution, vars, i, j, problem[i][j]);
			}
		}
	}

	return backtrack(solution, vars, 0);
}

/**
 * Program entry function
 */
int main(void)
{
	board problem, solution;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> problem[i][j];
		}
	}

	if (solve(problem, solution))
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << solution[i][j];
				if (j != 8)
				{
					cout << ' ';
				}
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No solutions" << endl;
	}

	return 0;
}
