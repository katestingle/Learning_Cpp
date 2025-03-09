 /******************************************************************************
# Author:           Kate Stingle
# Assignment:       Assignment 4 (CS 161B)
# Date:             January 26th, 2025
# Description:      - The purpose of this program is to read to, sort(ascending 
                      class order), and output 2 parallel lists of courses and the 
                      number of students enrolled in them. The program will then cancel 
                      all classes with less than 20 students by removing the courses 
                      from the list, and will print the updated list of courses and
                      the number of students enrolled. The program uses input 
                      validation, and always prints a welcome and exit message.

# Input:            - int &num 
                        -  collected and validated within readInt()
                        - used for collecting the number of students in a course, 
                        - will ultimately be stored in students[]. 
                        - Cannot be >25 students
                    - char courseNums[][MAXCHAR] 
                        - for holding the names and course numbers, 
                        - parallel with students[]. 
                        - Inputted within readInput()

# Output:           - char courseNums[MAX_COURSES][MAXCHAR] 
                        - printed as is, then courses cancelled, then reprinted
                        - 51 characters(columns) max per course.
                        - 20 courses(rows) max.
                    - int students[MAX_COURSES] 
                        - list of number of students in each course
                        - parallel with courseNums[]
                        - printed as is, then courses cancelled, then reprinted

# Sources:          Assignment 4 Specifications
#******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// CONSTANTS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
int const MAX_COURSES = 20;
int const MAXCHAR = 51;
int const MAX_STUDENTS = 25;
string const WELCOME_MSG = "Welcome to my Course Rosters program!!";
string const EXIT_MSG = "Thank you for checking out my Course Rosters program!";
string const INPUT_MSG = "Enter course number and students enrolled when prompted. \nEnter Quit or quit for course number when you are done.";
string const COURSE_PROMPT = "Enter course number : ";
string const STUDENTS_PROMPT = "Number of students enrolled : ";
string const STUDENTS_ERR_MSG = "Invalid number!! Please enter a number between 0 and 25";

// FUNCTION HEADERS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
// always prints welcome message
void welcome(); 
// prompt and read to the course and students arrays
void readInput(char courseNums[][MAXCHAR], int students[], int& count); 
// reads int for students in a course, called in readInput(), validates less than 25
void readInt(string prompt, int& num); 
// prints each course name and the number of students in each course, formatted neatly
void printList(char courseNums[][MAXCHAR], int students[], int count);
// This takes the 2 arrays and the count and removes all courses with less than 10 students in the course.
void cancelCourses(char courseNums[MAX_COURSES][MAXCHAR], int students[MAX_COURSES], int& count); 
// SHIFTING array to DELETE item, called each time an item is deleted in cancelCourses()
void deleteCourse(char courseNums[MAX_COURSES][MAXCHAR], int students[MAX_COURSES], int& count, int delIndex);

// MAIN - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
int main() {
    //  the arrays for course numbers and students.
    char courseNums[MAX_COURSES][MAXCHAR];
    int students[MAX_COURSES];
    int count = 0; // preset before array is filled, edited within readInput()
    welcome(); // always print welcome message
    readInput(courseNums, students, count); // arrays are filled in order
    cout << "List of courses and students: " << endl;
    printList(courseNums, students, count); // prints course #’s and students neatly
    cancelCourses(courseNums, students, count); // cancel the courses with less than10 students in them.
    cout << "List after cancellations : " << endl;
    printList(courseNums, students, count); // print filtered course #’s and students 
    cout << EXIT_MSG; // always print exit message
    return 0;
}

// FUNCTION DEFINITIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
void welcome() { // always prints welcome message
    cout << WELCOME_MSG << endl;
}

// prompt and read to the course and students arrays
void readInput(char courseNums[][MAXCHAR], int students[], int& count) {
    cout << INPUT_MSG << endl; // give user input instructions
    char courseNum[MAXCHAR]; // the inputted course number at a given time
    int numStudents; // the inputted num of students at a given time
    cout << COURSE_PROMPT;
    cin >> courseNum; // get course number
    while (strcmp(courseNum, "quit") != 0 && strcmp(courseNum, "Quit") != 0 && count < MAX_COURSES) { // continue prompting for courses until quit or max courses reached
        readInt(STUDENTS_PROMPT, numStudents); // get numStudents(validated in readInt())
        if (count == 0) { // if no items in list, dont need to sort
            strcpy_s(courseNums[count], courseNum);
            students[count] = numStudents;
        }
        else { // sort list by comparing 
            int i = 0;
            while (strcmp(courseNums[i], courseNum) < 0 && i < count) {
                i++; // go through courseNums[] until findcorrect alphabetical/numerical spot
            }
            //in a loop copy one course object to the next space
            //This is the process of shifting to make room.
            for (int j = count; j > i; j--) {
                strcpy_s(courseNums[j], courseNums[j - 1]);
                students[j] = students[j - 1];
            }
            //insert into the right position AFTER shifting all the courses
            strcpy_s(courseNums[i], courseNum);
            students[i] = numStudents;
        }
        //increment size - one more course inserted.
        count++;
        cout << COURSE_PROMPT;
        cin >> courseNum; // get course number
    }
}

// reads int for students in a course, called in readInput(), validates less than 25 and >0
void readInt(string prompt, int& num) {
    cout << prompt;
    cin >> num;
    while (cin.fail() || num < 0 || num > MAX_STUDENTS) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << STUDENTS_ERR_MSG << endl;
        cout << prompt;
        cin >> num;
    }
}

// prints each course name and the number of students in each course, formatted neatly
void printList(char courseNums[][MAXCHAR], int students[], int count){
    for (int i = 0; i < count; i++) {
        cout << setw(10) << left << courseNums[i] << right << students[i] << endl;
    }
}

// This function takes the 2 arrays and the count and removes all courses with less than 10 students in the course by continuously shifting the array. 
void cancelCourses(char courseNums[MAX_COURSES][MAXCHAR], int students[MAX_COURSES], int& count) {
    for (int i = 0; i < count; i++) {
        if(students[i] < 10) {
            deleteCourse(courseNums, students, count, i); // count is now 1 less, the was next item is now current item
            i--; // in order to not skip the current item, we need to minus 1 from i before the for loop adds 1, so that the i remains the same.
        }
     }
}

// SHIFTING array to DELETE item, called each time an item is deleted in cancelCourses()
void deleteCourse(char courseNums[MAX_COURSES][MAXCHAR], int students[MAX_COURSES], int& count, int delIndex){
    for (int i = delIndex; i < count - 1; i++) {
        strcpy_s(courseNums[i], courseNums[i + 1]);
        students[i] = students[i + 1];
    } // now the lists are shifted left to delete delIndex course
    courseNums[count - 1][0] = '\0'; // delete last course after shifting
    students[count - 1] = 0; // delete last index of students[]
    count--;
}
