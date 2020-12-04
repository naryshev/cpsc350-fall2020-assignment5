/*
Daniel Naryshev
2327209
dnaryshev@chapman.edu

Eshaan Vora
2318955
evora@chapman.edu

Assignment 5 - Student DB
*/
#include "Menu.h"

using namespace std;

Menu::Menu()
{
	// file io
	struct stat buffer;
	if (stat (StuTable.c_str(), &buffer) == 0)
	{
			studentBST.loadFromFile(StuTable);
	}
	if (stat (FacTable.c_str(), &buffer) == 0)
	{
			facultyBST.loadFromFile(FacTable);
	}
}

Menu::~Menu()
{

}

bool Menu::isMalformed(string input)
{
	for (int i=0; i<input.size(); ++i)
	{
		if (!isdigit(input[i]))
		{
			return true;
		}
	}
	return false;
}

void Menu::printMenu()
{
	cout << "Student Database Menu:" << endl;
	cout << 1 << "Print all student info (by ascending id)" << endl;
	cout << 2 << "Print all faculty info (by ascending id)" << endl;
	cout << 3 << "Print student info given student id" << endl;
	cout << 4 << "Print faculty info given faculty id" << endl;
	cout << 5 << "Print info of student's faculty advisor given student id" << endl;
	cout << 6 << "Print all advisees of a faculty member given faculty" << endl;
	cout << 7 << "Add a new student" << endl;
	cout << 8 << "Delete a student given the id" << endl;
	cout << 9 << "Add a new faculty member" << endl;
	cout << 10 << "Delete a faculty member given the id" << endl;
	cout << 11 << "Change a student's advisor" << endl;
	cout << 12 << "Remove an advisee from a faculty member" << endl;
	cout << 13 << "Rollback" << endl;
	cout << 14 << "Exit" << endl;
	cout << "--- \n" << endl;
	cout << "Enter an option: ";
}

void Menu::promptOptions()
{
	string inputStr;
	int inputNum;
	printMenu();
	while (true)
	{
		cin >> inputStr;
		if (isMalformed(inputStr))
		{
			cout << "Malformed int. Try again: ";
			continue;
		}

		inputNum = atoi(inputStr.c_str());
		cout << "---Option " << inputNum << "---" << endl;
		switch (inputNum)
		{
			case 1:
				printAllStudents();
				break;
			case 2:
				printAllFaculty();
				break;
			case 3:
				printStudent();
				break;
			case 4:
				printFacultyMember();
				break;
			case 5:
				printAdvisor();
				break;
			case 6:
				printAdvisees();
				break;
			case 7:
				addStudent();
				break;
			case 8:
				deleteStudent();
				break;
			case 9:
				addFacultyMember();
				break;
			case 10:
				deleteFacultyMember();
				break;
			case 11:
				changeAdvisor();
				break;
			case 12:
				removeAdvisee();
				break;
			case 13:
				rollback();
				break;
			case 14:
				exit();
				return;
			default:
				cout << "Invalid option. Try again: ";
				continue;
		}
		printMenu();
	}
}

void Menu::printAllStudents()
{
	if (!studentBST.isEmpty())
		studentBST.printTree();
	else
		cout << "ERROR. Student table is empty." << endl;
}

void Menu::printAllFaculty()
{
	if (!facultyBST.isEmpty())
		facultyBST.printTree();
	else
		cout << "ERROR. Faculty table is empty." << endl;
}

int Menu::promptInt(string promptMsg)
{
	string input;
	cout << promptMsg;
	while (true)
	{
		getline(cin, input);
		if (!input.empty())
		{
			if (isMalformed(input))
				cout << "Malformed int. Try again: ";
			else
				break;
		}

		else
			cout << "ERROR. Input field empty. Try again: ";
	}
	return atoi(input.c_str());
}

void Menu::printStudent()
{
	if (!studentBST.isEmpty())
	{
		int inputNum = promptInt("Enter student ID: ");
		printStudentInfo(inputNum);
	}
	else
		cout << "ERROR. Student table empty. Add a student before printing its info." << endl;
}

void Menu::printStudentInfo(int studentID)
{
	Student sr(studentID);
	if (studentBST.contains(sr))
		studentBST.printNode(sr);
	else
		cout << "ERROR. Student ID#" << studentID << " not found." << endl;
}

void Menu::printFacultyMember()
{
	if (!facultyBST.isEmpty())
	{
		int inputNum = promptInt("Enter faculty ID: ");
		printFacultyInfo(inputNum);
	}
	else
		cout << "ERROR. Faculty table empty. Add a faculty member before printing its info." << endl;
}

void Menu::printFacultyInfo(int facultyID)
{
	Faculty fr(facultyID);
	if (facultyBST.contains(fr))
		facultyBST.printNode(fr);
	else
		cout << "ERROR. Faculty ID#" << facultyID << " not found." << endl;
}

void Menu::printAdvisor()
{
	if (!studentBST.isEmpty())
	{
		int studentID = promptInt("Enter student ID: ");
		Student sr(studentID);
		Student val = studentBST.find(sr);
		if (val.id >= 0)
		{
			if (val.advisorId < 0)
				cout << val.name << " has no faculty advisor." << endl;
			else
				printFacultyInfo(val.advisorId);
		}
		else
			cout << "ERROR. Student ID#" << studentID << " not found." << endl;
	}
	else
		cout << "ERROR. Student table empty. Add a student before printing its info." << endl;
}

void Menu::printAdvisees()
{
	if (!facultyBST.isEmpty())
	{
		int facultyID = promptInt("Enter faculty ID: ");
		Faculty fr(facultyID);
		Faculty val = facultyBST.find(fr);
		if (val.id >= 0)
		{
			ListNode<int> *node = val.adviseeIds->head;
			if (node != NULL)
			{
				while (true)
				{
					Student sr;
					sr.id = node->data;
					Student stud = studentBST.find(sr);
					cout << stud.name << endl;
					if (node->next == NULL)
						break;
					else
						node = node->next;
				}
			}
			else
				cout << "ERROR. " << val.name << " has no advisees.";
		}
		else
			cout << "ERROR. Faculty ID#" << facultyID << " not found." << endl;
	}
	else
		cout << "ERROR. Faculty table empty. Add a faculty member before printing its info." << endl;
}

void Menu::promptString(string promptMsg, string &input, bool nonEmpty)
{
	cout << promptMsg;
	while (true)
	{
		getline(cin, input);
		if (nonEmpty && input.empty())
			cout << "ERROR. Input field empty. Try again: ";
		else
			break;
	}
}

bool Menu::isMalformedDouble(string input)
{
	bool hasPoint = false;
	if (input.size() == 1 && !isdigit(input[0]))
		return true;
	if (input[input.size()-1] == '.')
		return true;
	for (int i=0; i<input.size()-1; ++i)
	{
		if (input[i] == '.')
		{
			if (hasPoint)
				return true;
			else
				hasPoint = true;
		}
		else if(!isdigit(input[i]))
			return true;
	}
	return false;
}

void Menu::addStudent()
{
	string hack;
	getline(cin, hack);

	int id = promptInt("Enter student id: ");

	string promptMsg = "Enter student name: ";
	string name;
	promptString(promptMsg, name, true);

	promptMsg = "Enter student level: ";
	string level;
	promptString(promptMsg, level, true);

	promptMsg = "Enter student major: ";
	string major;
	promptString(promptMsg, major, true);

	promptMsg = "Enter student GPA: ";
	double gpa;
	cout << promptMsg;
	while (true)
	{
		string sgpa;
		getline(cin, sgpa);
		if (sgpa.empty())
		{
			cout << "ERROR. Input field empty. Try again: ";
			continue;
		}
		else
		{
			gpa = atof(sgpa.c_str());
			break;
		}
	}

	cout << "Press [Enter] to skip adding an advisor ID." << endl;
	promptMsg = "Enter advisor ID: ";
	string advisorId;
	int advisorIdNum;
	promptString(promptMsg, advisorId, false);
	if (advisorId.empty())
		advisorIdNum = -1;
	else
		advisorIdNum = atoi(advisorId.c_str());

	Student sr(id, name, level, major, gpa, advisorIdNum);
	if (studentBST.contains(sr))
	{
		cout << "ERROR. Student ID " << id << " already exists." << endl;
		return;
	}

	Faculty fr(advisorIdNum);
	if (advisorIdNum == -1 || facultyBST.contains(fr))
		studentBST.insert(sr);
	else
		cout << "Advisor ID " << advisorId << " does not exist." << endl;
}

void Menu::deleteStudent()
{
	if (studentBST.isEmpty())
	{
		cout << "ERROR. Student table empty. Please add a student before printing its info." << endl;
		return;
	}

	int id = promptInt("Enter student id: ");

	Student sr(id);
	if (studentBST.contains(sr))
	{
		Faculty fr;
		fr.addAdviseeID(id);
		bool successful = facultyBST.removeStudentId(id);

		if (!successful)
			studentBST.deleteNode(sr);
		else
			cout << "ERROR. Student already has an advisor. Please change or remove student's advisor before deleting the student." << endl;
	}
	else
		cout << "ERROR. Student ID#" << id << " does not exist." << endl;
}

void Menu::addFacultyMember()
{

	int id = promptInt("Enter faculty id: ");

	string promptMsg = "Enter faculty name: ";
	string name;
	promptString(promptMsg, name, true);

	promptMsg = "Enter faculty level: ";
	string level;
	promptString(promptMsg, level, true);

	promptMsg = "Enter faculty department: ";
	string department;
	promptString(promptMsg, department, true);

	Faculty fr(id, name, level, department);


	cout << "Enter a single advisee ID and press [Enter] to add it." << endl;
	cout << "When you are finished adding IDs, type /done and press [Enter]" << endl;
	promptMsg = "Enter advisee ID: ";
	string input;
	cout << promptMsg;
	while (true)
	{
		getline(cin, input);
		getline(cin, input);

		if (input.empty())
			cout << "ERROR. Input field is empty. Try again: ";
		else if (input == "/done")
			break;
		else if (!isMalformed(input))
		{
			int idNum = atoi(input.c_str());
			fr.addAdviseeID(idNum);
			cout<<promptMsg;
		}
		else
			cout << "ERROR. Malformed int. Try again: ";
	}
	facultyBST.insert(fr);
}

void Menu::deleteFacultyMember()
{
	if (facultyBST.isEmpty())
	{
		cout << "ERROR. Faculty table empty. Add a faculty member before printing its info." << endl;
		return;
	}


	int id = promptInt("Enter faculty id: ");

	Faculty fr(id);
	Faculty found = facultyBST.find(fr);
	if (found.id != -1)
	{

		if (found.hasNoAdvisees())
			facultyBST.deleteNode(found);
		else
			cout << "ERROR. Faculty ID#" << id << " has advisees. Remove advisees before deleting faculty member." << endl;
	}
	else
		cout << "ERROR. Faculty ID#" << id << " does not exist." << endl;
}

void Menu::changeAdvisor()
{
	//add functionality
}

void Menu::removeAdvisee()
{
	//add functionality
}

void Menu::rollback()
{
	//add functionality
}

void Menu::exit()
{
	cout << "Exiting..." << endl;
}
