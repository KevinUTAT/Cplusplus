#ifndef POLYGON_H
#define POLYGON_H
#include "Shape.h"
#include "easygl.h"

using namespace std;

class Polygon : public Shape
{
private:
	t_point* vertex;
	int numVer;
	t_point getVecBetweenPoints(t_point start, t_point end) const;
public:
	Polygon(string _name, string _colour, float _xcen,
		float _ycen, t_point* vertex_, int numVer_);

	virtual ~Polygon();

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
