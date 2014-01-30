/* 
* Project : Hostage Rescue
* Name : Srinivasa Santosh Kumar Allu
* A-number : A01900937
* Description: This class contains  the information related to wall like position of walls in the map*/

#ifndef Wall_H
#define Wall_H
#include "Actor.h"


class Wall : public Actor {

public:

	//sets the coordinate's of wall and returns wall object
	Wall getActor(World worldref)
	{
		Wall wall_ref=Wall();
		int counter=0;
		for (int i=0; i < worldref.getNoOfRows(); i++)
		{
			for(int j=0;j<worldref.getNoOfColumns();j++)
			{
				if(worldref.getGrid().getGridCell(counter).getActor()=='W')
				{
					wall_ref.setXcoordinate(i);
					wall_ref.setYcoordinate(j);	     
				}  
				counter++;
			}
		}
		return wall_ref;
	}


};

#endif