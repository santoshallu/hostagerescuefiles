Name : Srinivasa Santosh Kumar
A-number: A01900937
Project: Hostage Rescue
Date: 10th Dec 2013

Description: This is a small game in which player has to free all the hostages from the maze and exit the maze with in a given time step limit

User Manual:
Note: During selection of a item you need to input a number for the corresponding item to be selected
---------------------------------------------------------------------------------------------------------------------------------------	
When you run the program an  menu is displayed with four options

1) Play Game: once user selects play game he will be redirected to another menu which lists mazes that a player can choose. User needs to select a maze
(enter number corresponding to the maze name displayed with number) once user selects maze he will be redirected to another screen which displays
game. From there user will be able to play game.After Game is completed or player lost or player quits player will be displayed with two options 
"press q to return menu" or "press cz to undo move". Its undo's only one step for each undo move . So if you want you to do multiple undo's then
you to enter multiple undo key's("cz") and the same is for redo.
2) Instructions: This shows instructions on how to play game 
3) Credits : This shows project name and the name,A-number who developed the game
4) Exit: user exits from the game

---------------------------------------------------------------------------------------------------------------------------------------	
World Representation And Classes

There are 14 files in this project apart from maps.

Actor.h,Actor_Impl.h - Actor_Impl is the implementation of Actor 
Bomb.h,Box.h,Exit.h,Hostage.h,Player.h,Wall.h - extends actor and has respective implementations for their individual objects 
World.h,World_impl.h - World contains entire information related to the game and World_impl is the implementation of World
Grid.cpp- Represents the entire Grid/Map
GridCell.cpp - Represents individual grid cell inside the Grid/Map. Each GridCell contains an Actor
Hostage_Rescue.cpp - This is the starting of execution where it contains main method. 
                     From that main method respective functions()  will be called based on the userInput.
Message.cpp- This class contains the messages which are displayed in the game.	

Bomb,Box,Exit,Hostage,Player,Wall Extends Actor

---------------------------------------------------------------------------------------------------------------------------------------				 
Maps

All the map files are in the maps folder and all the maps should be text or'.txt' files.

---------------------------------------------------------------------------------------------------------------------------------------	
Extra Features

I have implemented undoandredo personal feature.

Use "cz" for undo and "rz" for redo. These are already explained in instructions defined in the game.

All undo's and redo's are stored in a vector which is of type World (World Class).
 
---------------------------------------------------------------------------------------------------------------------------------------	
Data Structures Used

Array,Vector,Stack

---------------------------------------------------------------------------------------------------------------------------------------	
General :

So objects Bomb,Box,Exit,Hostage,Player,Wall Extends Actor. When ever an action is performed corresponding actions
which are applicable to objects will be set in the Grid based on what type of action it is.

Note: When User Places Map in the maps folder . place correct Maps like map size should tally with the map Given because there is no
validation for map

All the player movements , actions performed by player will be in player class and when an action is done current world state is sent
as response to the called function which is defined in main class. so and each world state is set and also stored in a vector which is primarily used
for undo and redo operations.

In Box class Corresponding coordinates are set when a box is pushed and also all validations like whether box can be moved or not is also checked

In Bomb Class When a player steps bomb is acquired by the player . A player can hold only 3 bombs if it is more than 3 then player ignores/discards
the bombs. In bomb class it checks whether bomb can be placed left,right,up,down of a player. And explosion ,recursive explosion of bomb is implemented
is bomb class. And also Bomb coordinates are set when bomb is placed

In Exit,Wall Class only setting of coordinates of Exit Wall is only performed because there are no specific actions can be performed on it.

In Hostage Class hostage count,  setting of coordinates of Hostage is implemented.

And In World Class and its World Implementation contains each and every detail related to the game 

In Hostage Rescue Class - This is the starting point of execution as it contains main method(). Here respective functions are called based on user input. 
And also all validations like if player or hostage is dead displays appropriate  message and displays an option to undo or quit

---------------------------------------------------------------------------------------------------------------------------------------	
Tough Parts Faced During Implementation

Recursive Bomb explode I mean when bomb is present in the bomb's range(3 X 3) was kind of tough for me to implement.

And also Bomb Implementation is also kind of tough for me to implement (Bomb Explosion).

---------------------------------------------------------------------------------------------------------------------------------------	











 