/*
* Project : Hostage Rescue
* Name : Srinivasa Santosh Kumar Allu
* A-number : A01900937
* Description: This class contains all the information related to player class like posiiton of player , player movements and when player moves what action needs to be done */

#ifndef Player_H
#define Player_H

#include "Box.h"
#include "Bomb.h"

class Player : public Actor { 


public:
	Box box_ref;
	Bomb bomb_ref;
	int bombXCoordinate; // row or X coordinate of bomb
	int bombYCoordinate;  // column or Y coordinate of bomb

	// this function calls appropriate function based on Input and the function called performs an action and returns the current world 
	World play(World worldref,Player player_ref,string playerInput) 
	{
		int posX=player_ref.getXcoordinate();
		int posY=player_ref.getYcoordinate();

		if(playerInput.compare("u")==0)
		{
			return moveUp(posX,posY,worldref,player_ref);
		}
		else if(playerInput.compare("d")==0)
		{
			return moveDown(posX,posY,worldref,player_ref);
		}
		else if(playerInput.compare("l")==0)
		{
			return moveLeft(posX,posY,worldref,player_ref);
		}
		else if(playerInput.compare("r")==0)
		{
			return moveRight(posX,posY,worldref,player_ref);
		}
		else if(playerInput.compare("w")==0)
		{
			return playerSkipsTurn(worldref);
		}
		else if(playerInput.compare("q!")==0)
		{
			worldref.setQuitMaze(true);
			cout << worldref.getMessageRef().getPlayerQuitsMaze()<< endl;
			return worldref;
		}
		else if(playerInput.compare("bl")==0 || playerInput.compare("br")==0 || playerInput.compare("bu")==0 || playerInput.compare("bd")==0 ) 
		{

			if( worldref.getNoOfBombs()>0) // when player has more than one bomb
			{
				return placeBomb(posX,posY,worldref,player_ref,playerInput);
			}
			else // when player has zero bombs
			{
				cout <<  worldref.getMessageRef().getPlayerNoBombs() << endl; // displays appropriate error message 
				return worldref;
			}
		}
		else 
		{
			cout <<  worldref.getMessageRef().getInvalidPlayMove() << endl; // / displays appropriate error message
			return worldref;
		}
	}

	World moveUp(int posX,int posY,World worldref,Player player_ref) //  player moves up  performs an action and returns the current world 
	{
		int swapPosX=0;
		int blockObject=(posX-2)*worldref.getNoOfColumns()+posY;
		int leastRow = posX;

		// checks the upper boundary and also checks whether an object that a player cannot move on is present in the upper direction
		if(posX > 0 && worldref.getGrid().getGridCell((posX-1)*worldref.getNoOfColumns()+posY).getActor()!='X' && worldref.getGrid().getGridCell((posX-1)*worldref.getNoOfColumns()+posY).getActor()!='@'  )
		{              
			swapPosX = posX;
			posX  = posX-1;
            
			// if box is present when playes moves up
			if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='B' )
			{

				worldref=box_ref.moveBoxUp(posX,posY,worldref,box_ref);
				if(blockObject>leastRow)
				{
					if(worldref.getGrid().getGridCell((posX-1)*worldref.getNoOfColumns()+posY).getActor()!='X')
					{
						player_ref.setXcoordinate(posX);
						player_ref.setYcoordinate(posY);
					}
				}

			}

            // if bomb is present when playes moves up
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='o' )
			{  
				cout << worldref.getMessageRef().getPlayerMovedUp();
				worldref=player_ref.bombFoundUpOrDown(posX,posY,swapPosX,worldref,player_ref);

			}
            
			 // if exit is present when playes moves up
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='E' )
			{

				worldref=player_ref.exitFromUpOrDown(posX,posY,swapPosX,worldref,player_ref);
			}
            

            // if hostage is present when playes moves up
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='H' )
			{

				worldref.hostageRescued();
				worldref=player_ref.movePlayerUpOrDown(posX,posY,swapPosX,worldref,player_ref);
				cout << worldref.getMessageRef().getPlayerMovedUpRescuedHostage() << endl;
			}
            
			// when '.' is present when player movedUp
			else
			{
				cout << worldref.getMessageRef().getPlayerMovedUp() << endl<< endl;
				worldref=player_ref.movePlayerUpOrDown(posX,posY,swapPosX,worldref,player_ref);	
			}
		}
        
		//player cannot be moved up because of an obstacle 
		else
		{
			cout<< worldref.getMessageRef().getPlayerCannotBeMovedUp() << endl; 
			if(worldref.getHostageCount()==0)// used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}
		}
        

		// checks if bomb placed and number of time steps is 3
		if(worldref.getBombPlaced() &&  worldref.getTimeBombStep()-worldref.getTimeStep()==2)
		{
			worldref=bomb_ref.explodeBomb(worldref.getbombXCoordinate(),worldref.getbombYCoordinate(),worldref,bomb_ref);			
			cout << worldref.getMessageRef().bombExploded() << endl;
		}

		worldref=bomb_ref.explodeBombsInRange(bomb_ref,worldref); //  calls to explode multiple bombs in range of explosion
		worldref.setTimeStep(worldref.getTimeStep()-1);
		return worldref;
	}
    
	
	World moveDown(int posX,int posY,World worldref,Player player_ref) // when player moves Down  performs an action and returns the current world 
	{
		int swapPosX=0;
		int blockObject=(posX+2)*worldref.getNoOfColumns()+posY;
		int totalMazeSize = (worldref.getNoOfRows()* worldref.getNoOfColumns())-1;

        // checks the lower boundary and also checks whether an object that a player cannot move on is present in the lower/down direction
		if(posX< worldref.getNoOfRows()-1 &&  worldref.getGrid().getGridCell((posX+1)*worldref.getNoOfColumns()+posY).getActor()!='X' && worldref.getGrid().getGridCell((posX+1)*worldref.getNoOfColumns()+posY).getActor()!='@'  )
		{              
			swapPosX = posX;
			posX  = posX+1;

           // if box is present when playes moves down
			if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='B'  )
			{

				worldref=box_ref.moveBoxDown(posX,posY,worldref,box_ref);
				if(blockObject<totalMazeSize)
				{
					if(worldref.getGrid().getGridCell((posX+1)*worldref.getNoOfColumns()+posY).getActor()!='X')
					{
						player_ref.setXcoordinate(posX);
						player_ref.setYcoordinate(posY);
					}
				}	
			}

			 // if bomb is present when playes moves down
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='o')
			{
				cout << worldref.getMessageRef().getPlayerMovedDown() ;
				worldref=player_ref.bombFoundUpOrDown(posX,posY,swapPosX,worldref,player_ref);
			}

			// if hostage is present when playes moves down
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='H' )
			{

				worldref.hostageRescued();
				worldref=player_ref.movePlayerUpOrDown(posX,posY,swapPosX,worldref,player_ref);
				cout << worldref.getMessageRef().getPlayerMovedDownRescuedHostage()<< endl ;
			}

			 // if exit is present when playes moves down
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='E' )
			{
				worldref=player_ref.exitFromUpOrDown(posX,posY,swapPosX,worldref,player_ref);
			}

			// when '.' is present when player moved down
			else
			{
				cout << worldref.getMessageRef().getPlayerMovedDown() << endl<< endl;
				worldref=player_ref.movePlayerUpOrDown(posX,posY,swapPosX,worldref,player_ref);

			}

		}

		
		else //player cannot be moved down because of an obstacle 
		{
			cout<< worldref.getMessageRef().getPlayerCannotBeMovedDown() << endl;
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}


		}

		// checks if bomb placed and number of time steps is 3
		if(worldref.getBombPlaced() &&  worldref.getTimeBombStep()-worldref.getTimeStep()==2)
		{
			worldref=bomb_ref.explodeBomb(worldref.getbombXCoordinate(),worldref.getbombYCoordinate(),worldref,bomb_ref);	
			cout << worldref.getMessageRef().bombExploded() << endl;
		}


		worldref=bomb_ref.explodeBombsInRange(bomb_ref,worldref); // to explode multiple bombs in range of explosion
		worldref.setTimeStep(worldref.getTimeStep()-1);
		return worldref;

	}

	World moveLeft(int posX,int posY,World worldref,Player player_ref)  // when player moves left  performs an action and returns the current world 
	{ 
		int swapPosY=0;
		int blockObject=posY-2;
        
		// checks the leftside boundary and also checks whether an object that a player cannot move on is present in the left direction
		if(posY > 0 && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY-1).getActor()!='X' && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY-1).getActor()!='@')
		{              
			swapPosY = posY;
			posY  = posY-1;

			// if box is present when playes moves left
			if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='B' )
			{
				worldref=box_ref.moveBoxLeft(posX,posY,worldref,box_ref);

				if(blockObject>0)
				{
					if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY-1).getActor()!='X')
					{
						player_ref.setXcoordinate(posX);
						player_ref.setYcoordinate(posY);
					}
				}

			}

			// if bomb is present when playes moves left
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='o')
			{
				cout<< worldref.getMessageRef().getPlayerMovedLeft() ;
				worldref=player_ref.bombFoundLeftOrRight(posX,posY,swapPosY,worldref,player_ref);


			}

             // if exit is present when playes moves left
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='E')
			{
				worldref=player_ref.exitFromLeftOrRight(posX,posY,swapPosY,worldref,player_ref);
			}

             // if hostage is present when playes moves left
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='H' )
			{

				worldref.hostageRescued();
				worldref=player_ref.movePlayerLeftOrRight(posX,posY,swapPosY,worldref,player_ref);
				cout<< worldref.getMessageRef().getPlayerMovedLeftRescuedHostage() << endl;
			}

			else // when '.' is present when player moved left
			{
				cout<< worldref.getMessageRef().getPlayerMovedLeft() << endl<< endl;
				worldref=player_ref.movePlayerLeftOrRight(posX,posY,swapPosY,worldref,player_ref);

			}

		}
		else //player cannot be moved up because of an obstacle 
		{
			cout<< worldref.getMessageRef().getPlayerCannotBeMovedLeft() << endl;
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}

		}

		// checks if bomb placed and number of time steps is 3
		if(worldref.getBombPlaced() &&  worldref.getTimeBombStep()-worldref.getTimeStep()==2)
		{
			worldref=bomb_ref.explodeBomb(worldref.getbombXCoordinate(),worldref.getbombYCoordinate(),worldref,bomb_ref);	
			cout << worldref.getMessageRef().bombExploded() << endl;
		}
		worldref=bomb_ref.explodeBombsInRange(bomb_ref,worldref); // to explode multiple bombs in range of explosion
		worldref.setTimeStep(worldref.getTimeStep()-1);
		return worldref;
	}



	World moveRight(int posX,int posY,World worldref,Player player_ref) // when player moves right performs an action and returns the current world 
	{
		int swapPosY=0;
		int blockObject=posY+2;

		// checks the right side boundary and also checks whether an object that a player cannot move on is present in the right direction
		if(posY < worldref.getNoOfColumns()-1 && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY+1).getActor()!='X' && worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY+1).getActor()!='@' )
		{              
			swapPosY = posY;
			posY  = posY+1;
			// if box is present when playes moves right
			if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='B' )
			{
				worldref=box_ref.moveBoxRight(posX,posY,worldref,box_ref);
				if(blockObject<worldref.getNoOfColumns())
				{
					if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY+1).getActor()!='X' )
					{
						player_ref.setXcoordinate(posX);
						player_ref.setYcoordinate(posY);
					}
				}
			}

			// if bomb is present when playes moves right
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='o')
			{
				cout<< worldref.getMessageRef().getPlayerMovedRight() ;
				worldref=player_ref.bombFoundLeftOrRight(posX,posY,swapPosY,worldref,player_ref);
			}

            // if exit is present when playes moves right
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='E')
			{
				worldref=player_ref.exitFromLeftOrRight(posX,posY,swapPosY,worldref,player_ref);
			}

			// if hostage is present when playes moves right
			else if(worldref.getGrid().getGridCell((posX)*worldref.getNoOfColumns()+posY).getActor()=='H' )
			{
				worldref.hostageRescued();
				worldref=player_ref.movePlayerLeftOrRight(posX,posY,swapPosY,worldref,player_ref);
				cout<< worldref.getMessageRef().getPlayerMovedRightRescuedHostage() << endl ;
			}

			else // when '.' is present when player moved right
			{
				cout<< worldref.getMessageRef().getPlayerMovedRight() << endl << endl;
				worldref=player_ref.movePlayerLeftOrRight(posX,posY,swapPosY,worldref,player_ref);

			}

		}
		//player cannot be moved up because of an obstacle 
		else 
		{
			cout<< worldref.getMessageRef().getPlayerCannotBeMovedRight() << endl;
			if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
			{
				cout << worldref.getMessageRef().allHostagesRescued() << endl;
			}

		}
        // checks if bomb placed and number of time steps is 3
		if(worldref.getBombPlaced() &&  worldref.getTimeBombStep()-worldref.getTimeStep()==2)
		{
			worldref=bomb_ref.explodeBomb(worldref.getbombXCoordinate(),worldref.getbombYCoordinate(),worldref,bomb_ref);
			cout << worldref.getMessageRef().bombExploded() << endl;
		}
		worldref=bomb_ref.explodeBombsInRange(bomb_ref,worldref); // to explode multiple bombs in range of explosion
		worldref.setTimeStep(worldref.getTimeStep()-1);
		return worldref;
	}

    // when player skips a turn
	World playerSkipsTurn(World worldref)
	{
		worldref.setTimeStep(worldref.getTimeStep()-1);
		cout << worldref.getMessageRef().getPlayerSkippedTurn()<< endl;

		 // checks if bomb placed and number of time steps is 3
		if(worldref.getBombPlaced() &&  worldref.getTimeBombStep()-worldref.getTimeStep()==3)
		{
			worldref=bomb_ref.explodeBomb(worldref.getbombXCoordinate(),worldref.getbombYCoordinate(),worldref,bomb_ref);
			cout << worldref.getMessageRef().bombExploded() << endl;
		}
		worldref=bomb_ref.explodeBombsInRange(bomb_ref,worldref);// to explode multiple bombs in range of explosion
		return worldref;


	}
    // calls addbombs method in world and returns current world
	World addBomb(World worldref)
	{
		worldref.addBombs();
		return worldref;
	}
    
	// tries to place bomb up or right or down or left based on the Input
	World placeBomb(int posX,int posY,World worldref,Player player_ref,string playerInput)
	{
        //placing bomb to the left
		if(playerInput.compare("bl")==0)
		{
			worldref=bomb_ref.placeBombLeft(posX,posY,worldref,bomb_ref); // checks whether bomb can be placed left
			if(worldref.getGrid().getGridCell(posX*worldref.getNoOfColumns()+posY-1).getActor()=='@') // if bomb is placed to the left
			{
				bombXCoordinate=posX;
				bombYCoordinate = posY-1;
				worldref=player_ref.setBombCoordinates(bombXCoordinate,bombYCoordinate,worldref);
				worldref.bombExploded();// reduce bomb count
				cout << worldref.getMessageRef().bombPlacedLeft()<< endl;
			}

		}

		 //placing bomb to the right
		if(playerInput.compare("br")==0)
		{
			worldref=bomb_ref.placeBombRight(posX,posY,worldref,bomb_ref);// checks whether bomb can be placed right
			if(worldref.getGrid().getGridCell(posX*worldref.getNoOfColumns()+posY+1).getActor()=='@') // if bomb is placed to the right
			{
				bombXCoordinate=posX;
				bombYCoordinate = posY+1;
				worldref=player_ref.setBombCoordinates(bombXCoordinate,bombYCoordinate,worldref);
				worldref.bombExploded();
				cout << worldref.getMessageRef().bombPlacedRight()<< endl;
			}

		}

		 //placing bomb in the upper direction
		if(playerInput.compare("bu")==0)
		{
			worldref=bomb_ref.placeBombUp(posX,posY,worldref,bomb_ref); // checks whether bomb can be placed up
			if(worldref.getGrid().getGridCell((posX-1)*worldref.getNoOfColumns()+posY).getActor()=='@') // if bomb is placed up
			{
				bombXCoordinate=posX-1;
				bombYCoordinate = posY;
				worldref=player_ref.setBombCoordinates(bombXCoordinate,bombYCoordinate,worldref);
				worldref.bombExploded();
				cout << worldref.getMessageRef().bombPlacedUp()<< endl;

			}

		}

		 //placing bomb in the lower/down direction
		if(playerInput.compare("bd")==0)
		{
			worldref=bomb_ref.placeBombDown(posX,posY,worldref,bomb_ref);// checks whether bomb can be placed down
			if(worldref.getGrid().getGridCell((posX+1)*worldref.getNoOfColumns()+posY).getActor()=='@') // if bomb is placed up
			{
				bombXCoordinate= posX+1;
				bombYCoordinate = posY;
				worldref=player_ref.setBombCoordinates(bombXCoordinate,bombYCoordinate,worldref);
				worldref.bombExploded();
				cout << worldref.getMessageRef().bombPlacedDown()<< endl;
			}

		}

		return worldref;

	}
    

	//sets the bomb cordinates and returns current world
	World setBombCoordinates(int bombXCoordinate,int bombYCoordinate,World worldref)
	{
		worldref.setTimeBombStep(worldref.getTimeStep());
		worldref.setbombXCoordinate(bombXCoordinate);
		worldref.setbombYCoordinate(bombYCoordinate);
		worldref.setBombPlaced(true);
		return worldref;
	}
    
	//setting player coordinates when player moves up or down  and returns current world
	World movePlayerUpOrDown(int posX,int posY,int swapPosX,World worldref,Player player_ref)
	{
		player_ref.setXcoordinate(posX);
		player_ref.setYcoordinate(posY);
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P');
		worldref.setGridCell(worldref,swapPosX*worldref.getNoOfColumns()+posY,'.');
		if(worldref.getHostageCount()==0)// used as a condition to display message when all hostages have been rescued
		{
			cout << worldref.getMessageRef().allHostagesRescued() << endl;
		}
		return worldref;
	}

	//setting player coordinates when player moves left or right and returns current world
	World movePlayerLeftOrRight(int posX,int posY,int swapPosY,World worldref,Player player_ref)
	{
		player_ref.setXcoordinate(posX);
		player_ref.setYcoordinate(posY);
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P');
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+swapPosY,'.');
		if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have been rescued
		{
			cout << worldref.getMessageRef().allHostagesRescued() << endl;
		}
		return worldref;
	}
    
	//setting player coordinates when bomb is found left or right and returns current world
	World bombFoundLeftOrRight(int posX,int posY,int swapPosY,World worldref,Player player_ref)
	{
		worldref=player_ref.addBomb(worldref);
		player_ref.setXcoordinate(posX);
		player_ref.setYcoordinate(posY);
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P');
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+swapPosY,'.');

		if(worldref.getHostageCount()==0) // used as a condition to display message when all hostages have 
		{
			cout << worldref.getMessageRef().allHostagesRescued() << endl;
		}
		return worldref;
	}

	//setting player coordinates when is found up or down  and returns current world
	World bombFoundUpOrDown(int posX,int posY,int swapPosX,World worldref,Player player_ref)
	{
		worldref=player_ref.addBomb(worldref);
		player_ref.setXcoordinate(posX);
		player_ref.setYcoordinate(posY);
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P');
		worldref.setGridCell(worldref,swapPosX*worldref.getNoOfColumns()+posY,'.');


		if(worldref.getHostageCount()==0)
		{
			cout << worldref.getMessageRef().allHostagesRescued() << endl;
		}
		return worldref;

	}
 

	//setting player coordinates amd reached exit flag to true  when player reaches exit from up or down and returns current world
	World exitFromUpOrDown(int posX,int posY,int swapPosX,World worldref,Player player_ref)
	{
		worldref.setReachedExit(true);
		player_ref.setXcoordinate(posX);
		player_ref.setYcoordinate(posY);
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P');
		worldref.setGridCell(worldref,swapPosX*worldref.getNoOfColumns()+posY,'.');
		return worldref;
	}
    
	//setting player coordinates amd reached exit flag to true  when player reaches exit from left or right and returns current world
	World exitFromLeftOrRight(int posX,int posY,int swapPosY,World worldref,Player player_ref)
	{
		worldref.setReachedExit(true);       
		player_ref.setXcoordinate(posX);
		player_ref.setYcoordinate(posY);
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+posY,'P');
		worldref.setGridCell(worldref,posX*worldref.getNoOfColumns()+swapPosY,'.');	
		return worldref;
	}
    
	//sets the coordinate's of player returns player
	Player getActor(World worldref)
	{
		Player player_ref=Player();
		int counter=0;
		for (int i=0; i < worldref.getNoOfRows(); i++)
		{
			for(int j=0;j<worldref.getNoOfColumns();j++)
			{
				if(worldref.getGrid().getGridCell(counter).getActor()=='P')
				{
					player_ref.setXcoordinate(i);
					player_ref.setYcoordinate(j);	     
				}  
				counter++;
			}
		}
		return player_ref;
	}

};

#endif