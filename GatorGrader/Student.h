#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

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