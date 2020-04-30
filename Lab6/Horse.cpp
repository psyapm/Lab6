#include "Horse.h"
float aT;

Horse::Horse() : // Constructor
	animationTime(2.f), nangle(45.f), hangle(-90.f)
{      // initialise animation time and angles

}

void Horse::update(float dT)

{
	aT = fmod(aT + dT, animationTime);          // update time in animation cycle
	float aS = 14.f*aT / animationTime;				  // calculate stage (out of 14)

	// Animation cycle: move head down for first 7 seconds then reverse animation
	// nangle sets position of neck (from 45 degrees to 45 degrees down)
	// hangle sets position of head (from 90 degrees down forward 
	if (aS < 1.f || aS > 13.f)
	{                 // 1st or final stage      
		nangle = -45.f;
		hangle = -90.f;
	}
	else if (aS < 2.f || aS > 12.f)
	{          // 2nd or 13th stage
		nangle = -67.5f;
		hangle = -67.5f;
	}
	else if (aS < 3.f || aS > 11.f)
	{          // 3rd or 12th stage    
		nangle = -90.f;
		hangle = -45.f;
	}
	else if (aS < 4.f || aS > 10.f)
	{          // 4th or 11th stage
		nangle = -112.5f;
		hangle = -60.f;
	}
	else if (aS < 5.f || aS > 9.f)
	{           // 5th or 10th stage
		nangle = -135.f;
		hangle = -60.f;
	}
	else if (aS < 6.f || aT > 8.f)
	{           // 6th or 9th stage
		nangle = -135.f;
		hangle = -50.f;
	}
	else
	{                                     // 7th and 8th stage
		nangle = -135.f;
		hangle = -45.f;
	}
}

void Horse::display()
{
	glPushMatrix();                                         // save transformation state
	glPushAttrib(GL_ALL_ATTRIB_BITS);                   // save style attributes (and more)
	glColor3f(0.5f, 0.5f, 0.5f);                        // colour horse grey

	// Project from Object Space to World Space
	glTranslatef(pos[0], pos[1], pos[2]);               // Position
	glScalef(scale[0], scale[1], scale[2]);             // Scale
	glRotatef(rotation[1], 0.f, 1.f, 0.f);              // Set orientation (Y)
	glRotatef(rotation[2], 0.f, 0.f, 1.f);              // Set orientation (Z)
	glRotatef(rotation[0], 1.f, 0.f, 0.f);              // Set orientation (X)

	drawHorse();                                        // draw Horse

	glPopAttrib();                                      // restore style attributes
	glPopMatrix();                                          // restore transformation state
}

void Horse::drawHorse()
{
	glTranslatef(0.f, 2.f, 0.f);                            // move draw position upwards
	glPushMatrix();                                         // save state
	box(4.f, 1.f, 1.f);                                 // draw BODY
	glPushMatrix();                                     // save position in centre of body
	glTranslatef(1.75f, 0.f, 0.5f);                     // move to front right of body
	drawLeg();                                          // draw a LEG (front right)
	glPopMatrix();                                      // pop back to central point
	glPushMatrix();                                     // save position in centre of body
	glTranslatef(1.75f, 0.f, -0.5f);                    // move to front left of body
	drawLeg();                                          // draw a LEG (front left)
	glPopMatrix();                                      // pop back to central point
	glPushMatrix();                                     // save position in centre of body
	glTranslatef(-1.75f, 0.f, 0.5f);                    // move to back right of body
	drawLeg();                                          // draw a LEG (back right)
	glPopMatrix();                                      // pop back to central point
	glPushMatrix();                                     // save position in centre of body
	glTranslatef(-1.75f, 0.f, -0.5f);                   // move to back left of body
	drawLeg();                                          // draw a LEG (back left)
	glPopMatrix();                                      // pop back to central point
	glPushMatrix();                                     // save position in centre of body
	glTranslatef(1.75f, 0.f, 0.f);                      // move to front of body
	glRotatef(nangle, 0.f, 0.f, 1.f);                      // ANIMATION PIVOT rotate neck by nangle
	drawNeck();                                         // draw NECK
	glPushMatrix();                                     // save position at base of neck
	glRotatef(hangle, 0.f, 0.f, 1.f);                      // ANIMATION PIVOT rotate head by hangle
	drawHead();                                         // draw HEAD
	glPopMatrix();                                      // pop to base of neck
	glPopMatrix();                                      // pop back to central point    
	glPopMatrix();                                          // restore state
}

void Horse::drawLeg()
{
	glTranslatef(0.f, -1.f, 0.f);
	box(0.25f, 2.f, 0.25f);
}
void Horse::drawNeck()
{
	glTranslatef(0.f, 0.75f, 0.f);
	box(0.8f, 1.5f, 0.8f);
	glTranslatef(0.f, 0.75f, 0.f);
}
void Horse::drawHead()
{
	glTranslatef(0.f, 0.4f, 0.f);
	box(0.75f, 1.5f, 0.75f);
}
void Horse::box(float sx, float sy, float sz)
{
	glPushMatrix();
	glScalef(sx, sy, sz);                               // scale solid cube by size parameters
	glutSolidCube(1.f);
	glPopMatrix();
}