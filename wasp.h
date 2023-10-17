/**
 *   @file: wasp.h
 * @author: Brennan Blain
 *   @date: August 9, 2023
 *  @brief: Wasp class
 */
#ifndef WASP_H
#define WASP_H

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "bug.h"
using namespace std;

class Wasp : public Bug {
   public:

/**
* @brief Construct a new ant object set symbol to Q
*/
    Wasp() : Bug(){setSymbol('Q');};

/**
* @brief - Construct a new wasp object set row col and steps
* @param size_t newR, size_t newC - to set col and row too
*/
    Wasp(size_t newR, size_t newC) : Bug(){ starve = 0; setSteps(0);};

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
   
   private:
    size_t starve; 
};

void Wasp :: move(Bug* grid[][GRID_SIZE])
{
    int newRow = getRow(); // set newrow to row wasps is in now
    int newCol = getCol(); // set newcol to col wasps is in now 
    int oldRow = getRow(); // set oldrow to row wasps is in now
    int oldCol = getCol(); // set oldcol to col wasps is in now

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
    if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE) //if new loc is on the grid
    {
        
        if (grid[newRow][newCol] == nullptr || grid[newRow][newCol]->getSymbol() == ';') // if new loc is empty or occupied by an ant 
        {
            if(grid[newRow][newCol] == nullptr) //if new loc. is empty increment starve
            {
                starve++;

            }
            else //if new loc wasn't empty set starve to zero (must have eaten an ant)
            {
                starve = 0;
            }

            grid[getRow()][getCol()] = nullptr; //set locaton where wasp was to nullptr
            setRow(newRow);// set wasps new row to one found
            setCol(newCol); //set wasps new col to one found
            grid[newRow][newCol] = this; //set grid location to current bug
        }
        else //if new loc was occupied by anything otherthan nullptr or ; (Q), increment starve and dont move
        {
            starve++;
        }
        
    } 
    else //if new loc was off grid increment starve 
    {
        starve++;
    }

    if (starve >= 3) //if wasps goes 3 turns with out eating
    {
        grid[getRow()][getCol()] = nullptr; // set location where wasp is to nullptr (will be the new location found above)
    } 
    else if (starve >= 3 && (newRow < 0 || newRow >= GRID_SIZE || newCol < 0 || newCol >= GRID_SIZE)) // if wasps starves and the new location generated was off the grid
    {
        grid[oldRow][oldCol] = nullptr; // set the original location of the wasps to nullptr (because it never moved)
    }
}

void Wasp :: breed(Bug* grid[][GRID_SIZE])
{
    if (getSteps() >= 8) { //if wasp has survived 8 rounds
        int newRow, newCol;
        setSteps(0); //reset step count

        for (int i = -1; i <= 1; ++i) { //  can move left (-1), none (0), or right (1)
            for (int j = -1; j <= 1; ++j) { // can move down (-1), none (0), or up(1)
                if (i == 0 && j == 0) { // 0,0 is current location of bug breeding
                    continue; // skip the current location
                }

                newRow = getRow() + i; //either increment or decrement by 1 or keep same (move left or right or none)
                newCol = getCol() + j; //either increment or decrement by 1 or keep same (move up or down or none)


                if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && (grid[newRow][newCol] == nullptr || grid[newRow][newCol]->getSymbol() != 'Q')) { 
                    //see if new loaction is valid and not occupied by another wasp, will return to for loop if conditons not meeet and try a new loc.
                    Wasp* newWasp = new Wasp(); //create new wasp
                    newWasp->setRow(newRow); //set new ant to open x found
                    newWasp->setCol(newCol); //set new ant to open y found 
                    newWasp->setSteps(0); //set steps to 0 for new wasp
                    grid[newRow][newCol] = newWasp; //set grid location to new wasp
                    return;
                }
            }
        }
        
    }
}

#endif  // WASP_H