// this files defines the SpaceMission struct and the attributes that a SpaceMission contains
// as mission_launches.txt is read, the data is stored in an array of SpaceMissions
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_CHAR = 101; // max number of characters for a string attribute

struct SpaceMission {
	char organization[MAX_CHAR]; // to hold the organization name, MAXCHAR = 101
	char location[MAX_CHAR]; // to hold the location of the mission
	char date[MAX_CHAR]; // to hold the date& UTC time for the mission
	double cost; // to hold the cost, in thousands of dollars, of the mission, validated
	char status[8]; // to hold the status(Success / Fail) of the mission, validated
};

// function prototypes
SpaceMission readSpaceMission(); // reads and validates a Space Mission's attributes from 
								// the user, returning the entire SpaceMission object to 
								// add to missions[] in MissionsData.cpp	