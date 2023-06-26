#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "coordinate.h"

class Maze {

    public:
        Maze();
        void InitialiseLayout(int height, int width, std::ifstream& mazeData);
        void PrintMaze();

    private:
        Coordinate startPos;
        Coordinate exit;
        std::vector<std::vector<char>> layout;
};

class MazeLoader {

    public:
        static Maze LoadMazeFromFile(const std::string& fileName);
};

#endif