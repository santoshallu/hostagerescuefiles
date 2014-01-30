/*
Project : Hostage Rescue
Author : Srinivasa Santosh Kumar Allu
A-number: A01900937
Description: This class contains methods to get the messages which are displayed in the game. */

#include <string>
using namespace std;

class Messages
{

public:

	string getPlayerMovedRight()
	{
		return "Player Moved Right ";
	}

	string getPlayerCannotBeMovedRight()
	{
		return "Player Cannot Be Moved Right\n";
	}

	string getBoxCannotBeMovedRight()
	{
		return "Box Cannot Be Moved Right\n";
	}

	string getPlayerMovedRightRescuedHostage()
	{
		return "Player Moved Right and Rescued Hostage\n";

	}

	string getPlayerMovedBoxRight()
	{
		return "Player Moved Right and Pushed The Box\n";
	}


	string getPlayerMovedLeft()
	{
		return "Player Moved Left ";
	}

	string getPlayerCannotBeMovedLeft()
	{
		return "Player Cannot Be Moved Left\n";
	}

	string getBoxCannotBeMovedLeft()
	{
		return "Box Cannot Be Moved Left\n";
	}

	string getPlayerMovedLeftRescuedHostage()
	{
		return "Player Moved Left and Rescued Hostage\n";
	}

	string getPlayerMovedBoxLeft()
	{
		return "Player Moved Left and Pushed The Box\n";
	}



	string getPlayerMovedUp()
	{
		return "Player Moved Up ";
	}

	string getPlayerCannotBeMovedUp()
	{
		return "Player Cannot Be Moved Up\n";
	}
	string getBoxCannotBeMovedUp()
	{
		return "Box Cannot Be Moved Up\n";
	}

	string getPlayerMovedUpRescuedHostage()
	{
		return "Player Moved Up and Rescued Hostage\n";
	}

	string getPlayerMovedBoxUp()
	{
		return "Player Moved Up and Pushed The Box\n";
	}



	string getPlayerMovedDown()
	{
		return "Player Moved Down ";
	}

	string getPlayerCannotBeMovedDown()
	{
		return "Player Cannot Be Moved Down\n";
	}

	string getBoxCannotBeMovedDown()
	{
		return "Box Cannot Be Moved Down\n";
	}

	string getPlayerMovedDownRescuedHostage()
	{
		return "Player Moved Down and Rescued Hostage\n";
	}

	string getPlayerMovedBoxDown()
	{
		return "Player Moved Down and Pushed The Box\n";
	}

	string getPlayerSkippedTurn()
	{
		return "Player skipped a turn\n";
	}

	string getPlayerQuitsMaze()
	{
		return "Player quits the maze\n";
	}

	string getPlayerNoBombs()
	{
		return "Player dont have enough bombs\n";
	}

	string getInvalidPlayMove()
	{
		return "Invalid Input \nuse any of u,d,l,r,w,q!,bu,bd,bl,br,cz,rz as defined in instruction set\n";
	}

	string bombExploded()
	{
		return "Bomb Exploded\n";
	}

	string bombPlacedRight()
	{
		return "Bomb is placed on the right side of player\n";
	}

	string bombCannotBePlacedRight()
	{
		return "Bomb Cannot be Placed Right\n";
	}

	string bombPlacedLeft()
	{
		return "Bomb is placed on the left side of player\n";
	}

	string bombCannotBePlacedLeft()
	{
		return "Bomb Cannot be Placed Left\n";
	}

	string bombPlacedUp()
	{
		return "Bomb is placed on the up side of player\n";
	}

	string bombCannotBePlacedUp()
	{
		return "Bomb Cannot be Placed Up\n";
	}

	string bombPlacedDown()
	{
		return "Bomb is placed on the down side of player\n";
	}

	string bombCannotBePlacedDown()
	{
		return "Bomb Cannot be Placed Down\n";
	}

	string allHostagesRescued()
	{
		return "All the Hostages have been Rescued!Please Exit the Maze before time becomes zero";
	}

	string playerHasbombLimit()
	{
		return "grabbed bomb\n";
	}

	string bombLimitReached()
	{
		return "couldn't Grab Bomb because maximum bomb limit reached\n" ;
	}

	string invalidInputReenter()
	{
		return "That is an invalid input please reenter your input\n";
	}

	string wonTheGame()
	{
		return "Player was able to exit maze and rescues all hostages within the given time limit :)\n";
	}

	string quitOrUndo()
	{
		return "Press q to return to menu or cz to undo move\n";
	}

	string undo()
	{
		return "Player made an undo\n";
	}

	string redo()
	{
		return "Player made an redo\n";
	}

	string exitwithoutHostages()
	{
		return "Player Reached Exit Without Rescuing All Hostages! Player Lost :(\n";
	}

	string failure()
	{
		return "FAILURE\n";
	}

	string success()
	{
		return "SUCCESS\n";
	}

	string hostagePlayerExplosionRange()
	{
		return "Hostage,Player Killed Because Hostage,Player are in the range Of Explosion\n";
	}

	string playerExplosionRange()
	{
		return "Player Killed Because Player Was in the range Of Explosion\n";
	}

	string hostageExplosionRange()
	{
		return "Hostage Killed Because Hostage Was in the range Of Explosion\n";
	}

	string noMovesUndo()
	{
		return "There are no Moves To Undo\n";
	}

	string noMovesRedo()
	{
		return "There are no Moves To Redo\n";
	}

	string noTimeSteps()
	{
		return "Player lost because Time Expired! And maze has been destroyed with player Inside :(\n";
	}

	string initialState()
	{
		return "Game started .. use any of u,d,l,r as defined in instructions \n";
	}

	string drawLine()
	{
		return "--------------------------------------------------------";
	}





};
