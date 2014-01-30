/* 
* Project : Hostage Rescue
* Author : Srinivasa Santosh Kumar Allu
* A-number: A01900937
* Description: This class represents the Grid */


#include<vector>
#include<string>
#include<iostream>
#include "GridCell.cpp"



using namespace std;

class Grid
{
private:
	int rowSize;
	int columnSize;
	vector <GridCell> gridCellsRef;

public:

	void createGrid(vector<string> map,int rows,int columns) // this is used to create entire grid with the gridcell objects
	{
		rowSize=rows;
		columnSize=columns;

		for (int i=0; i < rowSize; i++)
		{
			for(int j=0;j<columnSize;j++)
			{
				
				gridCellsRef.push_back(GridCell(i,j,map[i][j]));
			  	
			}

		}

	}
	
	int getRowSize() // gets the number of rows
	{
      return rowSize;
	}

	int getColumnSize() // gets number of columns
	{
      return columnSize;
	}

	vector <GridCell>  getGridcells() // gets all the gridcells
	{
      return gridCellsRef;
	}

	void setGridcells(vector <GridCell> gridCellsRef) // sets all the grid cells
	{
      this->gridCellsRef=gridCellsRef;
	}

	void setGridCell(int index,char actor) // sets a particular grid cell with an actor object
	{
		gridCellsRef[index].setActor(actor);
	}

    GridCell getGridCell(int index) // gets a particular grid cell for a given index
	{
     return gridCellsRef[index];
	}


	

};