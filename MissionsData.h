#include "SpaceMission.h"
#include <fstream>
#include <iostream>
using namespace std;
// MissionData.h and MissionData.cpp contain all functions 
// related to editing the SpaceMission missions[] array
// These functions allow the user to interact with the data
// It also includes functions to load to the array from 
// mission_launches.txt and write to mission_launches.txt 
// from the array

// constants
const int MAX = 30; // max number of missions that can be loaded to and fro mission_launches.txt
char const FILE_NAME[] = "mission_launches.txt";

// function prototypes
bool openInFile(ifstream& inFile); // returns true if succesfully opened input file, false if not
bool openOutFile(ofstream& outFile); // same as openInFile, but for output file
int loadData(ifstream& inFile, SpaceMission missions[]); // returns -1 if error loading data, else returns the count of missions loaded
void printData(SpaceMission missions[MAX], int const& count); // prints the data in the missions[] array in a neat format
void printShortenedData(SpaceMission missions[MAX], int const& count); // prints the data in the missions[] array in a shortened formatwith indexes
void removeMission(SpaceMission missions[], int& count); // removes a mission from the missions[] array
void addMission(SpaceMission missions[], int& count); // adds a mission to the missions[] array, calls readSpaceMission() to validate input
void calcAvgCost(SpaceMission missions[MAX], int const &count); // calculates and outputs the average cost of the missions in the missions[] array
void writeData(ofstream &outFile, SpaceMission missions[MAX], int const &count); // writes the data in the missions[] array to mission_launches.txt
