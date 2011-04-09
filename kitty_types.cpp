#include "kitty_types.h"

/**
 * Point constructor
 */
point::point()
{
	this->x = 0;
	this->y = 0;
}

/**
 * Point constructor, which sets point coordinates to
 * specified values
 */
point::point(int x, int y)
{
	this->x = x;
	this->y = y;
}

