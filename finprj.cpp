/******************************************************************************
# Author:           Kate Stingle
# Assignment:       Final Project (CS 161B)
# Date:             March 9th, 2025
# Description:      The purpose of this program is to allow the user to interact 
					with space mission data that is read from a “mission_launches.txt’ 
					file, and written to after. The program will always print an output 
					message, and the first real thing it tries to do is open the inFile 
					with is assigned to mission_launches.txt. It will print an error 
					message and print immediately if it fails to open that file. If not, 
					the program proceeds to call the function loadData(), which reads from 
					the text file to the arrays, and quits if there was an error that occurred. 
					If not error occurred, then all data has been successfully copied to the 
					SpaceMission missions[] array. Next, the program will enter the menu loop 
					where the majority of the program is run. This is a menu driven program, 
					so the user will be able to choose to:
						(P)RINT the data
						(R)EMOVE a mission from the data
						(A)DD a mission to the data
						(C)ALCULATE avg cost of the missions
						(Q)UIT
# Sources:          
- Final Project Specifications
- https://www.kaggle.com/datasets/sefercanapaydn/mission-launches for mission_launches.txt
#******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "MissionsData.h"
using namespace std;

// constants
const char WELCOME[] = "Welcome!\nThis program allows the user to interact with and edit a data file about space missions.\n";
const char MENU[] = "Pick an option from below:\n\n\t(P)rint the data\n\t(R)emove a mission from the data\n\t(A)dd a mission to the data\n\t(C)alculate the average cost of the missions\n\t(Q)uit";
const char OPEN_ERROR[] = "Error opening file. Exiting program.";
const char NO_DATA[] = "No data was loaded. Exiting program.";
const char LOAD_ERROR[] = "Error loading data. Exiting program.";

// function prototypes for menu control
void exeOption(char command, SpaceMission missions[], int &count); // executes the user's command. Doesn't include 'Q' because while loop checks for that
void displayMenu(); // dislays the menu, called inside menu loop
void readOption(char& command); // reads the character option from the user, validates and converts it to capital letter

// MAIN
int main() {
	//declare variables
	ifstream inFile; // for reading from mission_launches.txt
	ofstream outFile; // for writing to mission_launches.txt
	SpaceMission missions[MAX]; // array of SpaceMission structs to read to/write from
	int count = 0; // number of missions inside of missions[]
	char choice; // user's choice from the menu, validated in readOption()

	// always output welcome message
	cout << WELCOME << endl;
	// attempt to open inFile, exit if fail to open
	if (!openInFile(inFile)) {
		cout << OPEN_ERROR << endl;
		return 0;
	}
	// attempt to load data to missions[], exit if fail to load
	count = loadData(inFile, missions); // returns -1 is fail to load data  
	if (count == -1) { // error loading data
		cout << LOAD_ERROR << endl;
		return 0;
	}
	else if (count == 0) { // no data in file
		cout << NO_DATA << endl;
		return 0;
	}
	else {
		cout << "Data loaded successfully." << endl << endl;
	}
	
	// proceed to menu loop
	displayMenu();
	readOption(choice);
	while (choice != 'Q') { // exits when user enters Q to quit
		exeOption(choice, missions, count);
		displayMenu();
		readOption(choice);
	}
	if (!openOutFile(outFile)) {
		cout << "Error opening file for writing. Data not written to \"" << FILE_NAME << "\"" << endl;
	}
	else{// write data to file
		writeData(outFile, missions, count);
	}
	cout << endl <<"Thank you for using my program!";
	return 0;
}

// FUNCTION DEFINITIONS

//called inside of menu loop
void displayMenu() {
	cout << MENU << endl;
}

// called inside of menu loop
// executed the user's command. Doesn't include 'Q' because while loop checks for that
void exeOption(char command, SpaceMission missions[], int& count) {
	if (command == 'P') {
		// print the data
		printData(missions, count);
	}
	else if (command == 'R') {
		// remove a mission from the data
		removeMission(missions, count);
	}
	else if (command == 'A') {
		// add a mission to the data
		addMission(missions, count);
	}
	else if (command == 'C') {
		calcAvgCost(missions, count);
		// calculate the average cost of the missions
	}
}

// called inside of menu loop
// reads the character option from the user, validates and converts it to capital letter
void readOption(char& command) {
	cin >> command;
	cin.ignore(100, '\n');
	command = toupper(command);
	while (command != 'P' && command != 'R' && command != 'A' && command != 'C' && command != 'Q') {
		cout << "Invalid Option!! Please enter a character for one of the options above" << endl;
		cin >> command;
		cin.ignore(100, '\n');
		command = toupper(command);
	}
}