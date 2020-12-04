/*
Daniel Naryshev
2327209
dnaryshev@chapman.edu

Eshaan Vora
2318955
evora@chapman.edu

Assignment 5 - Student DB
*/
#include "BST.h"
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

//for file io
const string StuTable = "studentTable";
const string FacTable = "facultyTable";

class Menu
{
	private:
		StudentTable studentBST;
		FacultyTable facultyBST;
		bool isMalformed(string input);
		void printMenu();
		int promptInt(string promptMsg);
		void printStudentInfo(int studentId);
		void printFacultyInfo(int facultyId);
		bool isMalformedDouble(string input);
		void promptString(string promptMsg, string &input, bool nonEmpty);

	public:
		Menu();
		~Menu();
		void promptOptions();
		void printAllStudents();
		void printAllFaculty();
		void printStudent();
		void printFacultyMember();
		void printAdvisor();
		void printAdvisees();
		void addStudent();
		void deleteStudent();
		void addFacultyMember();
		void deleteFacultyMember();
		void changeAdvisor();
		void removeAdvisee();
		void rollback();
		void exit();
};
