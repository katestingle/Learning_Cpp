/******************************************************************************
# Author:           Kate Stingle
# Lab:              Discussion #7
# Date:             March 8th, 2025
# Description:      This program is a menu-run program that teaches the user about pointers and the 3 different ways the * operator is used in c++. There will be 4 option in the menu: (1) Using ‘*’ to declare a pointer variable, (2) Using ‘*’ as a “dereferencing operator”, (3) Using ‘*’  as a multiplication operator, and (4) QUIT. Each explanation will also include an interactable example where the user can look at code, input values and observe the output to better understand what the asterisk * does. This program uses input validation and always prints a welcome and exit message. It will continue to teach the 3 different uses and repromt the menu for the user’s choice until they enter the integer (4) to quit.

# Input:            In void readInt(int *num):
                        - Int *num is the pointer for the integer to read to. Input is validated within readInt()
                    In void readDouble(double *num):
                        - Double *num is the pointer for the double to read to Input is validated within readDouble()
                    In int chooseMenu():
                        - Int choice (holds the inputted number 1-4 for the user to respond to when given the menu prompt. Validate within readInt() and chooseMenu())
# Output:           In void teachDeclarePointer():
                        - Int num (read to using readInt(&num), used to demonstrate the value of num vs the address of num &num)
                        - Int *num_ptr = &num (used to demonstrate declaration of pointers in this segment, as well as printing the memory address of the pointer itself vs the address of the object that it points to)
                    In void teachDereferencing():
                        - Int num (read to using readInt(&num), used to assign address to pointer num_ptr)
                        - Int *num_ptr = &num (used to demonstrate dereferencing of pointers in this segment)
                    In void teachMultiply():
                        - Int num1 (read to using readInt(&num1), used to multiply with double num2 to demonstrate the mathematical operation of multiplying using the asterisk in c++)
                        - Double num2 (read to using readDouble(&num2), multiplied w int num1
# Sources:          None
#******************************************************************************/


#include <iostream>
#include <limits>
using namespace std;

// constants
const char READINT_ERR_MSG[] = "Invalid Input!!Please Enter an integer value : "; // for void readInt()
const char READDOUBLE_ERR_MSG[] = "Invalid Input!!Please Enter a double value : "; // for void readDouble()
const char WELCOME_MSG[] = "Welcome to CS School!\nToday's topic of interest is pointers and the 3 different roles that the \nasterisk(*) operator can play in c++ programs with respect to pointers"; // for void welcome()
const char EXIT_MSG[] = "Thank you for using my pointer program!";
// for int chooseMenu()
const char MENU_PROMPT[] = "(1) Using '*' to declare a pointer variable\n(2) Using '*' as a \"dereferencing operator\"\n(3) Using '*'  as a multiplication operator\n(4) QUIT\nChoose 1 Option(integers 1 - 4 only) : ";
const char MENU_ERR_MSG[] = "Invalid option!Please enter an integer 1 - 4 : ";

// Function declarations
void welcome(); // prints the welcome message and purpose of program
int chooseMenu();   // displays the formatted menu, reads the choice as an integer from input, validates it and returns that choice (1-4)
void readInt(int* num);  // used to read & validate an integer from the user to the integer variable that num points to
void readDouble(double* num); // like readInt() , used to read & validate an double from the user to the double variable that num points to
void teachDeclarePointer(); // teaches the user how * is used when declaring pointers, called when chooseMenu() returns 1 to main()
void teachDereferencing();  // teaches the user how * is used when dereferencing pointers to access the variable that they point to, called when chooseMenu() returns 2 to main()
void teachMultiply(); // teaches the user how the math operator * is used when multiplying two numbers. Called when chooseMenu() returns 3 to main()

// MAIN
int main() {
    welcome();
    int choice = chooseMenu();

    while (choice != 4) {
        if (choice == 1)
            teachDeclarePointer();
        else if (choice == 2)
            teachDereferencing();
        else
            teachMultiply();

        choice = chooseMenu();
    }

    cout << EXIT_MSG << endl;
    return 0;
}

// FUNCITON DEFINITIONS

// prints the welcome message and purpose of program
void welcome() {
    cout << "======================================================================" << endl;
    cout << WELCOME_MSG << endl;
    cout << "Before we begin, I reccomend you maximize your terminal screen as you will be doing a lot of reading" << endl;
}

// displays the formatted menu, reads the choice as an integer from input, validates it and returns that choice (1-4)
int chooseMenu() {
    int choice;
    cout <<"\n======================================================================" << endl;
    cout << "MENU\n======================================================================" << endl;
    cout << MENU_PROMPT;
    readInt(&choice);

    while (choice < 1 || choice > 4) {
        cout << MENU_ERR_MSG;
        readInt(&choice);
    }

    return choice;
}

// used to read & validate an integer from the user to the integer variable that num points to
void readInt(int* num) {
    cin >> *num;
    while (cin.fail()) {
        cout << READINT_ERR_MSG;
        cin.clear();
        cin.ignore(1000000, '\n');
        cin >> *num;
    }
}

// like readInt() , used to read & validate an double from the user to the double variable that num points to
void readDouble(double* num) {
    cin >> *num;
    while (cin.fail()) {
        cout << READDOUBLE_ERR_MSG;
        cin.clear();
        cin.ignore(1000000, '\n');
        cin >> *num;
    }
}

// teaches the user how * is used when declaring pointers, called when chooseMenu() returns 1 to main()
void teachDeclarePointer() {
    cout << "** In order to understand how to declare a pointer variable, we must 1st understand what a pointer is **\n\n";
   
    cout << "Definition of a Pointer variable:\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "A variable of 'pointer data type' that holds the address of a memory location that it 'points to'. \n";
    cout << "Every variable has its own address in memory, whether it is in Static / Global storage or on the stack. \n";
    cout << "You can assign the memory location of another variable to a pointer variable, so that the pointer 'points' \nto that variable.\n\n";
    cout << "Syntax of declaring a pointer variable: (use the asterisk '*')\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "\t [type] * pntr_0; // declares a pointer variable that 'points' to an object of type [type]\n";
    cout << "below shows declaring and setting an int pointer variable to a 'null' value.\n";
    cout << "These pointers do not point to any valid memory location until they are changed\n";
    cout << "\t int * pntr_1 = 0;\n";
    cout << "\t int * pntr_2 = NULL;\n";
    cout << "\t int * pntr_3 = nullptr;\n";
    cout << "declaring a pointer variable\n";
    cout << "\t [type] myTypeObject; // declares a variable of type [type].\n";
    cout << "\t [type] * pntr_4; // uses '*' to declare a pointer variable that points to an object of type [type]\n";
    cout << "\t pntr_4 = &myTypeObject; // sets the pointer variable to contain the address of myTypeObject, which\n\t therefore 'points to' the object myTypeObject.\n";
    cout << "All variables have their own memory address that can be accessed by typing the address operator(&) in front \nof the variable name(&myTypeObject).\n";
    cout << "we set pointer variables to contain memory addresses that point to other variables, but not containing the \nvariables themselves.\n";
    cout << "so, this would be incorrect syntax, as we cannot assign a pointer to the value of an object:\n";
    cout << "\t [type] * pntr_5 = myTypeObject;\n\n";
    cout << "----------------------------------------------------------------------------------\n";
    cout << "RESOURCE FOR FURTHER EXPLANATION OF POINTERS:  https://www.w3schools.com/c/c_pointers.php\n";
    cout << "----------------------------------------------------------------------------------\n";

    cout << endl << "LET'S PRACTICE" << endl;
    cout << "----------------------------------------------------------------------------------\n";
    cout << "Enter an integer value that you would like to store in an integer variable 'num': ";
    int num;
    readInt(&num);
    cout << "Great! According to the code below, num now contains the integer: " << num << endl;
    cout << "\t int num; \n\t readInt(&num); " << endl;
    cout << "Now, the code will declare a POINTER using the asterisk '*' to POINT TO num" << endl;
    cout << "\t int* num_ptr = &num;" << endl;
    cout << "Notice that we put a memory operator '&' in front of num. This is because num_ptr contains the address of an \ninteger type variable, but does not contain the variable itself." << endl;
    cout << "Now, we can access the value of num by using the asterisk as a \"dereferencing operator\".See the 2nd option in \nthe menu for further explanation on this operation: " << endl;
    cout << "\t cout << * num_ptr;" << endl;
    int* num_ptr = &num;
    cout << "The output from the last code segment was: " << *num_ptr << endl;
    cout << endl << "We can also print the hexidecimal addresses for 1) the pointer variable itself and 2) the variable the \npointer points to. See below :" << endl;
    cout << "\t cout << & num_ptr << \"    \" << num_ptr << \"    \" << &num;" << endl;
    cout << "Output: " << &num_ptr << " " << num_ptr << " " << &num << endl;
    cout << "Notice that the last 2 memory addresses are the same. Because num_ptr contains the memory address of \nnum, getting the address of num using the address operator &num produces the same output as printing the \nvalue of a pointer actively pointing to num." << endl;
}

// teaches the user how * is used when dereferencing pointers to access the variable that they point to, 
// called when chooseMenu() returns 2 to main()
void teachDereferencing() {
    cout << "\nIndirection = dereferencing = using '*' to access the VALUE of the variable that a pointer points to. " << endl;
    cout << "Because pointer variables contain memory addresses of objects, rather than the objects themselves, simply " << endl;;
    cout << "printing the pointer without the dereferencing operator (*) actually just prints the hexadecimal memory address " << endl;
    cout << "of the object it points to" << endl << endl;
   
    cout << "EXAMPLE:" << endl;
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "Enter an integer value that you would like to store in an integer variable 'num': ";
    int num;
    readInt(&num);
    int* num_ptr = &num;
    cout << "\t int num; \n\t readInt(&num);" << endl;
    cout << "Now we will declare a pointer that points to an object of type int. We will initialize it with the memory address\nof num." << endl;
    cout << "\t int * num_ptr = &num;" << endl;
    cout << "num_ptr DOES NOT CONTAIN THE VALUE -8 ! When we print the num_ptr without the dereferencing operator (*), it " << endl;
    cout << "simply outputs the hexidecimal address of num, which is the address that num_ptr contains." << endl;
    cout << "When we print the num_ptr WITH the operator(*) in front of the pointer name, it outputs the VALUE of the \ninteger num that num_ptr points to. " << endl;
    cout << "\t cout << num_ptr << \"    \" << *num_ptr;" << endl;
    cout << "Output from the last code segment: " << num_ptr << "    " << *num_ptr << endl;
    cout << "Putting the asterisk in front of a pointer variable to access its value is called \"dereferencing\".\n\n";

    cout << "SPECIAL DEREFERENCING (*) SYNTAX: arrays\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "To access the value of a term in an array from a pointer name, when the pointer points to an array, the \nfollowing syntax shall be used:\n";
    cout << "    [type] myArray[] = {1, 2, 3, 4, 5};\n";
    cout << "    [type] *myArray_ptr = myArray; // points to first index of array\n";
    cout << "We can assign the pointer to the array name because the array name points to the first element. " << endl;
    cout << "The address of the array name = address of the 1st element.\n";
    cout << "Now, let's access terms in the array that myArray_ptr is pointing to using the DEREFERENCING OPERATOR (*) and an index i\n";
    cout << "    int i = 0;\n";
    cout << "    cout << *(myArray_ptr +i) << \"    \" << myArray[i];\n";
    cout << "Output: 1    1\n";
    cout << "If we change the index, we can access different terms in myArray by both the pointer and the array name itself\n";
    cout << "    i = 3;\n";
    cout << "    cout << *(myArray_ptr + i) << \"    \" << myArray[i];\n";
    cout << "Output: 4    4\n";
}

// teaches the user how the math operator * is used when multiplying two numbers. 
// Called when chooseMenu() returns 3 to main()
void teachMultiply() {
    cout << "The asterisk (*) as a MULTIPLICATION OPERATOR\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "The syntax of this use is pretty much the same as all of the other mathematical operators in C++\n";
    cout << "    [num1] * [num2]\n";
    cout << "This expression will evaluate to the value of num1 TIMES the value of num2\n";
    cout << "Keep in mind that there are some data types you cannot directly multiply with the * operator, such as strings, pointers, and booleans, without additional handling.\n";
    cout << "The most common data types to multiply include:\n";
    cout << "\t - Integers, long\n";
    cout << "\t - Floating point numbers : (float, double, long double)\n";
    cout << "\t - Doubles\n";
    cout << "\t - characters(they will be converted to their designated integer first before multiplying)\n";
    cout << "You can mix the data types that you are multiplying. For example:\n";
    cout << "    Double product = 8 * 9.2\n";
    cout << "    char newChar = 'c' * 2\n\n";

    cout << "TRY IT OUT (corresponding code is indented)\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "    int num1;\n";
    cout << "    cout << \"Enter an integer: \";\n";
    cout << "    readInt(&num1);\n";
    cout << "Enter an integer: ";
    int num1;
    readInt(&num1);
    cout << "    double num2;\n";
    cout << "    cout << \"Enter a double: \";\n";
    cout << "    readDouble(&num2);\n";
    cout << "Enter a double: ";
    double num2;
    readDouble(&num2);
    cout << "    cout << \"Product: \" << num1*num2 << endl;" << endl;
    cout << "Product: " << num1 * num2 << endl;
}
