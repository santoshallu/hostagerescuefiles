/*
Project : Hostage Rescue
Author : Srinivasa Santosh Kumar Allu
A-number: A01900937
Description: This is a small game where some hostages are trapped in a maze.The final goal is to free all the hostages from the maze and
exit the maze with in a given time step limit. */

#include<iostream>
#include <iomanip>
#include <string> 
#include <vector>
#include "World.h"
#include "Actor.h"
#include "Player.h"
#include "Bomb.h"
#include "Box.h"
#include "Hostage.h"
#include "Wall.h"
#include "Exit.h"

using namespace std;

const int max_bombs=3;


int main();
void gameInformation(World worldref); // displays the game information like total timestep,number of moves ,number of hostages, hostages rescues , and number of acquired by player
void play(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo); // this functions is used to checks condition and calls appropriate functions based on the condition like when player quits it calls playerQuitsMaze function
void checkReachedExitWithHostagesRescued(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo); // if player reaches exit withall hostages rescued then it displays appropriate success  message and asks user whether to undo or quit
void playerQuitsMaze(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo);//if player quits maze then it displays appropriate error message and asks user whether to undo or quit
void checkReachedExitWithOutHostagesRescued(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo);// if player reaches exit without hostages rescued then it displays appropriate error message and asks user whether to undo or quit
void checkHostageOrPlayedDead(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo); // if player or hostage or both are dead then it displays appropriate error message and asks user whether to undo or quit
void playIfTimeStepsRemains(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo); // if timestep remains then it allows player to play
void playerRanOutOfTimeSteps(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo); // if player ran out of time steps then appropriate error message is displayed and asks user whether to undo or quit
void playGame(World worldref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo); // here all objects coordinates are set and world initialization is done
void instructions(); // this function displays instructions on how to play game
void credits(); // this function displays credit of the person who developed the game




int main()
{     
	string userInput="";
	char processedInput;
	cout<< setw(10)<< " " << "Hostage Rescue"<<endl<<endl;
	cout<<"---------------------------------------"<<endl<<endl;
	cout <<  setw(10)<< " " <<  "1.Play Game" << endl<<endl;
	cout <<  setw(10)<< " " <<  "2.Help" << endl<<endl;
	cout <<  setw(10)<< " " <<  "3.Credits" << endl<<endl;
	cout <<  setw(10)<< " " <<  "4.Exit" << endl;
	cin >> userInput;
	World worldref=World();
	vector<World> worldrefStateUndo; //this array is used to store worldstate when player makes an undo
	vector<World> worldrefStateRedo; //this array is used to store worldstate when player makes an redo
	if(userInput.size()==1)
	{
		processedInput=userInput[0];
	}
	else
	{
		system("CLS");
		main();  
        cout<<"---------------------------------------"<<endl<<endl;
	    cout << worldref.getMessageRef().invalidInputReenter() << endl ;

	}
	switch(processedInput)
	{
	case '1':playGame(worldref,worldrefStateUndo,worldrefStateRedo) ;
		break;
	case '2':instructions();
		break;
	case'3':credits();
		break;
	case '4':break;
	default: system("CLS");
		cout << worldref.getMessageRef().invalidInputReenter() << endl ;
		main();
	}

	return 0;
}

World worldrefset;

void setWorld(World worldref) // sets the world
{
	worldrefset=worldref;
}

World getWorld() // gets the current world
{
	return worldrefset;
}


void playGame(World worldref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo)  // here all objects coordinates are set and world initialization is done
{
	Player player_ref=Player();
	setWorld(worldref.selectMaze(worldref));
	Hostage hostage_ref=Hostage();
	hostage_ref=hostage_ref.getActor(getWorld());
	setWorld(hostage_ref.noOfHostages(getWorld(),hostage_ref));
	cout << getWorld().getMessageRef().initialState() << endl;
	gameInformation(getWorld());
	getWorld().printMaze(getWorld());
	worldrefStateUndo.push_back(getWorld());
	play(player_ref,worldrefStateUndo,worldrefStateRedo);
}


void play(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo) // this functions is used to check conditions and calls appropriate functions based on the condition like when player quits it calls playerQuitsMaze function
{
	string playerInput="";

	if(getWorld().getReachedExit()==true && getWorld().getHostageCount()==0 && getWorld().getTimeStep()>= 0)
	{
		checkReachedExitWithHostagesRescued(player_ref,worldrefStateUndo,worldrefStateRedo);
	}
	else if(getWorld().getQuitMaze()==true)
	{
		playerQuitsMaze(player_ref,worldrefStateUndo,worldrefStateRedo);

	}

	else if(getWorld().getReachedExit()==true && getWorld().getHostageCount()> 0 && getWorld().getTimeStep()>= 0)
	{
		checkReachedExitWithOutHostagesRescued(player_ref,worldrefStateUndo,worldrefStateRedo);
	}


	else if(getWorld().getPlayerDead()==true || getWorld().getHostageDead()==true)
	{
		checkHostageOrPlayedDead(player_ref,worldrefStateUndo,worldrefStateRedo);
	}

	else if(getWorld().getTimeStep()>= 0)
	{
		playIfTimeStepsRemains(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else
	{
		playerRanOutOfTimeSteps(player_ref,worldrefStateUndo,worldrefStateRedo);
	}

}



void checkReachedExitWithHostagesRescued(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo) // if player reaches exit withall hostages rescued then it displays appropriate success message and asks user whether to undo or quit
{
	string playerInput="";

	if(getWorld().getReachedExit()==true && getWorld().getHostageCount()==0 && getWorld().getTimeStep()>= 0)
	{
		system("CLS");
		cout << getWorld().getMessageRef().wonTheGame() << endl;
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		cout<< getWorld().getMessageRef().success()<< endl;
choice1:
		cout << getWorld().getMessageRef().quitOrUndo() << endl;
		cin >> playerInput;
		if(playerInput.compare("q")==0) // player quits maze
		{
			system("CLS");
			main();
		}
		else if(playerInput=="cz" && worldrefStateUndo.size() > 1  ) // player undo's move
		{
			system("CLS");
			cout<< getWorld().getMessageRef().undo() << endl;
			worldrefStateRedo.push_back(worldrefStateUndo[worldrefStateUndo.size()-1]);
			worldrefStateUndo.pop_back();
			setWorld(worldrefStateUndo[worldrefStateUndo.size()-1]);
			gameInformation(getWorld());
			getWorld().printMaze(getWorld());
			play(player_ref,worldrefStateUndo,worldrefStateRedo);

		}
		else if(playerInput=="rz" &&  worldrefStateRedo.size() > 0 ) // player redo's move
		{
			cout<< getWorld().getMessageRef().redo() << endl; 
			setWorld(worldrefStateRedo[worldrefStateRedo.size()-1]);
			worldrefStateRedo.pop_back();
			gameInformation(getWorld());
			getWorld().printMaze(getWorld());
			play(player_ref,worldrefStateUndo,worldrefStateRedo);

		}
		else
		{
			goto choice1;
		}
	}

}

void playerQuitsMaze(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo) //if player quits maze then it displays appropriate error message and asks user whether to undo or quit
{
	string playerInput="";

choice2:
	cout << getWorld().getMessageRef().quitOrUndo() << endl;
	cin >> playerInput;
	if(playerInput.compare("q")==0) // player quits maze
	{
		system("CLS");
		main();
	}
	else if(playerInput=="cz" && worldrefStateUndo.size() > 1  )// player undo's move
	{
		system("CLS");
		cout<< getWorld().getMessageRef().undo() << endl;
		worldrefStateRedo.push_back(worldrefStateUndo[worldrefStateUndo.size()-1]);
		worldrefStateUndo.pop_back();
		setWorld(worldrefStateUndo[worldrefStateUndo.size()-1]);
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else if(playerInput=="rz" &&  worldrefStateRedo.size() > 0 ) // player redo's move
	{
		cout<< getWorld().getMessageRef().redo()<< endl; 
		setWorld(worldrefStateRedo[worldrefStateRedo.size()-1]);
		worldrefStateRedo.pop_back();
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else
	{
		goto choice2;
	}

}

void checkReachedExitWithOutHostagesRescued(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo) // if player reaches exit without hostages rescued then it displays appropriate error message and asks user whether to undo or quit
{
	string playerInput="";
	system("CLS");
	cout << getWorld().getMessageRef().exitwithoutHostages() << endl;
	gameInformation(getWorld());
	getWorld().printMaze(getWorld());
	cout<< getWorld().getMessageRef().failure()<< endl;
choice3:
	cout << getWorld().getMessageRef().quitOrUndo() << endl;
	cin >> playerInput;
	if(playerInput.compare("q")==0)// player quits maze
	{
		system("CLS");
		main();
	}
	else if(playerInput=="cz" && worldrefStateUndo.size() > 1  )// player undo's move
	{
		system("CLS");
		cout<< getWorld().getMessageRef().undo() << endl;
		worldrefStateRedo.push_back(worldrefStateUndo[worldrefStateUndo.size()-1]);
		worldrefStateUndo.pop_back();
		setWorld(worldrefStateUndo[worldrefStateUndo.size()-1]);
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else if(playerInput=="rz" &&  worldrefStateRedo.size() > 0 )// player redo's maze
	{
		cout<< getWorld().getMessageRef().redo() << endl; 
		setWorld(worldrefStateRedo[worldrefStateRedo.size()-1]);
		worldrefStateRedo.pop_back();
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else
	{
		goto choice3;
	}

}

void checkHostageOrPlayedDead(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo) // if player or hostage or both are dead then it displays appropriate error message and asks user whether to undo or quit
{
	string playerInput="";
	system("CLS");

	if(getWorld().getPlayerDead()==true && getWorld().getHostageDead()==true)
	{
		cout << getWorld().getMessageRef().hostagePlayerExplosionRange() << endl ;
	}
	else if(getWorld().getPlayerDead()==true)
	{
		cout << getWorld().getMessageRef().playerExplosionRange() << endl;
	}
	else if(getWorld().getHostageDead()==true)
	{
		cout << getWorld().getMessageRef().hostageExplosionRange() << endl ;

	}
	gameInformation(getWorld());
	getWorld().printMaze(getWorld());
	cout << getWorld().getMessageRef().failure() << endl<<endl;
choice4:
	cout << getWorld().getMessageRef().quitOrUndo() << endl;
	cin >> playerInput;
	if(playerInput.compare("q")==0) //player quits maze
	{
		system("CLS");
		main();
	}
	else if(playerInput=="cz" && worldrefStateUndo.size() > 1  ) // player undo's move
	{
		system("CLS");
		cout<< getWorld().getMessageRef().undo() << endl;
		worldrefStateRedo.push_back(worldrefStateUndo[worldrefStateUndo.size()-1]);
		worldrefStateUndo.pop_back();
		setWorld(worldrefStateUndo[worldrefStateUndo.size()-1]);
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else if(playerInput=="rz" &&  worldrefStateRedo.size() > 0 ) // player redo's move
	{
		cout<< getWorld().getMessageRef().redo() << endl; 
		setWorld(worldrefStateRedo[worldrefStateRedo.size()-1]);
		worldrefStateRedo.pop_back();
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else
	{
		goto choice4;
	}
}

void playIfTimeStepsRemains(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo) // if timestep remains then it allows player to play
{
	string playerInput="";
	player_ref=player_ref.getActor(getWorld());
	cin >> playerInput;
	system("CLS");

	if(playerInput=="cz" && worldrefStateUndo.size() > 1  ) // players undo's move
	{
		cout<< getWorld().getMessageRef().undo() << endl;

		worldrefStateRedo.push_back(worldrefStateUndo[worldrefStateUndo.size()-1]);
		worldrefStateUndo.pop_back();
		setWorld(worldrefStateUndo[worldrefStateUndo.size()-1]);
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
	}

	else if(playerInput=="rz" &&  worldrefStateRedo.size() > 0 ) // players redo's move
	{
		cout<< getWorld().getMessageRef().redo()<< endl; 
		setWorld(worldrefStateRedo[worldrefStateRedo.size()-1]);
		worldrefStateRedo.pop_back();
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());

	}

	else if(playerInput=="cz" && worldrefStateUndo.size() ==1) // player cannot undo because there are moves to undo
	{
		cout<< getWorld().getMessageRef().noMovesUndo() << endl;
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());

	}

	else if(playerInput=="rz" && worldrefStateRedo.size() ==0)  // player cannot redo because there are moves to redo
	{
		cout<< getWorld().getMessageRef().noMovesRedo() << endl;
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());

	}

	else
	{
		setWorld(player_ref.play(getWorld(),player_ref,playerInput));
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		worldrefStateUndo.push_back(getWorld());

	}
	play(player_ref,worldrefStateUndo,worldrefStateRedo);



}

void playerRanOutOfTimeSteps(Player player_ref,vector<World> worldrefStateUndo,vector<World> worldrefStateRedo) // if player ran out of time steps then appropriate error message is displayed and asks user whether to undo or quit
{
	string playerInput="";
	system("CLS");
	cout << getWorld().getMessageRef().noTimeSteps()<< endl << endl;
	gameInformation(getWorld());
	getWorld().printMaze(getWorld());
	cout << getWorld().getMessageRef().failure()<< endl<<endl;
choice5:
	cout << getWorld().getMessageRef().quitOrUndo() << endl;
	cin >> playerInput;
	if(playerInput.compare("q")==0) //player quits the maze
	{
		system("CLS");
		main();
	}
	else if(playerInput=="cz" && worldrefStateUndo.size() > 1  ) // player makes an undo
	{
		system("CLS");
		cout<< getWorld().getMessageRef().undo() << endl;
		worldrefStateRedo.push_back(worldrefStateUndo[worldrefStateUndo.size()-1]);
		worldrefStateUndo.pop_back();
		setWorld(worldrefStateUndo[worldrefStateUndo.size()-1]);
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else if(playerInput=="rz" &&  worldrefStateRedo.size() > 0 ) // player makes a redo
	{
		cout<< getWorld().getMessageRef().redo() << endl; 
		setWorld(worldrefStateRedo[worldrefStateRedo.size()-1]);
		worldrefStateRedo.pop_back();
		gameInformation(getWorld());
		getWorld().printMaze(getWorld());
		play(player_ref,worldrefStateUndo,worldrefStateRedo);

	}
	else
	{
		goto choice5;
	}
}

void gameInformation(World worldref)  // displays the game information like total timestep,number of moves ,number of hostages, hostages rescues , and number of acquired by player
{
	cout<<"--------------------------------------------------------"<<endl;
	cout << "Time:"<< setw(12)<< " "  << setw(5)  <<  worldref.getTimeStep()     << "         Moves:"<<  setw(13) <<    worldref.getTotalTimeStep()- worldref.getTimeStep()<< endl;
	cout << "Hostages:"<< setw(8)<< " "<< setw(5) << worldref.getTotalHostages() << "         Rescued:"<<  setw(11)  << worldref.getTotalHostages()-worldref.getHostageCount() << endl;
	cout << "Bombs:"<< setw(11)<< " " << setw(5)  << worldref.getNoOfBombs()     <<"         Max bombs:"<<  setw(9) << max_bombs << endl;
	cout<<"--------------------------------------------------------"<<endl<<endl;
}

void instructions() // this function displays instructions on how to play game
{
	string pressAnyKey="";
	system("CLS");
	cout<<"Key:         " << "Action" << endl<<endl;
	cout<<"--------------------------------------------------------"<<endl<<endl;
	cout <<"u"   << setw(12) << " "<<"Player Goes Up" <<endl;
	cout <<"d"   << setw(12)<< " "<<"Player Goes Down" <<endl;
	cout <<"l"  << setw(12)<< " "<<"Player Goes Left" <<endl;
	cout <<"r"  << setw(12)<< " "<< "Player Goes Right" <<endl;
	cout <<"w"  << setw(12)<< " "<< "Player Skips a Turn" <<endl;
	cout <<"q!"  << setw(11)<< " "<< "Player Quits Game" <<endl;
	cout <<"bu" << setw(11)<< " "<< "Player Places Bomb In the Upper Side of Player" <<endl;
	cout <<"bd" << setw(11)<< " "<< "Player Places Bomb In the Lower/Down Side of Player" <<endl;
	cout <<"bl" << setw(11)<< " "<< "Player Places Bomb In the Left Side of Player" <<endl;
	cout <<"br" << setw(11)<< " "<< "Player Places Bomb In the Right Side of Player" <<endl;
	cout <<"cz" << setw(11)<< " "<< "Player Undo's one step" <<endl;
	cout <<"rz" << setw(11)<< " "<< "Player Redo's one step" <<endl<<endl;
	cout << "Press Any Key to go to menu" << endl;
	cin >> pressAnyKey;
	system("CLS");
	main();

}

void credits() // this function displays credit of the person who developed the game
{
	string pressAnyKey="";
	system("CLS");
	cout<< setw(10)<< " " << "Hostage Rescue"<<endl<<endl;
	cout<<"---------------------------------------"<<endl;
	cout << "Name      :  Srinivasa Santosh Kumar Allu"<<endl;
	cout << "A-Number  :  A01900937"<<endl<<endl;
	cout << "Press Any Key to go to menu" << endl;
	cin >> pressAnyKey;
	system("CLS");
	main();


}