#include "maze.h"

Maze::Maze() {};

Maze MazeLoader::LoadMazeFromFile(const std::string& fileName) {
    
    std::ifstream fileStream("test_files/" + fileName);

    if (!fileStream) {
        throw std::runtime_error("could not open input file " + fileName);
    }

    Maze Maze;

    int height = 0;
    int width = 0;

    fileStream >> height >> width;

    if (fileStream.fail()) {
        throw std::runtime_error("could not read height and width of the maze");
    } else {
        Maze.InitialiseMaze(height, width, fileStream);
    }

    fileStream.close();
    
    return Maze;
}

void Maze::InitialiseMaze(int height, int width, std::ifstream& mazeData) {
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

    int xCoord = 0;
    int yCoord = 0;

    if (mazeData >> xCoord >> yCoord) {
        exit = Coordinate(xCoord, yCoord);
        if (mazeData >> xCoord >> yCoord) {
            startPos = Coordinate(xCoord, yCoord);
        }
    } else {
        throw std::runtime_error("could not read coordinates");
    }

    if (!isValidPosition(exit) || (layout.at(exit.getX()).at(exit.getY()) == 'l')) {
        throw std::runtime_error("exit outside maze or off path");
    }

    if (!isValidPosition(startPos)) {
        throw std::runtime_error("starting possition outside maze or off path");
    }

    char playerMove;
    while (mazeData >> playerMove && !mazeData.eof()) {

        if (!mazeData || (playerMove != 'l' && playerMove != 'r' && playerMove != 'u' && playerMove != 'd')) {
            throw std::runtime_error("invalid move");
        } else {
            playerMoves.push_back(playerMove);
        }
    } 

    layout.at(startPos.getX()).at(startPos.getY()) = 'P';
    layout.at(exit.getX()).at(exit.getY()) = 'x';
    playerPosition = startPos;

    PrintMaze();
}

void Maze::ExecuteMoves() {

    for (int i = 0; i < playerMoves.size(); i++) {

        layout.at(playerPosition.getX()).at(playerPosition.getY()) = '.';

        std::string nextMove;

        switch (playerMoves.at(i)) {

            case 'l':
                nextMove = "left";
                playerPosition.setY(-1);
                break;

            case 'r':
                nextMove = "right";
                playerPosition.setY(1);
                break;

            case 'u':
                nextMove = "up";
                playerPosition.setX(-1);
                break;

            case 'd':
                nextMove = "down";
                playerPosition.setX(1);
                break;
        }

        std::cout << "Next move is : " << nextMove << '\n';

        if (isValidMove(playerPosition) && isValidPosition(playerPosition)) {
            layout.at(playerPosition.getX()).at(playerPosition.getY()) = 'P';
        } else {
            throw std::runtime_error("player outside maze or off path");
        }
        
        std::cout << '\n';
        PrintMaze();
    }

    if (playerPosition == exit) {
        std::cout << "The player reached the exit!" << std::endl;
    } else {
        std::cout << "The player did not reach the exit." << std::endl;
    }
}

void Maze::PrintMaze() {
    for (int i = 0; i < layout.size(); i++) {
        for (int j = 0; j < layout.at(i).size(); j++) {
            std::cout << layout.at(i).at(j);
        }
        std::cout << '\n';
    }
}

bool Maze::isValidPosition(Coordinate coord) {
    if ((coord.getX() < 0 || coord.getX() >= layout.size()) || (coord.getY() < 0 || coord.getY() >= layout.at(0).size())) {
        return false;
    } else { return true;}
}

bool Maze::isValidMove(Coordinate coord) {
    return (layout.at(coord.getX()).at(coord.getY()) != 'l');
}