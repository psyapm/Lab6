#ifndef ___Tree__
#define ___Tree__

#define _USE_MATH_DEFINES
#include "DisplayableObject.h"
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Tree : public DisplayableObject       // a Tree is a DisplayableObject
{
public:
	Tree();                                 // constructor
	~Tree() { };                            // destructor
	void display();                         // overloaded virtual display function
	void addReplaceString(char flag, string str);
	void setReplaceString(char flag, string str);
	void setNumIter(unsigned int num);
	void setInitString(string str);
private:
	void branch();                          // draw branch function
	void getSequence();						//draw Self-Similar fractasl using 'Lindemayer Systems'
	int iter = 4;
	string init = "f";
	vector<string> change;
	vector<char> flags;
};
#endif