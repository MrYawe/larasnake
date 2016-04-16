#include <stdio.h>
#include <stdlib.h>
#include "coord.h"

Coord coordNew(int x, int y) {
	Coord res = malloc(sizeof(struct Coord));
	res->x=x;
	res->y=y;
	return res;
}

bool coordEquals(Coord c1, Coord c2) {
	bool res = false;
	if(c1->x == c2->x && c1->y == c2->y) {
		res = true;
	}
	return res;
}