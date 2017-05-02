#include "Polygon.h"
#include <iostream>
#include <cmath>
#include "easygl.h"

using namespace std;


t_point Polygon::getVecBetweenPoints(t_point start, t_point end) const {
	t_point vec;
	vec.x = end.x - start.x;
	vec.y = end.y - start.y;
	return (vec);
}


Polygon::Polygon(string _name, string _colour, float _xcen,
	float _ycen, t_point* vertex_, int numVer_)
	: Shape(_name, _colour, _xcen, _ycen), numVer(numVer_) {

	vertex = new t_point[numVer];
	
	for (int i = 0; i < numVer; i++) {
		vertex[i].x = vertex_[i].x - getXcen();
		vertex[i].y = vertex_[i].y - getYcen();
	}
}


Polygon::~Polygon() {
	delete [] vertex;
}


void Polygon::print() const {
	Shape::print();
	cout << "Polygon ";

	for (int i = 0; i < numVer; i++) {
		cout << "(" << vertex[i].x + getXcen() << "," 
			<< vertex[i].y + getYcen() << ")";
	}

	cout << endl;
}


void Polygon::scale(float scaleFac) {

	for (int i = 0; i < numVer; i++) {
		vertex[i].x *= scaleFac;
		vertex[i].y *= scaleFac;
	}
}


float Polygon::computeArea() const {
	float sum = 0;

	sum += (vertex[numVer - 1].x + vertex[0].x) * (vertex[numVer - 1].y - vertex[0].y);
	for (int i = 1; i < numVer; i++) {
		sum += (vertex[i-1].x + vertex[i].x) * (vertex[i-1].y - vertex[i].y);
	}

	return 0.5 * abs(sum);
}


float Polygon::computePerimeter() const {
	float sum = 0;
	for (int i = 0; i < (numVer - 1); i++) {
		sum += sqrt(pow((abs(vertex[i].x - vertex[i+1].x)), 2.0) 
			+ pow(abs((vertex[i].y - vertex[i + 1].y)), 2.0));
	}
	sum += sqrt(pow((abs(vertex[numVer-1].x - vertex[0].x)), 2.0)
		+ pow(abs((vertex[numVer-1].y - vertex[0].y)), 2.0));

	return sum;
}


void Polygon::draw(easygl* window) const {
	t_point drawArray[100];

	for (int i = 0; i < numVer; i++) {
		drawArray[i].x = vertex[i].x + getXcen();
		drawArray[i].y = vertex[i].y + getYcen();
	}

	window->gl_setcolor(getColour());
	window->gl_fillpoly(drawArray, numVer);
}


bool Polygon::pointInside(float x, float y) const {
	//float x_os = x - getXcen();
	//float y_os = y - getYcen();

	// Make a point that corresponds to where you clicked. Since all my
	// vertices are relative to the triangle center, it is more convenient
	// to also shift the click point so it is an offset from the triangle 
	// center.
	t_point click;
	click.x = x - getXcen();
	click.y = y - getYcen();

	// The test is that a horizontal line (ray) from x = -infinity to the click point
	// will cross (intersect) only one side of triangle to the left of the 
	// click point.  If the point is above or below the triangle, the ray will not
	// intersect any triangle sides. If the point is to the left of the triangle
	// the ray will also not intersect any sides to the left of the point.
	// If the point is to the right of the triangle, the ray will intersect
	// two sides of the triangle to its left. Only if the point is inside the 
	// triangle will the ray intersect exactly one side to the left of the point.

	t_point vecOfSide;
	float distanceAlongVector, yDistance;
	int endIndex;
	int sidesToLeft = 0;

	for (int istart = 0; istart < numVer; istart++) {
		endIndex = (istart + 1) % numVer; // Next vertex after istart
		vecOfSide = getVecBetweenPoints(vertex[istart], vertex[endIndex]);
		yDistance = (click.y - vertex[istart].y);
		if (vecOfSide.y != 0) {
			distanceAlongVector = yDistance / vecOfSide.y;
		}
		else if (yDistance == 0) {
			distanceAlongVector = 0;
		}
		else {
			distanceAlongVector = 1e10; // Really infinity, but this is big enough
		}

		// We intersect this side if the distance (scaling) along the side vector to 
		// get to our "click" y point is between 0 and 1.  Count the first 
		// endpoint of the side as being part of the line (distanceAlongVector = 0)
		// but don't count the second endPoint; we'll intersect that point later 
		// when we check the next side.
		if (distanceAlongVector >= 0 && distanceAlongVector < 1) {
			float xIntersection = vertex[istart].x + vecOfSide.x * distanceAlongVector;
			if (xIntersection <= click.x)
				sidesToLeft++;
		}
	}

	return (sidesToLeft == 1);
}