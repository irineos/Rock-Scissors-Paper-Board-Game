/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */


 #include <stdio.h>
 #include <stdlib.h>
  #include <time.h>
 #include <math.h>
 #include <GL/gl.h>     // openGL header
 #include <GL/glu.h>   // glut header
 #include <GL/glut.h>   // glut header
 #include "game.h"
 #include "stb_image.h"
 #include <iostream>
#include <unistd.h>
#include <string.h>

#define COLUMNS 15
#define ROWS 15

GLuint rock,scissors,paper;
void GoMenu(int);
bool fullscreen = false;
bool startGame = false;
int movesCount=0;
int score=0;
char textMoves[20];
char textScore[20];
char gameOver[30];
extern bool endGame ;
extern struct coords p[15][15] ;
float deltaMove1 = 0;
float deltaMove2 = 0;
float x = 0.0f, y = 0.0f;
bool pressed1,pressed2 = false;
int updown,rightleft=0;


//load images
GLuint loadTextureFromFile(const char *filename)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glShadeModel(GL_FLAT);
	//glEnable(GL_DEPTH_TEST);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

  return texture;
}

void FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);


}

void init(){
  glClearColor(0.0,0.0,0.0,1.0);

}

void drawText(float x,float y,float z,char* string){
  glColor3f(1,1,1);
  glRasterPos3f(x,y,z);
  int len,i;
  len=(int)strlen(string);
  for(i=0;i<len;i++){
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
  }
}

void computePos(float deltaMove,int i) {
  if(i==1)
    x = deltaMove * 0.1f;
  if(i==2)
    y = deltaMove * 0.1f;
}


 //----------------------------------------------//
 // Display                                      //
 //  - clears the screen                         //
 //  - draws the current scene and swaps buffers //
 //----------------------------------------------//
 void display() {

   //glClearColor(0.0, 0.0, 0.0, 1.0);

   glClearStencil(0);

 	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_STENCIL_TEST);
   glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

   if (pressed1 && rightleft<10 && rightleft>-10){
		computePos(deltaMove1,1);
    gluLookAt(x, 0, 0,
 		0, 0, -1,
 		0.0f, 1.0f, 0.0f);
   }
  if (pressed2 && updown<10 && updown>-10){
   computePos(deltaMove2,2);
   gluLookAt(0, y, 0,
   0, 0, -1,
   0.0f, 1.0f, 0.0f);
  }

   //glEnable(GL_TEXTURE_2D);
   glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
   glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

   showGrid();
   //glDisable(GL_TEXTURE_2D);

   sprintf(textMoves,"Moves: %d",movesCount);
   sprintf(textScore,"Score: %d",score);
   sprintf(gameOver,"G A M E   O V E R");



   if(!startGame && endGame){
     glClear(GL_COLOR_BUFFER_BIT);
     drawText(-2.3,2,-18,gameOver);
     drawText(-1.5,1.4,-20.5,textScore);

   }
   if(startGame){
    drawText(-7,7.3,-20.5,textMoves);
    drawText(5,7.3,-20.5,textScore);

  }

   glutSwapBuffers();
 }

 void reshape(GLsizei width, GLsizei height){
   if (height == 0) height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
   glViewport(0,0,width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
   //glMatrixMode(GL_MODELVIEW);
 }




 //------------------------------------------------------//
 // Normal_Keys                                          //
 //  - handles all "normal" keypresses (with ascii code) //
 //------------------------------------------------------//
 void normal_keys(unsigned char key, int x, int y) {
   if (key==27) exit(0);
 }
 //-----------------------------------------------------//
 // Special_Keys                                        //
 //  - handles all "special" keypresses (no ascii code) //
 //-----------------------------------------------------//
 void special_keys(int keys, int x, int y) {
   switch(keys) {
		case GLUT_KEY_F1:       // F1 toggles fullscreen mode
			fullscreen = !fullscreen;
			if (fullscreen) glutFullScreen();
			else glutReshapeWindow(600,600);
			break;

    case GLUT_KEY_LEFT:
      deltaMove1 = -0.1f;
      pressed1=true;
      if(rightleft>-10)
        rightleft-=1;
      break;
    case GLUT_KEY_RIGHT:
      deltaMove1 = 0.1f;
      pressed1=true;
      if(rightleft<10)
        rightleft+=1;
      break;
    case GLUT_KEY_UP:
      deltaMove2 = 0.1f;
      pressed2=true;
      if(updown<10)
        updown+=1;
      break;
    case GLUT_KEY_DOWN:
      deltaMove2 = -0.1f;
      pressed2=true;
      if(updown>-10)
        updown-=1;
      break;
		default:
			break;
	}
  glutPostRedisplay();
 }
 void releaseKey(int key, int x, int y) {

	switch (key) {
  case GLUT_KEY_RIGHT:
  case GLUT_KEY_LEFT:
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: pressed1 = false; pressed2=false; break;
	}
}

 //-----------------------------------------------------//
 // Mouse                                               //
 //  - handles all Mouse clicks                         //
 //-----------------------------------------------------//
 bool clicked = true;
 int temp_xy[2];

 void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
     int window_width = glutGet(GLUT_WINDOW_WIDTH);
     int  window_height = glutGet(GLUT_WINDOW_HEIGHT);

     GLbyte color[4];
     GLfloat depth;
     GLuint index;


     glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
     glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
     glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

     printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
            x, y, color[0], color[1], color[2], color[3], depth, index);

     if(index>0){
       if((index-1)%15>0){
         x = (index-1)/15;
         y = (index-1)%15;
       }
       else{
         x=(index-1)/15;
         y=0;
       }


       if(clicked && startGame){
         temp_xy[0]=x;
         temp_xy[1]=y;
         if(notBlack(x,y)){
          showNeighboors(temp_xy[0],temp_xy[1],clicked);
          clicked = false;
        }
      }
      else if(!clicked && startGame && x==temp_xy[0] && y==temp_xy[1]){
        showNeighboors(x,y,clicked);//unshow
        clicked = true;
      }
      else if(!clicked && startGame && (x==temp_xy[0]+1 && y==temp_xy[1] || x==temp_xy[0] && y==temp_xy[1]+1
                                     || x==temp_xy[0]-1 && y==temp_xy[1] || x==temp_xy[0] && y==temp_xy[1]-1)){

        changeNeighbors(x,y,temp_xy[0],temp_xy[1]);
        showNeighboors(temp_xy[0],temp_xy[1],clicked);    //unshow
        clicked = true;
        movesCount++;
        checkForExplosion(x,y);
        if(p[x][y].id!=p[temp_xy[0]][temp_xy[1]].id){
          checkForExplosion(temp_xy[0],temp_xy[1]);
        }
        eatWeakNeighbors(x,y);
        eatWeakNeighbors(temp_xy[0],temp_xy[1]);

        checkMovesCount(movesCount);
      }

      printf("%d\n",temp_xy[0] );
     }
    glutPostRedisplay();
   }
}


 //menu
 void GoMenu(int val){
    if(val==1){
        createGrid(true);
        startGame=true;
        movesCount=0;
        score=0;
        //showGrid();
    }
    if(val==2){
         exit(0);
    }
   glutPostRedisplay();

 }

void menu(){

    int sub1 = glutCreateMenu(GoMenu);
    glutAddMenuEntry("Start Game", 1);
    glutAddMenuEntry("Exit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}


/* Program entry point */
//const char* filename = "wall.jpg";
main(int argc, char** argv) {
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_STENCIL);
	glutInitWindowSize(600,600);
	glutCreateWindow("BraXaYa III");


  rock = loadTextureFromFile("rock.jpg");
  scissors = loadTextureFromFile("scissors.jpg");
  paper = loadTextureFromFile("paper.jpg");

  initGrid(COLUMNS,ROWS);

	glutDisplayFunc(display);
  //glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(normal_keys);
  glutSpecialFunc(special_keys);
  glutSpecialUpFunc(releaseKey);
  glutMouseFunc(mouse);
  menu();

  init();

  glutMainLoop();

  //Free our texture
  FreeTexture(rock);
  FreeTexture(scissors);
  FreeTexture(paper);
}
