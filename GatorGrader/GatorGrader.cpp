#include "stdafx.h"
#include "GatorGrader.h"

using namespace std;

//Driver code
int main()
{	
	Instructor *instructor = new Instructor();
	
	instructor->init();

	instructor->mainMenu();

    return 0;
}