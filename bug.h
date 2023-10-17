/**
 *   @file: bug.h
 * @author: Brennan Blain
 *   @date: August 9, 2023
 *  @brief: Bug base class
 */

#ifndef BUG_H
#define BUG_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const size_t GRID_SIZE = 20;
class Bug{
public:

/**
     * @brief Construct a new bug object
     *
     */
    Bug(){};

/**
 * getBeenMoved - returns the private variable beenMoved 
 */
    bool getBeenMoved() const {return beenMoved;}

/**
 * getRow - returns the private variable row 
 */
    size_t getRow() const{return row;}

/**
 * getCol - returns the private variable col 
 */
    size_t getCol() const{return col;}

/**
 * getSteps - returns the private variable steps 
 */
    size_t getSteps() const{return steps;};

/**
 * getSymbol - returns the private variable symbol 
 */
    char getSymbol() const{return symbol;}

/**
 * getSymbol - returns the private variable symbol 
 */
    char getSymbol(){return symbol;}

/**
 * setBeenMoved - sets the private variable beenMoved to bool given 
 * @param bool t_f  - takes bool to set beenMoved to
 */
    void setBeenMoved(bool t_f) {beenMoved = t_f;}

/**
 * setRow - sets the private variable Row to value given 
 * @param size_t r  - takes value to set Row to
 */
    void setRow(size_t r){row = r;}

/**
 * setCol - sets the private variable Col to value given 
 * @param  size_t c - takes value to set col to
 */
    void setCol(size_t c){col = c;}

/**
 * setSteps - sets the private variable steps to value given 
 * @param  size_t s - takes value to set step count to
 */
    void setSteps(size_t s){steps = s;}

/**
 * setSymbol - sets the private variable symbol to value given
 * @param char s  - takes char to set symbol to 
 */
    void setSymbol(char s){symbol = s;}

/**
 * move - moves bug either up,down,left or right if loc avaible to be moved to for specific bug type, also deals with starving for wasps
 * @param  Bug* grid[][GRID_SIZE] - takes the bug grid and edits it to resemble moves made
 */
    virtual void move(Bug* grid[][GRID_SIZE]){};

/**
 * breed - called when a specific bug reaches sufficent time steps, creates a new bug in an adjacent location if there are any open
 * @param  Bug* grid[][GRID_SIZE] - takes the bug grid and edits it to resemble moves made
 */
    virtual void breed(Bug* grid[][GRID_SIZE]) {};


    virtual ~Bug(){};

private:
    bool beenMoved = false;
    size_t steps;
    size_t row; //row location
    size_t col; //col location
    char symbol; //character to represent a bug
};


#endif