/******************************************************************************
# Author:           Kate Stingle
# Assignment:       Midterm Assignment (CS 161B)
# Date:             February 6th, 2025
# Description:      The purpose of this program was to demonstrate the 
					FIFO(First in First Out) system with an integer list queue[]. 
					To do this, the user has 3 options: quit, dequeue an 
					integer(also removing every integer in front of it), and
					print the current queue.
# Input:            char& choice in readOption(char& choice):
					  - Reference variable that exists in main as char choice
					  - Inputted and validated within readOption
					Int val in main()
					  - User inputs the value of the integer in the queue that they want to delete
					  - Called in main by dequeue(queue, size, val)
					  - queue() returns 2 if val is not in queue
# Output:           Int val int main()
					  - Also a user input variable
					  - Printed in line val + “is not in the queue” if it is not in the queue(dequeue() returns 2)
					Error message = “Invalid option.” + newline
					  - Outputted in readOption() whenever inputted choice is invalid
					  - Reprompt user for new choice after
					printQueue(queue, size) in main() PREWRITTEN
					  - Prints the current queue
					  - Called in main() after user inputs choice
					  - Also called in dequeue() after user inputs choice
# Sources:          Midterm Specifications
#******************************************************************************/
#include <iostream>
// no stl header files allowed
using namespace std;

// FUNCTION PROTOTYPES
int dequeue(int queue[], int& size, int& val); // removes a value out of a queue of integers
void printQueue(int queue[], int size); // prints the queue
int searchQueue(int queue[], int size, int val); // searches the queue for a value, returns -1 if not found, called in dequeue()
void deleteFirstVal(int queue[], int& size); // deletes the first value in the queue, size-- and shifts all values down
void readOption(char& choice); // reads in the user's option as a char, does input validation

// CONSTANTS
const int MAX = 3; // maximum size of queue

int main() {
    int queue[MAX] = { 8, -2, 3 }; // integer array for queue
    int size = 3;   // contains number of elements in queue

    // Add your code here
    char choice;
	cout << "Welcome to the FIFO Queue Program!" << endl; // always printed
	readOption(choice);
	while (choice != 'q') { // while user doesn't want to quit
		if (choice == '-') { // DEQUEUE
			int val;
			cout << "Integer: ";
			cin >> val;
			int result = dequeue(queue, size, val); // updates queue and size
			if (result == 1) { // underflow
				cout << "Queue is empty." << endl;
			}
			else if (result == 2) { // value not found
				cout << val << " is not in the queue." << endl;
			}
		}
		// PRINT QUEUE : for both 'p' and '-'
		printQueue(queue, size);
		readOption(choice); // re prompt user for option
	}
	cout << endl <<"Goodbye!" << endl; // exit msg always printed
    return 0;
}

// DEFINE FUNCTIONS

// Removes a value out of a queue of integers.
int dequeue(int queue[], int& size, int& val) {
    if (size == 0) { // queue is empty, no values to dequeue
        return 1; // return 1 on underflow
    } 
	int indexVal = searchQueue(queue, size, val); // returns the 1st index val is located @. -1 if not found
	if (indexVal == -1) {
		return 2; // return 2 on value not found
	}
	//if the value is found, delete the value from the queue, including the vlaues before it.
	for (int n = 0; n <= indexVal; n++) {
		//delete front index n times, essentially until previously inputted val has been deleted
		deleteFirstVal(queue, size);
	}
    // integers were removed from the FRONT of the queue
	return 0; // return 0 on successful dequeue
}

// Call this function to print the queue
void printQueue(int queue[], int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << queue[i];
		if (i != size - 1) {
			cout << ", ";
		}
    }
    cout << "]" << endl;
}

// Searches the queue for an int value, returns -1 if not found, called in dequque()
int searchQueue(int queue[], int size, int val) {
    for (int i = 0; i < size; i++) {  // worst case O(n) time complexity
        if (queue[i] == val) {
            return i; // item found at index i, return the index i where item is found
        }
    }
	return -1; // item not found in queue
}

//  Deletes the first value in the queue, size-- and shifts all values down
void deleteFirstVal(int queue[], int& size) {
	for (int i = 0; i < size-1; i++) {
		queue[i] = queue[i + 1]; // shift every value in the aray to the left, eliminating the first value
	} // the last value of the arr at queue[size-1] should be a copy of queue[size-2]
	queue[size - 1] = 0; // set last value to nothing since we decreased the size by one
	size--; // we decreased the size by one, so -1 from the reference variable size
}

// Reads in the user's option as a char reference, does input validation
void readOption(char& choice) {
	cout << endl << "Enter option (-, p, q): ";
	cin >> choice;
	while (cin.fail() || (choice != '-' && choice != 'p' && choice != 'q')) { // validate
		cin.clear(); // lower fail flag
		cin.ignore(1000, '\n'); // ifgnore buffer
		cout << "Invalid option." << endl << endl; // err msg if unknown command is entered, DOES NOT PRINT QUEUE
		cout << "Enter option(-, p, q): "; //reprompt
		cin >> choice;
	}
}