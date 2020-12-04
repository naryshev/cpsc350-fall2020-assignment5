/*
Daniel Naryshev
2327209
dnaryshev@chapman.edu

Eshaan Vora
2318955
evora@chapman.edu

Assignment 5 - Student DB
*/
#include "Student.h"

using namespace std;

Student::Student()
{
		id = -1;
		name = "";
		level = "";
		major = "";
		gpa = -1.0;
		advisorId = -1;
}

Student::~Student()
{

}

Student::Student(int newID)
{
		id = newID;
		name = "";
		level = "";
		major = "";
		gpa = -1.0;
		advisorId = -1;
}

Student::Student(int newID, string newName, string newLevel, string newMajor, double newGPA, int newAdvisorID)
{
		id = newID;
		name = newName;
		level = newLevel;
		major = newMajor;
		gpa = newGPA;
		advisorId = newAdvisorID;
}

Student::Student(string serializedSr)
{
		deserialize(serializedSr);
}

string Student::serialize()
{
		ostringstream oss;
		oss << id << ',' + name + ',' + level + ',' + major + ',' << gpa << ',' << advisorId;
		return oss.str();
}

void Student::deserialize(string serializedSr)
{
		stringstream ss(serializedSr);
		string item;
		int count = 0;
		while (getline(ss, item, ','))
		{
			if (count == 0) id = atoi(item.c_str());
			else if (count == 1) name = item;
			else if (count == 2) level = item;
			else if (count == 3) major = item;
			else if (count == 4) gpa = atof(item.c_str());
			else if (count == 5) advisorId = atoi(item.c_str());
			count++;
		}
}
