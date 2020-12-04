/*
Daniel Naryshev
2327209
dnaryshev@chapman.edu

Eshaan Vora
2318955
evora@chapman.edu

Assignment 5 - Student DB
*/
#include "Faculty.h"

using namespace std;

Faculty::Faculty()
{
	id = -1;
	name = "";
	level = "";
	department = "";
	adviseeIds = new LinkedList<int>();
}

Faculty::~Faculty()
{
	delete adviseeIds;
}

Faculty::Faculty(int newID)
{
	id = newID;
	name = "";
	level = "";
	department = "";
	adviseeIds = new LinkedList<int>();
}

Faculty::Faculty(int newID, string newName, string newLevel, string newDepartment)
{
	id = newID;
	name = newName;
	level = newLevel;
	department = newDepartment;
	adviseeIds = new LinkedList<int>();
}

Faculty::Faculty(string serializedFr)
{
	adviseeIds = new LinkedList<int>();
	deserialize(serializedFr);
}

string Faculty::serialize()
{
	ostringstream oss;
	oss << id << ',' + name + ',' + level + ',' + department + ',';
	ListNode<int> *node = adviseeIds->head;
	if (node != NULL) {
		while (true) {
			oss << node->data;
			if (node->next == NULL)
				break;
			else
			{
				oss <<',';
				node = node->next;
			}
		}
	}
	else
		oss<<'-';
	return oss.str();
}

void Faculty::deserialize(string serializedFr)
{
	stringstream ss(serializedFr);
	string item;
	int count = 0;
	while (getline(ss, item, ','))
	 {
		if (count == 0)
			id = atoi(item.c_str());
		else if
			(count == 1) name = item;
		else if
			(count == 2) level = item;
		else if
			(count == 3) department = item;
		else if
			(count >= 4) addAdviseeID(atoi(item.c_str()));
		count++;
	}
}

void Faculty::addAdviseeID(int id)
{
	adviseeIds->insertBack(id);
}

int Faculty::removeAdviseeID(int id)
{
	return adviseeIds->remove(id);
}

bool Faculty::containsAdviseeID(int id)
{
	return (adviseeIds->contains(id));
}

bool Faculty::hasNoAdvisees()
{
	return (adviseeIds->isEmpty());
}
