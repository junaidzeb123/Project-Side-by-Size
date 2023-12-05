#pragma once
#include<cmath>
#include"BigInt.h"

class Machine_Node;
class Files {
public:
	int id;
	std::string name;
	std::string content;
	Files()
	{
		id = 0;
		name = "NotAssigned.txt";
		content = "";
	}
};

class RoutingTable_Node {
public:
	int index;
	int nextMachineID;
	Machine_Node* nextMachineAddress;
	RoutingTable_Node* next;
	RoutingTable_Node* previous;

	RoutingTable_Node()
	{
		index = 0;
		nextMachineID = 0;
		nextMachineAddress = nullptr;
		next = nullptr;
		previous = nullptr;
	}
	RoutingTable_Node(int i, int ni, Machine_Node* ptr)
	{
		index = i;
		nextMachineID = ni;
		nextMachineAddress = ptr;
		next = nullptr;
		previous = nullptr;
	}
};

class RoutingTable {
public:
	RoutingTable_Node* Head;
	int count;
	RoutingTable()
	{
		Head = nullptr;
		count = 1;
	}

	void AddNode(Machine_Node* ptr)
	{
		RoutingTable_Node* newNode = new RoutingTable_Node;
		newNode->index = count;
		//newNode->nextMachineID = ptr->ID;
		newNode->nextMachineAddress = ptr;

		if (Head == nullptr)
			Head = newNode;
		else
		{
			RoutingTable_Node* temp = Head;
			while (temp->next)
				temp = temp->next;
			temp->next = newNode;
			newNode->previous = temp;
		}
		count++;
	}

};

class Machine_Node {
public:
	Bigint_160 ID;
	Machine_Node* next;
	RoutingTable* FT;
	Files* root;

	Machine_Node() {
		next = nullptr;
		FT = new RoutingTable;
		root = nullptr;
	}
	Machine_Node(Bigint_160 id) {
		ID = id;
		next = nullptr;
		FT = new RoutingTable;
		root = nullptr;
	}
};

class Machine_list {
public:
	Machine_Node* Head;
	Bigint_160 count("0");
	int Total_no_of_bits;//    i.e 160
	int no_of_bits_used;//		i.e 2^4

	Machine_list() {
		Head = nullptr;
		Total_no_of_bits = 0;
		no_of_bits_used = 0;
	}
	Machine_list(int total, int used)
	{
		Head = nullptr;
		Total_no_of_bits = total;
		no_of_bits_used = used;
	}
	
	void AddMachine(Bigint_160 ID) {
		Machine_Node* newNode = new Machine_Node(ID);

		if (!Head) {
			Head = newNode;
			Head->next = Head;
		}
		else {
			if (newNode->ID < Head->ID) {
				Machine_Node* last = Head;
				while (last->next != Head) {
					last = last->next;
				}
				last->next = newNode;
				newNode->next = Head;
				Head = newNode;
			}
			else {
				Machine_Node* current = Head;
				while (current->next != Head && current->next->ID < newNode->ID)
				{
					current = current->next;
				}

				newNode->next = current->next;
				current->next = newNode;
			}
		}
		count++;
	}
	

	void Diaplay()
	{
		Machine_Node* temp = Head;
		//cout << temp->ID << "->";
		temp = temp->next;
		while (temp != Head)
		{
			//cout << temp->ID << temp->FT->count << "->";
			temp = temp->next;
		}
	}

};

