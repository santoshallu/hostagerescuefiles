/* 
* Project : Hostage Rescue
* Name:Srinivasa Santosh Kumar Allu
* A-number:A01900937
* Description: This is an actor class which is used represent an object in a grid cell
*/

#ifndef Actor_H
#define Actor_H
#include "World.h"

class Actor
{
	int xCoordinate,yCoordinate; // row or column position

public:

	int getXcoordinate(); // gets the X-coordinate or row position in the Map
	void setXcoordinate(int xCoordinate); // sets the X-coordinate or row position in the Map
	int getYcoordinate(); // gets the Y-coordinate or column position in the Map
	void setYcoordinate(int yCoordinate); // gets the Y-coordinate or column position in the Map
	Actor getActor(World worldref); //sets the coordinate's of actor returns actor

};

#include "Actor_Impl.h"
#endif