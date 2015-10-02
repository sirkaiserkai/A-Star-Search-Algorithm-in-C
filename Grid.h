#include "Point.h"

#ifndef GRID_H
#define GRID_H

typedef struct {
        int x_dimension;
        int y_dimension;
        Point **grid;
        Point *goal;
} Grid_Container;

Point** makeGrid(int x_dim, int y_dim, int seed);
Point* get_Grid_Point(Grid_Container *grid, int x, int y);
int diamond_square_algorithm(int x_start, int y_start, int x_max, int y_max, Point **g);
int diamondSquare(int x_start, int y_start, int x_max, int y_max, Point **g);
int midPoint(int num1, int num2);

#endif // GRID_H
