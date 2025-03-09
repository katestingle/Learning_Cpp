// NOTE: This template is to be used for discussion ONLY! You must
// use the required Algorithmic Design Document for all Assignments.
/******************************************************************************
# Author:           Kate Stingle
# Lab:              Discussion #6
# Date:             February 21st, 2025
# Description:      This program introduces structs my creating a struct object,
     which is a class in school, using a function to read to the member in that object(subject name, teacher and period), and using a function to print those members to the console. The program uses input validation for integer input period and always prints a hello message.
# Input:            struct ClassInfo : contains subject, teacher and period that are read to
                       Char subject[MAX_CHAR] : contains the class/subject title
                       Char teacher[MAX_CHAR] : contains the teacher for the given class
                     Int period : contains the period 1-8 for the given class, validated by readInt(prompt)
# Output:      struct ClassInfo : contains subject, teacher and period that were previously read to
                     Char subject[MAX_CHAR] : contains the class/subject title
                     Char teacher[MAX_CHAR] : contains the teacher for the given class
                     Int period : contains the previously inputted period 1-8 for the given class
# Sources:          Discussion 6 specifications
#******************************************************************************/


#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Define constants
const int MAX_CHAR = 100;
const char WELCOME_MSG[] = "Welcome to your class schedule program!";
const char ERR_MSG[] = "Invalid Entry! Please enter an integer 1-8 for period"; //outputted in readInt()

// Define ClassInfo struct
struct ClassInfo {
    char subject[MAX_CHAR];
    char teacher[MAX_CHAR];
	int period; //validated with readInt function
};

// Function headers
void readClassInfo(ClassInfo& classInfo);
int readInt(const char prompt[]);
void printClassInfo(const ClassInfo& classInfo);

// Main function
int main() {
    ClassInfo myClass;
    // Welcome message always
    cout << WELCOME_MSG << endl << endl;
    // Read class info, pass by reference
    readClassInfo(myClass);
	// Print class info members, does not change them so pass by const reference
    printClassInfo(myClass);
    return 0;
}

// Function definitions

// Read all the member objects to a given ClassInfo object
void readClassInfo(ClassInfo& classInfo) {
    cout << "Enter Class Info:" << endl;
    cout << setfill('=') << setw(60) << " " << endl;
    // Read subject
    cout << "Class Subject: ";
    cin.getline(classInfo.subject, MAX_CHAR);
    // Read teacher
    cout << "Teacher: ";
    cin.getline(classInfo.teacher, MAX_CHAR);
    // Read and validate period
    classInfo.period = readInt("Period: ");
}

// Read and validate an integer, used for int period
int readInt(const char prompt[]) {
    int num;
    cout << prompt;
    cin >> num;
    while (!cin || num < 1 || num > 8) {
        cout << ERR_MSG << endl;
        cin.clear();
        cin.ignore(1000000,  '\n');
        cout << prompt;
		cin >> num;
    }
    return num;
}

// Print all the class info inside of a passed in ClassInfo object (const reference)
void printClassInfo(const ClassInfo& classInfo) {
    cout << endl << endl << "Your Class:" << endl;
    cout << setfill('=') << setw(60) << " " << endl;
    cout << "Subject: " << classInfo.subject << endl;
    cout << "Teacher: " << classInfo.teacher << endl;
    cout << "Period: " << classInfo.period << endl;
    cout << setfill('=') << setw(60) << endl;
}
