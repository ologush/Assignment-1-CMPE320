#include <iostream>
#include <fstream>

#include <sstream>
#include <stdexcept>
#include <algorithm> //std::sort



#include "insultgenerator_20125579.h"

using namespace std;

InsultGenerator::InsultGenerator(){};

FileException::FileException(const string& message) : message(message) {};
string& FileException::what() { return message; }

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message) {}
string& NumInsultsOutOfBounds::what() { return message; }


//Loads all the source phrases from the InsultsSource.txt file into three column vectors. 
// If the file cannot be read, the method should throw an exception.
vector<string> InsultGenerator::initialize(){ 
string line;
ifstream fileIn("InsultsSource.txt");
if(fileIn.fail())
{
throw FileException("File cannot be read.");
}
while(!fileIn.eof())
{
while(getline(fileIn, line)) {
string parse;

stringstream lineToParse(line);
getline(lineToParse, parse, '\t');
a.push_back(parse);
getline(lineToParse, parse, '\t');
b.push_back(parse);
getline(lineToParse, parse);
b.push_back(parse);


}
} 
fileIn.close();
}

//talkToMe function throws one random insult.
//Generates random numbers for corresponding word insults.
string InsultGenerator::talkToMe() {
int i,j,k;
i = rand() % 50;
j = rand() % 50;
k = rand() % 50;
string output = "Thou " + a[i] + " " + b[j] + " " + c[k] + "!";
return output;
}

vector<string> InsultGenerator::generate(const int i)
{

hash<string> hasher;
vector<long> hashes;
if(i < 1 || i > 10000)
{
throw NumInsultsOutOfBounds("Error!");
}
vector<string> ninsults;
while(i > ninsults.size())
{
string output(talkToMe());
long hash(hasher(output));
while(hashExists(hash, hashes)) {
output = talkToMe();
hash = hasher(output);
}
ninsults.push_back(output);
hashes.push_back(hash);
}


sort(ninsults.begin(), ninsults.end());
return ninsults;
}

int InsultGenerator::hashExists(long hashValue, vector<long> hashes) {
for(int i = 0; i < hashes.size(); i++) {
if(hashes[i] == hashValue) {
return 1;
}
}
return 0;
}

//Creates an output file for generated insults in alphabetical order.
// generateAndSave() generates the requested number of unique insults and saves them to the filename
// supplied. If the file cannot be written, the method should throw an exception. Note that the
// insults in the file should be in alphabetical order!
// Check the number to generate limits first:
int InsultGenerator::generateAndSave(const string fileName, const int numberToGenerate){
vector<string> generatedInsults = generate(numberToGenerate);

ofstream outFile("GeneratedInsults.txt");


if(outFile.fail())
{
throw FileException("File cannot be written.");
}

for(int i = 0; i < generatedInsults.size(); i++) {
outFile << generatedInsults.at(i) << endl;
}

outFile.close();
return 0;

}

// Test ability to generate the maximum number of insults and how long it takes.
