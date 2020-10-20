#pragma once

#include <string>
#include <vector>

using namespace std;

#define INPUT_FILE "InsultsSource.txt"
#define ROWS 50
#define UPPER_BOUND 10000
#define LOWER_BOUND 1

//Insult Generator class, responsible for generating and saving insults.
class InsultGenerator {
    public: 
        string talkToMe(); //Generates a signle insult that is returned by the function
        vector<string> generate(int numberOfInsults); //Generates a unique alphabetically sorted list of random insults and returns it
        void initialize(); //Initializes the class, reads the file in to store the Insults Source
        void generateAndSave(const string& fileName, int numberOfInsults); //Generate a unique alphabetically sorted list of random insults and saves it to a specified file
        
    private:
        void readFile(); //This is what reads the InsultsSource file, is called by initialize;
        string getRandomInsult(); //Generates a single random insult
        vector<string> columns[3];  //Stores all the insult sources read from the file
        int writeFile(string fileName, vector<string>& contents); //function responsible for writing to the file
        int hashExists(long hash, vector<long> hashes); //Function to check if the generated hash for an insult exists, used for ensuring generated insults are unique
};

//Exception class that is thrown when the number of insults asked to be generated is out of the specified bounds
class NumInsultsOutOfBounds {
    public:
        NumInsultsOutOfBounds(const string& message);
        string& what();
    private:
        string message;
};

//Exception class that is thrown when there is a problem reading or writing to the file
class FileException {
    public:
        FileException(const string& message);
        string& what();
    private:
        string message;
};
