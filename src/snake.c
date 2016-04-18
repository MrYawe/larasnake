/**
 * \file snake.c
 * \author groupe Larakis
 * \version 1
 * \date 21/02/2016
 * \brief Everything about the snake class
 * \details Contains all functions to manage the snake
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "constants.h"

// Headers for static functions of snake file
static void snakeAddFirstElement(Snake *s, int posX, int posY, Direction orientation);
static void snakeAddLastElement(Snake *s, int posX, int posY, Direction orientation);
static void snakeDeleteFirstElement(Snake *s);
//static void snakeDeleteLastElement(Snake *s);
//static int mod(int a, int b);

/**
 * \struct Snake
 * \brief The snake structure
 * \details The snake structure with all the snake attributes
 **/
struct Snake
{
	int id;
	Element *first;
	Element *last;
	int size;
	int speed;
	Direction direction;
	SnakeType type;
	bool isGhost;
};

/**
 * \struct Element
 * \brief The whole body of the snake
 * \details The Element structure which is a chained list which represents the body of the snake
 **/
struct Element
{
	int posX;
	int posY;
	Element *next;
	Element *previous;
	Direction orientation;
};

/**
 * \fn snakeCreate
 * \brief The function creates and returns a pointer to the snake
 * \details The function store a snake structure in the memory, initialize it and returns a pointer to this structure
 * \param size Int which correspond to the size of the created snake
 * \param id Int which represents the id to set to the created snake
 * \param d Direction initial of the snake
 * \return Pointer to the created snake
 */
Snake* snakeCreate(int size, int id, Direction d, SnakeType type)
{
	Snake *s = malloc(sizeof(struct Snake));
	s->first = NULL;
	s->last = NULL;
	s->size = 0;
	s->speed = SNAKE_DEFAULT_SPEED;
	s->id = id;
	s->direction = d;
	s->isGhost = false;
	//srand(rand()*time(NULL));
	//s->type = (int)rand()%NB_TYPES;
	s->type = type;
	int i;
	for (i=0; i<size; i++)
	{
		snakeAddFirstElement(s, 0, 0, s->direction);
	}
	return s;
}

/**
 * \fn snakeGoUp
 * \brief The function edit the snake to move it to the upper cell
 * \details The function add an element and delete the tail of the snake to make it go UP
 * \param s Snake to edit
 */
void snakeGoUp(Snake *s)
{
	snakeAddLastElement(s, s->last->posX, s->last->posY - 1, s->direction);
	//snakeAddLastElement(s, s->last->posX, mod(s->last->posY - 1, BOARD_SIZE));
	snakeDeleteFirstElement(s);
	s->direction = UP;
}

/**
 * \fn snakeGoDown
 * \brief The function edit the snake to move it to the lower cell
 * \details The function add an element and delete the tail of the snake to make it go DOWN
 * \param s Snake to edit
 */
void snakeGoDown(Snake *s)
{
	snakeAddLastElement(s, s->last->posX, s->last->posY + 1, s->direction);
	//snakeAddLastElement(s, s->last->posX, mod(s->last->posY + 1, BOARD_SIZE));
	snakeDeleteFirstElement(s);
	s->direction = DOWN;
}

/**
 * \fn snakeGoLeft
 * \brief The function edit the snake to move it to the left cell
 * \details The function add an element and delete the tail of the snake to make it go LEFT
 * \param s Snake to edit
 */
void snakeTurnLeft(Snake *s)
{
	snakeAddLastElement(s, s->last->posX - 1, s->last->posY, s->direction);
	//snakeAddLastElement(s, mod(s->last->posX - 1, BOARD_SIZE), s->last->posY);
	snakeDeleteFirstElement(s);
	s->direction = LEFT;
}

/**
 * \fn snakeGoRight
 * \brief The function edit the snake to move it to the right cell
 * \details The function add an element and delete the tail of the snake to make it go RIGHT
 * \param s Snake to edit
 */
void snakeTurnRight(Snake *s)
{
	snakeAddLastElement(s, s->last->posX + 1, s->last->posY, s->direction);
	//snakeAddLastElement(s, mod(s->last->posX + 1, BOARD_SIZE), s->last->posY);
	snakeDeleteFirstElement(s);
	s->direction = RIGHT;
}

/**
 * \fn snakeTeleportation
 * \brief The function allow the snake to teleport himself to an other cell
 * \details The function move the head of the snake to an other cell of the board
 * \param s Snake to edit
 * \param posX Int: X Position which is the target cell
 * \param posY Int: Y Position which is the target cell
 */
void snakeTeleportation(Snake *s, int posX, int posY)
{
	snakeAddLastElement(s, posX, posY, s->direction);
	snakeDeleteFirstElement(s);
}

/**
 * \fn snakeGetPos
 * \brief The function returns the coordinates of a bloc
 * \details The function iterates on the snake blocs and returns the correct position
 * \param s Snake to get
 * \param posBloc Int which is the number of the bloc to get
 * \return Returns the Coord of the bloc
 */
Coord snakeGetPos(Snake *s, int posBloc)
{
	Coord res = coordNew(0,0);
	if (posBloc < 0 || posBloc >= s->size)
	{
		printf("snakeGetPosition : Error pos parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posBloc; i++)
		{
			e = e->next;
		}
		res->x=e->posX;
		res->y=e->posY;
	}
	return res;
}

/**
 * \fn snakeGetDirection
 * \brief The function returns the value of the direction of the snake
 * \details The function returns the value of direction of the structure snake
 * \param s Snake : The snake to access
 * \return Returns Direction which correspond to the direction of the current snake
 */
Direction snakeGetDirection(Snake *s)
{
	return s->direction;
}

/**
 * \fn snakeSetDirection
 * \brief The function allow to set a value in the structure snake
 * \details The function test if the snake can't go backward and put the value in the snake structure
 * \param s Snake : Represents the snake to set
 * \param d Direction : Represents the direction to set to the snake
 */
void snakeSetDirection(Snake *s, Direction d)
{
	bool update = true;
	switch (s->direction)
	{
		case UP:
			if (d == DOWN)
				update = false;
		break;
		case DOWN:
			if (d == UP)
				update = false;
		break;
		case LEFT:
			if (d == RIGHT)
				update = false;
		break;
		case RIGHT:
			if (d == LEFT)
				update = false;
		break;
		default:
		break;
	}
	if (update)
	{
		s->direction = d;
	}
}


/**
 * \fn snakeGetSize
 * \brief The function returns the size of the snake
 * \details The function returns the attribute "size" of the snake
 * \param s Snake to access
 * \return Int: size of the snake
 */
int snakeGetSize(Snake *s)
{
	return s->size;
}

/**
 * \fn snakeGetSpeed
 * \brief The function returns the speed of the snake
 * \details The function returns the attribute "speed" of the snake
 * \param s Snake to access
 * \return Int: speed of the snake
 */
int snakeGetSpeed(Snake *s)
{
	return s->speed;
}

/**
 * \fn snakeSetSpeed
 * \brief The function sets the speed of the snake
 * \details The function sets a value to the attribute "speed" of the snake
 * \param s Snake to access
 * \param speed Int: speed to set
 */
void snakeSetSpeed(Snake *s, int speed)
{
	s->speed = speed;
}


/**
 * \fn snakeElementGetOrientation
 * \brief The function returns the orientation of an Element of the snake
 * \details The function returns the orientation of the posElem number Element of the snake
 * \param s Snake to access
 * \param posElem Int: number of the Element to access
 * \return Direction: Direction of the Element 
 */
Direction snakeElementGetOrientation(Snake *s, int posElem)
{
	Direction res = 0;
	if (posElem < 0 || posElem >= s->size)
	{
		printf("snakeElementGetOrientation : Error posElem parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posElem; i++)
		{
			e = e->next;
		}
		res = e->orientation;
	}
	return res;
}

/**
 * \fn snakeElementSetOrientation
 * \brief The function sets the orientation of an Element of the snake
 * \details The function sets the orientation of the posElem number Element of the snake
 * \param s Snake to access
 * \param posElem Int: number of the Element to access
 * \param d Direction: Direction to set to the Element to access 
 */
void snakeElementSetOrientation(Snake *s, int posElem, Direction d)
{
	if (posElem < 0 || posElem >= s->size)
	{
		printf("snakeElementSetOrientation : Error posElem parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posElem; i++)
		{
			e = e->next;
		}
		e->orientation = d;
	}
}


/**
 * \fn snakeSetGhost
 * \brief The function manage the ghost attribute to the snake
 * \details The function allows to edit the ghost attritute
 * \param s Snake to access
 * \param b Bool: value of the ghost attribute
 */
void snakeSetGhost(Snake *s, bool b)
{
	s->isGhost = b;
}


/**
 * \fn snakeIsGhost
 * \brief Accessor of the ghost attribute of the snake
 * \details The function allows to get the value of the ghost attritute
 * \param s Snake to access
 * \return Bool: value of the ghost attribute
 */
bool snakeIsGhost(Snake *s)
{
	return s->isGhost;
}

/**
 * \fn snakeGetId
 * \brief Accessor of the id attribute of the snake
 * \details The function allows to get the value of the id attritute
 * \param s Snake to access
 * \return Int: value of the id attribute
 */
int snakeGetId(Snake *s)
{
	return s->id;
}

/**
 * \fn snakeGetType
 * \brief Accessor of the type attribute of the snake
 * \details The function allows to get the value of the type attritute
 * \param s Snake to access
 * \return Int: value of the type attribute
 */
SnakeType snakeGetType(Snake *s)
{
	return s->type;
}

/**
 * \fn snakeSetType
 * \brief The function manage the type attribute to the snake
 * \details The function allows to edit the type attritute
 * \param s Snake to access
 * \param b Bool: value of the type attribute
 */
void snakeSetType(Snake *s, SnakeType t)
{
	s->type = t;
}

/**
 * \fn snakeInverseWay
 * \brief The function allow the snake to inverse himself
 * \details The function inverse the list of the snake
 * \param s Snake to edit
 */
void snakeInverseWay(Snake *s)
{
	Element *tampon = s->first;
	s->first = s->last;

	Element* tempElem = NULL;
	while (tampon)
	{
		Element* suivant = tampon->next;
		tampon->next = tempElem;
		tampon->previous = suivant;
	 	tempElem = tampon;
		tampon = suivant;
	}
	s->last = tempElem;
}

/**
 * \fn snakeDisplay
 * \brief The function allow to print the snake in the console
 * \details The console display all blocs of the snake in the console
 * \param s Snake : The snake to print
 */
void snakeDisplay(Snake *s)
{
	// char const* direc[] = {"le haut", "la gauche", "la droite", "le bas", "indéfini"};
	// printf("Le snake va vers %s\n", direc[s->direction]);
	// printf("L'id du snake est : %d\n", s->id);
	// char const* type[] = {"feu", "eau", "plante"};
	// printf("Le type du snake est : %s\n", type[s->type]);
	printf("\n");printf("\n");
	Element *curseur = s->first;
	int i=0;
	while(curseur != NULL)
	{
		printf("Actuel : %p | précédent : %p | suivant %p | posX %d | posY %d\n", curseur, curseur->previous, curseur->next, curseur->posX, curseur->posY);
		//printf("Maillon %d : [posX: %d, posY: %d]\n", i, curseur->posX, curseur->posY);
		curseur = curseur->next;
		i++;
	}
}

/**
 * \fn snakeUpdateElement
 * \brief The function update values of an element of the snake
 * \details The function iterates on the list of the elements of the snake and set a value
 * \param s Snake to edit
 * \param posElem Int which is the number of the bloc to get
 * \param posX X value to set to the Element
 * \param posY Y value to set to the Element
 */
void snakeUpdateElement(Snake *s, int posElem, int posX, int posY)
{
	if (posElem < 0 || posElem >= s->size)
	{
		printf("snakeUpdateElement : Error posElem parameter out of range\n");
	}
	else
	{
		int i;
		Element *e = s->first;
		for (i = 0; i < posElem; i++)
		{
			e = e->next;
		}
		e->posX = posX;
		e->posY = posY;
	}
}


/**
 * \fn snakeDelete
 * \brief The function free the memory of the snake
 * \details The function free all the list of Elements of the memory
 * \param s Snake to free from memory
 */
void snakeDelete(Snake *s)
{
	Element *curs = s->first;
	Element *curssuiv;
	while(curs != NULL)
	{
		curssuiv = curs->next;
		free(curs);
		curs = curssuiv;
	}
}


/**
 * \fn snakeAddFirstElement
 * \brief The function add an element at the beginning of the chained list
 * \details The function add an element and set it the correct values and then put this element into the snake
 * \param s Snake to edit
 * \param posX Int: value to set to the element
 * \param posY Int: value to set to the element
 * \param orientation Direction to set to the element
 */
static void snakeAddFirstElement(Snake *s, int posX, int posY, Direction orientation)
{
	Element *e = (Element*) malloc(sizeof(struct Element));
	e->posX = posX;
	e->posY = posY;
	e->orientation = orientation;
	e->previous = NULL;
	if (s->size == 0)
	{
		e->next = NULL;
		s->last = e;
	}
	else
	{
		s->first->previous = e;
		e->next = s->first;
	}
	s->first = e;
	s->size ++;
}

/**
 * \fn snakeAddLastElement
 * \brief The function add an element at the end of the chained list
 * \details The function add an element and set it the correct values and then put this element into the snake
 * \param s Snake to edit
 * \param posX Int: value to set to the element
 * \param posY Int: value to set to the element
 * \param orientation Direction to set to the element
 */
static void snakeAddLastElement(Snake *s, int posX, int posY, Direction orientation)
{
	if (s->size == 0)
	{
		snakeAddFirstElement(s, posX, posY, orientation);
	}
	else
	{
		Element *e = (Element*) malloc(sizeof(struct Element));
		e->posX = posX;
		e->posY = posY;
		e->orientation = orientation;
		e->previous = s->last;
		e->next = NULL;
		s->last->next = e;
		s->last = e;
		s->size++;
	}
}

/**
 * \fn snakeDeleteFirstElement
 * \brief The function delete an element at the beggining of the chained list
 * \details The function delete an element from the snake
 * \param s Snake to edit
 */
static void snakeDeleteFirstElement(Snake *s)
{
	if (s->size == 0)
	{
		printf("snakeDeleteFirstElement : Empty list\n");
	}
	else
	{
		Element *e = s->first;
		s->first = s->first->next;
		s->first->previous = NULL;
		free(e);
		s->size --;
	}
}

/**
 * \fn snakeDeleteLastElement
 * \brief The function delete an element at the end of the chained list
 * \details The function delete an element from the snake
 * \param s Snake to edit
 */
 /*
static void snakeDeleteLastElement(Snake *s)
{
	if (s->size == 0)
	{
		printf("snakeDeleteLastElement : Empty List !\n");
	}
	else
	{
		Element *e = s->last;
		s->last = s->last->previous;
		s->last->next = NULL;
		free(e);
		s->size --;
	}
}
*/

/**
 * \fn mod
 * \brief Mod function
 * \details The function makes a correct modular (negative numbers are correctedly modded)
 * \param a Int: number to mod
 * \param b Int: the number of modular
 */
/*
static int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}
*/
