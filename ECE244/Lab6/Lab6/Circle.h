#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "easygl.h"

using namespace std;


class Circle : public Shape
{
private:
	float r;
public:
	Circle(string _name, string _colour, float _xcen, float _ycen, float r_);

	//----------------------------------------------------------------
	//virtual overload functions

	virtual void print() const;
	virtual void scale(float scaleFac);
	virtual float computeArea() const;
	virtual float computePerimeter() const;
	virtual void draw(easygl* window) const;
	virtual bool pointInside(float x, float y) const;

};















#endif
