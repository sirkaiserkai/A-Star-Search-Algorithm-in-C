
What is it?
-----------
C implementation of A* and the Diamond-Square alogrithm. 
A* is path finding alogrithm used to traverse graphs. Diamond-square is a popular algorithm used in the generation of heightmaps. Commonly found in video games or other fields which require computer graphics. I implemented A* to traverse the randomly generated field with movement values considering change of height and direction for the movment cost. 

In addition, all other data structures and files included were written for this project.


Usage
-----------

Compilation:

	simply use make file or in terminal type:
	
		(CC) Main.c -o (Outfile) Point.c Grid.c PriorityQueue.c List.c -lm -std=c99 

Running:
	
	./Main.out 
		
		( Uses default value of n = 3 and timer based seed ).

	or

	./Main.out [n] [seed]

		[n] 	~ used for the formula 2^n + 1. Provides the bounds for the map
		[seed]	~ seed value used for generation of random numbers



Special thanks
--------------
To all my professors for all the hard work they do. Y'all are awesome.


