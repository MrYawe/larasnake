typedef struct Board
{
  int** tab;
  int tailleX;
  int tailleY;
} Board;

Board initBoard(int sizeX, int sizeY);
int getValue(Board b, int posx, int posy);
void setValue(Board b, int posx, int posy, int val);
void displayBoard(Board b);
void freeBoard(Board b);

