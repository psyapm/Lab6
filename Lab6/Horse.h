#ifndef ___Horse__
#define ___Horse__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include "Animation.h"
#include <cmath>

class Horse :
	public DisplayableObject,
	public Animation
{
public:
	Horse();                                    // constructor
	~Horse() {};                                 // destructor
	void display();                             // define display function (to be called by MyScene)
	void update(float dT);                      // define update function (to be called by MyScene)
private:
	float animationTime;                        // number of seconds in animation cycle
	float nangle, hangle;                       // neck and head angles

	void drawHorse();                           // main drawing functions
	void drawLeg();                             // leg
	void drawNeck();                            // neck
	void drawHead();                            // head
	void box(float sx, float sy, float sz);     // draw a scaled glutSolidCube (forms components of body)
};
#endif