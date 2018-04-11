#include <string>
#include <vector>
#include <fstream>

class Assignment {

private:
	std::string assignmentName;
<<<<<<< HEAD
	double pointsEarned;
	double pointsPossible;
=======
	double assignmentPoints;
>>>>>>> 8ee4712fe1fefad52ebe8d3627c25459733d14d0
public:
	Assignment(std::string name, double points);
	void setAssignmentName(std::string name);
	std::string getAssignmentName();
	void setPointsPossible(double points);
	double getPointsPossible();
	void setPointsEarned(double points);
	double getPointsEarned();
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
};

class Instructor {
private:
	std::string name;	
	std::vector<Course*> courseList;
public:
	//ifstream courseData;
	Course * currentCourse;	
	Instructor();
	Instructor(std::string name);
	void setName(std::string name);
	std::string getName();
	std::vector<Course*> &getCourseList();
	void firstTimeInstructor();
	void addCourse();
	void addCourse(std::string name);
	void menu();
};