/*
* Project : Hostage Rescue
* Author : Srinivasa Santosh Kumar Allu
* A-number: A01900937
* Description : This represents the entire world. This is the master class which has each and every detail related to the game.
*/

#ifndef World_H
#define World_H
#include "Grid.cpp" 
#include <stack>
#include <vector>
#include "Messages.cpp"



class World
{
private:
	int noOfRows; 
	int noOfColumns;
	int timeStep;
	Grid grid_ref; //use to refer grid
	stack<char> noOfBombs; // contains bombs acquired by player
	int bombXcoordinate;
	int bombYcoordinate;
	bool bombPlaced;
	int timeBombStep; // this is used to store timestep when player places bomb
	int hostageCount;
	int totalHostages;
	int totalTimeStep;
	bool playerDead;
	bool hostageDead;
	bool reachedExit;
	bool quitMaze;
	vector <string> directoryNames; //stores array of directory names 
	Messages messageref; // reference to message class 


public:
	World();
	void setRowsColumnsTime(vector<int> inputsFromFile); // sets rows,columns and timestep
	int getNoOfRows(); // gets no of rows
	int getNoOfColumns(); // gets no of columns
	int getTimeStep();// gets timestep
	void setTimeStep(int timeStep); // sets timestep after each move	
	void setGrid(Grid grid_ref); // sets the grid object
	Grid getGrid(); // gets the entire grid object
	World selectMaze(World worldref); // this is used to select maze once player selects the maze it calls loadmaze
	World loadMaze(World worldref); // this is used to read file from maps folders based on user input 
	void listFilesFromDirectory(World worldref); // lists the files from the given directory
	void setGridCell(World worldref,int index, char actor); // sets a grid cell with the actor
	void printMaze(World worldref); // prints the maze
	void addBombs(); // add bombs if number of bombs hold by player is less than 3
	int getNoOfBombs(); // gets number of bombs that player has
	void setbombXCoordinate(int bombXcoordinate); // sets the bomb x or row coordinate
	void setbombYCoordinate(int bombYcoordinate);  // sets the bomb y or column coordinate
	int getbombXCoordinate(); // gets the bomb x or row coordinate
	int getbombYCoordinate();  // gets the bomb y or column coordinate	
	void setTimeBombStep(int step);// sets timebombstep when player places bomb
	void setBombPlaced(bool condition); // this is set to true when bomb is placed by default it is false
	bool getBombPlaced();  //gets bombPlaced variable
	int getTimeBombStep(); // this is used to get timebomstep when bomb has been placed
	void bombExploded(); // once bomb is exploded it reduces bombCount
	void hostageRescued(); // reduces hostagecount by 1 when hostage is rescued
	void setHostageCount(int hostageCount); // sets the hostage count 
	int getHostageCount(); //gets Hostage Count
	void setPlayerDead(bool playerDead); // sets playerDead variable to true
	void setHostageDead(bool hostageDead); // sets hostageDead variable to true
	bool getHostageDead(); //gets playerDead variable
	bool getPlayerDead(); //gets hostageDead variable
	int getTotalHostages(); // gets initial total number of hostages in the map
	int getTotalTimeStep(); // gets initial total timestep described in the map
	void setReachedExit(bool reachedExit); // sets reachedExit to true when player reaches exit
	bool getReachedExit(); // gets reachedExit variable
	void setQuitMaze(bool quitMaze); // sets quitMaze to true when player quits Maze
	bool getQuitMaze(); //gets quitMaze variable
	Messages getMessageRef(); // gets the reference of Message 

};

#include "World_Impl.h"
#endif