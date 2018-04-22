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

//constructor
Course::Course(string name) {
	courseName = name;
}

//deconstructor
Course::~Course() {

	string line;

	//object of type ifstream created called file
	ifstream file("courses.txt");
	ofstream temp("temp.txt");
	
	//while loop to read in file, line by line
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

//mutator method to set name of course
void Course::setCourseName(string name) {
	courseName = name;
}

//accessor method to return name of course
string Course::getCourseName() {
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

string Course::tag(saveType type) {

	string tag;
	
	//# denotes a course in the text file
	if (type == courseSave) {
		tag = "#";
		return tag;
	}

	//$ denotes a student in the text file
	if (type == studentSave) {
		tag = getCourseName().append("$");
		return 	tag;
	}

	//@ denotes assignment in text file
	if (type == assignmentSave) {
		tag = getCourseName().append("@");
		return tag;
	}

	//& denotes assignment in text file
	if (type = masterAssignmentSave) {
		tag = getCourseName().append("&");
		return tag;
	}
}

//method to add a student
void Course::addStudent() {

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

//overloaded method to add a student
void Course::addStudent(string first, string last, string full) {

	Student *student = new Student(first, last, full);
	studentList.push_back(student);	
	return student;
}

//method to add an assignment
void Course::addAssignment() {	

	string newAssignmentName;
	string newAssignmentPoints;
	double points;

	cout << "Assignment Name:" << endl;
	getline(cin, newAssignmentName);
	
	cout << "Assignment points:" << endl;
	getline(cin, newAssignmentPoints);

	points = atof(newAssignmentPoints.c_str());

	Assignment *assignment = new Assignment(newAssignmentName, points);
	//adds assignment to vector assignmentList
	assignmentList.push_back(assignment);

	for (unsigned int i = 0; i < studentList.size(); i++) {
		studentList[i]->addStudentAssignment(assignment);
	}

	save("", newAssignmentName,points, assignmentSave);
	save("", newAssignmentName, points, masterAssignmentSave);

	cout << "Assignment '" << newAssignmentName << "' worth " << points << " points has been added to course " << courseName << endl;
}

//overloaded method to add assignment
void Course::addAssignment(string name, double points) {

	Assignment *assignment = new Assignment(name, points);

	//adds assignment to vector assignmentList
	assignmentList.push_back(assignment);

	for (unsigned int i = 0; i < studentList.size(); i++) {
		studentList[i]->addStudentAssignment(assignment);
	}
}

//method to grade assignment
void Course::gradeAssignment() {

	string whichAssignment;

	cout << "Which assignment would you like to grade?";

	getline(cin, whichAssignment);

	string oneOrAll;

	cout << "Would you like to grade an assignment for a single student or all students?" << endl;
	cout << "1. Single student" << endl;
	cout << "2. All students" << endl;

	getline(cin, oneOrAll);

	//grades a single student's assignment
	if (oneOrAll == "1") {
		string whichStudent;

		cout << "Which student would you like to grade?" << endl;

		getline(cin, whichStudent);
		
		bool studentFound = false;
		//searches for student
		for (unsigned int i = 0; i < studentList.size(); i++) {
			if (studentList[i]->getFullName() == whichStudent) {
				studentList[i]->gradeStudentAssignment(whichAssignment, this);
				studentFound = true;
				break;
			}
		}

		//student doesn't exist
		if (studentFound == false) {
			cout << "You have no student '" << whichStudent << "'" << endl;
			return;
		}		
	}

	//grade all students
	if (oneOrAll == "2") {
	//grade all students
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

	cout << "Which assignment would you like to grade?";
}

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

void Course::save(string studentName, string newItem, double numPoints, saveType addItem) {

	string line;
	ifstream file("courses.txt");
	ofstream temp("temp.txt");
	vector<string> fileContent;
	string reset = newItem;

	string points = to_string(numPoints);
	points.erase(points.end() - 4, points.end());

	while (getline(file, line)) {
		fileContent.push_back(line);
	}	

	for (unsigned int i = 0; i < fileContent.size(); i++) {

		vector<string>::iterator it = fileContent.begin() + i;
		newItem = reset;

		if (addItem == courseSave) {
			fileContent.insert(it, newItem.insert(0, tag(addItem)));
			break;
		}

		if (addItem == studentSave) {
			if (it->substr(1, it->back()) == courseName) {
				fileContent.insert(it + 1, newItem.insert(0, tag(addItem)));
				break;
			}
		}

		if (addItem == assignmentSave) {			
			if (it->substr(0, courseName.size()) == courseName && it->at(courseName.size()) == '$') {							
				fileContent.insert(it + 1, newItem.insert(0, tag(addItem)));
			}	
		}

		if (addItem == masterAssignmentSave) {
			if (it->substr(1, it->back()) == courseName) {
				newItem.insert(0, tag(addItem));
				newItem.append(" ");

				newItem.append(points);
				fileContent.insert(it + 1, newItem);
			}
		}

		if (addItem == gradeSave) {
			if ((fileContent[i].substr(courseName.size() + 1, fileContent[i].back()) == studentName) && ((it + 1)->substr(0, courseName.size()) == courseName && (it + 1)->at(courseName.size()) == '@')) {
				fileContent[i + 1].append(" ");
				fileContent[i + 1].append(points);
			}
		}
	}

	vector<string>::iterator write;

	for (write = fileContent.begin(); write != fileContent.end(); write++) {
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

//method to print course information
void Course::print() {

	cout << courseName << endl;

	//Sorts list Alphabetically
	studentList = studentAlphaSort();

	//prints all students in course
	cout << "Students:" << endl;
	for (unsigned int i = 0; i < studentList.size(); i++) {
		if (studentList[i] == studentList.back()) {
			cout << studentList[i]->getFirstName() << " " << studentList[i]->getLastName() << endl;

		}
		else {
			cout << studentList[i]->getFirstName() << " " << studentList[i]->getLastName() << ", ";
		}
	}	

	//prints all existing assignments in course
	cout << "Assignments:" << endl;
	for (unsigned int i = 0; i < assignmentList.size(); i++) {
		if (assignmentList[i] == assignmentList.back()) {
			cout << assignmentList[i]->getAssignmentName() << ": " << assignmentList[i]->getPossiblePoints() << endl;
		}
		else {
			cout << assignmentList[i]->getAssignmentName() << ": " << assignmentList[i]->getPossiblePoints() << ", ";
		}
	}

	cout << endl;
}

//method for instructor to choose how to manage course
void Course::courseMenu() {

	string menuChoice;

	cout << "What would you like to do in " << courseName << "?" << endl;
	cout << "1. Grade Assignment" << endl;
	cout << "2. New assignment" << endl;
	cout << "3. Add student(s)" << endl;
	cout << "4. View scores for student" << endl;
	cout << "5. Print course" << endl;

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
		print();
	}
}

//Alphabetical Sorter
std::vector<Student*> Course::studentAlphaSort() {

	vector<Student*> alphaSort = studentList;
	std::string a;
	std::string b;
	//sorts students alphabetically by last name
	for (unsigned int i = 0; i < studentList.size() - 1; i++) {
		for (unsigned int j = 0; j < alphaSort.size() - i - 1; j++) {
			a = alphaSort[j]->getLastName();
			b = alphaSort[j + 1]->getLastName();

			//for loop to go through next character if previous characters were the same
			for (unsigned int k = 0; k < a.size(); k++) {
				if (a[k] > b[k]) {
					iter_swap(alphaSort.begin() + j, alphaSort.begin() + j + 1);
				}
				else if (a[k] == b[k]) {
					continue;
				}
				else {
					break;
				}
			}

		}
	}
	return alphaSort;
}