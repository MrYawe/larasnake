#include <stdio.h>
#include <stdlib.h>
#include "coord.h"

/**
 * \fn Coord coordNew(int x, int y)
 * \brief The function creates a new Coord
 * \details The function store the Coord on the memory
 * \param x Int which correspond to the X value
 * \param y Int which correspond to the Y value
 * \return Pointer to the created Coord
 */
Coord coordNew(int x, int y) {
	Coord res = malloc(sizeof(struct Coord));
	res->x=x;
	res->y=y;
	return res;
}

/**
 * \fn bool coordEquals(Coord c1, Coord c2)
 * \brief The function check if 2 coord are equals
 * \details The function check if X and Y of the 2 coord are the same
 * \param c1 Coord: First coordonate to compare
 * \param c2 Coord: Second coordonate to compare
 * \return Bool : true if it's equals, false if not
 */
bool coordEquals(Coord c1, Coord c2) {
	bool res = false;
	if(c1->x == c2->x && c1->y == c2->y) {
		res = true;
	}
	return res;
}