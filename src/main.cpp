#include "include/util.hpp"
#include "include/grahamScan.hpp"

int main(){
	Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
	int n = sizeof(points)/sizeof(points[0]);
	convexHull(points, n);
	return 0;
}