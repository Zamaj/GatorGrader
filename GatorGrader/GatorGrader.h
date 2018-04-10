#include <string>
#include <vector>
#include <fstream>

class Assignment {

private:
	std::string assignmentName;
	double points;
public:
	Assignment(std::string name, double points);
	void setAssignmentName();
	std::string getAssignmentName();
	void setPoints();
	double getPoints();
};

class Student {
private:
	std::string firstName;
	std::string lastName;
};

class Course {
private:
	std::string courseName;
public:
	std::vector<std::string> students;
	std::vector<Assignment*> assignments;
	Course(std::string name);
	void setCourseName(std::string name);
	std::string getCourseName();
	void courseOptions();
	void addStudent();
	void addAssignment();
};

class Instructor {
private:
	std::string name;	
public:
	//ifstream courseData;
	Course * currentCourse;
	std::vector<Course*> courseList;
	Instructor();
	Instructor(std::string name);
	void setName(std::string name);
	std::string getName();
	void firstTimeInstructor();
	void addCourse();
	void menu();
};