/**
 *   @file: ant.h
 * @author: Brennan Blain
 *   @date: August 9, 2023
 *  @brief: Ant class
 */

#ifndef ANT_H
#define ANT_H

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "bug.h"
using namespace std;

class Ant : public Bug {
   public:

/**
* @brief Construct a new ant object set symbol to ;
*/
    Ant() : Bug() { setSymbol(';');};

/**
* @brief - Construct a new ant object set row col and steps
* @param size_t newR, size_t newC - to set col and row too
*/
    Ant(size_t newR, size_t newC): Bug(){setSteps(0);};

/**
 * move - moves bug either up,down,left or right if loc avaible to be moved to for specific bug type, also deals with starving for wasps
 * @param  Bug* grid[][GRID_SIZE] - takes the bug grid and edits it to resemble moves made
 */
    void move(Bug* grid[][GRID_SIZE]);

/**
 * breed - called when a specific bug reaches sufficent time steps, creates a new bug in an adjacent location if there are any open
 * @param  Bug* grid[][GRID_SIZE] - takes the bug grid and edits it to resemble moves made
 */
    void breed(Bug* grid[][GRID_SIZE]);
};

void Ant :: move(Bug* grid[][GRID_SIZE])
{
    int newRow = getRow();
    int newCol = getCol();

    
    int direction = rand() % 4; //find random number between 0-4 for new location

    switch (direction) {
        case 0: // up
            newRow = getRow() - 1;
            break;
        case 1: // down
            newRow = getRow() + 1;
            break;
        case 2: // left
            newCol = getCol() - 1;
            break;
        case 3: // right
            newCol = getCol() + 1;
            break;
    }

    // see if new location is on grid and not occupied
    if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && grid[newRow][newCol] == nullptr) {
        grid[getRow()][getCol()] = nullptr; //set ants old position to nullptr
        setRow(newRow); //set new row 
        setCol(newCol); //set new col
        grid[newRow][newCol] = this; //set grid location to current bug
    }
    
}

void Ant :: breed(Bug* grid[][GRID_SIZE])
{
    if (getSteps() >= 3) { //if ant has survived 3 rounds
        int newRow;
        int newCol;
        setSteps(0); //reset steps back to 0

        for (int i = -1; i <= 1; ++i) { //  can move left (-1), none (0), or right (1)
            for (int j = -1; j <= 1; ++j) {// can move down (-1), none (0), or up(1)
                if (i == 0 && j == 0) { // 0,0 is current location of bug breeding
                    continue; // skip the current location
                }

                newRow = getRow() + i; //either increment or decrement by 1 or keep same (move left or right or none)
                newCol = getCol() + j; //either increment or decrement by 1 or keep same (move up or down or none)

                if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && grid[newRow][newCol] == nullptr) { //see if new loaction is valid and not occupied, will return to for loop if conditons not meeet and try a new loc.
                    Ant* newAnt = new Ant(); //create a new ant
                    newAnt->setRow(newRow); //set new ant to open x found
                    newAnt->setCol(newCol); //set new ant to open y found 
                    newAnt->setSteps(0); //set steps to 0 for new ant
                    grid[newRow][newCol] = newAnt; //set grid location to new ant
                    return;
                }
            }
        }
        
    }
}
#endif  // ANT_H
