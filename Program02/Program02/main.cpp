#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;


#include "function.h"

int main() {
    vector<wordStruct> wordList, posList, negList;
    int returnVal = readSentimentFile(wordList, posList, negList);
    
    if (returnVal == -1) {
        cerr << "Error: Failed to read sentiment file." << endl;
        return 1; // Exit with an error code
    }
    ofstream outputFile("reviewsPart1.txt"); // Create an output file stream

    // Output positive word list (for testing)
    for (auto i : posList) {
        cout << i.word << " " << i.value << endl;
    }

    // Process review files
    for (int i = 1; i <= 8; i++) {
        string reviewFile = "review" + to_string(i) + ".txt";
        returnVal = processReview(reviewFile, wordList, posList, negList, outputFile);
        if (returnVal == -1) {
            cerr << "Error: Failed to process review file " << reviewFile << endl;
            return 1; 
        }
    }
    outputFile.close(); // Close the output file stream
    return 0; 
}