/******************************************************************************
# Author: Kate Stingle
# Lab:    Discussion 5
# Date:   2/16/2025
# Description: The purpose of this program is to read from a file of STEM majors and their statistics,
			   calculate the percent women and men for each major, and writes the results
			   to an output file. Additionally, it will calculate the overall probability that 
			   a student is female given that they are a STEM major(so percent women of whole file)
#
# Input:    - ifstream inFile - ifStream object that reads from a file of the name that the user enters
#           - string fileName - name of file to be read from, code was prewritten. terminate if file does not open
#           In ratioCalc():
#			  - char major[MAX_CHAR] - name of major, read from inFile
#			  - int numMen - number of men in a particuar major
#			  - int numPpl - total number of people in a particular major
#          In wiStemCalc():
#			  - int numPpl - total number of people in a particular major
#			  - int numWomen - number of women in a particular major
# Output:	- outFile - ofstream object writing to a file named "stemout.txt"
#          In ratioCalc():
#			  - char major[MAX_CHAR] - name of major, read from inFile		
#			  - double percentMen - calculated percent men, also used to calc percent women (%women = 100- %men)
#          In wiStemCalc():
#			  - double totalPpl - total number of people in all majors, accumulated
#			  - double totalWomen - number of owmne in all majors, accumulated. 
#				                    used to calculate probability(totalWomen/totalPpl)
# Sources: Discussion 5 specifications
#******************************************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string> // only for file name input (pre-written code)
#include <cstring> // no more <string> past this module of CS161B, only char arrays (C-strings)
using namespace std;

// function prototypes
bool openFile(ifstream& inFile, string fileName); // opens file, return true if file opens, false if not
void ratioCalc(ifstream& inFile, ofstream& outFile); // calculates & writes percentages of women and men for each major to outFile
void wiStemCalc(ifstream& inFile, ofstream& outFile); // calculates the probability that a student is female given they are a stem major

// constants
int const MAX_CHAR = 100; // max number of characters in a major name

// main
int main() {
	//declare file streams
    ifstream inFile;
	ofstream outFile; 
    string fileName;

    cout << "Enter name of input file:";
    cin >> fileName;

	if (!openFile(inFile, fileName)) { // attempt to open inFile based on inputted file name
        cout << "file did not open. Program terminating!!!";
        return 0;
    }

	//open output file, terminate if it does not open
	outFile.open("stemout.txt"); // open otuput file
	if (!outFile.is_open()) { // if output file does not open
		cout << "output file did not open. Program terminating!!!";
		return 0;
	}

	ratioCalc(inFile, outFile); // write percent women and men for each major to outFile
	wiStemCalc(inFile, outFile); // write probability student is female given stem major to outFile

    inFile.close();
	outFile.close(); // close files
	return 0;
}

// function to open file
// returns true if file opens
// returns false if file does not open for any reason
// parameters: file stream variable by reference and fileName

bool openFile(ifstream& inFile, string fileName) {
    inFile.open(fileName);
    if (!inFile) {
        return false;
    }
    return true;
}


// READS total, number of women, number of men, and the name of each major from inFile, ignoring the first line
// CALCULATES the percent women and men for each major
// WRITES the name, percent women and percent men for each major to outFile, rounded to 2 decimal places
void ratioCalc(ifstream& inFile, ofstream& outFile) {
	inFile.ignore(1000, '\n'); // ignore first line
    // declare variables for info for each major
	// these variables change with each loop iteration, line by line, because each line is a different major
	char major[MAX_CHAR]; // specific major name, read from inFile
    int numMen; // number of men in that specific major, read from inFile
	int numPpl; // total number of people in that specific major, read from inFile
	double percentMen; // calculated percentage of men in that major, outputted to 2 dec pnts to outFile. Also used to calculate percent women
	/// READ each line of inFile, CALCULATE percent, and WRITE info to outFile
    while (!inFile.eof()) { // continue until all majros have been analyzed
		// READ info for each major
		inFile.ignore(10, ' '); // ignore the Major-Code and the space after it
		inFile >> major; // read major name
		inFile.ignore(100, ' '); // ignore the space after the major name,
		inFile.ignore(100, ' '); // and ignore the major category, including the space after it
		inFile >> numPpl; // read number of people in that major
		inFile.ignore(); // ignore the space after the number of people
		inFile >> numMen; // read number of men for that major
		inFile.ignore(1000, '\n'); // ignore the rest of the line
		// CALCULATE percent men
		percentMen = (static_cast<double>(numMen) / numPpl) * 100; // calculate percent men in that major
		// WRITE info to outFile
		outFile << major << " "; // name of major
		outFile << fixed << setprecision(2); // set precision to 2 decimal places
		outFile << "Men: " << percentMen << "% "; // percent men
		outFile << "Women: " << 100 - percentMen << "%" << endl; // calc and write percent women, new line
    }
	// now outFile contains major name, percent women and men for each major
}

// READS total and num women from inFile for each major
// CALCULATES total people in all stem majors and total num women in all stem majors,
// THEN CALCULATES the probability that a student is female given that they are a stem major
// WRITES the probability to outFile rounded to 2 decimal places
void wiStemCalc(ifstream& inFile, ofstream& outFile) {
	inFile.clear(); // clear eof flag because of previous ratioCalc() function
	inFile.seekg(0, ios::beg); // go back to beginning of file
	inFile.ignore(1000, '\n'); // ignore first line
	// declare variables for info for each major
	// these variables change with each loop iteration, line by line, because each line is a different major
	int numPpl; // total number of people in that major, read from inFile
	int numWomen; // number of women in that major, read from inFile
	double totalPpl = 0; // total number of people in all majors, accumulated
	double totalWomen = 0; // number of women in all majors, accumulated
	// READ each line of inFile
	while (!inFile.eof()){
		// READ info for each major
		inFile.ignore(10, ' '); // ignore the Major-Code and the space after it
		inFile.ignore(100, ' '); // ignore major name
		inFile.ignore(100, ' '); // ignore major category
		inFile >> numPpl; // read number of people in that major
		inFile.ignore(); // ignore the space after the number of people
		inFile.ignore(100, ' '); // ignore num men
		inFile >> numWomen; // read number of women in that major
		inFile.ignore(1000, '\n'); // ignore the rest of the line
		// CALCULATE total people and total
		totalPpl += numPpl; // accumulate total people	
		totalWomen += numWomen; // accumulate total women
	}
	// WRITE probability to outFile
	outFile << fixed << setprecision(2); // set precision to 2 decimal places
	outFile << "Probability that a student is female given that they are a STEM major: ";
	outFile << (totalWomen / totalPpl) * 100 << "%" << endl; // calculate and write probability to outFile
}