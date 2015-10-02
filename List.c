#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Point.h"
#include "PriorityQueue.h"
#include "Grid.h"
#include "List.h"


/*
 * Function: makeArrayList
 *
 * Factory method for Arraylist. Sets default
 * size to 10.
 *
 * @returns: ArrayList* to new allocated array.
 */
ArrayList* makeArrayList() 
{
	ArrayList* arr = NULL;
	
	arr = (ArrayList *) malloc(sizeof(ArrayList));
	
	arr->pointArray 	= NULL;
	arr->sizeOfArray 	= 10;
	arr->numberOfElements 	= 0;
	arr->memoryAllocated 	= sizeof(Point) * 10;

	arr->pointArray = (Point *) malloc(arr->memoryAllocated);
	
	return arr;
}

/*
 * Function: add
 *
 * @Parameters: ArrayList *arr  ~ arraylist which the point is being added too
 * 		Point p		~ Point being added to the array list.
 * @returns:	P
 */
int add(ArrayList *arr, Point p)
{
	
	if (arr->numberOfElements  == arr->sizeOfArray)
	{
		Point *temp = NULL;
		int newMemory = 0;
	
		newMemory = sizeof(Point) * 10 + arr->memoryAllocated;
		temp = (Point *) realloc(arr->pointArray, newMemory);
		
		if (temp == NULL)
		{
			return 0;
		}
		else 
		{
			arr->pointArray = temp;
			arr->sizeOfArray += 10;
			arr->memoryAllocated = newMemory;
		}
	}

	arr->pointArray[arr->numberOfElements] = p;
	arr->numberOfElements += 1;
	return 1;
}

/*
 * Function: contains
 *
 * @Parameters:	ArrayList *arr	~ pointer to array list
 *		Point p		~ point being compared against.
 *
 * @returns:	true if point p is contained within arr.
 */
bool contains(ArrayList *arr, Point p)
{
	int i = 0;
	for (i = 0; i < getSize(arr) ; i++)
	{
		if (equals(get(arr, i), p))
		{
			return true;
		}
	}

	return false;
}

/*
 * Function: get
 *
 * @Parameters: ArrayList *arr 	~ pointer to arraylist 
 *		int index	~ index where desired element is located.
 *
 * @returns:	desire Point struct
 */
Point get(ArrayList *arr, int index)
{
	return arr->pointArray[index];
}


int getSize(ArrayList *arr)
{
	return arr->numberOfElements;
}


void free_ArrayList(ArrayList *arr)
{
	if (arr != NULL)
		free(arr->pointArray);
	free(arr);
}

void printArrayList(ArrayList *arr)
{
	int i = 0;
	for ( i = 0; i < getSize(arr); i++)
	{
		Point p = get(arr, i);
		printPoint(p);
	}
}

/*
 * Function: get_By_Points
 * 
 * @Paremters: 	ArrayList *arr  ~ pointer to arraylist from which the retrival will occur
 *		int x		~ x coordinate
 *		int y		~ y coordinate
 *
 * Another get method used to retrive a point struct by its x and y coordinate.
 * I did not use my contains() method as it would cost additional runtime in order 
 * to retrive it so I essentially recycled the code and had the Point be returned.
 * I regret the lame method name. 
 *
 * Memory allocation does occur be sure to free.
 *
 * @Returns:	Allocated pointer to a point struct. 
 */
Point* get_By_Points(ArrayList *arr, int x, int y)
{
	if ( x < 0 || y < 0)
	{
		return NULL;
	}

	Point p;
	Point *rtrnPoint = NULL;
	rtrnPoint = (Point *) malloc(sizeof(Point));
	setPoint( &p, x, y, 0, 0);
	int i = 0;
	
	for ( i = 0; i < getSize(arr); i++)
	{
		*rtrnPoint = get(arr, i);
		if ( equals( *rtrnPoint, p))
		{
			return rtrnPoint;
		}
	}
		
	return NULL;
}
