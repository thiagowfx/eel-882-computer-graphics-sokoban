#include "game.hpp"


void sdldie(const char* msg) {
  std::cout << msg << std::endl;
  std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
  exit(1);
}

Game::Game(SDL_Window* window, SDL_GLContext* glContext, int screenWidth, int screenHeight) :
  window(window),
  glContext(glContext),
  screenWidth(screenWidth),
  screenHeight(screenHeight) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    /* Create the OpenGL context. */
    *glContext = SDL_GL_CreateContext(window);
    if(*glContext == NULL) {
      sdldie("OpenGL context could not be created");
    }

    /* OpenGL initialization. */

    /* Z-Depth. */
    glEnable(GL_DEPTH_TEST);

    /*Lighting initializations*/
    glEnable(GL_NORMALIZE);         //Normalizes the normal vectors of every vertex (ie. size = 1)
    glShadeModel(GL_SMOOTH);        //Shadind model is smooth
    glEnable(GL_LIGHTING);          //Enables lighting

    /*Cleans the background and sets it to the RGB parameters*/
    glClearColor(0.5, 0.5, 0.5, 1.0);

    /*Sets the Projection Matrix to the Identity*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*Defines the camera's properties: where it is, where it's looking at, the up vector*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0, 4.0, 2.0, 0, 0, 0, 0, -0.1, 1); //camera's initial position at (4,4,2), looking at (0,0,0) and up = (0,-0.1,1)

    sokoReshape();
  }

Game::~Game() {

}

void Game::renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*Ambient's lighting - eg. Light all around despite the light sources*/
  GLfloat ambientIntesity[4] = {1.5, 1.5, 1.5, 1.0};          //Ambient's light is white
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntesity);

  /*Light source number 0*/
  GLfloat light0Intensity[4] = {0, 1, 0, 1.0};                 //Light0 is green
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0Intensity);          //For specular reflection
  GLfloat light0Position[4] = {1, 1, 0, 0};                    //Light0's position
  glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT0);

  /*Light source number 1*/
  GLfloat light1Intensity[4] = {1.0, 0, 0, 1.0};               //Light1 is red
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1Intensity);          //For specular reflection
  GLfloat light1Position[4] = {1, 0, 1, 0};                    //Light1's position
  glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
  glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT1);

  /*Light source number 1*/
  GLfloat light2Intensity[4] = {1.0, 1.0, 0, 1.0};             //Light2 color
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2Intensity);           //For diffuse reflection
  glLightfv(GL_LIGHT2, GL_SPECULAR, light2Intensity);          //For specular reflection
  GLfloat light2Position[4] = {0, 1, 1, 0};                    //Light2's position
  glLightfv(GL_LIGHT2, GL_POSITION, light2Position);
  glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0);             //Attenuation
  glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0); 
  glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.1);
  glEnable(GL_LIGHT2);


  /*Objects drawing*/
  glMatrixMode(GL_MODELVIEW);

  /*Reads phase file and draws the scene*/
  using namespace std;
  ifstream phase;
  string line;
  phase.open("map1.txt");
  if( phase.is_open()){
    int row = -3;
    while ( getline(phase, line) ){
      int column = -3;
      istringstream streamLine(line);
      while (! streamLine.eof()){
        int number;
        streamLine >> number;
        double const size = 0.5;
        if (number == 0){
          drawCube(row, column, 0, size);         //drawing empty floor
        }
        else if(number == 1){
          //add character texture and draws character here
          drawCube(row, column, 0, size);         //drawing character's floor
        }
        else if(number == 2){
          drawCube(row, column, 0, size);         //drawing light box's floor
          //add light box texture here
          //drawCube(row*size, column*size, 0.5, size);       //drawing light box
        }
        else if(number == 3){
          drawCube(row, column, 0, size);         //drawing heavy box's floor
          //add heavy box texture here
          //drawCube(row*size, column*size, 0.5, size);       //drawing heavy box
        }
        else if (number == 4){
          drawCube(row, column, 0, size);         //drawing the walls' floor
          //add wall texture here
          drawCube(row, column, 0.5, size);       //drawing the walls
        }
        else if (number == 5){
          //add target texture here
          //drawCube(row*size, column*size, 0, size);         //drawing the target
        }
        column ++;
      }
    row ++; 
    }
    phase.close();
  }
  else cout << "Unable to open file" << endl;

  glFlush();
  SDL_GL_SwapWindow(window);
}

void Game::drawCube(GLdouble x, GLdouble y, GLdouble z, GLdouble edge)
{
  /* This function draws a cube of size (edge x edge x edge) centered at position (x, y, z)*/
  GLdouble halfEdge = edge/2;
  glEnable(GL_TEXTURE_2D);


  /*coloring the cube*/
  GLfloat color[4] = {0, 0.3, 1, 1};                                      //Cube's color
  GLfloat white[4] = {1, 1, 1, 1};                                        //White
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);         //Ambient and diffuse reflections
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);                    //Specular reflection
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);                      //Shininess is 100


  glPushMatrix();
  glTranslatef(x*size, y*size, z);

  glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0, 0, -1);  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 0, -1);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 0, -1);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);  glVertex3f(  halfEdge, -halfEdge, halfEdge );
    glNormal3f(0, 0, 1);  glVertex3f(  halfEdge,  halfEdge, halfEdge );
    glNormal3f(0, 0, 1);  glVertex3f( -halfEdge,  halfEdge, halfEdge );
    glNormal3f(0, 0, 1);  glVertex3f( -halfEdge, -halfEdge, halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge, -halfEdge, -halfEdge );
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge,  halfEdge, -halfEdge );
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge,  halfEdge,  halfEdge );
    glNormal3f(1, 0, 0);  glVertex3f( halfEdge, -halfEdge,  halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge,  halfEdge,  halfEdge );
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(-1, 0, 0);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);  glVertex3f(  halfEdge,  halfEdge,  halfEdge );
    glNormal3f(0, 1, 0);  glVertex3f(  halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 1, 0);  glVertex3f( -halfEdge,  halfEdge, -halfEdge );
    glNormal3f(0, 1, 0);  glVertex3f( -halfEdge,  halfEdge,  halfEdge ); 
  glEnd();

  glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);  glVertex3f(  halfEdge, -halfEdge, -halfEdge );
    glNormal3f(0, -1, 0);  glVertex3f(  halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0, -1, 0);  glVertex3f( -halfEdge, -halfEdge,  halfEdge );
    glNormal3f(0, -1, 0);  glVertex3f( -halfEdge, -halfEdge, -halfEdge );
  glEnd();

  glFlush();
  glPopMatrix();
}

void Game::setOldPosition(GLdouble x, GLdouble y) {
  this->oldx = x;
  this->oldy = y;
}

void Game::setNewPosition(GLdouble xnew, GLdouble ynew) {
  int passo_x = xnew - oldx;
  int passo_y = ynew - oldy;

  setOldPosition(xnew, ynew);

  glMatrixMode(GL_MODELVIEW);
    glRotatef(atan(2*passo_x), 0, 0, 1);
    glRotatef(atan(2*passo_y), 0, 1, 0);

  SDL_GL_SwapWindow(window);
}

void Game::sokoReshape() {
  // TODO: atualizar screenWidth, screenHeight
  glViewport (0, 0, screenWidth, screenHeight);	//Changes the viewport to the whole window
  
  //sets projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (GLdouble)screenWidth/(GLdouble)screenHeight, 1.0, 10.0) ;
  glMatrixMode(GL_MODELVIEW);
}
