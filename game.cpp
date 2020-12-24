#include "game.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>     // openGL header
#include <GL/glu.h>   // glut header
#include <GL/glut.h>
#include "stb_image.h"
#include <iostream>
#include <string.h>

int gridX,gridY;
void showGrid();
int gridX1=15;
int gridY1=16;
bool endGame = false;
extern bool startGame;
extern char gameOver[30];
extern GLuint rock,scissors,paper;
float cubeSize = 30.0f;
float offset = 10.0f;
extern int score;

void countScore(int);

/*struct coords{
  float x,y,z;
  float r,g,b;
  const char *id;
};
*/
struct coords p[15][15];



void initGrid(int x,int y){
  gridX=x;
  gridY=y;
  createGrid(false);
}

int gameMode(bool start){
  if (start == false){
    return 0;
  }
  else{
    int r = (rand()%5)+1;
    return r;
  }
}

void rgbHelper(float r,float g,float b,int x,int y){
  p[x][y].r =r;
  p[x][y].g=g;
  p[x][y].b=b;
}

int toNum(const char* id,int i){
  if(i==1){
    if(id=="s")
      return 1;
    else if(id=="r")
      return 2;
    else if(id=="p")
      return 3;
   }
   if(i==2){
    if(id=="p")
      return 1;
    else if(id=="r")
      return 2;
    else if(id=="s")
      return 3;
    }
}

void explosionDistance1(int x,int y,int c){
  if(toNum(p[x][y].id,1)==1 || toNum(p[x][y].id,1)==2 || toNum(p[x][y].id,1)==3){
    //orizontia
    if(c==1){
      int x1[]={x-2,x-1,x,x+1,x+2,x+1,x,x-1};
      int y1[]={y,y+1,y+1,y+1,y,y-1,y-1,y-1};
      for(int i=0;i<8;i++){
        if(x1[i]<15 && x1[i]>=0 && y1[i]<15 && y1[i]>=0 ){
          if((toNum(p[x][y].id,1)%3)+1 != toNum(p[x1[i]][y1[i]].id,1)){
              rgbHelper(0,0,0,x1[i],y1[i]);
              p[x1[i]][y1[i]].id="black";
              countScore(2);
          }
          else{
            countScore(-1);
          }
        }
      }
    }
    //katheta
    if(c==2){
      int x1[]={x,x+1,x+1,x+1,x,x-1,x-1,x-1};
      int y1[]={y+2,y+1,y,y-1,y-2,y-1,y,y+1};
      for(int i=0;i<8;i++){
        if(x1[i]<15 && x1[i]>=0 && y1[i]<15 && y1[i]>=0 ){
          if((toNum(p[x][y].id,1)%3)+1 != toNum(p[x1[i]][y1[i]].id,1)){
              rgbHelper(0,0,0,x1[i],y1[i]);
              p[x1[i]][y1[i]].id="black";
              countScore(2);
          }
          else{
            countScore(-1);
          }
        }
      }
    }
  }
}

void explosionDistance2_3(int x,int y,int c){
  if(toNum(p[x][y].id,2)==1 || toNum(p[x][y].id,2)==2 || toNum(p[x][y].id,2)==3){
    //orizontia
    if(c==1){
      int x1[]={x-3,x-1,x,x+1,x+3,x+1,x,x-1,x-4,x-1,x,x+1,x+4,x+1,x,x-1};
      int y1[]={y,y+2,y+2,y+2,y,y-2,y-2,y-2,y,y+3,y+3,y+3,y,y-3,y-3,y-3};
      for(int i=0;i<8;i++){
        if(x1[i]<15 && x1[i]>=0 && y1[i]<15 && y1[i]>=0 ){
          if((toNum(p[x][y].id,2)%3)+1 == toNum(p[x1[i]][y1[i]].id,2)){
              rgbHelper(0,0,0,x1[i],y1[i]);
              p[x1[i]][y1[i]].id="black";
              countScore(3);
          }
          else{
            countScore(-3);
          }
        }
      }
    }
    //katheta
    if(c==2){
      int x1[]={x,x+2,x+2,x+2,x,x-2,x-2,x-2,x,x+3,x+3,x+3,x,x-3,x-3,x-3};
      int y1[]={y+3,y+1,y,y-1,y-3,y-1,y,y+1,y+4,y+1,y,y-1,y-4,y-1,y,y+1};
      for(int i=0;i<8;i++){
        if(x1[i]<15 && x1[i]>=0 && y1[i]<15 && y1[i]>=0 ){
          if((toNum(p[x][y].id,2)%3)+1 == toNum(p[x1[i]][y1[i]].id,2)){
              rgbHelper(0,0,0,x1[i],y1[i]);
              p[x1[i]][y1[i]].id="black";
              countScore(3);
          }
          else{
            countScore(-3);
          }
        }
      }
    }
  }
}


void unit(int x,int y,bool start){
  int a = gameMode(start);
  if(a==0){
    p[x][y].id="mpez";
    rgbHelper(1.0,0.871,0.778,x,y);
  }
  if(a==1){
    p[x][y].id="red";
    rgbHelper(1,0,0,x,y);
  }
  if(a==2){
    p[x][y].id="blue";
    rgbHelper(0,0,1,x,y);
  }
  if(a==3){
    rgbHelper(1,1,1,x,y);
    p[x][y].id="s";

  }
  if(a==4){
    rgbHelper(1,1,1,x,y);
    p[x][y].id ="r";
  }
  if(a==5){
    rgbHelper(1,1,1,x,y);
    p[x][y].id ="p";

  }
}

void createGrid(bool start){
  float ofi = 0;
  float ofj = 0;
  int i,j;
  for(i=0;i<gridX;i++){
    ofj=0;
    for(j=0;j<gridY;j++){

      p[i][j].x = ofi;
      p[i][j].y = ofj;
      p[i][j].z = -1.0f;

      unit(i,j,start);

      ofj+=1.4;
    }
    ofi+=1.4;
  }
}

void showGrid(){
  for(int i=0;i<gridX;i++){
    for(int j=0;j<gridY;j++){
      glStencilFunc(GL_ALWAYS,(gridX*i+j)+1,-1);
      if(strcmp(p[i][j].id,"mpez")==0 || strcmp(p[i][j].id,"red")==0 || strcmp(p[i][j].id,"blue")==0 || strcmp(p[i][j].id,"black")==0){
        glColor3f(p[i][j].r,p[i][j].g,p[i][j].b);
        glPushMatrix();
        glTranslatef(p[i][j].x-(gridX1/2+(gridX1-1)*0.2), p[i][j].y-(gridY1/2+(gridY1-1)*0.2), p[i][j].z -29.0);
        glutSolidCube(1);
        glPopMatrix();
      }

      if(strcmp(p[i][j].id,"r")==0){
        glColor3f(p[i][j].r,p[i][j].g,p[i][j].b);
        glBindTexture(GL_TEXTURE_2D,rock);

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        //glEnable(GL_TEXTURE_GEN_Q);
        //glEnable(GL_TEXTURE_GEN_R);
        glPushMatrix();
        glTranslatef(p[i][j].x-(gridX1/2+(gridX1-1)*0.2), p[i][j].y-(gridY1/2+(gridY1-1)*0.2), p[i][j].z -29.0);
        glutSolidCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        //glDisable(GL_TEXTURE_GEN_Q);
        glDisable(GL_TEXTURE_GEN_R);
        glDisable(GL_TEXTURE_2D);

      }

      if(strcmp(p[i][j].id,"s")==0){
        glColor3f(p[i][j].r,p[i][j].g,p[i][j].b);
        glBindTexture(GL_TEXTURE_2D,scissors);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glEnable(GL_TEXTURE_GEN_R);
        glPushMatrix();
        glTranslatef(p[i][j].x-(gridX1/2+(gridX1-1)*0.2), p[i][j].y-(gridY1/2+(gridY1-1)*0.2), p[i][j].z -29.0);
        glutSolidCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_GEN_R);
        glDisable(GL_TEXTURE_2D);
      }

      if(strcmp(p[i][j].id,"p")==0){
        glColor3f(p[i][j].r,p[i][j].g,p[i][j].b);
        glBindTexture(GL_TEXTURE_2D,paper);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glEnable(GL_TEXTURE_GEN_R);
        glPushMatrix();
        glTranslatef(p[i][j].x-(gridX1/2+(gridX1-1)*0.2), p[i][j].y-(gridY1/2+(gridY1-1)*0.2), p[i][j].z -29.0);
        glutSolidCube(1);
        glPopMatrix();
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        glDisable(GL_TEXTURE_GEN_R);
        glDisable(GL_TEXTURE_2D);
      }
      //printf("(%f,%f)(%f,%f,%f) %s\n", p[i][j].x,p[i][j].y,p[i][j].r,p[i][j].g,p[i][j].b,p[i][j].id);
    }
  }
}



void darkerColor(int x,int y){
  if(p[x][y].id == "red"){
    rgbHelper(0.545,0,0,x,y);
  }
  else if(p[x][y].id == "blue"){
    rgbHelper(0.098,0.098,0.439,x,y);
  }
  else if(p[x][y].id == "black"){
    rgbHelper(0.1,0.1,0.1,x,y);
  }
  else{
    rgbHelper(0.412,0.412,0.412,x,y);
  }
}

void normalColor(int x,int y){
  if(p[x][y].id == "red"){
    rgbHelper(1,0,0,x,y);
  }
  else if(p[x][y].id == "blue"){
    rgbHelper(0,0,1,x,y);
  }
  else if(p[x][y].id == "black"){
    rgbHelper(0,0,0,x,y);
  }
  else{
    rgbHelper(1,1,1,x,y);
  }
}

void showNeighboors(int x,int y,bool clicked){
  if(clicked){
    darkerColor(x,y);
    if(x+1<15)
      darkerColor(x+1,y);
    if(y+1<15)
      darkerColor(x,y+1);
    if(x-1>=0)
      darkerColor(x-1,y);
    if(y-1>=0)
      darkerColor(x,y-1);
  }
  else{
    normalColor(x,y);
    if(x+1<15)
      normalColor(x+1,y);
    if(y+1<15)
      normalColor(x,y+1);
    if(x-1>=0)
      normalColor(x-1,y);
    if(y-1>=0)
      normalColor(x,y-1);
  }
  printf("%s\n",p[x][y].id);
}

void changeNeighbors(int x0,int y0,int x1,int y1){
  float tempr,tempg,tempb;
  const char* tempid;

  tempr=p[x0][y0].r;
  tempg=p[x0][y0].g;
  tempb=p[x0][y0].b;
  tempid=p[x0][y0].id;

  p[x0][y0].r=p[x1][y1].r;
  p[x0][y0].g=p[x1][y1].g;
  p[x0][y0].b=p[x1][y1].b;
  p[x0][y0].id=p[x1][y1].id;

  p[x1][y1].r=tempr;
  p[x1][y1].g=tempg;
  p[x1][y1].b=tempb;
  p[x1][y1].id=tempid;

}

void countScore(int s){
  score+=s;
}

void checkForExplosion(int x,int y){
  if(x+1<15 && x-1>=0){
    if(p[x][y].id==p[x+1][y].id && p[x][y].id==p[x-1][y].id){
      explosionDistance1(x,y,1);
      explosionDistance2_3(x,y,1);
      rgbHelper(0,0,0,x,y);
      p[x][y].id="black";
      rgbHelper(0,0,0,x+1,y);
      p[x+1][y].id="black";
      rgbHelper(0,0,0,x-1,y);
      p[x-1][y].id="black";
      countScore(10);
    }
  }

  if(x+2<15){
    if(p[x][y].id==p[x+1][y].id && p[x][y].id==p[x+2][y].id){
      explosionDistance1(x+1,y,1);
      explosionDistance2_3(x+1,y,1);
      rgbHelper(0,0,0,x,y);
      p[x][y].id="black";
      rgbHelper(0,0,0,x+1,y);
      p[x+1][y].id="black";
      rgbHelper(0,0,0,x+2,y);
      p[x+2][y].id="black";
      countScore(10);

    }
  }

  if(x-2>=0){
    if(p[x][y].id==p[x-1][y].id && p[x][y].id==p[x-2][y].id){
      explosionDistance1(x-1,y,1);
      explosionDistance2_3(x-1,y,1);
      rgbHelper(0,0,0,x,y);
      p[x][y].id="black";
      rgbHelper(0,0,0,x-1,y);
      p[x-1][y].id="black";
      rgbHelper(0,0,0,x-2,y);
      p[x-2][y].id="black";
      countScore(10);

    }
  }

  if(y+1<15 && y-1>=0){
    if(p[x][y].id==p[x][y+1].id && p[x][y].id==p[x][y-1].id){
      explosionDistance1(x,y,2);
      explosionDistance2_3(x,y,2);
      rgbHelper(0,0,0,x,y);
      p[x][y].id="black";
      rgbHelper(0,0,0,x,y+1);
      p[x][y+1].id="black";
      rgbHelper(0,0,0,x,y-1);
      p[x][y-1].id="black";
      countScore(10);

    }
  }

  if(y-2>=0){
    if(p[x][y].id==p[x][y-1].id && p[x][y].id==p[x][y-2].id){
      explosionDistance1(x,y-1,2);
      explosionDistance2_3(x,y-1,2);
      rgbHelper(0,0,0,x,y);
      p[x][y].id="black";
      rgbHelper(0,0,0,x,y-1);
      p[x][y-1].id="black";
      rgbHelper(0,0,0,x,y-2);
      p[x][y-2].id="black";
      countScore(10);

    }
  }

  if(y+2<15){
    if(p[x][y].id==p[x][y+1].id && p[x][y].id==p[x][y+2].id){
      explosionDistance1(x,y+1,2);
      explosionDistance2_3(x,y+1,2);
      rgbHelper(0,0,0,x,y);
      p[x][y].id="black";
      rgbHelper(0,0,0,x,y+1);
      p[x][y+1].id="black";
      rgbHelper(0,0,0,x,y+2);
      p[x][y+2].id="black";
      countScore(10);

    }
  }
}

void eatWeakNeighbors(int x,int y){
    //scissors>paper
    if(x+1<15){
      if(p[x][y].id=="s" && p[x+1][y].id=="p"){
        rgbHelper(0,0,0,x+1,y);
        p[x+1][y].id="black";

        countScore(1);
      }
    }
    if(x-1>0){
      if(p[x][y].id=="s" && p[x-1][y].id=="p"){
        rgbHelper(0,0,0,x-1,y);
        p[x-1][y].id="black";

        countScore(1);
      }
    }
    if(y+1<15){
      if(p[x][y].id=="s" && p[x][y+1].id=="p"){
        rgbHelper(0,0,0,x,y+1);
        p[x][y+1].id="black";

        countScore(1);
      }
    }
    if(y-1>0){
      if(p[x][y].id=="s" && p[x][y-1].id=="p"){
        rgbHelper(0,0,0,x,y-1);
        p[x][y-1].id="black";

        countScore(1);
      }
    }
    //rock>scissors
    if(x+1<15){
      if(p[x][y].id=="r" && p[x+1][y].id=="s"){
        rgbHelper(0,0,0,x+1,y);
        p[x+1][y].id="black";

        countScore(1);
      }
    }
    if(x-1>0){
      if(p[x][y].id=="r" && p[x-1][y].id=="s"){
        rgbHelper(0,0,0,x-1,y);
        p[x-1][y].id="black";

        countScore(1);
      }
    }
    if(y+1<15){
      if(p[x][y].id=="r" && p[x][y+1].id=="s"){
        rgbHelper(0,0,0,x,y+1);
        p[x][y+1].id="black";

        countScore(1);
      }
    }
    if(y-1>0){
      if(p[x][y].id=="r" && p[x][y-1].id=="s"){
        rgbHelper(0,0,0,x,y-1);
        p[x][y-1].id="black";

        countScore(1);
      }
    }
    //paper>rock
    if(x+1<15){
      if(p[x][y].id=="p" && p[x+1][y].id=="r"){
        rgbHelper(0,0,0,x+1,y);
        p[x+1][y].id="black";

        countScore(1);
      }
    }
    if(x-1>0){
      if(p[x][y].id=="p" && p[x-1][y].id=="r"){
        rgbHelper(0,0,0,x-1,y);
        p[x-1][y].id="black";

        countScore(1);
      }
    }
    if(y+1<15){
      if(p[x][y].id=="p" && p[x][y+1].id=="r"){
        rgbHelper(0,0,0,x,y+1);
        p[x][y+1].id="black";

        countScore(1);
      }
    }
    if(y-1>0){
      if(p[x][y].id=="p" && p[x][y-1].id=="r"){
        rgbHelper(0,0,0,x,y-1);
        p[x][y-1].id="black";

        countScore(1);
      }
    }
    //reverse
    //paper<scissors
    if(x+1<15){
      if(p[x][y].id=="p" && p[x+1][y].id=="s"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(x-1>0){
      if(p[x][y].id=="p" && p[x-1][y].id=="s"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(y+1<15){
      if(p[x][y].id=="p" && p[x][y+1].id=="s"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(y-1>0){
      if(p[x][y].id=="p" && p[x][y-1].id=="s"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    //scissors<rock
    if(x+1<15){
      if(p[x][y].id=="s" && p[x+1][y].id=="r"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(x-1>0){
      if(p[x][y].id=="s" && p[x-1][y].id=="r"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(y+1<15){
      if(p[x][y].id=="s" && p[x][y+1].id=="r"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(y-1>0){
      if(p[x][y].id=="s" && p[x][y-1].id=="r"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    //rock<paper
    if(x+1<15){
      if(p[x][y].id=="r" && p[x+1][y].id=="p"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(x-1>0){
      if(p[x][y].id=="r" && p[x-1][y].id=="p"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(y+1<15){
      if(p[x][y].id=="r" && p[x][y+1].id=="p"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
    if(y-1>0){
      if(p[x][y].id=="r" && p[x][y-1].id=="p"){
        rgbHelper(0,0,0,x,y);
        p[x][y].id="black";

        countScore(1);
      }
    }
}

bool notBlack(int x,int y){
  if(p[x][y].id!="black"){
    return true;
  }
  else
    return false;
}



void checkMovesCount(int movesCount){
  if(movesCount==30){

    endGame = true;
    startGame=false;
  }
}
