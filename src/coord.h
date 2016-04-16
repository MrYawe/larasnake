#ifndef COORD_H
#define COORD_H

#include <stdbool.h>

typedef struct Coord *Coord;
struct Coord
{
	int x;
	int y;
};

Coord coordNew(int x, int y);
bool coordEquals(Coord c1, Coord c2);

#endif