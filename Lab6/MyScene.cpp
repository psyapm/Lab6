#ifndef ___MyScene__
#define ___MyScene__
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <map>
#include "Tree.h"
#include "Horse.h"
#include "Stage.h"
int width, height;                          // define global window size variables
int prevTime;                               // for calculating animation time

map<string, DisplayableObject*> objects;     // define map of DisplayableObjects

void setup();                               // for window setup and Object creation
void draw();                                // rendering function
void reshape(int _width, int _height);      // to handle resizing window

int main(int argc, char **argv);
float runtime();                            // calculates difference in time between last call

void checkGLError();                        // display and OpenGL errors to console
void destroyObjects();                      // destroy objects from memory on close
#endif

#include "MyScene.h"
using namespace std;

void setup()
{
	width = 600;                                   // initialise global window variables
	height = 400;                                   // define in your header: int width, height;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(width, height);              // set window size
	glutCreateWindow("My Scene");                   // create and show window (named MyScene)

	cameraRadius();                     // initialise camrad variable (based on window height)
	Stage* stage = new Stage();         // new instance of Stage object    
	stage->size(camrad);                // resize to bound scene
	objects["_stage"] = stage;           // Add to objects map with id "stage"

	Tree* tree = new Tree();                       // create new Tree
	tree->position(-width / 2.f, 0.f, -width / 2.f);
	tree->size(50.f);
	tree->setReplaceString('f', "ff-[-& f + ff + < + f] + [+>f--f&-f]");
	objects["tree"] = tree;                         // add tree to map of DisplayableObjects

	Horse* horse = new Horse();                     // create new Horse
	horse->size(40.f);
	objects["horse"] = horse;                       // add horse to map of DisplayableObjects

	reshape(width, height);                         // set projection properties (ignore for now)
	prevTime = glutGet(GLUT_ELAPSED_TIME);          // initialise animation timer

	cen[0] = 0.f;									// sets model centre (pointing at the origin)
	cen[1] = 0.f;
	cen[2] = 0.f;

	glEnable(GL_DEPTH_TEST);
}

void setGlobalLight()
{
	const GLfloat global_ambient[4] = { 0.f, 0.f, 0.f, 1.0f };

	// Set lighting effect colours and positional parameter
	float ambient[] = { .2f, .2f, .2f, 1.f };      // ambient light (20% white)
	float diffuse[] = { .5f, .5f, .5f, 1.f };      // diffuse light (50% white)
	float specular[] = { .5f, .5f, .5f, 1.f };      // specular light (100% white)
	float position[] = { 1.f, .5f, 1.f, 0.f };      // directional light (w = 0)
	// Attach properties to single light source (GL_LIGHT0)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);      // set ambient parameter of light source
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);      // set diffuse parameter of light source
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);    // set specular parameter of light source
	glLightfv(GL_LIGHT0, GL_POSITION, position);    // set direction vector of light source
	// Enable this lighting effects
	glEnable(GL_LIGHTING);  // enable scene lighting (required to enable a light source)
	glEnable(GL_LIGHT0);    // enable light source with attached parameters (GL_LIGHT0)    
}

void draw()
{
	glEnable(GL_NORMALIZE);
	//glClearColor(1.f, 1.f, 1.f, 1.f);                   // set background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	glMatrixMode(GL_MODELVIEW);                         // set for model and viewing operations
	glLoadIdentity();                                   // reset drawing

	positionCamera();                               // set the camera position before anything else

	glTranslatef(0.f, -height / 2.f, 0.f);          // can now draw at z = 0
	//glColor3f(1.f, 0.f, 0.f);                           // set default draw colour to red

	// calculate runtime between now and last draw call
	float dT = runtime();
	Animation* ani_obj;
	// for each pair in the objects map (in this case, one Tree called "tree" and one Horse called "horse")
		// pair is type <string, DisplayableObject*> so must call on 'second' element
	for (map <string, DisplayableObject*>::iterator itr = objects.begin(); itr != objects.end(); ++itr) {
		ani_obj = dynamic_cast<Animation*>(itr->second);
		if (ani_obj != NULL) ani_obj->update(dT);        // update if subclasses Animation
		itr->second->display();                         // call display method on DisplayableObject
	}

	checkGLError();
	glutSwapBuffers();                                  // execute all commands, swap buffers
}

void positionCamera()
{
	cameraRadius();                                 // calculate current camera position
	eye[0] = camrad * sin(camangle);                  // set eye x (at camrad*sin(0)[ = 0])
	eye[1] = cen[1];                                // set eye y (at 0)
	eye[2] = camrad * cos(camangle);                  // set eye z (at camrad*cos(0)[ = 1])
	gluLookAt(eye[0], eye[1], eye[2],               // eye position
		cen[0], cen[1], cen[2],               // point that you are looking at (origin)
		0.f, 1.f, 0.f);                       // up vector (0, 1 0)
}

void cameraRadius()
{
	camrad = (height / 2.f) / tan(M_PI / 8.f);      // calcualte camera radius based on height
}

void reshape(int _width, int _height)
{
	width = _width;																	// update global dimension variables
	height = _height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();																// reset matrix
	gluPerspective(75.0, (GLdouble)width / (GLdouble)height, 1.0, 4000.0);
	//glOrtho(-width/2.f, width/2.f, -height/2.f, height/2.f, 1.f, camrad*2.f);       // orthographic
	glMatrixMode(GL_MODELVIEW);														// return matrix mode to modelling and viewing
}

void keyPressed(int keyCode, int xm, int ym)
{           // Special (coded) key pressed
	float incr = (float)M_PI / 36.f;   // increment angle by 5 degrees
	if (keyCode == GLUT_KEY_LEFT)
	{                      // left arrow (move camera left around scene)
		camangle -= incr;     // decrement camera angle
	}
	else if (keyCode == GLUT_KEY_RIGHT)
	{              // right arrow (move camera right around scene)
		camangle += incr;     // increment camera angle
	}
}

void keyPressed(unsigned char key, int xm, int ym)
{     // ASCII key pressed
	float incr = (float)M_PI / 36.f;   // increment angle by 5 degrees
	if (key == ' ')
	{                                     // if space bar pressed
		camangle = 0.f;                   //reset angle to 0.0
	}
	else if (key == 'a')
	{                      // left arrow (move camera left around scene)
		camangle -= incr;     // decrement camera angle
	}
	else if (key == 'd')
	{                      // left arrow (move camera left around scene)
		camangle += incr;     // decrement camera angle
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // Initialise GL environment
	setup();                        // Call additional initialisation commands

	glutKeyboardFunc(keyPressed);       // ASCII key handling
	glutSpecialFunc(keyPressed);        // Coded key handling

	glutDisplayFunc(draw);          // Register scene to render contents of draw() function
	glutIdleFunc(draw);             // Register scene to draw content on back buffer
	glutReshapeFunc(reshape);       // Register reshape function to handle window resizing
	checkGLError();                 // Check any OpenGL errors in initialisation
	glutMainLoop();                 // Begin rendering sequence
	// Upon exit
	destroyObjects();
	return 0;
}

float runtime()
{
	int currTime = glutGet(GLUT_ELAPSED_TIME);      // number of milliseconds since start of program
	float dT = static_cast<float>(currTime - prevTime) / 1000.0f; // calculate time difference between calls to runtime (in seconds)
	prevTime = currTime;                            // update time variable
	return dT;                                      // return time change
}

void destroyObjects()
{
	for (map <string, DisplayableObject*>::iterator itr = objects.begin(); itr != objects.end(); ++itr) {
		delete itr->second;                         // delete all objects from memory
	}
	objects.clear();                                // clear map
}

void checkGLError()
{
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error) {   // Loop until no errors found
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
		error = glGetError();                                  // Get next glError
	}
}