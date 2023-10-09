#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

struct wordStruct {
    string word;
    double value;
};

// Function to read 'sentiment.txt' and populate the sentiment word list
int readSentimentFile(vector<wordStruct>& wordList,vector<wordStruct>& posList,vector<wordStruct>& negList){

    ifstream sentimentFile("sentiment.txt");
    if (!sentimentFile.is_open()) {
        cerr << "Error: Could not open 'sentiment.txt'." << endl;
        return -1; // Return an error code
    }

    string line;
    while (getline(sentimentFile, line)) {
        stringstream ss(line);
        string word;
        double sentimentValue;

        // Tokenize the line (comma-separated values)
        getline(ss, word, ',');
        ss >> sentimentValue;

        // Create a wordStruct and add it to the wordList
        wordStruct w;
        w.word = word;
        w.value = sentimentValue;
        wordList.push_back(w);

        // Categorize words as positive or negative
        if (sentimentValue > 1.25) {
            posList.push_back(w);
        }
        else if (sentimentValue < -1.25) {
            negList.push_back(w);
        }
    }


sentimentFile.close();
return 0; 

}

// Function to process a review and calculate its sentiment
int processReview(string fileName, vector<wordStruct> wordList,vector<wordStruct> posList,vector<wordStruct> negList, ofstream& outputFile) {    
    ifstream reviewFile(fileName);
    if (!reviewFile.is_open()) {
        cerr << "Error: Could not open '" << fileName << "'." << endl;
        return -1; // Return an error code
    }

    string line;
    string formattedReview;
    double totalSentiment = 0.0;

    while (getline(reviewFile, line)) {
        // Append lines to form the complete review text
        formattedReview += line + ' ';

        
        stringstream ss(line);
        string word;

        while (ss >> word) {
            // Normalize the word (convert to lowercase and strip punctuation)
            for (char& c : word) {
                c = tolower(c); // Convert to lowercase
                if (!isalnum(c)) {
                    c = ' '; // Replace punctuation with space
                }
            }

            // Find the word in the wordList and get its sentiment value
            double sentimentValue = 0.0;
            for (const wordStruct& w : wordList) {
                if (word == w.word) {
                    sentimentValue = w.value;
                    break;
                }
            }

            // Add the sentiment value to the total sentiment
            totalSentiment += sentimentValue;
        }


        // Format the review to 80 characters or less per line 
        const int lineLength = 80;
        string formattedLine;
        for (char c : formattedReview) {
            formattedLine += c;
            if (formattedLine.size() >= lineLength && c == ' ') {
                outputFile << formattedLine << endl;
                formattedLine.clear();
            }
        }
        // Print the remaining part of the review
        if (!formattedLine.empty()) {
            outputFile << formattedLine << endl;
        }

        // Print the formatted review
        outputFile << "PROCESSING FILE: " << fileName << endl;
        outputFile << "FORMATTED REVIEW:" << endl;
        outputFile << formattedReview << endl;
        outputFile << "ORIGINAL SENTIMENT: " << fixed << setprecision(2) << totalSentiment << endl;
        outputFile << endl << endl << endl;

        reviewFile.close();
        return 0;
    }
}

    