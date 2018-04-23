#pragma once
//#include "Assignment.h"
//#include "Student.h"
//#include "Instructor.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Assignment;
class Student;

class Course {
private:
	std::string courseName;
	std::vector<Student*> studentList;
	std::vector<Assignment*> assignmentList;
	Student* currentStudent;
	Assignment* currentAssignment;
public:
	enum saveType {courseSave, studentSave, assignmentSave, masterAssignmentSave, gradeSave};
	Course(std::string name);
	~Course();
	void setCourseName(std::string name);
	std::string getCourseName();
	const vector<Student*>& getStudentList();
	const vector<Assignment*>& getAssignmentList();
	std::string tag(saveType type);
	void addStudent();
	void addStudent(std::string first, std::string last, std::string full);
	void save(std::string studentName, std::string newItem, double numPoints, saveType addItem);
	void addAssignment();
	void addAssignment(std::string name, double points);
	void gradeAssignment();
	void showStudentGrade();
	void showStudentAverage();
	void showAllStudentAverages();
	void print();
	void courseMenu();
	void refresh();
	std::vector<Student*> studentAlphaSort();
};