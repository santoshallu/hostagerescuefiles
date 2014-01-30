/* 
* Project : Hostage Rescue
* Name : Srinivasa Santosh Kumar Allu
* A-number : A01900937
* Description: This class contains all the information related to box like pushing the boxes and also checks whether box can be pushed to a particular location if yes 
then it pushes the box*/

#ifndef Box_H
#define Box_H
#include "Actor.h"

class Box : public Actor {


public:

	//checks whether box can be moved down if yes then it moves box down and returns world object
	World moveBoxDown(int posX,int posY,World worldref,Box box_ref)
	{

		if(posX<worldref.getNoOfRows()-1 &&  worldref.getGrid().getGridCell((posX+1)*worldref.getNoOfColumns()+posY).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P'); //moving player down
			worldref.setGridCell(worldref,(posX-1)*worldref.getNoOfColumns()+posY,'.');
			posX  = posX+1;
			box_ref.setXcoordinate(posX+1);
			box_ref.setYcoordinate(posY);
			worldref.setGridCell(worldref,(posX*worldref.getNoOfColumns()+posY),'B'); //moving box up
			cout << worldref.getMessageRef().getPlayerMovedBoxDown()<< endl;
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;
		}
		else
		{

			cout <<  worldref.getMessageRef().getBoxCannotBeMovedDown() << endl; // displays that box cannot be moved bown
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}

	}
    
	//checks whether box can be moved up if yes then it moves box up and returns world object
	World moveBoxUp(int posX,int posY,World worldref,Box box_ref)
	{

		if(posX > 0 && worldref.getGrid().getGridCell((posX-1)*worldref.getNoOfColumns()+posY).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P'); //moving player up
			worldref.setGridCell(worldref,(posX+1)*worldref.getNoOfColumns()+posY,'.');	
			posX  = posX-1;
			box_ref.setXcoordinate(posX-1);
			box_ref.setYcoordinate(posY);
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'B'); //moving box up 
			cout <<  worldref.getMessageRef().getPlayerMovedBoxUp() << endl;
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}
		else
		{

			cout << worldref.getMessageRef().getBoxCannotBeMovedUp() << endl; // displays that box cannot be moved up
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}

	}
    
	//checks whether box can be moved left if yes then it moves box left and returns world object
	World moveBoxLeft(int posX,int posY,World worldref,Box box_ref)
	{

		if(posY > 0 && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY-1).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P'); //moving player left
			worldref.setGridCell(worldref,(posX)*worldref.getNoOfColumns()+posY+1,'.');
			posY  = posY-1;
			box_ref.setXcoordinate(posX);
			box_ref.setYcoordinate(posY-1);
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'B'); //moving box left
			cout <<  worldref.getMessageRef().getPlayerMovedBoxLeft() << endl;
			if(worldref.getHostageCount()==0)// used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}
		else
		{

			cout <<worldref.getMessageRef().getBoxCannotBeMovedLeft() << endl;  // displays that box cannot be moved left
			if(worldref.getHostageCount()==0)// used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}

	}

    //checks whether box can be moved right if yes then it moves box right and returns world object
	World moveBoxRight(int posX,int posY,World worldref,Box box_ref)
	{

		if(posY < worldref.getNoOfColumns()-1 && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY+1).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P'); //moving player right
			worldref.setGridCell(worldref,(posX)*worldref.getNoOfColumns()+posY-1,'.');
			posY  = posY+1;
			box_ref.setXcoordinate(posX);
			box_ref.setYcoordinate(posY+1);
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'B'); //moving box right 
			cout <<  worldref.getMessageRef().getPlayerMovedBoxRight() << endl;
			if(worldref.getHostageCount()==0)// used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}
		else
		{

			cout << worldref.getMessageRef().getBoxCannotBeMovedRight() << endl; // displays that box cannot be moved right
			if(worldref.getHostageCount()==0)// used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl; 
			}
			return worldref;

		}

	}

	//sets the coordinate's of box and returns box object
	Box getActor(World worldref)
	{
		Box box_ref=Box();
		int counter=0;

		for (int i=0; i < worldref.getNoOfRows(); i++)
		{
			for(int j=0;j<worldref.getNoOfColumns();j++)
			{
				if(worldref.getGrid().getGridCell(counter).getActor()=='B')
				{
					box_ref.setXcoordinate(i);
					box_ref.setYcoordinate(j);	     
				}  
				counter++;
			}
		}

		return box_ref;

	}

};

#endif