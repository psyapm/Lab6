#ifndef ___MyScene__
#define ___MyScene__
#include <gl/glut.h> // include freeglut libraries
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>
int width;                                   // initialise global window variables
int height;                                   // define in your header: int width, height;
int prevTime;
float runTime;
void setup();
void reshape(int _width, int _height);
void draw();
int main(int argc, char **argv);
void checkGLError();                        // Prints any OpenGL errors to console

#endif

#include <stdio.h>
#include "Tree.h"
#include <string>
#include <map>

float camrad, camangle = 0.f;
float eye[3];
float cen[3];

void setup();
void reshape(int _width, int _height);
void draw();
void setGlobalLight();
void positionCamera();
void cameraRadius();

void keyPressed(int keyCode, int xm, int ym);
void keyPressed(unsigned char key, int xm, int ym);

int main(int argc, char **argv);
void checkGLError(); // Prints any OpenGL errors to console

