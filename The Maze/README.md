# The Maze

This program is a C++ implementation of a solver for the maze game. The maze game involves navigating
through a maze, represented by a grid of walls and paths, from a starting point to an exit point. The goal
is to execute a sequence of moves to reach the exit while staying within the valid paths and avoiding the
walls.

The program expects an input file as a command-line parameter. This file should contain the description of
the maze, including its dimensions, layout, starting position, exit position, and a list of player moves.
The program reads this input file, initializes the maze, executes the player moves, and determines whether
the player reached the exit or not.

The program will print the maze to the screen before and after executing each player move. After executing
the moves, it will provide one of the following messages:

    "The player did not reach the exit."
    "The player reached the exit!"

In case of errors, the program will print an error message and stop. All error messages begin with the
string, "An error occurred:", followed by a specific error message explaining the issue.

Example input files, such as "maze1", "maze2", etc., are provided for testing the program.