#include "Circle.h"
#include <iostream>
#include <cmath>
#include "easygl.h"

using namespace std;


Circle::Circle(string _name, string _colour, float _xcen, float _ycen, float r_) 
	: Shape(_name, _colour, _xcen, _ycen), r(r_) {}


void Circle::print() const {
	Shape::print();
	cout << " circle radius: " << r << endl;
}


void Circle::scale(float scaleFac) {
	r *= scaleFac;
}


float Circle::computeArea() const {
	return PI * pow(r, 2.0);
}


float Circle::computePerimeter() const {
	return 2 * PI * r;
}


void Circle::draw(easygl* window) const {

	window->gl_setcolor(getColour());
	window->gl_fillarc(getXcen(), getYcen(), r, 0, 360);
}


bool Circle::pointInside(float x, float y) const {
	float dx = abs(x - getXcen()); //x offset from center
	float dy = abs(y - getYcen()); //y offset from center

	float dis = sqrt(pow(dx, 2.0) + pow(dy, 2.0));

	if (dis > r) return false;
	else return true;
}