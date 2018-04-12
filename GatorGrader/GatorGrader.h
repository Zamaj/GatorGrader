#include <string>
#include <vector>
#include <fstream>

class Assignment {

private:
	std::string assignmentName;
	double assignmentPoints;
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
public:
	Student();
	Student(std::string first, std::string last);
	std::string getFirstName();
	std::string getLastName();
};

class Course {
private:
	std::string courseName;
	std::vector<Student*> studentList;
	std::vector<Assignment*> assignmentList;
public:
	Course(std::string name);
	void setCourseName(std::string name);
	std::string getCourseName();
	void showCourseOptions();
	void addStudent();
	void addStudent(std::string first, std::string last);
	void addAssignment();
	void addAssignment(std::string name, double points);
	void print();
	void courseMenu();
};

class Instructor {
private:
	std::string instructorName;	
	std::vector<Course*> courseList;
public:
	//ifstream file;
	Course * currentCourse;	
	Instructor();
	Instructor(std::string name);
	void setName(std::string name);
	std::string getName();
	std::vector<Course*> &getCourseList();
	void firstTimeInstructor();
	void addCourse();
	void addCourse(std::string name);
	void removeCourse();
	void mainMenu();
	void init();
};