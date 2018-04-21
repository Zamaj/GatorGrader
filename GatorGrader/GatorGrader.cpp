#include "stdafx.h"
#include "GatorGrader.h"

using namespace std;

int main()
{	
	Instructor *instructor = new Instructor();
	instructor->init();
	string exitOption;
	cout << "To exit, press E" << endl;
	getline(cin, exitOption);
	if (exitOption == "E") {
		return 0;
	}
	if (instructor->ifStudent ==false) {
		instructor->mainMenu();
	}
	

	
	//instructor->currentCourse->print();

    //return 0;
}