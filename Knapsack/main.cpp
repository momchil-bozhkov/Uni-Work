#include "knapsack.h"

int main(int argc, char* argv[]) {

    try {                                                            // Main is kept clean and simple by containing only
        HandleInput(argc, argv);                                     // the error handler which has combined functionality  
    }                                                                // for transferring towards knapsack.cpp and continuing
    catch(const std::exception& excpt)                               // instantiation of the program with correctly provided
    {                                                                // input or terminating execution
        std::cout << excpt.what() << std::endl;
        return 1;
    }

    return 0;
}