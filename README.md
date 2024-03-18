# Predator-Prey Simulation Game (Ants vs Doodlebugs)

This is a simple simulation game implemented in C++ where the prey are represented by ants ('o') and the predators by doodlebugs ('X'). The critters live in a 20x20 grid of cells where only one critter may occupy a cell at a time, and they are not allowed to move off the edges of the world. Time is simulated in discrete time steps, and each critter performs actions during each time step.

## Critters' Actions
### Ants:

Move: At each time step, a random move is generated: up, down, right, or left. If the neighboring cell in the selected direction is occupied or it would move off the grid, the ant stays in the current cell.

Breed: If an ant survives three time steps, it breeds. This is simulated by creating a new ant in an adjacent empty cell (up, down, right, or left). If no empty cell is available, breeding occurs when an empty cell becomes available in subsequent time steps.

### Doodlebugs:

Move: At each time step, if there is an adjacent ant, the doodlebug moves to the cell containing that ant. If no ant is available to eat in an adjacent cell, the doodlebug moves randomly like an ant.

Breed: If a doodlebug survives for eight time steps, it breeds by creating a new doodlebug in an adjacent empty cell (up, down, right, or left).
Starve: If a doodlebug has not eaten an ant within the last three time steps, it starves and dies.

## Simulation Flow
Doodlebugs move first, followed by ants.
Doodlebugs and ants breed at the same time.
At the end of each time step, some doodlebugs may starve and die.

## Game Initialization
The world is initialized with 5 doodlebugs and 100 ants.
The user must press enter to initiate a time step.
Representation of Grid State
Ant: 'o'
Doodlebug: 'X'
Empty cell: '.'

## Compile the C++ program.
Execute the compiled program.
Press enter to initiate each time step.
Observe the grid state printed after each time step to see the movement and actions of ants and doodlebugs.
Enjoy simulating the interactions between ants and doodlebugs in this predator-prey world!
