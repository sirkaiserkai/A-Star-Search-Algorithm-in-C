#include "Point.h"
#include "stdio.h"

/*
 * Function: setPoint
 *
 * @Parameters: Point *p 	~ Point struct being modified
 *		int x_value	~ x position given to node.
 *		int y_value	~ y position given to node.
 * 		bool wall_value	~ if set as wall then set true
 *		bool goal_value	~ if set as goal then set true
 *
 * @returns: 	int for successful completion.
 */
int setPoint(Point *p, int x_value, int y_value, bool wall_value, bool goal_value) 
{
	p->x 	= x_value;
	p->y 	= y_value;
	p->wall = wall_value;
	p->goal = goal_value;
	p->height = -1;
	p->parent_x = -1;
	p->parent_y = -1;
	return 1;
} 

bool isWall(Point p) 
{
	return p.wall;
}

bool isGoal(Point p)
{
	return p.goal;
}

int setHeight(Point *p, int num) 
{
	p->height = num;
	return 1;	
}


/*
 * Function: setAsGoal
 *
 * @Parameters:	Point *p ~ pointer to point struct which is set as goal.
 *
 * Goal cannot exist as a wall. As such when setAsGoal is called it 
 * sets the wall setting to false.
 *
 * @Returns: 1 on successful completion.
 */
int setAsGoal(Point *p)
{
	if (isWall(*p)) {
		p->wall = false;	
	}
	p->goal = true;
	return 1;
}

bool hasHeight(Point p) 
{
	return p.height >= 0 ? true : false;
}

bool equals(Point p1, Point p2) 
{
	if (p1.x == p2.x && p1.y == p2.y)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

/*
 * Function: diagonal
 *
 * @Parameters:	Point p1 ~ Point being compared.
 *		Point p2 ~ Point being compared.
 *
 * Method checks to see if two points are diagonal from
 * one another. Realistically, it only checks to see if
 * two points are vertical or horizontal to one another. 
 * However, its usage occurs only with neighbooring 
 * points as such I considered it overkill to have to 
 * compare distance to check if neighboors.
 *
 * @returns: true if diagonal.
 *
 */
bool diagonal(Point p1, Point p2)
{
	if (equals(p1, p2))
	{
		return false;
	} 
	else if (p1.x == p2.x)
	{
		return false;
	}
	else if (p1.y == p2.y)
	{
		return false;
	}
	return true;
}

/*
 * Function: Compare
 * 
 * @Parameters: Point p1 | p2 ~ Point being compared
 * 
 * @return:
 *      if p1.value > p2.value : return 1;
 *      if p1.value < p2.value : return -1;
 *      if p1.value = p2.value : return 0;
 */
int compare(Point p1, Point p2)
{
        if (p1.f_score > p2.f_score)
        {
                return 1;
        }
        else if (p1.f_score < p2.f_score)
        {
                return -1;
        }
        else
        {
                return 0;
        }
}


/*
 * Function: swap
 *
 * @Paramters: Point *p1 | *p2 ~ pointer to a "Point" struct to switch with 
 *
 * @return 1 upon successful completion.
 */
int swap(Point *p1, Point *p2)
{

        Point temp = *p2;
        *p2 = *p1;
        *p1 = temp;
        return 1;
}

/*
 * Function: printPoint
 *
 * @Parameters: Point p ~ prints information pertaining to this point.
 *
 */
void printPoint(Point p)
{
	printf("Point[%d][%d]: Height = %d | f_score = %d | isWall = %d | isGoal = %d | parent[%d][%d]\n", p.x, p.y, p.height, p.f_score, isWall(p), isGoal(p), p.parent_x, p.parent_y);
}

