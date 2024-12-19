#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "Shape.h"
#include "../Global.h"
/**
 * @see Shape.cpp
 */
class Rectangle : public Shape
{
public:
	bool overlap(const Shape &s) const;
	double center_x() const { return (x1 + x2) / 2; }
	double center_y() const { return (y1 + y2) / 2; }
	void update_center_x(const double &x) {
		double dx = x - center_x();
		x1 += dx, x2 += dx;
	}
	void update_center_y(const double &y) {
		double dy = y - center_y();
		y1 += dy, y2 += dy;
	}
	const ShapeType getType() const { return ShapeType::RECTANGLE; }
public:
	Rectangle() : texture_type(0){}
	Rectangle(double x1, double y1, double x2, double y2, int texture_type,const RectangleParams& params)
    : x1{x1}, y1{y1}, x2{x2}, y2{y2}, texture_type{texture_type},move_type{params.move_type}, 
      can_move{params.can_move}, visible{params.visible}, can_hold{params.can_hold},can_burn(params.can_burn),
      vx{params.vx}, vy{params.vy}, 
      boundary_1(params.boundary_1),boundary_2(params.boundary_2),detect_range(params.detect_range),dir(params.dir),detect_side{params.detect_side}{}
	Rectangle(int x1, int y1, int x2, int y2, int texture_type) :
		x1{static_cast<double>(x1)},
		y1{static_cast<double>(y1)},
		x2{static_cast<double>(x2)},
		y2{static_cast<double>(y2)}, 
		texture_type{texture_type} {}
	double x1, y1, x2, y2;
	int texture_type;
	int move_type;
	bool can_move;
	bool visible;
	bool can_hold;
	bool can_burn;
	double vx, vy;
	double boundary_1;
	double boundary_2;
	double detect_range;
	bool dir;
	Detect_side detect_side;
};

#endif
