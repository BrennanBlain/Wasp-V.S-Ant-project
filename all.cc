#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const size_t NUM_WASPS = 5;
const size_t NUM_ANTS = 100;
const size_t GRID_SIZE = 20;
class Bug{
public:
    Bug(){};
    bool getBeenMoved() const {return beenMoved;}
    size_t getRow() const{return row;}
    size_t getCol() const{return col;}
    size_t getSteps() const{return steps;};
    char getSymbol() const{return symbol;}

    void setBeenMoved(bool t_f) {beenMoved = t_f;}
    void setRow(size_t r){row = r;}
    void setCol(size_t c){col = c;}
    void setSteps(size_t s){steps = s;}
    void setSymbol(char s){symbol = s;}
    char getSymbol(){return symbol;}
    virtual void move(Bug* grid[][GRID_SIZE]){};
    virtual void breed(Bug* grid[][GRID_SIZE]) {};
    virtual ~Bug(){};
private:
    bool beenMoved = false;
    size_t steps;
    size_t row; //row location
    size_t col; //col location
    char symbol; //character to represent a bug
};

class Ant : public Bug {
   public:
    Ant() : Bug() { setSymbol(';');};
    Ant(size_t newR, size_t newC): Bug(){setSteps(0);};
    void move(Bug* grid[][GRID_SIZE]);
    void breed(Bug* grid[][GRID_SIZE]);
};

class Wasp : public Bug {
   public:
    Wasp() : Bug(){setSymbol('Q');};
    Wasp(size_t newR, size_t newC) : Bug(){ starve = 0; setSteps(0);};
    void move(Bug* grid[][GRID_SIZE]);
    void breed(Bug* grid[][GRID_SIZE]);
   
   private:
    size_t starve; 
};

void initializeGrid(Bug* grid[][GRID_SIZE]);
void displayGrid(Bug* grid[][GRID_SIZE]);
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

void Ant :: move(Bug* grid[][GRID_SIZE])
{
    int newRow = getRow();
    int newCol = getCol();

    // Generate a random direction (0: up, 1: down, 2: left, 3: right)
    int direction = rand() % 4;

    switch (direction) {
        case 0: // Up
            newRow = getRow() - 1;
            break;
        case 1: // Down
            newRow = getRow() + 1;
            break;
        case 2: // Left
            newCol = getCol() - 1;
            break;
        case 3: // Right
            newCol = getCol() + 1;
            break;
    }

    // Check if the new position is valid and not occupied
    if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && grid[newRow][newCol] == nullptr) {
        // Update the bug's position
        grid[getRow()][getCol()] = nullptr;
        setRow(newRow);
        setCol(newCol);
        grid[newRow][newCol] = this;
    }
    
}

void Ant :: breed(Bug* grid[][GRID_SIZE])
{
    if (getSteps() >= 3) {
        int newRow, newCol;
        setSteps(0);

        // Check each adjacent location for breeding
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) {
                    continue; // Skip the current location
                }

                newRow = getRow() + i;
                newCol = getCol() + j;

                if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && grid[newRow][newCol] == nullptr) {
                    Ant* newAnt = new Ant();
                    newAnt->setRow(newRow);
                    newAnt->setCol(newCol);
                    newAnt->setSteps(0);
                    grid[newRow][newCol] = newAnt;
                    return;
                }
            }
        }
        
    }
}

void Wasp :: move(Bug* grid[][GRID_SIZE])
{
    int newRow = getRow();
    int newCol = getCol();
    int oldRow = getRow();
    int oldCol = getCol();

    int direction = rand() % 4;

    switch (direction) {
        case 0: // Up
            newRow = getRow() - 1;
            break;
        case 1: // Down
            newRow = getRow() + 1;
            break;
        case 2: // Left
            newCol = getCol() - 1;
            break;
        case 3: // Right
            newCol = getCol() + 1;
            break;
    }
    if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE) 
    {
        
        if (grid[newRow][newCol] == nullptr || grid[newRow][newCol]->getSymbol() == ';') 
        {
            //bool gonna_starve = false;
            if(grid[newRow][newCol] == nullptr)
            {
                //gonna_starve = true;
                starve++;

            }
            // if (gonna_starve)
            // {
            //     starve++;
            // }
            else
            {
                starve = 0;
            }

            grid[getRow()][getCol()] = nullptr;
            setRow(newRow);
            setCol(newCol);
            grid[newRow][newCol] = this;
        }
        else
        {
            starve++;
        }
        
    } 
    else 
    {
        // Increment starve counter if the new position is invalid
        starve++;
    }

    // Handle starvation conditions
    if (starve >= 3) {
        grid[getRow()][getCol()] = nullptr;
    } else if (starve >= 3 && (newRow < 0 || newRow >= GRID_SIZE || newCol < 0 || newCol >= GRID_SIZE)) {
        grid[oldRow][oldCol] = nullptr;
    }
}

void Wasp :: breed(Bug* grid[][GRID_SIZE])
{
    if (getSteps() >= 8) {
        int newRow, newCol;
        setSteps(0);

        // Check each adjacent location for breeding
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) {
                    continue; // Skip the current location
                }

                newRow = getRow() + i;
                newCol = getCol() + j;

                if (newRow >= 0 && newRow < GRID_SIZE && newCol >= 0 && newCol < GRID_SIZE && (grid[newRow][newCol] == nullptr || grid[newRow][newCol]->getSymbol() != 'Q')) {
                    Wasp* newWasp = new Wasp();
                    newWasp->setRow(newRow);
                    newWasp->setCol(newCol);
                    newWasp->setSteps(0);
                    grid[newRow][newCol] = newWasp;
                    return;
                }
            }
        }
        
    }
}

void initializeGrid(Bug* grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            grid[i][j] = nullptr;
        }
    }

    for (int antCount = 0; antCount < NUM_ANTS; ++antCount) {
        int x, y;

        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != nullptr);

        Ant* newAnt = new Ant();
        newAnt->setRow(x);
        newAnt->setCol(y);
        newAnt -> setSteps(0);
        grid[x][y] = newAnt;
    }

    for (int waspCount = 0; waspCount < NUM_WASPS; ++waspCount) {
        int x, y;

        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (grid[x][y] != nullptr);

        Wasp* newWasp = new Wasp();
        newWasp->setRow(x);
        newWasp->setCol(y);
        newWasp->setSteps(0);
        grid[x][y] = newWasp;
    }
}

void displayGrid(Bug* grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        cout << '|';
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr) {
                cout << grid[i][j]->getSymbol();
            } else {
                cout << ' '; // Print empty cell
            }
            cout << '|';
        }
        cout << endl;
    }
    
}

void timeStep(Bug* grid[][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            Bug* currentBug = grid[i][j];
            if (currentBug != nullptr && currentBug->getSymbol() == 'Q' && !currentBug->getBeenMoved()) {
                currentBug->move(grid);
                currentBug->setBeenMoved(true);
                currentBug->setSteps(currentBug->getSteps() + 1);
                if (currentBug->getSteps() >= 8)
                {
                    currentBug -> breed(grid);
                }
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            Bug* currentBug = grid[i][j];
            if (currentBug != nullptr && currentBug->getSymbol() == ';' && !currentBug->getBeenMoved()) {
                currentBug->move(grid);
                currentBug->setBeenMoved(true);
                currentBug->setSteps(currentBug->getSteps() + 1);
                if (currentBug->getSteps() >= 3)
                {
                    currentBug -> breed(grid);
                }
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            Bug* currentBug = grid[i][j];
            if (currentBug != nullptr) {
                currentBug->setBeenMoved(false);
            }
        }
    }
}