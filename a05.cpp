/******************************************************************************
# Author:           Kate Stingle
# Assignment:       Assignment 5 (CS 161B)
# Date:             February 19th, 2025
# Description:      This program reads from salaries.txt and prints the job titles,
#					residencies, usd salaries and remote ratios for each individual.
# Input:            - ifstream inFile for salaries.txt
#                   Read to in loadData():
#                     - char[][] jobTitles : job titles for each individual
#                     - char[][] residencies : residencies for each individual
#                     - int[] usdSalaries : salaries for each individual
#                     - int[] remoteRatios : remote ratios for each individual
#                  *** NOT READ TO but worth noting:** 
#                     - int count : the number of individuals/data entries accumulated 
						while loading to data lists. This makes it so we don’t need 
						terminator values for the lists
# Output:           - welcome and exit messages
#                   Error messages:
#                   - const char INPUT_FAIL_MSG[] : if .fail() while loading to lists
#                   - const char OPEN_FILE_FAIL[] : printed if openFile() returns false
#                   In printLists():
#                     - char[][] jobTitles : job titles for each individual
#                     - char[][] residencies : residencies for each individual
#                     - int[] usdSalaries : salaries for each individual
#                     - int[] remoteRatios : remote ratios for each individual
#                   In findHighestPay() Data Analysis:
#                     - char highestPayJob[] : job title of the individual with the highest pay
#                     - int highestPay : the highest paid individual in the data set's salary
#                   In calcAvgRemoteRatio():
#                     - double avgRemoteRatio : used in calcAvgRemoteRatio() to accumulate and 
						calc the % of CS Jobs working remote 
# Sources:          Assignment 5 Specifications, "salaries.csv" for salaries.txt
#******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

// CONSTANTS
const int MAX_CHAR = 51;
const int MAX_ENTRIES = 30;
const char SEPARATOR = ';'; // the character that separates each data value in the file
const char INPUT_FAIL_MSG[] = "Error!!Problem Loading Data.Program terminating!!";
const char OPEN_FILE_FAIL[] = "Error!!Problem Opening Input File.Program terminating!!";
const char NO_DATA_MSG[] = "No Data in File to work with!!Program terminating!!";
const char WELCOME[] = "Welcome to my File input / output program.\nThis program will read item job titles, residency, salary and %remote from a file and calculate / output the highest paid individual and their job title, and the percent of jobs worked remote.";
const char THANKU[] = "Thank you";

// FUNCTION PROTOTYPES
bool openFile(ifstream& inFile); // attempt to open file, return false if fail
int loadData(ifstream& inFile, char jobTitles[][MAX_CHAR], int usdSalaries[], int remoteRatios[], char residencies[][3]); // returns the count after calculating, returns -1 if error
void printData(char jobTitles[][MAX_CHAR], int usdSalaries[], int remoteRatios[], char residencies[][3], int count); // printsall lsitds in eligible format
void findHighestPay(char jobTitles[][MAX_CHAR], int salaries[], int count); // finds the name and salary for the highest paid individual in the dataset
void calcAvgRemoteRatio(int remoteRatios[], int count); // cal and print avg remote ratio of all the jobs in the data set

// MAIN
int main() {
    // declare input file stream object (for salaries.txt)
    ifstream inFile;
    // declare lists to fill and the count(TBD)
    int count;
    char jobTitles[MAX_ENTRIES][MAX_CHAR];
    char residencies[MAX_ENTRIES][3];
    int salaries[MAX_ENTRIES];
    int remoteRatios[MAX_ENTRIES];
    // begin output
    cout << WELCOME << endl;// always print welcome msg
    if(!openFile(inFile)) { // attempt to open file, if fail terminate
        cout << OPEN_FILE_FAIL << endl;
        return 1; // return 1 on error occurrence
    } 
    // file is now succesfully open, lets load the data
    count = loadData(inFile, jobTitles, salaries, remoteRatios, residencies); // -1 if fail
    if (count == -1) { // failure has occurred while loading from file to arrays
        cout << INPUT_FAIL_MSG << endl;
        return 1; // return 1 on error occurrence
    }
    else if (count == 0) { // no data in file to work with, terminate
        cout << NO_DATA_MSG << endl;
        return 0; // terminate because no analysis can be made
    }
    printData(jobTitles, salaries, remoteRatios, residencies, count); // prints data from lists
    findHighestPay(jobTitles, salaries, count); // search and print individual w/ highest pay & job
    calcAvgRemoteRatio(remoteRatios, count); // prints avg of ratios = Σ(remote ratios)/count 
    cout << THANKU << endl; // always print exit msg when error not occurred
	return 0;
}

// FUNCTION DEFINITIONS

// attempts to open the file “salaries.txt”
// returns true if open is successful, false if not
bool openFile(ifstream& inFile) {
    inFile.open("salaries.txt");
    if(!inFile) {
		cout << OPEN_FILE_FAIL << endl;
        return false; // failed to open
    }
    return true; // open successful
}

// attempts to load all of the needed data into their respective lists, ignoring the first line 
// loads the following lists: jobTitles, salaries, remoteRatios, and residencies
// if .fail() after any input, returns -1 to count in main. This input error will be dealt with there
// count contains the accumulated number of entries in the file inFile // if count >30, then the file exceeds the max number of entries, so return -1 to terminate analysis 
// if data load is successful & valid, loadData() returns count, which is the accumulated # of entries
int loadData(ifstream& inFile, char jobTitles[][MAX_CHAR], int usdSalaries[], int remoteRatios[], char residencies[][3]) {
    int count = 0; // count accumulation always starts at 0, returns 0 if no data in file
    inFile.ignore(1000, '\n'); // ignore first line

    while (!inFile.eof()) { // for each entry
        // get entry values
        inFile.ignore(100, SEPARATOR); // discard first item of line
        inFile.ignore(100, SEPARATOR); // discard second item of line
        inFile.ignore(100, SEPARATOR); // discard third item of line

        inFile.getline(jobTitles[count], MAX_CHAR, SEPARATOR); // get job title
        if (inFile.fail()) {
            return -1; // fail
        }

        inFile.ignore(100, SEPARATOR); // discard fourth item of line
        inFile.ignore(100, SEPARATOR); // discard fifth item of line

        inFile >> usdSalaries[count]; // get usd salary
        if (inFile.fail()) {
            return -1; // fail
        }

        inFile.ignore(100, SEPARATOR); // discard sixth item of line

        inFile.getline(residencies[count], 3, SEPARATOR); // get residency
        if (inFile.fail()) {
            return -1; // fail
        }

        inFile >> remoteRatios[count]; // get remote ratio
        if (inFile.fail()) {
            return -1; // fail
        }

        inFile.ignore(100, '\n'); // reached end of entry
        count++;

        if (count > MAX_ENTRIES) { // if too many data points, do not analyze data
            return -1;
        }
    }

    return count;
}

// formats all of the data from the lists in a readable format
void printData(char jobTitles[][MAX_CHAR], int usdSalaries[], int remoteRatios[], char residencies[][3], int count) {
    // Print the header
    cout << left << setw(30) << "Job Titles" << setw(10) << "Residency" << setw(15) << "Salary (USD)" << setw(10) << "% Remote" << endl;
    cout << setfill('_') << setw(65) << "_" << setfill(' ') << endl; // Separator line

    // Print the data rows
    for (int i = 0; i < count; i++) {
        cout << left << setw(30) << jobTitles[i] << setw(10) << residencies[i] << "$ " << setw(13) << usdSalaries[i]<< setw(10) << remoteRatios[i] << "%" << endl;
    }
}

// finds the job title and salary of highest paid individual in the data set 
// outputs that job title and salary 
// finds the job title and salary of highest paid individual in the data set
// outputs that job title and salary
void findHighestPay(char jobTitles[][MAX_CHAR], int salaries[], int count) {
    int highestPay = salaries[0]; // always start at first in list to compare values
    char highestPayJob[MAX_CHAR];
    strcpy_s(highestPayJob, jobTitles[0]);

    for (int i = 1; i < count; i++) { // start from 1 since 0 is already considered
        if (salaries[i] > highestPay) {
            highestPay = salaries[i];
            strcpy_s(highestPayJob, jobTitles[i]);
        }
    }

    cout << "The individual with the highest pay is a " << highestPayJob << " with an annual salary $" << highestPay << " USD." << endl;
}

// summative analysis: 
// calculates and prints the avg % remote of all of the jobs in the dataset
// done by accumulating all of the remote Ratios and dividing by count(number of entries)
void calcAvgRemoteRatio(int remoteRatios[], int count) {
    double avgRemoteRatio = 0;

    for (int i = 0; i < count; i++) {
        avgRemoteRatio += remoteRatios[i];
    }

    avgRemoteRatio /= count;

    cout << "On average, these CS Jobs are " << avgRemoteRatio << "% Remote." << endl;
}
