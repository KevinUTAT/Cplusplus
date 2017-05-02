#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Rectangle.h"
using namespace std;


Rectangle::Rectangle(string _name, string _colour, float _xcen, float _ycen,
	float width_, float height_)
	: Shape(_name, _colour, _xcen, _ycen), width(width_), height(height_) {}


Rectangle::~Rectangle() {
	//Nothing need to be deleted
}


void Rectangle::print() const{
	Shape::print();
	cout << "rectangle width: " << width << " height: " << height << endl;

}


void Rectangle::scale(float scaleFac) {

	width *= scaleFac;
	height *= scaleFac;

}


float Rectangle::computeArea() const {
	return (width * height);
}


float Rectangle::computePerimeter() const {
	return ((width + height) * 2);
}


void Rectangle::draw(easygl* window) const {
	t_point coords[4];

	coords[0].x = getXcen() - width / 2;
	coords[0].y = getYcen() + height /2;

	coords[1].x = getXcen() + width / 2;
	coords[1].y = getYcen() + height / 2;

	coords[2].x = getXcen() + width / 2;
	coords[2].y = getYcen() - height / 2;

	coords[3].x = getXcen() - width / 2;
	coords[3].y = getYcen() - height / 2;

	window->gl_setcolor(getColour());
	window->gl_fillpoly(coords, 4);
}


bool Rectangle::pointInside(float x, float y) const {
	float dx = abs(x - getXcen()); //x offset from center
	float dy = abs(y - getYcen()); //y offset from center

	if (dx > (width / 2)) return false;
	if (dy > (height / 2)) return false;

	return true;
}