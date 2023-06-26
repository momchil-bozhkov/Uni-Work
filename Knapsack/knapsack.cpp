#include "knapsack.h"

void HandleInput(int argc, char* argv[]) {
    
    if (argc < 2) {
        throw std::runtime_error("No input filename given");
    }

    // Datastructures used for file input handling (user-provided console string, input file stream reader and fileName variable for storage)
    std::vector<std::string> userInput;
    std::ifstream inFS;
    std::string fileName;

    for (int i = 0; i < argc; i++) {
        userInput.push_back(argv[i]);           
    }

    fileName = userInput.back();
    inFS.open(fileName);

    if (!inFS.is_open()) {                                              // Checking for existing and correctly opened
        throw std::runtime_error("Could not open file " + fileName);    // file, if no file with such name is found
    }                                                                   // exception is thrown and handled

    // Datastructures used for storing file contents with subsequent data needed for problem solution
    int bagCapacity = 0;
    std::vector<int> weights;
    std::vector<int> values;

    inFS >> bagCapacity;

    while (!inFS.eof() && inFS.good()) {
        int itemWeight;
        int itemValue;

        inFS >> itemWeight;                                             // While there are no errors in the stream, reading through the file, 
        inFS >> itemValue;                                              // continuously distribute and populate vectors with data

        if (!inFS.fail()) {
            weights.push_back(itemWeight);                              // Error checking for correct
            values.push_back(itemValue);                                // data type inputs in file
        }
    }
    
    // Close file and filestream
    inFS.close();

    // Vector used for keeping track of stolen items
    std::vector<bool> chosenItems(weights.size());

    // Initiate recursion and transfer output for formatting
    HandleOutput(bagCapacity, weights, values, chosenItems, Recursion(bagCapacity, weights, values, chosenItems));
}

//----------------------------------------------------------------------------------------------------------------------------//

int Recursion(int bagCapacity, std::vector<int>& weights, std::vector<int>& values, std::vector<bool>& chosenItems, int index) {    // index paramater is used for vector access and keeping track of recursion cycle

    if (bagCapacity <= 0 || index >= weights.size()) {     // Both base cases when the bag is full
        return 0;                                          // and when there are no more items on the list
    }

    // Variable for comparison when an item is chosen to be taken
    int includeItem = 0;

    std::vector<bool> copyV = chosenItems;      // Copy of the vector, used for tracking the stolen items, which will be updated when an item is chosen to be stolen

    if (weights.at(index) <= bagCapacity) {
        
        copyV.at(index) = true;
        includeItem = values.at(index) + Recursion(bagCapacity - weights.at(index), weights, values, copyV, index + 1);
    }

    // Variable for comparison when item is chosen to be skipped
    int skipItem = Recursion(bagCapacity, weights, values, chosenItems, index + 1);

    if (includeItem > skipItem) {
        chosenItems = copyV;            // Comparing final values with item
        return includeItem;             // included or not and returning the
    } else {                            // higher option as well as providing 
        return skipItem;                // the correct tracking vector
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

void HandleOutput(int bagCapacity, std::vector<int>& weights, std::vector<int>& values, std::vector<bool>& chosenItems, int totalValue) {

    // Variable used for actual weight of stolen goods
    int itemsCapacity = 0;

    for (int i = 0; i < chosenItems.size(); i++) {
        if (chosenItems.at(i) == true) {
            itemsCapacity += weights.at(i);             // Calculating actual weight of stolen goods 
        }
    }

    std::cout << "With a capacity of " << bagCapacity << " kg, the total value is " << totalValue << " Euro, leadig to a total weight of " << itemsCapacity << " kg" << std::endl;

    std::cout << "The following items are included: ";

    for (int j = 0; j < chosenItems.size(); j++) {
        
        if (chosenItems.at(j) == true) {
            std::cout << "[" << weights.at(j) << ", " << values.at(j) << "] ";
        }
    }

    std::cout << std::endl;
}