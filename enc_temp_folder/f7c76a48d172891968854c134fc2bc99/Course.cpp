#include "stdafx.h"
#include "Assignment.h"
#include "Student.h"
#include "Course.h"
#include "Instructor.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

/*The Course class contains most of the 
functionality for the proigram. It allows users to perform most primary actions associated with a course, 
such as adding assignments, students, and grading assignments.*/

Course::Course(string name) 
{
	courseName = name;
}

// Removes course data from file
Course::~Course() 
{
	string line;

	ifstream file("courses.txt");
	ofstream temp("temp.txt");
	 
	//If data doesn't contain course name, copy to new file
	while (getline(file, line)) {

		if (!(line.substr(1, line.back()) == courseName || line.substr(0, courseName.size()) == courseName)) {
			temp << line << endl;
		}		
	}	

	file.close();
	temp.close();

	remove("courses.txt");
	rename("temp.txt", "courses.txt");
}

void Course::setCourseName(string name) 
{
	courseName = name;
}

string Course::getCourseName() 
{
	return courseName;
}

const vector<Student*>& Course::getStudentList()
{
	return studentList;
}

const vector<Assignment*>& Course::getAssignmentList()
{
	return assignmentList;
}

// Provides identifying tags for type of item to be saved
string Course::tag(saveType type) 
{

	string tag;

	if (type == courseSave)
	{
		tag = "#";
		return tag;
	}

	if (type == studentSave)
	{
		tag = getCourseName().append("$");
		return 	tag;
	}

	if (type == assignmentSave)
	{
		tag = getCourseName().append("@");
		return tag;
	}

	if (type = masterAssignmentSave) 
	{
		tag = getCourseName().append("&");
		return tag;
	}

	return "?";
}

// Walks user through adding student
void Course::addStudent() 
{
	string newStudentName;
	string newStudentFirstName;
	string newStudentLastName;

	cout << "Please enter student's first and last name:" << endl;
	getline(cin, newStudentName);

	istringstream studentAttributes(newStudentName);
	studentAttributes >> newStudentFirstName >> newStudentLastName;

	Student *student = new Student(newStudentFirstName, newStudentLastName, newStudentName);
	studentList.push_back(student);

	save("", newStudentName, 0, studentSave);	

	cout << "Student '" << newStudentFirstName << " " << newStudentLastName << "' added to course " << courseName << endl;

	cout << endl;
}

// Adds student based on stats (used during startup)
void Course::addStudent(string first, string last, string full) 
{
	Student *student = new Student(first, last, full);
	studentList.push_back(student);
}

// Manual assignment entry
void Course::addAssignment()
{	
	string newAssignmentName;
	string newAssignmentPoints;
	double points;

	if (studentList.size() == 0) 
	{
		cout << "Please add at least one student before adding assignments" << endl;
		cout << endl;
		return;
	}

	cout << "Assignment Name: (At this time, assignments may only be one word)" << endl;
	getline(cin, newAssignmentName);
	
	cout << "Assignment points:" << endl;
	getline(cin, newAssignmentPoints);

	points = atof(newAssignmentPoints.c_str());

	Assignment *assignment = new Assignment(newAssignmentName, points);
	assignmentList.push_back(assignment);

	for (unsigned int i = 0; i < studentList.size(); i++)
	{
		studentList[i]->addStudentAssignment(assignment);
	}

	save("", newAssignmentName, points, masterAssignmentSave);
	save("", newAssignmentName,points, assignmentSave);
	

	cout << "Assignment '" << newAssignmentName << "' worth " << points << " points has been added to course " << courseName << endl;
}

// Automatic assignment addition used during startup
void Course::addAssignment(string name, double points) 
{
	Assignment *assignment = new Assignment(name, points);
	assignmentList.push_back(assignment);

	for (unsigned int i = 0; i < studentList.size(); i++) 
	{
		studentList[i]->addStudentAssignment(assignment);
	}
}

//User-graded assignments
void Course::gradeAssignment() 
{
	string whichAssignment;

	cout << "Which assignment would you like to grade?";

	getline(cin, whichAssignment);

	string oneOrAll;

	cout << "Would you like to grade an assignment for a single student or all students?" << endl;
	cout << "1. Single student" << endl;
	cout << "2. All students" << endl;

	getline(cin, oneOrAll);

	// Users can choose to grade a specific student's assignment...
	if (oneOrAll == "1") 
	{
		string whichStudent;

		cout << "Which student would you like to grade?" << endl;

		getline(cin, whichStudent);
		
		bool studentFound = false;

		for (unsigned int i = 0; i < studentList.size(); i++)
		{
			if (studentList[i]->getFullName() == whichStudent)
			{
				studentList[i]->gradeStudentAssignment(whichAssignment, this);
				studentFound = true;
				break;
			}
		}

		if (studentFound == false) 
		{
			cout << "You have no student '" << whichStudent << "'" << endl;
			return;
		}		
	}

	// Or do them all at once
	if (oneOrAll == "2") 
	{
		cout << "Enter the grade for each student:" << endl;
		cout << "(If you wish to exit grading process grading at any point, just enter 'c')" << endl;

		for (unsigned int i = 0; i < studentList.size(); i++) 
		{
			string grade;
			double points;

			cout << studentList[i]->getFullName() << ": " << endl;
			getline(cin, grade);

			if (grade == "c") 
			{
				return;
			}

			points = atof(grade.c_str());

			studentList[i]->gradeStudentAssignment(whichAssignment, points, this);
		}		
	}
}

//Show grade for student on a specific assignment
void Course::showStudentGrade()
{
	string studentName;

	cout << "Enter the name of the student:" << endl;

	getline(cin, studentName);

	bool studentFound = false;

	for (unsigned int i = 0; i < studentList.size(); i++)
	{
		if (studentList[i]->getFullName() == studentName)
		{
			currentStudent = studentList[i];
			studentFound = true;
			break;
		}
	}

	if (studentFound == false)
	{
		cout << "No such student" << endl;
		return;
	}

	string assignmentName;

	cout << "Enter the name of the assignment:" << endl;

	getline(cin, assignmentName);

	for (unsigned int i = 0; i < currentStudent->getStudentAssignments().size(); i++) {
		if (currentStudent->getStudentAssignments()[i]->getAssignmentName() == assignmentName) {
			cout << studentName << ": " << currentStudent->getStudentAssignments()[i]->getEarnedPoints() << "/" << currentStudent->getStudentAssignments()[i]->getPossiblePoints() << endl;
			return;
		}
	}
}

void Course::showAllStudentGrades() 
{
	string assignmentName;

	cout << "Enter the name of the assignment:" << endl;

	getline(cin, assignmentName);

	for (unsigned int j = 0; j < studentList.size(); j++)
	{
		for (unsigned int i = 0; i < studentList[j]->getStudentAssignments().size(); i++) {

			if (studentList[j]->getStudentAssignments()[i]->getAssignmentName() == assignmentName)
			{
				cout << studentList[j]->getFullName() << ": " << studentList[j]->getStudentAssignments()[i]->getEarnedPoints() << "/" << studentList[j]->getStudentAssignments()[i]->getPossiblePoints() << endl;

				break;
			}			
		}
	}	
}

//Show average for student from all assignments (i.e. grade in class)
void Course::showStudentAverage()
{
	string studentName;
	
	cout << "Enter the name of the student:" << endl;
	
	getline(cin, studentName);

	for (unsigned int i = 0; i < studentList.size(); i++) {

		if (studentList[i]->getFullName() == studentName)
		{
			cout << studentName << ": " << studentList[i]->getAverageGrade() << endl;			
			return;
		}
	}

	
	cout << "No student '" << studentName << "'" << endl;
	return;	
}

void Course::showAllStudentAverages()
{
	for (unsigned int i = 0; i < studentList.size(); i++)
	{
				
		cout << studentList[i]->getFullName() << ": " << studentList[i]->getAverageGrade() << endl;			
	}
}

void Course::showAssignmentAverage()
{
	string assignmentSelect;
	bool assignmentFound = false;
	double assignmentTotal = 0;
	double average;
	
			//get user input
	cout << "Enter the name of the assignment:" << endl;
	getline(cin, assignmentSelect);
	
			//iterate to look for assignment
	for (unsigned int i = 0; i < assignmentList.size(); i++)
	{
		if (assignmentList[i]->getAssignmentName() == assignmentSelect)
		{
			currentStudent = studentList[i];
			assignmentFound = true;
			break;
		}
	}
	
			//if assignment does not exist
	if (assignmentFound == false)
	{
		cout << "No such assignment" << endl;
		return;
	}
	
			//average calculation
	for (unsigned int i = 0; i < assignmentList.size(); i++)
	{
		assignmentTotal += assignmentList[i]->getEarnedPoints();
	}
	
	average = assignmentTotal / assignmentList.size();
	cout << "Assignment " << assignmentSelect << " average is: " << average << endl;
	return;
}

// Major driving function behind file system
void Course::save(string studentName, string newItem, double numPoints, saveType addItem) {

	string line;
	ifstream file("courses.txt");
	ofstream temp("temp.txt");
	vector<string> fileContent;
	string reset = newItem;

	string points = to_string(numPoints);
	points.erase(points.end() - 4, points.end());

	// Reads file content into string vector
	while (getline(file, line)) 
	{
		fileContent.push_back(line);
	}

	// Add course if no content
	if (fileContent.size() == 0 && addItem == courseSave)
	{

		vector<string>::iterator it = fileContent.begin();

		fileContent.insert(it, newItem.insert(0, tag(addItem)));		
	}

	else if (fileContent.size() == 0 && addItem != courseSave)
	{
		cout << "Please add a course first" << endl;
		return;
	}

	else 
	{

		for (unsigned int i = 0; i < fileContent.size(); i++)
		{

			vector<string>::iterator it = fileContent.begin() + i;
			newItem = reset;

			// Saves using different method based on type of data
			if (addItem == courseSave)
			{
				fileContent.insert(it, newItem.insert(0, tag(addItem)));
				break;
			}

			if (addItem == studentSave)
			{
				if (it->substr(1, it->back()) == courseName)
				{
					fileContent.insert(it + 1, newItem.insert(0, tag(addItem)));
					break;
				}
			}

			if (addItem == assignmentSave)
			{
				if (it->substr(0, courseName.size()) == courseName && it->at(courseName.size()) == '$') 
				{
					fileContent.insert(it + 1, newItem.insert(0, tag(addItem)));
				}
			}

			if (addItem == masterAssignmentSave)
			{
				if (it->substr(1, it->back()) == courseName) 
				{
					newItem.insert(0, tag(addItem));
					newItem.append(" ");

					newItem.append(points);
					fileContent.insert(it + 1, newItem);
				}
			}

			if (addItem == gradeSave)
			{
				if (fileContent[i].length() >= courseName.length() && (fileContent[i].substr(courseName.size() + 1, fileContent[i].back()) == studentName))
				{
					it++;
					int counter = 0;

					while (it != fileContent.end() && it->at(courseName.size()) != '$')
					{
						if (it->substr(courseName.size() + 1, newItem.size()) == newItem)
						{
							if (it->size() >= courseName.length() + newItem.length() + 3 && isdigit(it->at(courseName.length() + newItem.length() + 3)))
							{
								it->erase(courseName.length() + newItem.length() + 3, it->back());
								cout << "Existing grade overwritten" << endl;
								it->append(" ");
								it->append(to_string(numPoints));
							}

							else {
								it->append(" ");
								it->append(to_string(numPoints));
							}
						}

						it++;
						counter++;
					}

					i += counter;
				}
			}
		}
	}

	vector<string>::iterator write;

	// Writes data to new file
	for (write = fileContent.begin(); write != fileContent.end(); write++)
	{
		temp << *write << endl;
	}

	file.close();
	temp.close();

	remove("courses.txt");
	rename("temp.txt", "courses.txt");	
}

//adds all of the assignments in a course to each student
void Course::refresh() {
	studentList.front()->addStudentAssignment(assignmentList.front());
}

//Prints students and assignments in a course
void Course::print() 
{

	cout << courseName << endl;
	
	cout << "Students:" << endl;
	for (unsigned int i = 0; i < studentList.size(); i++) {
		if (studentList[i] == studentList.back()) 
		{
			cout << studentList[i]->getFirstName() << " " << studentList[i]->getLastName() << endl;

		}
		else
		{
			cout << studentList[i]->getFirstName() << " " << studentList[i]->getLastName() << ", ";
		}
	}	

	cout << "Assignments:" << endl;
	for (unsigned int i = 0; i < assignmentList.size(); i++)
	{
		if (assignmentList[i] == assignmentList.back())
		{
			cout << assignmentList[i]->getAssignmentName() << ": " << assignmentList[i]->getPossiblePoints() << endl;
		}
		else
		{
			cout << assignmentList[i]->getAssignmentName() << ": " << assignmentList[i]->getPossiblePoints() << ", ";
		}
	}

	cout << endl;
}

void Course::courseMenu()
{	
	string menuChoice;

	while (true) 
	{
		cout << "What would you like to do in " << courseName << "?" << endl;
		cout << "1. Grade Assignment" << endl;
		cout << "2. New assignment" << endl;
		cout << "3. Add student(s)" << endl;
		cout << "4. View assignment score for student" << endl;
		cout << "5. View assignment score for all students" << endl;
		cout << "6. View average for student" << endl;
		cout << "7. View average for all students" << endl;
		cout << "8. Print course" << endl;
		cout << endl;
		cout << "Enter 'm' to return to main menu" << endl;

		getline(cin, menuChoice);

		if (menuChoice == "1")
		{
			gradeAssignment();
		}

		if (menuChoice == "2")
		{
			addAssignment();
		}

		if (menuChoice == "3")
		{
			addStudent();
		}

		if (menuChoice == "4")
		{
			showStudentGrade();
		}

		if (menuChoice == "5")
		{
			showAllStudentGrades();
		}

		if (menuChoice == "6") 
		{
			showStudentAverage();
		}				

		if (menuChoice == "7")
		{
			showAllStudentAverages();
		}

		if (menuChoice == "8")
		{
			print();
		}

		if (menuChoice == "m")
		{
			break;
		}
	}
}

std::vector<Student*> Course::studentAlphaSort() {
	vector<Student*> alphaSort = studentList;
	std::string a;
	std::string b;
	//sorts students alphabetically by last name
	for (unsigned int i = 0; i < studentList.size() - 1; i++)
	{
		for (unsigned int j = 0; j < alphaSort.size() - i - 1; j++) 
		{
			a = alphaSort[j]->getLastName();
			b = alphaSort[j + 1]->getLastName();
			for (unsigned int k = 0; k < a.size(); k++)
			{
				if (a[k] > b[k]) 
				{
					iter_swap(alphaSort.begin() + j, alphaSort.begin() + j + 1);
				}
				else if (a[k] == b[k]) 
				{
					continue;
				}
				else 
				{
					break;
				}
			}

		}
	}

	return alphaSort;
}