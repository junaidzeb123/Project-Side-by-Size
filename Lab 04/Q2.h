#include <iostream>
class graph {
	bool** matrix;
	int size;
public:
	graph(int size) {
		this->size = size;
		matrix = new bool* [size];
		for (int i = 0; i < size; i++) {
			matrix[i] = new bool[size];
			for (int j = 0; j < size; j++) {
				matrix[i][j] = 0;
			}
		}
	}
	void addEdge(int src, int des) {
		matrix[src][des] = 1;
	}
	bool isEdge(int src, int des) {
		return matrix[src][des];
	}
	void removeEdge(int src, int des) {
		matrix[src][des] = 0;
	}
	void display() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
};
class Node
{
public:
	int data;
	Node*next;
	Node() {
		next = nullptr;
	}
	Node(int d) {
		data = d;
		next = nullptr;
	}
};

class AdjList {
public:
	Node* head;
	AdjList() {
		head = nullptr;
	}
	void insert(Node* newNode) {
		Node* temp = head;
		if (head) {
			head = newNode;
			return;
		}
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	/*Void Display() {
		Node* temp = head;
		while (temp){
			std::cout << temp->data << " ";
			temp = temp->next;
		}
	}*/
};

class Graph {
	int size;
	AdjList* list;
public:
	Graph(int size) {
		this->size = size;
		for (int i = 0; i < size; i++) {
			Node* newNode = new Node(i + 1);
			list->insert(newNode);
		}
	}
	void Graphdisplay() {

	}
};