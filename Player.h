/*
 * @author Kai Johnson
 * @date Friday, 6 March 2015 
 * 
 * header file for Player 
 */

#ifndef PLAYER_H
#define PLAYER_H


int heuristic_estimate(Point start, Point goal);
int calculate_g_score(Point current, Point neighbor);
ArrayList* aStar(Grid_Container *grid, Point start, Point goal);
ArrayList* getNeighborPoints(Point p, Grid_Container *g);
ArrayList* reconstruct_Path(ArrayList *map, Point goal);

#endif /* PLAYER_H */ 
