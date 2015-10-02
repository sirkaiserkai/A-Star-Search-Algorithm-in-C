#ifndef POINT_H
#define POINT_H

#include <stdbool.h>

typedef struct 
{
	int x, y;		// Location on a 2D grid
	int height;		// Height value
	int f_score;		// Total cost
	int g_score;
	bool wall;		// if this point contains a wall
	bool goal;		// if this point contains the goal
	bool start;
	int parent_x;
	int parent_y;
} Point;

int setPoint(Point *p, int x_value, int y_value, bool wall_value, bool goal_value);
int setHeight(Point *p, int height);
int setAsGoal(Point *p);
bool isWall(Point p);
bool isGoal(Point p);
bool hasHeight(Point p);
bool equals(Point p1, Point p2);
bool diagonal(Point p1, Point p2);
int compare(Point p1, Point p2);
int swap(Point *p1, Point *p2);
void printPoint(Point p);
int setParent(Point *child, Point *parent);


#endif // POINT_H
