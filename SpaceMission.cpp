// this file defines the functions for the SpaceMission struct
#include "SpaceMission.h"
#include <iostream>
// function definitions

// reads and validates a Space Mission's attributes from 
// the user, returning the entire SpaceMission object to 
// add to missions[] in MissionsData.cpp
SpaceMission readSpaceMission() {
	SpaceMission mission;
	cout << "Enter mission info below:" << endl;
	cout << setfill('=') << setw(40) << '=' << setfill(' ') << endl;
	cout << "Organization: ";
	cin.getline(mission.organization, MAX_CHAR, '\n');
	while (mission.organization[0] == '\0') {
		cout << "Invalid input!! Please enter an organization name: ";
		cin.getline(mission.organization, MAX_CHAR, '\n');
	}
	cout << "Location: ";
	cin.getline(mission.location, MAX_CHAR, '\n');
	cout << "Date: ";
	cin.getline(mission.date, MAX_CHAR, '\n');
	cout << "Cost: ";
	cin >> mission.cost;
	cin.ignore(100, '\n');
	while (cin.fail() || mission.cost < 0) {
		cin.clear();
		cout << "Invalid input!! Please enter a positive number for the cost: ";
		cin.ignore(100, '\n');
		cin >> mission.cost;
	}
	cout << "Status(S = Success, F = Fail): ";
	char statusChar;
	cin >> statusChar;
	statusChar = toupper(statusChar);
	while (cin.fail() || (statusChar != 'S' && statusChar != 'F')) {
		cin.ignore(100, '\n');
		cout << "Invalid input!! Please enter 'S' for Success or 'F' for Fail: ";
		cin >> statusChar;
		statusChar = toupper(statusChar);
	}
	if (statusChar == 'S') {
		strcpy_s(mission.status, "Success");
	}
	else {
		strcpy_s(mission.status, "Failure");
	}
	cout << setfill('=') << setw(40) << '=' << setfill(' ') << endl;
	return mission;
}