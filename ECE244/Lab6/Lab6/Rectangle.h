#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "easygl.h"

using namespace std;


class Rectangle : public Shape
{
private:
	float width;
	float height;
public:
	Rectangle(string _name, string _colour, float _xcen, float _ycen,
		float width_, float height_);

	virtual ~Rectangle();

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