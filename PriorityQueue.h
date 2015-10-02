#include "Point.h"
#include <stdbool.h>

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct 
{
	Point *pointArray; // Array of points (Nodes)
	int size; // size of the array
	int numberOfElements; // number of elements in PQ
	unsigned int memorySize; // size of memory allocated (for resizing pointArray).
	
} PQ;

PQ* makePQ(); // returns a new priority queue base size 10
int insert(PQ *pq, Point p); // inserts an element into the PQ
int getPQSize(PQ *pq); // returns size of PQ
int heapify(PQ *pq, int index);
void printTree(PQ *pq); // prints contents of PQ as appears in array
Point pop(PQ *pq); // removes root of PQ
bool isEmpty(PQ *pq);
bool containsPoint(PQ *pq, Point p);
Point* getPoint(PQ *pq, int i);
void free_PQ(PQ *pq);

#endif // PRIORITYQUEUE_H
