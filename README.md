
### Name: Brennan Blain

### Email: bb828119@ohio.edu

### Run with:./a.out
### Compile with:make

### Description: This is a game of survival between ants and wasps. In this simulation, ants and wasps live together on a grid. Each grid cell can only be occupied be one critter. Ants can survive on their own and can breed. Wasps can only survive if they eat ants. In this simulation, you are to create a two-dimension grid of 20x20. The simulation starts by creating 5 wasps and 100 ants. Only one bug occupies each cell. Bugs are not allowed to leave this world. They will either survive or die within this grid. We are going to simulate time by taking time-steps.
### The ant behaves as follows:
### • Move: Every time-step, it randomly tries to move to an adjacent cell (up, down, left, oright). If the cell is occupied or the ant moves off the grid, then it stays in the current cell. An ant must not move more than once in each time-step.
### • Breed: If an ant survives for three time-steps, the ant will spawn another ant. It will create a new ant in any of the adjacent cells if any are available. If none are available, then no breeding occurs. Once an offspring is produced, an ant cannot produce another ant until three more time-steps have elapsed.
### The wasp behaves as follows:
### • Move: Every time-step if there is an adjacent ant (randomly selected cell), the wasp will move to that cell and eat the ant. Otherwise, the wasp moves according to the same rules as the ant. A wasp cannot eat other wasps. A Wasp must not move more than once in each time-step.
### • Breed: if the wasp survives eight time-steps, it will spawn another wasp in any of the adjacent cells.
### • If a wasp has not eaten an ant within the last three time-steps, then at the end of the third time-step it will starve and die. The wasp should be removed from the grid of cells. During one turn, all the wasps should move before the ants. This involves going to every element of the grid and determine how the object inside the cell should move.

