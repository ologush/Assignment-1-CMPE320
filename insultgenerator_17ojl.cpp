#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "insultgenerator_17ojl.h"
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

void InsultGenerator::initialize() {
    readFile();
};

string InsultGenerator::talkToMe() {
    string insult;
    insult = getRandomInsult();
    return insult;
};

vector<string> InsultGenerator::generate(const int numberOfInsults) {

    hash<string> hasher;
    vector<string> generatedInsults;
    vector<long> hashes;

    

    if(numberOfInsults > UPPER_BOUND) {
        throw NumInsultsOutOfBounds("The number of insults you entered is too high");
    } 

    if(numberOfInsults < LOWER_BOUND) {
        throw NumInsultsOutOfBounds("The number of insults you entered is too low");
    }

    for(int i = 0; i < numberOfInsults; i++) {
        string newInsult = getRandomInsult();
        long hashValue = hasher(newInsult);
        while(hashExists(hashValue, hashes)) {
            newInsult = getRandomInsult();
            hashValue = hasher(newInsult);
        }

        generatedInsults.push_back(newInsult);
        hashes.push_back(hashValue);
    }

    sort(generatedInsults.begin(), generatedInsults.end());

    return generatedInsults;
}

int InsultGenerator::hashExists(const long hash, const vector<long> hashes) {
    for(int i = 0; i < hashes.size(); i++) {
        if(hashes[i] == hash) {
            return 1;
        }
    }
    return 0;
};


void InsultGenerator::generateAndSave(const string& fileName, const int numberOfInsults) {

    vector<string> generatedInsults = generate(numberOfInsults);
    writeFile(fileName, generatedInsults);
};

int InsultGenerator::writeFile(const string fileName, vector<string>& contents) {

    int lineCount(0);

    

    ofstream fileOut(fileName);
    int lines(contents.size());

    if(fileOut.fail()) {
        throw FileException("Unable to write to file");
    }
    while (lineCount < lines) {
        fileOut << contents.at(lineCount) << endl;
        lineCount++;
    }
    fileOut.close();

    return lineCount;
}

void InsultGenerator::readFile() {
    int wordCount(0);

    string line, word;
    
    ifstream fileIn(INPUT_FILE);
    if(fileIn.fail()) {
        throw FileException("Unable to read file");
    };

    int count = 0;

    while(!fileIn.eof()) {
        while(getline(fileIn, line, '\n')) {

            string parse;
            stringstream lineToParse(line);
            getline(lineToParse, parse, '\t');
            columns[0].push_back(parse);
            getline(lineToParse, parse, '\t');
            columns[1].push_back(parse);
            getline(lineToParse, parse, '\n');
            columns[2].push_back(parse);
        }
    }
    fileIn.close();
};

string InsultGenerator::getRandomInsult() {

    string finalInsult = "Thou ";

    for(int i = 0; i < 3; i++) {

        int rando = (rand() % ROWS);
        string word = columns[i][rando];
        
        finalInsult += word;
        if(i < 2) {
            finalInsult += " ";
        }
    }

    //Takes care of the \n character causing problems when adding the !
    finalInsult.pop_back(); 
    finalInsult += "!";
    
    
    return finalInsult;
};

FileException::FileException(const string& message) : message(message) {};
string& FileException::what() { return message; }

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message) {}
string& NumInsultsOutOfBounds::what() { return message; }