/**
 *   @file: predator-prey.cc
 * @author: Brennan Blain
 *   @date: August 9, 2023
 *  @brief: Predator Pray game of wasps and ants.
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "ant.h"
#include "bug.h"
#include "wasp.h"

using namespace std;

/// Constants and function prototypes
const size_t NUM_WASPS = 5;
const size_t NUM_ANTS = 100;

/**
 * initializeGrid - creates a grid 20x20 full of pointers for bugs, filled with 5 wasps objects and 100 ant objects at random loactions
 * @param  Bug* grid[][GRID_SIZE] - takes the bug grid and fills it
 */
void initializeGrid(Bug* grid[][GRID_SIZE]);

/**
 * displayGrid - takes the 20x20 grid and prints organized display showing location of all objects in grid
 * @param  Bug* grid[][GRID_SIZE] - takes the filled bug grid to be displayed
 */
void displayGrid(Bug* grid[][GRID_SIZE]);

/**
 * timeStep - sends all objects on grid to be moved as well as checks both bugs for breeding as well as wasps for starvation, every time the user hits enter
 * @param  Bug* grid[][GRID_SIZE] - parses trough grid and takes every object and sends it to move function with grid as well as to starve and breed functions with grid if applicable
 */
void timeStep(Bug* grid[][GRID_SIZE]);


int main(int argc, char const* argv[]) {
    Bug* grid[GRID_SIZE][GRID_SIZE];
    srand(time(nullptr));

    initializeGrid(grid);
    string ans = "";
    do
    {
        displayGrid(grid);
        timeStep(grid);
        cout << "hit enter to move again, type n to quit: ";
        getline(cin, ans);
    } while (ans == "");
    
    //if you want, you run the simulation a certain number of times
    //uncomment the following
    /*
    displayGrid(grid);
    for (size_t i = 0; i < 1000; i++)
    {
        timeStep(grid);
    }
    displayGrid(grid);
    */
    
    return 0;
}  /// main

void initializeGrid(Bug* grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            grid[i][j] = nullptr; //initialize all locations inside grid to nullptr
        }
    }

    for (int antCount = 0; antCount < NUM_ANTS; ++antCount) { //populate grid with ants
        int x;
        int y;

        do {
            x = rand() % GRID_SIZE; //find a random x cord
            y = rand() % GRID_SIZE; // find a random y cord
        } while (grid[x][y] != nullptr); 

        Ant* newAnt = new Ant(); //create a new ant
        newAnt->setRow(x); //set new ants row to x cord found
        newAnt->setCol(y); //set new,ants col to y cord found
        newAnt -> setSteps(0); //set steps to zero for breeding purpose
        grid[x][y] = newAnt; // put ant on grid
    }

    for (int waspCount = 0; waspCount < NUM_WASPS; ++waspCount) { //populate grid with wasps
        int x;
        int y;

        do {
            x = rand() % GRID_SIZE; //find a random x cord
            y = rand() % GRID_SIZE; // find a random y cord
        } while (grid[x][y] != nullptr);

        Wasp* newWasp = new Wasp(); //create a new wasp
        newWasp->setRow(x);//set new wasp row to x cord found
        newWasp->setCol(y);//set new wasp col to y cord found
        newWasp->setSteps(0);//set steps to zero for breeding purpose
        grid[x][y] = newWasp; // put wasp on grid
    }
}

void displayGrid(Bug* grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        cout << '|'; //for every element in row print |
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr) {
                cout << grid[i][j]->getSymbol();// if cord is not empty get the symbol for what is in it
            } else {
                cout << ' '; // Print empty cord
            }
            cout << '|'; // close the cord so | | 
        }
        cout << endl; //endl once all cords in x have been parced through 
    }
    
}

void timeStep(Bug* grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i) //moving all wasps first
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            Bug* currentBug = grid[i][j]; //create pointer to poiint at contents in location x,y on grid
            if (currentBug != nullptr && currentBug->getSymbol() == 'Q' && !currentBug->getBeenMoved()) { // if xy is not empty and is occupied by Q and hasnt been moved 
                currentBug->move(grid); // move contents of xy
                currentBug->setBeenMoved(true); //set moved to true to ensure contents wont be moved twice in one turn
                currentBug->setSteps(currentBug->getSteps() + 1); //increment contents steps count by 1
                if (currentBug->getSteps() >= 8) // if wasps survived 8 steps then breed
                {
                    currentBug -> breed(grid);
                }
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; ++i) //move all ants second 
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            Bug* currentBug = grid[i][j]; //create pointer to point at contents in location x,y on grid
            if (currentBug != nullptr && currentBug->getSymbol() == ';' && !currentBug->getBeenMoved()) { // if xy is not empty and is occupied by ; and hasnt been moved
                currentBug->move(grid); //move contnets of xy
                currentBug->setBeenMoved(true); //set moved to true to ensure contents wont be moved twice in one turn
                currentBug->setSteps(currentBug->getSteps() + 1);//increment contents steps count by 1
                if (currentBug->getSteps() >= 3) // if ant survived 3 steps then breed
                {
                    currentBug -> breed(grid);
                }
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; ++i) { //after all elements have been moved set moved back to false for next turn
        for (int j = 0; j < GRID_SIZE; ++j) {
            Bug* currentBug = grid[i][j];
            if (currentBug != nullptr) {
                currentBug->setBeenMoved(false);
            }
        }
    }
}

