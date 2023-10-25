#ifndef GRAHAMSCAN_HPP
#define GRAHAMSCAN_HPP
#include "util.hpp"

struct Point{
	int x, y;
};

Point nextToTop(stack<Point> &S);
void swap(Point &p1, Point &p2);
int distSquared(Point p1, Point p2);
int orientation(Point p, Point q, Point r);
int compare(const void *vp1, const void *vp2);
void convexHull(Point points[], int n);

#endif