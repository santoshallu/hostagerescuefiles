/* 
* Project : Hostage Rescue
* Name : Srinivasa Santosh Kumar Allu
* A-number : A01900937
* * Description: This class contains all the information related to exit like position of exit in the map*/

#ifndef Exit_H
#define Exit_H
#include "Actor.h"


class Exit : public Actor {

public:
	
    //sets the coordinate's of exit and returns exit object
	Exit getActor(World worldref)
	{
		Exit exit_ref=Exit();
		int counter=0;
		for (int i=0; i < worldref.getNoOfRows(); i++)
		{
     		for(int j=0;j<worldref.getNoOfColumns();j++)
			{
				if(worldref.getGrid().getGridCell(counter).getActor()=='E')
				{
					exit_ref.setXcoordinate(i);
					exit_ref.setYcoordinate(j);	     
				}  
				counter++;
			}
		}

		return exit_ref;

	}
	
 
};

#endif