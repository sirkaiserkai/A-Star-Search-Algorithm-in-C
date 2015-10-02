#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "Grid.h"
#include "List.h"
#include "PriorityQueue.h"
#include "Player.h"


/*
 * Function: aStart
 *
 * @Parameters: Grid_Container grid 	~ grid_container to find neighboors
 *		Point start		~ starting point
 *		Point goal		~ goal point
 *
 * Uses an pseudocode I found of wikipedia as guidance on my implementation.
 *
 * @returns an array of points which contains the path to the goal from the start point
 * 
 *
 */
ArrayList* aStar( Grid_Container *grid, Point start, Point goal) 
{
	int i = 0;

	ArrayList *closed_set 	= NULL;
	PQ *open_set 		= NULL;
	ArrayList *map 		= NULL;
	
	start.g_score = 0;
	start.f_score = start.g_score + heuristic_estimate( start, goal);

	open_set 	= makePQ();
	closed_set 	= makeArrayList();
	map		= makeArrayList();
	
	insert(	open_set, start);
	
	while ( !isEmpty( open_set))
	{
		
		Point current = pop(open_set);
		//printf("Current x: %d y: %d\n", current.x, current.y);
		if ( isGoal( current))
		{	
			
			ArrayList* rtrnList = NULL;
			free_PQ( open_set);
			free_ArrayList(closed_set);
			
			rtrnList = reconstruct_Path(map, current);
			
			free_ArrayList( map);
			return  rtrnList;
		}
		
		add(closed_set, current);
		ArrayList *neighbors 	= NULL; 
		neighbors = getNeighborPoints(current, grid); 
		//printf("Printing neighbors:\n");
		//printArrayList(neighbors);
		for ( i = 0; i < getSize( neighbors); i++)
		{
			Point neighbor = get( neighbors, i);
			
			if ( !contains( closed_set, neighbor)) 
			{

				int tentative_g_score = calculate_g_score(current, neighbor);

				if (!containsPoint( open_set, neighbor) || tentative_g_score < neighbor.g_score)
				{
					neighbor.parent_x = current.x;
					neighbor.parent_y = current.y;
					add( map, current); 
					neighbor.g_score = tentative_g_score;
					
					if (!isGoal(neighbor)) 
					{
						neighbor.f_score = neighbor.g_score + heuristic_estimate( current, neighbor);
					} 
					else 
					{
						neighbor.f_score = 0;
					}
					
					if (!containsPoint( open_set, neighbor))
					{
						insert( open_set, neighbor);
					}
				}
				
			}
			
		}
		free_ArrayList(neighbors);
	}
	return NULL; 
}

/*
 * Function heuristic_estiamte
 *
 * Uses Diagonal shortcut method.
 *
 * @Parameters:	Point currentPosition 	~ loction currently in grid
 *		Point goal		~ goal location
 *
 * @returns:	Heuristic value 	
 */
int heuristic_estimate(Point currentPosition, Point goal)
{
	int xDistance = abs(currentPosition.x - goal.x);
	int yDistance = abs(currentPosition.y - goal.y);
	
	if (xDistance > yDistance)
	{
		return 14 * yDistance + 10*(xDistance - yDistance);
	}
	else 
	{
		return 14 * xDistance + 10*(yDistance - xDistance);
	}
	
}

/*
 * Function: calculate_g_score
 *
 * @Paramters:	Point current	~ current location
 *		Point goal	~ 
 * 
 * Calculates the g score for the neighbooring points to
 * the current point. The diagonal movemnts cost is increased
 * since diagonal movement on a grid is sqrt(2) * horizontal/vertical
 * movement. Elevation change is also factored into the cost.
 * 
 * @returns:	int calculated movement cost
 */
int calculate_g_score(Point current, Point target)
{
	if (equals(current, target))
	{
		return 0;
	}
	else if (diagonal(current, target))
	{
		return 14 + current.g_score + abs(current.height - target.height);
		//return 50 + current.g_score + abs(current.height - target.height);
	}
	else 
	{
		return 10 + current.g_score + abs(current.height - target.height);
	}
}

/*
 * Function: getNeighborPoints
 *
 * @Parameters: Points p 		~ Point object whose neighbors are desired.
 *		Grid_Container *g	~ Grid_Container containing the grid 
 *
 * NOTE: Memory allocated in this method. 
 *
 * @Returns: ArrayList* ~ allocated arraylist containing all neighbooring grid points (sans walls).
 */
ArrayList* getNeighborPoints(Point p, Grid_Container *g)
{
	int i = 0;
	int x_Values[8]; 
	int y_Values[8];
	
	x_Values[0] = p.x - 1;
	y_Values[0] = p.y - 1;
	
	x_Values[1] = p.x - 1;
	y_Values[1] = p.y;
	
	x_Values[2] = p.x - 1;
	y_Values[2] = p.y + 1;
	
	x_Values[3] = p.x;
	y_Values[3] = p.y - 1;
	
	x_Values[4] = p.x;
	y_Values[4] = p.y + 1;

	x_Values[5] = p.x + 1;
	y_Values[5] = p.y - 1;
	
	x_Values[6] = p.x + 1;
	y_Values[6] = p.y;
		
	x_Values[7] = p.x + 1;
	y_Values[7] = p.y + 1;

	ArrayList *temp = NULL;
	temp = makeArrayList();
	
	for ( i = 0; i < 8; i++)
	{
		Point *neighbor = NULL;
		neighbor =  get_Grid_Point(g, x_Values[i], y_Values[i]);
		//printf("Neighbor Point: x = %d y = %d\n", neighbor->x, neighbor->y);
		if (neighbor != NULL && !isWall(*neighbor))
		{
			add(temp, *neighbor);
		}
		free(neighbor);
	}
	return temp;
		
}

/*
 * Function: reconstruct_Path
 * 
 * @Parameters: ArrayList* map 	~ Pointer to arraylist of navigated nodes
 *		Point goal	~ Point struct which holds the goal point
 *
 * Uses the goals parent's x and y points to navigate backwards and fill an
 * array list with the shortest path to the goal. 
 *
 * NOTE: Memory allocated within this method.
 *
 * @returns:	ArrayList* path ~ Arraylist containing the path.
 *
 */
ArrayList* reconstruct_Path(ArrayList *map, Point goal)
{
	int x = 0;
	int y = 0;
	ArrayList* path = NULL;
	Point *p 	= NULL;
	
	path 	= makeArrayList(); 
	
	add( path, goal);
	p = get_By_Points( map, goal.parent_x, goal.parent_y);
	
	while ( p != NULL )
	{
		add( path, *p);
		x = p->parent_x;
		y = p->parent_y;
		
		free(p);

		p = get_By_Points( map, x, y);
	}
	
	free(p);
	return path;
}
