#include "stdafx.h"
#include "GatorGrader.h"

using namespace std;

int main()
{	
	Instructor *instructor = new Instructor();

	//calls method init() in instructor class
	instructor->init();

	string exitOption;
	//gives student option to exit from seeing their courses
	cout << "To exit, press E" << endl;
	getline(cin, exitOption);

	if (exitOption == "E") {
		return 0;
	}

	//checks if boolean variable ifStudent is false
	//if variable is false, meaning that user is an instructor, calls mainMenu() function, which
	//is for instructors to then manage courses
	if (instructor->ifStudent ==false) {
		instructor->mainMenu();
	}
	

	
	//instructor->currentCourse->print();

    //return 0;
}