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
