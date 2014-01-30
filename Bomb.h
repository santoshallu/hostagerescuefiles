/*
* Project : Hostage Rescue
* Name : Srinivasa Santosh Kumar Allu
* A-number : A01900937
* Description: This class contains all the information related to bombs like checkingbombs in the range of explosion,player and checks whether player can place a bomb 
At a particular location*/

#ifndef Bomb_H
#define Bomb_H
#include "Actor.h"


class Bomb : public Actor {

public:
	vector<Bomb> bombsInRange; // stores the bombs coordinate in the range of explosion

	// checks whether player can place bomb left , if yes it places else displays appropriate error message . This functions returns world object
	World placeBombLeft(int posX,int posY,World worldref,Bomb bomb_ref) 
	{

		if(posY > 0 && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY-1).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY-1,'@'); //sets gridcell with active bomb
			return worldref;
		}
		else
		{
			cout << worldref.getMessageRef().bombCannotBePlacedLeft() << endl; // displays an error message like bomb cannot be placed left 
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}
	}

	// checks whether player can place bomb right , if yes it places else displays appropriate error message . This functions returns world object
	World placeBombRight(int posX,int posY,World worldref,Bomb bomb_ref)
	{

		if(posY > 0 && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY+1).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY+1,'@'); //sets gridcell with active bomb
			return worldref;

		}
		else
		{
			cout << worldref.getMessageRef().bombCannotBePlacedRight() << endl;// displays appropriate error message like bomb cannot be placed right 
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}
	}

	// checks whether player can place bomb up , if yes it places else displays appropriate error message . This functions returns world object
	World placeBombUp(int posX,int posY,World worldref,Bomb bomb_ref)
	{

		if(posY > 0 && worldref.getGrid().getGridCell((posX-1)*worldref.getNoOfColumns()+posY).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,(posX-1)*worldref.getNoOfColumns()+posY,'@');
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;//sets gridcell with active bomb
			}
			return worldref;

		}
		else
		{
			cout << worldref.getMessageRef().bombCannotBePlacedUp() << endl; // displays appropriate error message like bomb cannot be placed up 
			return worldref;

		}
	}

	// checks whether player can place bomb down , if yes it places else displays appropriate error message . This functions returns world object
	World placeBombDown(int posX,int posY,World worldref,Bomb bomb_ref)
	{

		if(posY > 0 && worldref.getGrid().getGridCell((posX+1)*worldref.getNoOfColumns()+posY).getActor()=='.')
		{ 
			worldref.setGridCell(worldref,(posX+1)*worldref.getNoOfColumns()+posY,'@'); //sets gridcell with active bomb
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
			return worldref;

		}
		else
		{
			cout << worldref.getMessageRef().bombCannotBePlacedDown() << endl; // displays appropriate error message like bomb cannot be placed down 
			return worldref;

		}
	}

	// this function explodes the bomb in the bomb range and then returns world object
	World explodeBomb(int posX,int posY,World worldref,Bomb bomb_ref)
	{
		int rowNeigh[] = {1, 0, -1}; // row NeighBours
		int colNeigh[] = {1, 0, -1}; // column NeighBours
		int i,j;
		for(i=0;i < 3 ;i++)
		{
			for(j=0;j < 3 ;j++)
			{

				if( posX ==worldref.getNoOfRows()-1 ) // checking boundary conditions 
				{
					if(i==0) // if it is near bottom right 
					{
						continue; 
					}
					worldref=checkPlayerHostageBomb(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],posX+rowNeigh[i],posY+colNeigh[j],bomb_ref); //checks whether player,hostage or bomb is in the range of explosion 
					if(worldref.getGrid().getGridCell((posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j]).getActor()!='E')
					{
						worldref.setGridCell(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],'.'); //sets the grid cell with '.'
					}
				}

				else if( posY ==worldref.getNoOfColumns()-1   )  // checking boundary conditions 
				{
					if(j==0) // if it is near bottom right 
					{
						continue;
					}
					worldref=checkPlayerHostageBomb(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],posX+rowNeigh[i],posY+colNeigh[j],bomb_ref); //checks whether player,hostage or bomb is in the range of explosion 
					if(worldref.getGrid().getGridCell((posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j]).getActor()!='E')
					{
						worldref.setGridCell(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],'.'); //sets the grid cell with '.'
					}
				}

				else if( posX == 0 ) // checking boundary conditions 
				{
					if(i==2) // if it is near top left 
					{
						continue;
					}
					worldref=checkPlayerHostageBomb(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],posX+rowNeigh[i],posY+colNeigh[j],bomb_ref); //checks whether player,hostage or bomb is in the range of explosion 
					if(worldref.getGrid().getGridCell((posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j]).getActor()!='E')
					{
						worldref.setGridCell(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],'.'); //sets the grid cell with '.'
					}
				}

				else if( posY == 0 ) // checking boundary conditions 
				{
					if(j==2) // if it is near top left 
					{
						continue;
					}
					worldref=checkPlayerHostageBomb(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],posX+rowNeigh[i],posY+colNeigh[j],bomb_ref); //checks whether player,hostage or bomb is in the range of explosion
					if(worldref.getGrid().getGridCell((posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j]).getActor()!='E')
					{
						worldref.setGridCell(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],'.');//sets the grid cell with '.'
					}
				}
				else
				{
					worldref=checkPlayerHostageBomb(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],posX+rowNeigh[i],posY+colNeigh[j],bomb_ref);
					if(worldref.getGrid().getGridCell((posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j]).getActor()!='E') //checks whether player,hostage or bomb is in the range of explosion
					{
						worldref.setGridCell(worldref,(posX+rowNeigh[i])*worldref.getNoOfColumns()+posY+colNeigh[j],'.');//sets the grid cell with '.'
					}
				}

			}
		}

		worldref.setBombPlaced(false); // as bomb is placed so it is set to false
		return worldref;
	}

	//checks whether player,hostage or bomb is in the range of explosion and returns world
	World checkPlayerHostageBomb(World worldref,int location,int posX,int posY,Bomb bomb_ref)
	{
		if(worldref.getGrid().getGridCell(location).getActor()=='P')
		{
			worldref.setPlayerDead(true); // if player is present in range of explosion setPlayerDead method to true
		}
		else if(worldref.getGrid().getGridCell(location).getActor()=='H')
		{
			worldref.setHostageDead(true); // if hostage is present setPlayerDead method to true
		}
		else if(worldref.getGrid().getGridCell(location).getActor()=='o' || worldref.getGrid().getGridCell(location).getActor()=='@')
		{
			bomb_ref.setXcoordinate(posX);
			bomb_ref.setYcoordinate(posY);
			bombsInRange.push_back(bomb_ref); // stores bomb objects which are in range of explosion
		}
		return worldref;

	}

	// explodes multiple bombs which are in range of explosion and returns world object 
	World explodeBombsInRange(Bomb bomb_ref,World worldref)
	{

		for(int i=0;i<bombsInRange.size();i++) // iterates the bombs which are in range of explosion
		{
			worldref=explodeBomb(bombsInRange[i].getXcoordinate(),bombsInRange[i].getYcoordinate(),worldref,bomb_ref); // calls explodeBomb method 

		}
		return worldref;
	}

	//sets the coordinate's of bomb and returns bomb object
	Bomb getActor(World worldref)
	{
		Bomb bomb_ref=Bomb();
		int counter=0;

		for (int i=0; i < worldref.getNoOfRows(); i++)
		{
			for(int j=0;j<worldref.getNoOfColumns();j++)
			{
				if(worldref.getGrid().getGridCell(counter).getActor()=='o')
				{
					bomb_ref.setXcoordinate(i);
					bomb_ref.setYcoordinate(j);	     
				}  
				counter++;
			}
		}
		return bomb_ref;
	}

};

#endif