/*Name : Srinivasa Santosh Kumar Allu
* A-number : A01900937
* Description: This class contains all the information related to Hostage like position of hostage in the map and number of hosatges*/

#ifndef Hostage_H
#define Hostage_H
#include "Actor.h"


class Hostage : public Actor {
int hostageCount;
public:
	
	Hostage()
	{
     hostageCount=0;
	}
  
	// sets the no of hostages in the world object 
    World noOfHostages(World worldref,Hostage hostage_ref)
	{
        worldref.setHostageCount(hostage_ref.getHostageCount());
		return worldref;
	}

	//sets the coordinate's of hostage and returns hostage object
	Hostage getActor(World worldref)
	{
		Hostage hostage_ref=Hostage();
		int counter=0;
		for (int i=0; i < worldref.getNoOfRows(); i++)
		{
			for(int j=0;j<worldref.getNoOfColumns();j++)
			{
				if(worldref.getGrid().getGridCell(counter).getActor()=='H')
				{
					hostage_ref.setXcoordinate(i);
					hostage_ref.setYcoordinate(j);	 
					hostageCount++;
					
				}  
				
				counter++;
			}
			hostage_ref.setHostageCount(hostageCount);
		}
       
		return hostage_ref;

	}

     // sets the hostage count
	void setHostageCount(int hostageCount)
	{
     this->hostageCount=hostageCount;
	}

	//gets the hostage count
	int getHostageCount()
	{
         return hostageCount;
	}
 
};

#endif