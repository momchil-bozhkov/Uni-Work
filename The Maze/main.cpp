#include <exception>
#include "maze.h"

int main(int argc, char* argv[]) {

    try {
        if (argc < 2) { 
            throw std::runtime_error("no input file name give");
        }
        else {
            std::string fileName = argv[1];
            Maze Maze = MazeLoader::LoadMazeFromFile(fileName);
            Maze.ExecuteMoves();
        }
    }
    catch(const std::exception& excpt) {
        std::cerr << "an error occured: " << excpt.what() << std::endl;
        return 1;
    }

    return 0;
}