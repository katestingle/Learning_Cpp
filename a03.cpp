/******************************************************************************
# Author:           Kate Stingle
# Assignment:       Assignment 3 (CS 161B)
# Date:             January 25th, 2025
# Description:      - This program calculates the letter grade based on a 
					  numerical score, for n assignments. This program reads 
					  the numerical scores from the user as input into a double 
					  array, and then calculates each letter grade from each score, 
					  filling the parallel array with the corresponding letter grade. 
					  The program uses input validation for the scores inside of 
					  readDouble(). The program will output both  parallel arrays so 
					  the user can view their score and the corresponding letter grade 
					  for each assignment. Then, it will sort the arrays in ascending 
					  grade order and print them in parallel again. Finally, the 
					  program will output the median score.

# Input:            - Double &num in void readDouble(string prompt, double &num)
					  - Validated within readDouble for being a double
					  - Validated in readScores(double scores[], int &count) for between 0-4
					  - Used to read scores to the score array

# Output:           - char array grades[] (for the inputted assignment scores 1-4)
					- Double array scores[] (for the calculated grades from the parallel array grades)
					- Double median (for the median score calculated & returned from 
					  the median() function, returned to main where it is outputted)

# Sources:          Assignment 3 Specifications
#******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//  CONSTANTS
string const ERR_MSG = "Invalid score!Please try again!!";
string const WELCOME_MSG = "Welcome to my Parallel Arrays program!";
string const EXIT_MSG = "Thank you for using my Parallel Arrays program!!";
string const READ_SCORE_PROMPT = "Please enter the list of scores(-1 to end input:) \nValid scores are between 0 and 4 inclusive.";
int const MAX_ARR = 20;

//  FUNCTION HEADERS
void welcome(); //welcome message always outputted
void readScores(double scores[], int& count); // reads & stores up to 20 double scores 0-4 until terminator score -1 is entered
void readDouble(string prompt, double& num); // outputs a prompt and reads a valid double from user. Uses input validation
void calcGrade(double scores[], char grade[], int count); // determines the char letter grade for each assignment in scores[] and assigned that letter grade to the parallel index in grades[]
void printList(double scores[], char grades[], int count); // prints each assignment’s score + “ “ + it’s grade. Each assignment separated by a new line
void sort(double scores[], char grade[], int count); // uses selection sort algorithm to sort grades in ascending order for both arrays scores[] and grades[]
double median(double scores[], int count); // calculates and returns the median score from the list of assignment scores


// MAIN
int main() {
	double scores[MAX_ARR];
	char grades[MAX_ARR];
	int count = 0; // always preset to 0 before reading scores. readScores() edits it
	welcome(); // always print welcome message
	readScores(scores, count); // prompts and assigns scores to inputted scores
	calcGrade(scores, grades, count); // calc grades into parallel grades array
	cout << endl << "Your stats are as below : " << endl << endl;
	cout << endl << "The list of scores and their grades are : " << endl;
	printList(scores, grades, count); // print unsorted grades
	sort(scores, grades, count); // sort arrays in ascending grade order
	cout << endl << "The list sorted by scores in ascending order : " << endl;
	printList(scores, grades, count); // print sorted grades
	cout << fixed << setprecision(2); //median score printed to 2 dec points
	cout << endl << "The median score is " << median(scores, count) << endl; // output median score 
	cout << endl << EXIT_MSG; // exit message always printed
	return 0;
}

// DEFINE FUNCTIONS
void welcome() { // w3elcome message always outputted
    cout << WELCOME_MSG << endl;
}

// reads & stores up to 20 double scores 0-4 until terminator score -1 is entered
void readScores(double scores[], int& count) { // prompt, read, validate to scores[]
    double score;
    cout << READ_SCORE_PROMPT << endl; // prompt for the score list

    readDouble("", score); // first iteration of prompting
    while (score != -1 && (score < 0 || score > 4)) { //validate score
        cout << ERR_MSG << endl;
        readDouble("", score);
    } //score is now valid to determine

    while (score != -1) { // keep prompting for score until -1 entered
        scores[count] = score;
        count++;
        if (count == 20) { // if reached max, quit the loop
            score = -1;
        } else { // if not reached max, keep prompting
            readDouble("", score);
            while(score != -1 && (score < 0 || score > 4)) { //validate score
                cout << ERR_MSG << endl;
                readDouble("", score);
            }
        }
        //score is now valid to determine
    }
}

// determines the char letter grade for each assignment in scores[] and assigned that letter grade to the parallel index in grades[]
void calcGrade(double scores[], char grade[], int count) {
    for(int i = 0; i < count; i++) { // for each assignment score, assign the grade
        if(scores[i] > 3.3) { // A = 3.3 - 4.0
            grade[i] = 'A';
        } else if(scores[i] > 2.7) { // B = 2.7 - 3.3
            grade[i] = 'B';
        } else if (scores[i] > 1.9) { // C = 1.9 - 2.7
            grade[i] = 'C';
        } else if (scores[i] > 1.1) { // D = 1.1 - 1.9
            grade[i] = 'D';
        } else { // F = 0.0 - 1.1
            grade[i] = 'F';
        }
    }
}

// prints the scores and grades in parallel
void printList(double scores[], char grades[], int count) {
    cout << fixed << setprecision(1); // preset to output all scores to 1 decimal point
    for(int i = 0; i < count; i++) { // for each assignment
        // prints each assignment’s score + “ “ + it’s grade + new line to seperate assignments
        cout << scores[i] << " " << grades[i] << endl;
    }
}

// uses selection sort algorithm to sort grades in ascending order for both arrays scores[] and grades[]
void sort(double scores[], char grade[], int count) { // use selection sort algorithm
    double tempScore; // temporary variable for swapping scores
    char tempGrade; // temporary variable for swapping grades
    int minIndex; // keeps track of the minimum grade as it traverses thru grades[]
    for (int i = 0; i < count; i++) {
        minIndex = i;    // always start at the current element
        for (int j = i; j < count; j++) {   // go through to the end of the array
            if (scores[j] < scores[minIndex]) { // determine the index of the minimum value
                minIndex = j;
            }
        }
        // now we have determined the index of the min grade, so let’s swap it with the i’th value
        if (minIndex != i) {
            tempScore = scores[i]; // remove value from i’th val and store in temporary value
            tempGrade = grade[i];
            scores[i] = scores[minIndex]; // assign i’th val to the minimum grade
            grade[i] = grade[minIndex];
            scores[minIndex] = tempScore;// assign old min grade index to the old i’th value
            grade[minIndex] = tempGrade; // essentially, swap values
        }
    }
}

// calculates and returns the median score from the list of assignment scores
double median(double scores[], int count) { //returns the median score value based on the sorted array scores[]
    if (count % 2 == 1) { // if count is odd, return the middle value
        return scores[(count - 1) / 2];
    } else { // if count is even, return the average of the 2 middle values
        return (scores[(count - 1) / 2] + scores[(count - 1) / 2 + 1]) / 2.0;
    }
}

// outputs a prompt and reads a valid double from user input stream. Uses input validation
void readDouble(string prompt, double& num) {
    cout << prompt; // always print prompt
    cin >> num; 
    while (cin.fail()) { // if not a valid double, print error and re-read
        cin.clear(); // lower fail flag
        cin.ignore(1000, '\n'); // clear buffer
        cout << ERR_MSG << endl; 
        cin >> num;
    }
    // refernce variable num is now a valid double
}
