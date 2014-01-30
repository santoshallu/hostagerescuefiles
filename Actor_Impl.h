/* 
* Project : Hostage Rescue
* Name:Srinivasa Santosh Kumar Allu
* A-number:A01900937
* Description: This is the implementation of actor class
*/

int Actor::getXcoordinate() // gets the X-coordinate or row position in the Map
	{
       return xCoordinate;
	}
	void  Actor::setXcoordinate(int xCoordinate) // sets the X-coordinate or row position in the Map
	{
		this->xCoordinate=xCoordinate;
	}
	int  Actor::getYcoordinate()  // gets the Y-coordinate or column position in the Map
	{
       return yCoordinate;
	}
	void  Actor::setYcoordinate(int yCoordinate) // gets the Y-coordinate or column position in the Map
	{
		this->yCoordinate=yCoordinate;
	}
	Actor Actor::getActor(World worldref)  //sets the coordinate's of actor returns actor
	{
		Actor actor = Actor();
		return actor;
	}

