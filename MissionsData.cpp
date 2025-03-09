#include <iostream>
#include "MissionsData.h"

// this file contains all of the functions used to manage a list of SpaceMissions missions[]
// these functions are executed in the main program, finprj.cpp upon user input


// function definitions

// attempts to open the file mission_launches.txt for inout
bool openInFile(ifstream& inFile) {
	inFile.open(FILE_NAME);
	if (!inFile.is_open()) {
		return false;
	}
	return true;
}

// attempts to open the file mission_launches.txt for ouput
bool openOutFile(ofstream& outFile) {
	outFile.open(FILE_NAME);
	if (!outFile.is_open()) {
		return false;
	}
	return true;
}

// function to load data from mission_launches.txt to the SpaceMission missions[] array
// assumes file is already open
// validates all inFile input and return -1 if error loading data
int loadData(ifstream& inFile, SpaceMission missions[]) {
	int count = 0;
	//ignore the first line of the file
	inFile.ignore(MAX_CHAR, '\n'); // ignore the first line of the file
	while (inFile.peek() != EOF) { // for each mission
		cout << count << "\t"; // debug
		inFile.getline(missions[count].organization, MAX_CHAR, ';'); // load organizaiton name
		cout << missions[count].organization << "\t"; // debug
		if (!inFile) {
			return -1; // error loading data
		}
		inFile.getline(missions[count].location, MAX_CHAR, ';'); // load location
		cout << missions[count].location << "\t"; // debug
		if (!inFile) {
			return -1; // error loading data
		}
		inFile.getline(missions[count].date, MAX_CHAR, ';'); // load date
		cout << missions[count].date << "\t"; // debug
		if (!inFile) {
			return -1; // error loading data
		}

		inFile >> missions[count].cost; // load cost
		cout << missions[count].cost << "\t"; // debug
		inFile.ignore(10,';'); // ignore the semicolon
		if (!inFile || missions[count].cost < 0) {
			return -1; // error loading data
		}

		inFile.getline(missions[count].status, 8, '\n'); // load status
		cout << missions[count].status  << endl; // debug
		if (strcmp(missions[count].status, "Success")!= 0 && strcmp(missions[count].status, "Failure")!= 0) { // error if status != 'Success' or 'Failure'
			return -1; // error loading data
		} // ignore the rest of line
		count++;
	}
	//close inFile
	inFile.close();
	return count;
}

// function to print the data in the missions[] array
// called when 'P' is entered in the menu
// called in exeOption()
void printData(SpaceMission missions[MAX], int const& count) {
	// Print header
	cout << endl << left << setw(15) << "Organization"
		<< setw(59) << "Location"
		<< setw(30) << "Date"
		<< setw(10) << "Cost($k)"
		<< "Status" << endl;
	cout << setfill('=') << setw(121) << "=" << setfill(' ') << endl;
	// Print each mission
	for (int i = 0; i < count; ++i) {
		cout << left << setw(15) << missions[i].organization
			<< setw(59) << missions[i].location
			<< setw(30) << missions[i].date
			<< setw(10) << fixed << setprecision(2) << missions[i].cost
			<< missions[i].status << endl;
		
	}
	cout << endl;
}

// prints the data in the missions[] array in a shortened format with indexes
void printShortenedData(SpaceMission missions[MAX], int const& count) {
	if (count == 0) { // no data in the dataset
		cout << "Sorry, your dataset if currently empty! You can add to your dataset by entering ‘A’ or ‘a’ for add on the main menu" << endl << endl;
	}
	else { // there is data in the datset to print
		// print header
		cout << endl << left << setw(6) << "index" << setw(15) << "Organization"
			<< setw(59) << "Location"
			<< setw(30) << "Date" << endl;
		cout << setfill('=') << setw(121) << "=" << setfill(' ') << endl;
		// Print each mission
		for (int i = 0; i < count; ++i) {
			cout << left << setw(6) << i << setw(15) << missions[i].organization
				<< setw(59) << missions[i].location
				<< setw(30) << missions[i].date << endl;
		}
	}
}

// adds a mission to the missions[] array, calls readSpaceMission() to validate input
void addMission(SpaceMission missions[], int& count) {
	if (count == MAX) { // if maximum
		cout << "Maximum # of missions has been reached! You can remove a mission by choosing 'R' on the main menu." << endl << endl;
	}
	else {
		missions[count] = readSpaceMission(); // read space mission info from user, returns the mission to append
		count++; // increment count
		cout << "Mission Entry has been added!" << endl << endl;
	}
}

// removes a mission from the missions[] array
void removeMission(SpaceMission missions[], int& count) {
	int index;
	if (count == 0) {
		cout << "No missions in your data set to remove!" << endl << endl;
	}
	else { // can remove mission
		printShortenedData(missions, count); // print the data with indexes
		cout << "Enter the number(on the left) of the mission to delete: ";
		cin >> index;
		while (!cin || index < 0 || index >= count) {
			cout << "Invalid Entry!! Please enter integer 0-" << count-1 << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> index;
		}
		cout << "Removing " << index << "..." << endl;
		for (int i = index; i < count - 1; ++i) {
			missions[i] = missions[i + 1]; // shift all elements to the left
		}
		count--; // decrement count
		cout << "Removal Complete!" << endl << endl;
	}
}

// This function takes the int count and SpaceMission missions[] by constant reference, calculates and outputs the average cost of the missions
void calcAvgCost(SpaceMission missions[MAX], int const& count) {
	double avgCost = 0;
	for (int i = 0; i < count; ++i) {
		avgCost += missions[i].cost;
	}
	if (count == 0) {
		cout << "Sorry! There are no missions in your dataset that have a cost to calculate average for. Returning to menu" << endl<< endl;
	}
	else {
		avgCost /= count;
		cout << "The average cost of the missions is: $"  << avgCost << "k" << endl << endl;
	}
}

void writeData(ofstream& outFile, SpaceMission missions[MAX], int const& count) {
	cout << endl << "Writing to " << FILE_NAME << "..." << endl;
	// write header
	outFile << "Organization;Location;Date;Price;Mission_Status" << endl;
	// write each mission
	for (int i = 0; i < count; ++i) { // write to file
		outFile << missions[i].organization << ';'
			<< missions[i].location << ';'
			<< missions[i].date << ';'
			<< missions[i].cost << ';'
			<< missions[i].status << endl;
	}
}