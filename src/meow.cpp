/**
 * Meow - Sudoku solution checking tool
 * Copyright (C) 2008  Olexandr Melnyk <me@omelnyk.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include "kitty_types.h"

using namespace std;

/**
 * Board representation. Possible cell values are 0-9, where 1-9
 * stand for corresponding numbers and 0 stands for an empty cell
 */
typedef int board[9][9];

/**
 * Returns whether all cells are assigned value without allowed
 * value range
 */
bool check_cells(board solution)
{
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if ((solution[x][y] <= 0) || (solution[x][y] > 9))
			{
				return false;
			}
		}
	}

	return true;
}

/**
 * Returns whether every row contains only distinct numbers
 */
bool check_rows(board solution)
{
	for (int y = 0; y < 9; y++)
	{
		bool used_numbers[10];

		for (int i = 1; i < 10; i++)
		{
			used_numbers[i] = false;
		}

		for (int x = 0; x < 9; x++)
		{
			if (used_numbers[solution[x][y]])
			{
				return false;
			}

			used_numbers[solution[x][y]] = true;
		}
	}

	return true;
}

/**
 * Returns whether every column contains only distinct numbers
 */
bool check_columns(board solution)
{
	for (int x = 0; x < 9; x++)
	{
		bool used_numbers[10];

		for (int i = 1; i < 10; i++)
		{
			used_numbers[i] = false;
		}

		for (int y = 0; y < 9; y++)
		{
			if (used_numbers[solution[x][y]])
			{
				return false;
			}

			used_numbers[solution[x][y]] = true;
		}
	}

	return true;
}

/**
 * Returns whether every box contains only distinct numbers
 */
bool check_boxes(board solution)
{
	for (int i = 0; i < 9; i++)
	{
		bool used_numbers[10];

		for (int j = 1; j < 10; j++)
		{
			used_numbers[j] = false;
		}

		for (int j = 0; j < 9; j++)
		{
			int x = (i % 3) * 3 + j % 3;
			int y = (i / 3) * 3 + j / 3;
			if (used_numbers[solution[x][y]])
			{
				return false;
			}

			used_numbers[solution[x][y]] = true;
		}
	}

	return true;
}

/**
 * Returns whether preset cells in problem have same values
 * in solution
 */
bool check_correspondence(board problem, board solution)
{
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if (problem[x][y] == 0)
			{
				continue;
			}

			if (solution[x][y] != problem[x][y])
			{
				return false;
			}
		}
	}

    return true;
}

/**
 * Returns whether problem solution is correct
 */
bool is_solution(board problem, board solution)
{
	return check_cells(solution) && check_rows(solution) &&
		check_columns(solution) && check_boxes(solution) &&
		check_correspondence(problem, solution);
}

/**
 * Program entry point
 */
int main(void)
{
	board problem;
	board solution;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> problem[i][j];
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> solution[i][j];
		}
	}

	if (is_solution(problem, solution))
	{
		cout << "Right" << endl;
	}
	else
	{
		cout << "Wrong" << endl;
	}

	return 0;
}

