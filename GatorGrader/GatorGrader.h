#include <string>
#include <vector>
#include <fstream>

class Assignment {

private:
	std::string assignmentName;
	double points;

public:
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
	Course(std::string name);
	void setCourseName(std::string name);
	std::string getCourseName();
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