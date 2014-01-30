/*
* Project : Hostage Rescue
* Author : Srinivasa Santosh Kumar Allu
* A-number: A01900937
* Description: This file contains implementation of world class */

using namespace std;
#include<iostream>
#include <vector>
#include<fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <dirent.h>
#include <sys/stat.h>


#include "World.h"
using namespace std;

World::World()
{
	bombPlaced=false;
	bombXcoordinate=0;
	bombYcoordinate=0;
	timeBombStep=0;
	hostageCount=0;
	totalHostages=0;
	totalTimeStep=0;
	playerDead=false;
	hostageDead=false;
	reachedExit=false;
	quitMaze=false;
}
void World::setRowsColumnsTime(vector<int> inputsFromFile) // sets rows,columns and timestep
{
	noOfRows= inputsFromFile[0];
	noOfColumns= inputsFromFile[1];
	timeStep=inputsFromFile[2];	
	totalTimeStep=timeStep;
}

int World::getNoOfRows()  // gets no of rows
{
	return noOfRows;
}

int World::getNoOfColumns() // gets no of columns
{
	return noOfColumns;
}
int World::getTimeStep() // gets timestep
{
	return timeStep;
}
void World::setTimeStep(int timeStep)  // sets timestep after each move
{
	this->timeStep=timeStep;

}
void World::setGrid(Grid grid_ref) // sets the grid object
{

	this->grid_ref=grid_ref;

}

Grid World::getGrid() // gets the entire grid object
{
	return grid_ref;
}


void World::listFilesFromDirectory(World worldref) // lists the files from the given directory
{
	string dir_name = "./maps"; // current directory

	DIR *dir;
	struct dirent *ent;
	struct stat filestat;

	if ((dir = opendir (dir_name.c_str())) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			// Skip the file if it is invalid or it is a directory
			string filepath = dir_name + "/" + ent->d_name;
			if (stat( filepath.c_str(), &filestat ))
				continue;
			if (S_ISDIR( filestat.st_mode ))
				continue;
			directoryNames.push_back(ent->d_name);
		}
		closedir (dir);
	}
	else {
		/* could not open directory */
		cerr << strerror(errno) << endl;
		return;
	}

	return;

}




World World::selectMaze(World worldref) // this is used to select maze once player selects the maze it calls loadmaze
{
	int userInput=0;

	system("CLS");
	cout << "please select the maze you would like to play" << endl << endl;
	listFilesFromDirectory(worldref);
	cout<<"------------------------------------------"<<endl<<endl;
	for(int i=0;i<directoryNames.size();i++)
	{
		cout <<  setw(10)<< " " << i+1 << ". "<< directoryNames[i].substr(0, directoryNames[i].find(".")) <<endl<< endl;
	}

	return loadMaze(worldref);

}


World World::loadMaze(World worldref) // this is used to read file from maps folder based on user input 
{
	string line;
	string userInput="";
	char processedInput;
	int lineCount=0;
validateInput:
	cin >> userInput;
	vector <int> rowsColumnsTime;
	vector <string> mapRepresentation;
	ifstream myfile;
	int i=0;
	int chartoIntInput=0;
	int fileFound=0;

	if(userInput.size()==1)
	{
		processedInput=userInput[0];
	}
	else
	{
		cout << messageref.invalidInputReenter() << endl ;
		goto validateInput;  
	}
	chartoIntInput=(int)processedInput-48;
	for(i=0;i<directoryNames.size();i++)
	{
		if(chartoIntInput==i+1)
		{
			myfile.open(("maps/"+directoryNames[i]).c_str());
			fileFound=1;

		}	      
	}
	if(fileFound==1)
	{

	}
	else
	{
		cout << messageref.invalidInputReenter() << endl ;
		goto validateInput;
	}
	system("CLS");
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			if(lineCount==0)
			{
				stringstream stream(line);
				while(1) 
				{
					int n;
					stream >> n;
					if(!stream)
						break;
					rowsColumnsTime.push_back(n);
				}
				worldref.setRowsColumnsTime(rowsColumnsTime);
			}
			else
			{
				mapRepresentation.push_back(line);
			}

			lineCount++;
		}

		myfile.close();
		grid_ref.createGrid(mapRepresentation,worldref.noOfRows,worldref.noOfColumns);		
		worldref.setGrid(grid_ref);
		return worldref;
	}

}

void World::setGridCell(World worldref,int index, char actor) // sets a grid cell with the actor
{
	grid_ref.setGridCell(index,actor);
	worldref.setGrid(grid_ref);
}



void World::printMaze(World worldref) // prints the maze
{
	int counter=0;
	for (int i=0; i < worldref.noOfRows; i++)
	{
		for(int j=0;j<worldref.noOfColumns;j++)
		{	
			cout << worldref.getGrid().getGridCell(counter).getActor();
			counter++;
		}
		cout<<endl;

	}		
	cout << endl;
	cout << getMessageRef().drawLine()<<endl<<endl;

}


void World::addBombs() // add bombs if number of bombs hold by player is less than 3
{
	if(getNoOfBombs()< 3)
	{
		noOfBombs.push('b');
		 cout <<  messageref.playerHasbombLimit() << endl;
	}
	else
	{

      cout <<messageref.bombLimitReached() << endl;
	}
}

void World::bombExploded() // once bomb is exploded it reduces bombCount
{
	noOfBombs.pop();
}

int World::getNoOfBombs() // gets number of bombs that player has
{
	return noOfBombs.size();
}

void World::setbombXCoordinate(int bombXcoordinate) // sets the bomb x or row coordinate
{
	this->bombXcoordinate=bombXcoordinate;
}

void World::setbombYCoordinate(int bombYcoordinate)  // sets the bomb y or column coordinate
{
	this->bombYcoordinate=bombYcoordinate;
}

int  World::getbombXCoordinate()  // gets the bomb x or row coordinate
{
	return bombXcoordinate;
}

int  World::getbombYCoordinate() // gets the bomb y or column coordinate	
{
	return bombYcoordinate;
}

void World::setBombPlaced(bool condition) // this is set to true when bomb is placed by default it is false
{
	bombPlaced=condition;
}

void World::setTimeBombStep(int step) // sets timebombstep when player places bomb
{
	timeBombStep=step;
}

int  World::getTimeBombStep() // this is used to get timebomstep when bomb has been placed
{
	return timeBombStep;
}

bool  World::getBombPlaced() //gets bombPlaced variable
{
	return bombPlaced;
}

void World::setHostageCount(int hostageCount) // sets the hostage count 
{
	this->hostageCount=hostageCount;
	totalHostages=hostageCount;
}

int World::getHostageCount() //gets Hostage Count
{
	return hostageCount;
}

void World::hostageRescued() // reduces hostagecount by 1 when hostage is rescued
{
	hostageCount=hostageCount-1;
}

void World::setPlayerDead(bool playerDead) // sets playerDead variable to true
{
	this->playerDead=playerDead;
}

void World::setHostageDead(bool hostageDead) // sets hostageDead variable to true
{
	this->hostageDead=hostageDead;
}

void World::setReachedExit(bool reachedExit) // sets reachedExit to true when player reaches exit
{
	this->reachedExit=reachedExit;
}

bool World::getReachedExit() // gets reachedExit variable
{
	return reachedExit;
}
bool World::getPlayerDead() //gets playerDead variable
{
	return playerDead;
}
bool World::getHostageDead() //gets hostageDead variable
{
	return hostageDead;
}

int World::getTotalHostages()  // gets initial total number of hostages in the map
{
	return totalHostages;
}

int World::getTotalTimeStep() // gets initial total timestep described in the map
{
	return totalTimeStep;
}

void World::setQuitMaze(bool quitMaze) //sets quitMaze variable
{
	this->quitMaze=quitMaze;
}

bool World::getQuitMaze() //gets quitMaze variable
{
	return quitMaze;
}

Messages World::getMessageRef() // gets the reference of Message 
{
return messageref;
}