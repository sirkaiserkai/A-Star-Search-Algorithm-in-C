#include "Grid.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define NOISE (rand() % 3)

/*
 * Function: makeGrid
 *
 * @Parameters:	int x_dim ~ size of x dimension
 *		int y_dim ~ size of y dimension
 *		int seed  ~ seed
 *
 * 
 * Factory method for grid contained within Grid_Container
 * Memory allocation does occur be sure to free.
 *
 * @Returns: A 2D array of Point objects with generated terrain heights.
 */
Point** makeGrid(int x_dim, int y_dim, int seed) {
        
	srand(seed);
	int i = 0;
        int j = 0;
        Point** g;

        g = (Point **) malloc (x_dim * sizeof(Point *));

        for (i = 0; i < x_dim; i++)
        {
                g[i] = (Point *) malloc (y_dim * sizeof(Point));
        }

        for (i = 0; i < x_dim; i++)
        {
                for (j = 0; j < y_dim; j++)
                {
                        Point p;
                        int randNum = rand() % 100;

                        if (randNum < 20)
                        {
                                setPoint(&p, i, j, 1, 0);
                        }
                        else
                        {
                                setPoint(&p, i, j, 0, 0);
                        }

                        g[i][j] = p;
                }
        }

        // SETS GOAL TO BOTTOM RIGHT
	setAsGoal(&g[x_dim - 1][y_dim- 1]);
	g[0][0].start = true;

	diamond_square_algorithm(0, 0, (x_dim - 1), (y_dim - 1), g);

        return g;
}

/*
 * Function: get_Grid_Point 
 *
 * @Parameters: Grid_Container *grid_c	~ grid container from which the point is being retrieved.
 *		int x			~ x coordinate
 *		int y			~ y coordinate
 * 
 * @returns:	returns pointer to a Point struct contained within grid_c->grid.
 */
Point* get_Grid_Point(Grid_Container *grid_c, int x, int y)
{
	Point *p = (Point *) malloc(sizeof(Point));
	int x_d = grid_c->x_dimension;
	int y_d = grid_c->y_dimension;
	
 	if ((x < x_d && x >= 0) && (y < y_d && y >= 0))
	{
		*p = grid_c->grid[x][y];
		return p;
	}
	
	return NULL;
	
}

/*
 * Function: diamond_square_algorithm
 *
 * @Parameters:	int x_start	~ lower bound for x dimension
 *		int y_start	~ lower bound for y dimension
 *		int x_max	~ max bound for x dimension
 *		int y_max	~ max bound for y dimension
 *		Point** g	~ Point 2D array 
 *		int seed	~ seed for random values.
 *
 * Using the diamond square alogrithm to generate landscapes 
 * which would have some consitency of height, over just random
 * values.
 *
 *
 * @returns: 1 upon successful completion.
 */
int diamond_square_algorithm(int x_start, int y_start, int x_max, int y_max, Point **g)
{
        /* Not a good method to create random numbers within a bounds. However,
           for now it works. */
        int randomValue0 = rand() % 10;
        int randomValue1 = rand() % 10;
        int randomValue2 = rand() % 10;
        int randomValue3 = rand() % 10;

        setHeight( &g[x_start][y_start], randomValue0);
        setHeight( &g[x_start][y_max], randomValue1);
        setHeight( &g[x_max][y_start], randomValue2);
        setHeight( &g[x_max][y_max], randomValue3);

        return diamondSquare(x_start, y_start, x_max, y_max, g);
}

/*
 * Function: diamondSquare
 * @Parameters: int x_start     ~ lower bound for x dimension
 *              int y_start     ~ lower bound for y dimension
 *              int x_max       ~ max bound for x dimension
 *              int y_max       ~ max bound for y dimension
 *              Point** g       ~ Point 2D array 
 * 
 * Recursive element of the diamond square alogrithm. Uses the 
 * averages of the four corners of the grid then performs averages
 * to fill in the mid points between the corners and the center point.
 * Recursively calls the method on subsequently smaller partitions of
 * the grid to fill in the points with height values.
 * 
 * @returns: 1 on successful completion.
 */
int diamondSquare(int x_start, int y_start, int x_max, int y_max, Point **g)
{

        int a 		= g[x_start][y_start].height;
        int b 		= g[x_start][y_max].height;
        int c 		= g[x_max][y_start].height;
        int d 		= g[x_max][y_max].height;

        int midx 	= midPoint(x_start, x_max);
        int midy 	= midPoint(y_start, y_max);
        int midValue 	= (a + b + c + d) / 4;

        setHeight( &g[midx][midy], midValue + NOISE); // Diamond step
	
        if(!hasHeight(g[midx][y_start])) 	{ setHeight( &g[midx][y_start], ( (a + c + midValue) / 3) + NOISE ); 	} // Mid-Top square step
        if(!hasHeight(g[midx][y_max]))		{ setHeight( &g[midx][y_max]  , ( (b + d) / 2) + NOISE );		} // Mid-Bottom square step
        if(!hasHeight(g[x_start][midy]))	{ setHeight( &g[x_start][midy], ( (a + b) / 2) + NOISE );		} // Left-Mid square step
        if(!hasHeight(g[x_max][midy]))		{ setHeight( &g[x_max][midy]  , ( (c + d + midValue) / 3) + NOISE );	} // Right-Mid square step

        // Uses 'distance' formula to check if a 3 by 3 matrix
        if ( (x_max - x_start) == 2)
        {
                return 1;
        }

        diamondSquare(x_start, y_start, midx, midy, g);
        diamondSquare(x_start, midy, midx, y_max, g);
        diamondSquare(midx, y_start, x_max, midy, g);
        diamondSquare(midx, midy, x_max, y_max, g);


        return 1;

}

int midPoint(int num1, int num2)
{
        return (num1 + num2) / 2;
}





