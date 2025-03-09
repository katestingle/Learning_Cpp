#include <iostream>
using namespace std;

int main() {
	int age = 47;
	int* age_ptr = &age;
	// '*' is used to declare a pointer, along with "dereferencing" the pointer
	// '&' is used to get the memory adress of a variable. in this case , it is used to assign the memory adress of the variable age to the pointer age_ptr
	// age_ptr is a pointer that not only has it's own memory adress, but also contains the memory adress of the variable that it "points" to.

	cout << "age before change: " << age << endl;
	cout << "age adress before value change" << &age << endl;
	cout << "age_ptr value before value change: " << *age_ptr << endl;
	cout << "age_ptr memory adress before: " << age_ptr << endl << endl;

	*age_ptr = 52;
	// see we use "inderection operator" '*' to change the value of the variable that the pointer age_ptr points to.
	// this DOES NOT CHANGE THE MEMORY ADRESS OF EITHER VARIABLE(age_ptr or age)
	// this is called "dereferencing" the pointer, or "indirect referencing"

	cout << "age: " << age << endl;
	cout << "age's memory adress: " << &age << endl;
	cout << "age_ptr: " << endl;
	cout << "points to the memory adress : " << age_ptr << endl;
	cout << "age_ptr value : " << *age_ptr << endl;
	cout << "age_ptr memory adress : " << &age_ptr << endl << endl;

	cout << "we can see that the memory adress of all of the variable remained the same." << endl;
	cout << "the only thing that changed was the value of the variable that the pointer was pointing to, which is int age" << endl;

	int nums[] = { 1, 2, 3, 4, 5 };
	int* nums_ptr = nums;
	cout << " * (nums_ptr + 2): " << * (nums_ptr + 2) << "  =?=  *nums_ptr[2]" << nums[2] << endl;

	cout << endl << 'c' << endl;
	cout << 'c' * 2 << endl;
}