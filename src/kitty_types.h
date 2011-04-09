/**
 * Kitty - greedy backtracking-based Sudoku solver
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

#ifndef _KITTY_TYPES_H
#define _KITTY_TYPES_H 1

/**
 * Board representation. Possible cell values are 0-9, where 1-9
 * stand for corresponding numbers and 0 stands for an empty cell
 */
typedef int board[9][9];

/**
 * Signifies which values a given cell can contain. For example:
 * if flags[5] is set to true, then cell can contain value 5.
 * count should be set to a number of flags, which are true.
 * flag[0] is reserved for convenience and should not be included
 * in count value
 */
struct cell_variants
{
	int unrestricted_count;
	int restrictions[10];
};

/**
 * Coordinates container for a point on a two-dimensional
 * surface
 */
struct point
{
public:

	int x;
	int y;

	point();
	point(int x, int y);
};

#endif
