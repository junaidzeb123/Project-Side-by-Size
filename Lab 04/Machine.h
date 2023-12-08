#pragma once
#include<cmath>
#include"BigInt.h"
using  std::string;
using  std::cout;
using  std::endl;
class Machine_Node;
class Files {
public:
	int id;
	string name;
	string content;
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
	Bigint_160 nextMachineID;
	Machine_Node* nextMachineAddress;
	RoutingTable_Node* next;
	RoutingTable_Node* previous;

	RoutingTable_Node()
	{
		index = 0;
		nextMachineAddress = nullptr;
		next = nullptr;
		previous = nullptr;
	}
	RoutingTable_Node(int i )
	{
		index = i;
		next = nullptr;	
		nextMachineAddress = nullptr;
		previous = nullptr;
	}
};

class RoutingTable {
public:
	RoutingTable_Node* Head;
	RoutingTable_Node* tail;
	int count;
	RoutingTable()
	{
		Head = nullptr;
		tail = nullptr;
		count = 1;
	}
	void AddNode()
	{
		RoutingTable_Node* newNode = new RoutingTable_Node(count);
		newNode->index = count;
		//newNode->nextMachineID = ptr->ID;
	//	newNode->nextMachineAddress = ptr;

		if (Head == nullptr) {
			Head = newNode;
			tail = newNode;
		}
		else
		{
			RoutingTable_Node* temp = Head;
			while (temp->next) {
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
			newNode->previous = temp;
			tail = newNode;
		}
		count++;
	}
	void Diaplay()
	{
		RoutingTable_Node* temp = Head;
		while (temp != nullptr)
		{
			cout<<"index " << temp->index << "\t";
			cout<<"nextmachineid\t" << temp->nextMachineAddress << "\n";
			temp = temp->next;
		}
		cout << endl;
	}
};
class Machine_Node {
public:
	Bigint_160 ID;
	Machine_Node* next;
	RoutingTable FT;
	Files* root;

	Machine_Node() {
		next = nullptr;
		root = nullptr;
	}
	Machine_Node(Bigint_160 id,int sizeofTables) {
		ID = id;
		next = nullptr;
		root = nullptr;
		for (int i = 0; i < sizeofTables; i++) {
			FT.AddNode();
		}
	}
};


class Machine_list {
	Machine_Node* Head;
	int count;// ("0");
	int no_of_bits_used;//		
	int sizeofTables;
public:

	Machine_list() {
		Head = nullptr;
		sizeofTables = 0;
		no_of_bits_used = 0;
	}
	Machine_list(int total, int used)
	{
		Head = nullptr;
		no_of_bits_used = used;
	}
	void mangesuccessors() {
		Machine_Node* temp = Head;
		while (temp->next != Head && temp != nullptr)
		{
			int i = 1;
			RoutingTable_Node* tableTemp = temp->FT.Head;
			while (tableTemp != nullptr)
			{
				unsigned long long int  decimalValue;
				std::stringstream ss(temp->ID.to_string());

				// Convert decimal string to integer
				ss >> decimalValue;
				unsigned long long int calculatedId = decimalValue + pow(2, i-1);
				Machine_Node* temp2 = temp->next;
				while (  temp2->ID.to_string() < std::to_string(calculatedId) && temp2->next != temp)
				{
					temp2 = temp2->next;
				}
				tableTemp->nextMachineAddress = temp2;
				tableTemp->nextMachineID = temp2->ID;
				tableTemp = tableTemp->next;
				i++;
				
			}
			temp = temp->next;
		}
	}
	void AddMachine(Bigint_160 ID) {
		Machine_Node* newNode = new Machine_Node(ID,sizeofTables);

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
		mangesuccessors();
	}

	void Diaplay()
	{
		Machine_Node* temp = Head;
		cout << temp->ID.to_string() << "\n";
		temp->FT.Diaplay();
		temp = temp->next;
		while (temp != Head)
		{
			cout << temp->ID.to_string() <<"\n";
			temp->FT.Diaplay();
			temp = temp->next;
		}
	}
	void setSizeofTables(int n) {
		sizeofTables = n;
	}
};

