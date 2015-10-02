/*
 * @author Kai Johnson
 * Priority queue method definitions
 *
 * There exist many implementation of priority queues in C
 * however, from what I've read most of which I found had strange
 * copyright restrictions or were questionably implemented.
 * So I've rolled my own, also it never hurts to refresh
 * on data structures.
 * 
 * NOTE: This is a min-heap implementation 
 *
 */


#include "Point.h"
#include "PriorityQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


/*
 * Function: makePQ
 *
 * Factory method for PQ
 * 
 * NOTE: Memory is allocated in this method.
 *
 * @Returns: allocated PQ* struct
 */
PQ* makePQ()
{
	PQ *pq = NULL;
	pq = (PQ *) malloc(sizeof(PQ));
	pq->memorySize = sizeof(Point) * 10;
	pq->pointArray = (Point *) malloc(pq->memorySize);
	pq->size = 10;
	pq->numberOfElements = 0;
	
	return pq;	
}

/*
 * Function: insert
 *
 * @Parameter: 	PQ *pq 	~ pointer to priority queue
 *		Point p ~ point struct being inserted.
 *
 * Checks to see if pq has space in order to insert new point
 * 	if not: reallocates space for insertion.
 * 
 * Then inserts node at the end of array at open index.
 * Then rearranges tree so that the point is in the 
 * correct location based on its value.	
 *
 * @return: 	1 if successfully inserted.
 *		0 if unsuccessful.
 */
int insert(PQ *pq, Point p) 
{
	// when array is full realloc
	if ( (getPQSize(pq) + 1) == pq->size )
	{
		Point *temp = NULL;
		int newMemory = 0;


		// The correct implementation of realloc (Sooo many headaches with these two lines of code).
		newMemory = sizeof(Point) * 10 + pq->memorySize;
		temp = (Point *) realloc( pq->pointArray, newMemory);

		if (temp == NULL)
		{
			return 0; // Failure to realloc
		}
		else 
		{
			pq->pointArray = temp; // realloc successful
			pq->size += 10; // update size of array
			pq->memorySize = newMemory; // update current allocated memory for PQ
		}
	}
	
	int i = 0;
	int max = getPQSize(pq) + 1; 
	pq->pointArray[max] = p; 
	
	for ( i = max; (compare(pq->pointArray[(i/2)], pq->pointArray[i]) == 1)
			 && (i/2 != 0); i = i/2) 
	{
		Point temp = pq->pointArray[(i/2)];
		pq->pointArray[(i/2)] = pq->pointArray[i];
		pq->pointArray[i] = temp;
	}
	
	pq->numberOfElements += 1;
	return 1;
}


/*
 * Function: getSize
 *
 * @Parameters: PQ *pq ~ pointer to priority queue
 *
 * @returns: number of elements inside of PQ
 */
int getPQSize(PQ *pq) 
{
	return pq->numberOfElements;
}


/*
 * Function: printTree
 *
 * @Parameters: PQ *pq ~ pointer to priority queue
 *
 * prints contents of tree as it would appear in 
 * an array.
 */
void printTree(PQ *pq) 
{
	printf("\nPQ array:\n");
	int i = 0;
	for (i = 0; i <= pq->numberOfElements; i++)
	{
		printf("Position[%d]: ", i);
		printPoint(pq->pointArray[i]);
	}
}


/*
 * Function: pop
 * 
 * @Parameters: PQ *pq ~ pointer to priority queue 
 *
 * removes the root (lowest value node) from the PQ
 * then readjusts the tree to ensure it holds as a
 * min heap.
 *
 * @return: Point* ~ returns a pointer to the top node. 
 */
Point pop(PQ *pq) 
{

	// Allocate memory for a new pointer for return element
	Point p;
	p = pq->pointArray[1];
	//p  = (Point *) malloc(sizeof(Point));

	if (getPQSize(pq) == 1)
	{
			
		pq->numberOfElements -= 1;
		return p;
	}
	
	pq->pointArray[1] = pq->pointArray[getPQSize(pq)];

	pq->numberOfElements -= 1;

	heapify(pq, 1);
	return p;
}


/*
 * Function: heapify
 *
 * @Parameters: PQ *pq 		~ pointer to priority queue
 *		int index	~ node index to heapify
 *
 *
 * A recursive method which is organizes the array as a min
 * heap. Ensures after the swap the lowest value is the
 * root of the tree.
 *
 * @return: 1 if change occured else 0 if no change.
 */
int heapify(PQ *pq, int index) 
{
	//printf("Entering Heapify Index: %d\n", index);
	Point* parent = getPoint(pq, index);
	
	if (parent == NULL)  
	{
		//printf("Parent is NULL\n");
		return 0;
	}	
	
	Point *leftChild = getPoint(pq, (index * 2));
	
	if (leftChild != NULL && compare(*parent, *leftChild) == 1)
	{
		//printf("Parent > leftChild\n");
		//printf("\tParent.height = %d\n", parent->height);
		//printf("\tleftChild.height = %d\n", leftChild->height);
		swap(parent, leftChild);
		heapify(pq, (index * 2));
		heapify(pq, index);
		return 1;
	}
	
	
	Point *rightChild = getPoint(pq, (index * 2 + 1));

	if (rightChild != NULL && compare(*parent, *rightChild) == 1)
	{
		//printf("Parent > rightChild\n");
		swap(parent, rightChild);
		heapify(pq, (index * 2 + 1));
		heapify(pq, index);
		return 1;
	}

	return 0; // No changes made.
}


/*
 * Function: isEmpty
 * 
 * @Parameters: PQ *pq ~ pointer to priority queue
 *
 * @returns: true if empty else false;
 */
bool isEmpty(PQ *pq) 
{
	if (getPQSize(pq) == 0)
	{
		return true;
	}

	return false;
}

/*
 * Function: containsPoint
 *
 * @Parameters: PQ *pq 	~ pointer to priority queue
 *		Point p	~ Point object being compared to
 * 
 * @returns:	boolean value if point contained in PQ
 */
bool containsPoint(PQ *pq, Point p)
{
	int i = 0;
	for (i = 0; i < pq->numberOfElements; i++)
	{
		if (equals(pq->pointArray[i], p))
		{
			return true;
		}
	}
	
	return false; // Point not contained within PQ
}


/*
 * Function: getPoint
 *
 * @Parameters: PQ *pq 	~ pointer to priority queue from which the point is being retrived
 *		int i	~ index location.  
 * @return: *Point at index : NULL if out of bounds
 */
Point* getPoint(PQ *pq, int i) 
{
	if (i > pq->numberOfElements)
	{
		return NULL;
	}  
	
	return &pq->pointArray[i];
}



/*
 * Function: free_PQ
 *
 * @Parameters: PQ *pq ~ pointer to a priority queue
 *
 * frees the memory allocated for PQ
 */
void free_PQ(PQ *pq)
{
	if (pq!= NULL)
		free(pq->pointArray);
	free(pq);	
}


/*
int main() 
{
	printf("Priority Queue Test main\n");
	srand(12);
	PQ *pq = makePQ();
	
	int i =0;

	for (i = 20; i > 1; i-- ) {
		Point p;
		setPoint(&p, i, i, 0, 0);
		int randomNumber = rand() % 100;
		p.f_score =  randomNumber;
		insert(pq, p);
	}

	Point p;
	p.f_score = 21;
	insert(pq, p);
	p.f_score = 22;
	insert(pq, p);
	p.f_score = 30;
	insert(pq, p);
	
	printf("PQ-size: %d | PQ->numberOfElements = %d\n", pq->size, pq->numberOfElements);
	printTree(pq);
	
	
	
	i = 0;
	
	printf("\nEmptying PQ\n");
	while (!isEmpty(pq))
	{
		Point p = (pop(pq));
		printTree(pq);
		printf("\tPoint[%d] f_score: %d\n", i, p.f_score);
		fflush(stdout);
		i++;
	}
	
}*/
