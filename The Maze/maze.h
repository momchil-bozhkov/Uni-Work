#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "coordinate.h"

class Maze {

    public:
        Maze();
        void InitialiseMaze(int height, int width, std::ifstream& mazeData);
        void PrintMaze();
        void ExecuteMoves();
        bool isValidPosition(Coordinate coord);
        bool isValidMove(Coordinate coord);

    private:
        Coordinate startPos;
        Coordinate exit;
        Coordinate playerPosition;
        std::vector<std::vector<char>> layout;
        std::vector<char> playerMoves;
};

class MazeLoader {

    public:
        static Maze LoadMazeFromFile(const std::string& fileName);
};

#endif