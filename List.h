typedef struct
{
	Point* pointArray;	// Array of points
	int sizeOfArray; 	// max size of array
	int numberOfElements;	// number of points within array
	unsigned int memoryAllocated;	// size of memory allocated
} ArrayList;

ArrayList* makeArrayList();
int add(ArrayList *arr, Point p);
int getSize(ArrayList *arr);
bool contains(ArrayList *arr, Point p);
Point get(ArrayList *arr, int index);
Point* get_By_Points(ArrayList *arr, int x, int y);
void free_ArrayList(ArrayList *arr);
void printArrayList(ArrayList *arr);


