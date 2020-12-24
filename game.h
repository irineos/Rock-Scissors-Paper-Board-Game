#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

void initGrid(int,int);
void createGrid(bool);
void showGrid();
void showNeighboors(int,int,bool);
void changeNeighbors(int,int,int,int);
void checkMovesCount(int);
void checkForExplosion(int,int);
bool notBlack(int,int);
void drawText(float,float,float,char*);
void eatWeakNeighbors(int,int);

struct coords{
  float x,y,z;
  float r,g,b;
  const char *id;
};

extern struct coords p[15][15];



#endif
