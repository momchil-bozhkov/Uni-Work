#include "maze.h"

Coordinate::Coordinate() {
    xCoordinate = 0;
    yCoordinate = 0;
}

Coordinate::Coordinate(int x, int y) {
    xCoordinate = x;
    yCoordinate = y;
}

Maze::Maze() {
}

void Maze::InitialiseLayout(int height, int width, std::ifstream& mazeData) {
    layout.resize((height * width), std::vector<char>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            char layoutElement;
            
            if (mazeData >> layoutElement) {
                if (layoutElement != 'l' && layoutElement != '.') {
                    throw std::runtime_error("could not read maze layout");
                } else {
                    layout.at(i).at(j) = layoutElement;
                }
            }
        }
    }
}

void Maze::PrintMaze() {
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout.at(i).size(); j++) {
            std::cout << layout.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }
}

Maze MazeLoader::LoadMazeFromFile(const std::string& fileName) {
    
    std::ifstream fileStream(fileName);

    if (!fileStream) {
        throw std::runtime_error("could not open input file " + fileName);
    }

    Maze Maze;

    int height = 0;
    int width = 0;

    fileStream >> height >> width;

    if (fileStream.fail()) {
        throw std::runtime_error("could nnot read height and width of the maze");
    } else {
        Maze.InitialiseLayout(height, width, fileStream);
    }

    fileStream.close();
    
    return Maze;
}
