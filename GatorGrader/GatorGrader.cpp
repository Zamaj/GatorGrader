#include "stdafx.h"
#include "GatorGrader.h"

using namespace std;

int main()
{	

	Instructor *instructor = new Instructor();
	
	instructor->init();

	instructor->mainMenu();

	//instructor->currentCourse->print();

    return 0;
}