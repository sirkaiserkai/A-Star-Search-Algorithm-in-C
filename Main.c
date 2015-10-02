#include "Point.h"
#include "Grid.h"
#include "List.h"
#include "Player.h"
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Declarations */

void paint(ArrayList *path, Grid_Container g);
int findn( int num);


int main(int argc, char* argv[]) {
	long x_dimension = 0;
	long y_dimension = 0;
	int seed = 0;
	Grid_Container g;

	if (argc == 1) 
	{
		x_dimension = pow(2,3) + 1;
		y_dimension = pow(2,3) + 1;
		seed = time(NULL);
	} 
	else if (argc == 3) 
	{
		x_dimension = (pow(2,strtol(argv[1], NULL, 10))) + 1;
		y_dimension = x_dimension;
		seed = strtol(argv[2], NULL, 10);
	}
	else 
	{
		printf("usage: Main [n] [seed]   (NOTE: 2^n + 1 = Grid dimensions)\n");
		return 0;
	}
	g.grid = makeGrid(x_dimension, y_dimension, seed);
	g.x_dimension = x_dimension;
	g.y_dimension = y_dimension;


	ArrayList *path = aStar( &g, g.grid[0][0], g.grid[x_dimension -1][y_dimension -1]);

	printf("Seed: %d\n", seed);
	paint(path, g);
	if (path != NULL)
	{
		printf("\nPath from start to end: \n\n");
		printArrayList(path);
	}
	else 
	{
		printf("\tNo path. Cannot reach goal.\n");
	}
	
	free_ArrayList(path);
	
	return 1;
	
	
} // END OF MAIN


/* Definitions */


/*
 * Function: paint
 *
 * Parameters:	ArrayList* path  ~ arraylist containg the path to the goal.
 *		Grid_Container g ~ struct holding the grid object.
 *
 * Prints the grid out and draws the path from the start to the goal in green.
 * Impassable walls colored red in order to help visualization.
 *
 */
void paint(ArrayList* path, Grid_Container g) 
{
	int i = 0;
	int j = 0;
	
	for (i = 0; i < g.x_dimension; i++) 
	{
		for (j = 0; j < g.y_dimension; j++)
		{
			Point p = g.grid[i][j];

			if (p.start == true)
			{
				printf("\033[36;1m S\033[0m ");
			}
			else if (isWall(p)) 
			{
				printf("\e[31m W\033[0m ");
			}
			else if (isGoal(p))
			{
				printf("\033[36;1m G\033[0m ");
			}
			else if (path != NULL && contains(path, p))
			{
				if (findn(p.height) == 1) 
					printf("\e[32m %d\033[0m ", p.height);
				else
					printf("\e[32m%d\033[0m ", p.height);
				
			}
			else 
			{
				if (findn(p.height) == 1)
                                        printf(" %d ", p.height);
                                else
                                        printf("%d ", p.height);

			}
		}

		printf("\n");
	}
}

/*
 * Function: findn
 *
 * Simple method which finds the length of digits of the parameters.
 * Used for spacing in paint method above.
 */
int findn(int num)
{
	if ( num < 10 )
 		return 1;
	if ( num < 100 )
		return 2;
	
	return 0;
}
