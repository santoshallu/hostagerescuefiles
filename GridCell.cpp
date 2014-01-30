/*
* Project : Hostage Rescue
* Name: Srinivasa Santosh Kumar Allu
* A-number: A01900937
* Description: This class represents individual grid cell */


class GridCell
{
private:
	int xCoordinate, yCoordinate;
	char actor;

public:

GridCell(int xCoordinate,int yCoordinate,char actor) // sets the grid cell for a particular row/X and column/Y coordiate with an actor object
{
this->xCoordinate=xCoordinate;
this->yCoordinate=yCoordinate;
this->actor =actor;
}

void setXcoordinate(int xCoordinate) // sets X or row coordinate
{
this->xCoordinate=xCoordinate;
}

int getXcoordinate() // gets x or row coordinate
{
return xCoordinate;
}

void setYcoordinate(int yCoordinate) // sets Y or column coordinate
{
this->yCoordinate=yCoordinate;
}

int getYcoordinate() // gets Y or column coordinate
{
return yCoordinate;
}

void setActor(char actor) // sets actor 
{
this->actor=actor;
}

char getActor() // gets actor
{
 return actor;

}

};