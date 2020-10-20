/* A demo of simple text file I/O */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function prototypes.
// Allows you to implement functions in any order since they have already been identified, and
// provides a concise list of the functions in this program at the top of the source code.
vector<string> readFile(const string& filename);
int writeReverse(const string& filename, const vector<string>& contents);
int main();

// Reads the contents of the text file and returns a vector of
// each line in the file.
vector<string> readFile(const string& filename) {

	int wordCount(0);
	string line, word;

	ifstream fileIn(filename);
	vector<string> contents;
	if (fileIn.fail()) {
		cerr << "Unable to open file: " << filename << endl;
		return contents;
	}
	while (getline(fileIn, line))
		contents.push_back(line);
	cout << contents.size() << " lines read." << endl;
	fileIn.close();

	// Demonstrating another way to read the file.
	ifstream fileInAgain(filename);
	while (fileInAgain >> word) {
		wordCount++;
	}
	fileInAgain.close();
	cout << wordCount << " words in file." << endl;

	return contents;

} // end readFile

// Writes the file in reverse order, returning the number of lines
// written.
int writeReverse(const string& filename, const vector<string>& contents) {

	int lineCount(0);
	ofstream fileOut(filename);
	int lines(contents.size());

	if (fileOut.fail()) {
		cerr << "Unable to open file: " << filename << endl;
		return lineCount;
	}
	while (lineCount < lines) {
		fileOut << contents.at(lines - lineCount - 1) << endl;
		lineCount++;
	}
	fileOut.close();

	return lineCount;

} // end writeReverse

int main () {

	string filenameIn("Test.txt");
	string filenameOut("TestOut.txt");

	vector<string> contents = readFile(filenameIn);

	int result = writeReverse(filenameOut, contents);
	if (result)
		cout << result << " lines written." << endl;
	else
		cerr << "Unable to write to: " << filenameOut << endl;

	return 0;

} // end main


