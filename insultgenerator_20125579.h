#pragma once

#include <string>
#include <vector>

using namespace std;

class FileException {
    public:
        FileException(const string& message);
        string& what();
    private:
        string message;
};

class NumInsultsOutOfBounds{
    public:
        NumInsultsOutOfBounds(const string& message);
        string& what();

    private:
        string message;
};

class InsultGenerator {
    public:
        InsultGenerator();
        vector<string> initialize();
        string talkToMe(); 
        vector<string> generate(const int i);
        int generateAndSave(const string fileName, const int numberToGenerate);

    private:
        int hashExists(long hashValue, vector<long> hashes);
        string filename;
        vector<string> a, b, c;
};