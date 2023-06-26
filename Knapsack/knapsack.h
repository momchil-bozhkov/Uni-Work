#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <iostream>                                                 // This header file is protected from accidental multiple preprocessor 
#include <fstream>                                                  // inclusions. It is used to provide the needed functionality
#include <vector>                                                   // of the libraries it contains and a simple view of the declarations
#include <exception>                                                // and parameters for the 3 functions of the program

void HandleInput(int argc, char* argv[]);   // Takes as input from the user, the number of arguments (args) and the actual contents as a string of characters (argv) from the console

int Recursion(int bagCapacity, std::vector<int>& weights, std::vector<int>& values, std::vector<bool>& chosenItems, int index = 0);   // Takes as input all the data of the input files, already formatted from the input handler and ready for use

void HandleOutput(int bagCapacity, std::vector<int>& weights, std::vector<int>& values, std::vector<bool>& chosenItems, int totalValue);   // Takes as input the fully reworked data and uses it to provide formatted output

#endif