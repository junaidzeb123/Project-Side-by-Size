#pragma once
#include<iostream>
#include<string>
#include <fstream>
#include<cmath>
using namespace std;
struct Node {
	int location;
	Node* next;
	Node* prev;
	Node* down;
	Node* up;
	int estimatedCost;
	int actualCost;
	Node() {
		next = nullptr;
		prev = nullptr;
		down = nullptr;
		up = nullptr;
		location = -1;
		estimatedCost = -1;
		actualCost = -1;
	}
};
class Transport_Layer_optimization {
public:
	Node* MetroHead;
	Node* BusHead;
	Node* WalkHead;
	Transport_Layer_optimization();
	void ReadFile(string fileName);
	void HelperForReadFile(Node* Head, int* stations, int size);
	void HelperForUpandDown(Node* up, Node* down);
	void addNode(int layer, int Location_id);
	void DeleteNode(int layer, int Location_id);
	bool Helper1ForGetPath(Node* &startLocation, int start); // helper1 to getPath
	void HelperForGetPath2(Node*& currentLocation, int& layer, bool& downMovementOuter, string& path);
	string GetPath(int start, int end);
	string removeSubstringFromFormattedString(const string& formattedString, const string& substringToRemove);
	std::string removeLastArrow(const std::string& inputString);
	bool containsSubstring(const std::string& mainString, const std::string& substring) {
		return mainString.find(substring) != std::string::npos;
	}

};
Transport_Layer_optimization::Transport_Layer_optimization(){
	MetroHead = nullptr;
	BusHead = nullptr;
	WalkHead = nullptr;

}
void Transport_Layer_optimization::HelperForReadFile(Node* Head, int* stations, int size) {
	Node* temp = Head;
	temp->location = stations[0];
	for (int i = 1; i < size; i++) {
		temp->next = new Node;
		temp->next->location = stations[i];
		temp->next->prev = temp;
		temp = temp->next;
	}
}
void Transport_Layer_optimization::HelperForUpandDown(Node* up, Node* down) {
	while (up && down) {
		while (down->location <= up->location) {
			if (down->location == up->location) {
				up->down = down;
				down->up = up;
			}
			else {
				up->down = nullptr;
				down->up = nullptr;
			}
			down = down->next;
			if (!down)
				break;
		
		}
		up = up->next;
	
	}
}
void Transport_Layer_optimization::ReadFile(string fileName) {

	ifstream fin;
	fin.open(fileName);
	int n;
	fin >> n;
	int m;
	fin >> m;
	int q;
	fin >> q;

	int* metroStation = new int[n];
	int* BusStation = new int[m];
	int* WalkingStation = new int[q];
	for (int i = 0; i < n; i++) {
		fin >> metroStation[i];
	}
	for (int i = 0; i < m; i++) {
		fin >> BusStation[i];
	}
	for (int i = 0; i < q; i++) {
		fin >> WalkingStation[i];
	}
	

	MetroHead = new Node;
	Node* temp = MetroHead;	
;
	BusHead = new Node;
	HelperForReadFile(temp, metroStation, n);
	temp = BusHead;
	HelperForReadFile(temp, BusStation, m);
	WalkHead = new Node;
	temp = WalkHead;
	HelperForReadFile(temp, WalkingStation, q);
	/*code to link up down*/
	temp = MetroHead;
	HelperForUpandDown(MetroHead, BusHead);
	HelperForUpandDown(BusHead, WalkHead);
	//print();
	fin.close();
}
void Transport_Layer_optimization::addNode(int layer, int Location_id) {

	Node* temp = nullptr;
	if (layer == 1) {
		temp = MetroHead;
	}
	else if (layer == 2) {
		temp = BusHead;
	}
	else if (layer == 3) {
		temp = WalkHead;
	}

	Node* newNode = new Node();
	newNode->location = Location_id;
	if (temp == nullptr) {
		if (layer == 1) {
			 MetroHead = newNode;
		}
		else if (layer == 2) {
			 BusHead = newNode;
		}
		else if (layer == 3) {
			 WalkHead = newNode;
		}
		return;
	}
	while (temp->next) {
		if (Location_id <= temp->next->location)
			break;
		temp = temp->next;

	}
	
	newNode->prev = temp;
	newNode->next = temp->next;
	if (temp == MetroHead) {

	}
	if (!temp->next) {
		temp->next = newNode;
	}
	else {
		temp->next->prev = newNode;
		temp->next = newNode;
	}
	HelperForUpandDown(MetroHead, BusHead);
	HelperForUpandDown(BusHead, WalkHead);

}
void Transport_Layer_optimization::DeleteNode(int layer, int Location_id) {
	Node* temp = nullptr;
	if (layer == 1)
		temp = MetroHead;
	else if (layer == 2)
		temp = BusHead;
	else if (layer == 3)
		temp = WalkHead;
	while (temp->next) {
		if (Location_id == temp->location)
			break;
		temp = temp->next;
	}
	if (temp->next) {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}
	if (!temp->next) {
		temp->prev->next = temp->next;
		delete temp;
	}
	if (layer == 1)
		temp = MetroHead;
	else if (layer == 2)
		temp = BusHead;
	else if (layer == 3)
		temp = WalkHead;
	cout << temp->location << " ";
	while (temp->next) {
		cout << temp->next->location << " ";
		temp = temp->next;
	}
	cout << "\nin backward\n";
	while (temp) {
		cout << temp->location << " ";
		temp = temp->prev;
	}
	HelperForUpandDown(MetroHead, BusHead);
	HelperForUpandDown(BusHead, WalkHead);
	cout << "\n in delete node\n";
	//cout << temp->location << endl;
}
void Transport_Layer_optimization::HelperForGetPath2(Node*& currentLocation, int&layer,bool& downMovementOuter,string&path) {
	if (currentLocation->down) {
		downMovementOuter = true;
		string substring2 = to_string(currentLocation->location) + "-" + to_string(layer + 1);
		if (containsSubstring(path, substring2)) {
			substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
			path = removeSubstringFromFormattedString(path, substring2);
			currentLocation = currentLocation->down;
			layer++;
			substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
			if (!containsSubstring(path, substring2))
				path = removeSubstringFromFormattedString(path, substring2);
		}
		else {
			substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
			if (!containsSubstring(path, substring2))
				path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
			currentLocation = currentLocation->down;
			layer++;
			substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
			if (!containsSubstring(path, substring2))
				path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
		}
	}

}
bool Transport_Layer_optimization::Helper1ForGetPath(Node*&startLocation, int start) {
	while (startLocation) {
		if (start == startLocation->location) {
			return true;

		}
		startLocation = startLocation->next;
	}
	return false;
}
string Transport_Layer_optimization::GetPath(int start, int end) {
	Node* currentLocation = MetroHead;
	string path = "";
	bool isStartFound = false;
	bool isReachedEnd = false;
	// to temp in to starter node
	int layer = 1;
	if (!Helper1ForGetPath(currentLocation, start)) {
		currentLocation = BusHead;
		layer++;
		if (!Helper1ForGetPath(currentLocation, start)) {
			currentLocation = WalkHead;
			layer++;
			if (!Helper1ForGetPath(currentLocation, start)) {
				cout << "The starter station is not found\n";
				return " ";
			}
			else {
				path += to_string(start) + "-" + to_string(layer);
			}
		}
		else {
			path += to_string(start) + "-" + to_string(layer);

		}
	}
	else {
		path += to_string(start) + "-" + to_string(layer);

	}

	if (start == end)
		return path;
	bool downMovementOuter = true;
	bool downMovement = false;
	while (!isReachedEnd) {
		if (start < end) {
			if (currentLocation->up && !downMovementOuter) {
				currentLocation = currentLocation->up;
				layer--;
				downMovement = false;
				path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
			}
			if (currentLocation->down && !currentLocation->next) {
				HelperForGetPath2(currentLocation, layer, downMovementOuter, path);
				downMovement = true;
			}
			else if(!currentLocation->next){
				while (!currentLocation->down) {
					string substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
					if (containsSubstring(path, substring2)) {
						if(path != substring2)
						path = removeSubstringFromFormattedString(path, substring2);
					}
					else {
						path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
					}
					currentLocation = currentLocation->prev;
					 
						downMovement = false;
					HelperForGetPath2(currentLocation, layer, downMovement, path);
					
				}
			}
			while (currentLocation->next) {
				if (currentLocation->location == end) {
					isReachedEnd = true;
					break;
				}
				while(currentLocation->up && !downMovement) {
					layer--;
					currentLocation = currentLocation->up;
					path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
					downMovement = false;

				}
				if (currentLocation->next->location - currentLocation->location == 1 ) {
					currentLocation = currentLocation->next;
					path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
					downMovement = false;

				}
				else {
					
					if(currentLocation->down && (start < currentLocation->location))
					HelperForGetPath2(currentLocation, layer, downMovement, path);
					else {
						while (!currentLocation->down) {
							string substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
							if (containsSubstring(path, substring2)) {
								if (path != substring2)
									path = removeSubstringFromFormattedString(path, substring2);
							}
							else
								path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
							currentLocation = currentLocation->prev;

						}
						if(currentLocation->down)
							HelperForGetPath2(currentLocation, layer, downMovement, path);

					}

				}
				if (currentLocation->location == end) {
					isReachedEnd = 1;
					break;
				}
				//cout << "Path dlfjald= " << path << endl;
				
			}
		}
		else if(currentLocation->prev){
		
			while(currentLocation->up && !downMovement) {
				currentLocation = currentLocation->up;
				layer--;
				path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
			}
			if (currentLocation->location - currentLocation->prev->location == 1) {
				currentLocation = currentLocation->prev;
				downMovement = false;
				path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
			}
			else if (currentLocation->down  ) {
				currentLocation = currentLocation->down;
				layer++;
				downMovement = true;;
				path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
			}
			else {
				while (!currentLocation->down) {
					string substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
					if (containsSubstring(path, substring2))
					path = removeSubstringFromFormattedString(path, substring2);
					else
						path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
					currentLocation = currentLocation->next;
					if (currentLocation->down) {
						substring2 = to_string(currentLocation->location) + "-" + to_string(layer+1);
						if (containsSubstring(path, substring2)) {
							substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
							path = removeSubstringFromFormattedString(path, substring2);
						}
						
						currentLocation = currentLocation->down;
						downMovement = true;
						layer++;
						substring2 = to_string(currentLocation->location) + "-" + to_string(layer);
						if (!containsSubstring(path, substring2))
						path += " -> " + to_string(currentLocation->location) + "-" + to_string(layer);
						break;
					}

				}
			}
			if (currentLocation->location == end) {
				isReachedEnd = 1;
				break;
			}

		}


	}

	//cout << "Path = " << path << endl;
	return path;


}
std::string Transport_Layer_optimization:: removeLastArrow(const std::string& input) {
    std::string result = input;

    // Find the last occurrence of " -> " in the string
    size_t found = result.rfind(" -> ");

    // If " -> " is found at the end of the string, remove it
    if (found != std::string::npos && found == result.length() - 4) {
        result.erase(found);
    }

    return result;
}
string Transport_Layer_optimization:: removeSubstringFromFormattedString(const string& formattedString, const string& substringToRemove) {
	string result;
	size_t subLength = substringToRemove.length();
	size_t i = 0;

	while (i < formattedString.length()) {
		// Check if the substringToRemove matches the current position in the formattedString
		bool foundSubstring = true;
		for (int j = 0; j < subLength; ++j) {
			if (i + j >= formattedString.length() || formattedString[i + j] != substringToRemove[j]) {
				foundSubstring = false;
				break;
			}
		}

		// If we found the substring, skip it
		if (foundSubstring) {
			// Skip the substring and the arrow that follows it
			i += subLength + 4;
		}
		else {
			// Otherwise, add the current character to the result
			result += formattedString[i];
			++i;
		}
	}
	result = removeLastArrow(result);
	return result;
}




class Transport_Cost_Calculator {
public:
	Node* MetroHead;
	Node* BusHead;
	Node* WalkHead;
	int totalLocations;
	int UpDownCost;
	Transport_Cost_Calculator();
	void HelperForReadFile(Node* Head, int* stations, int size);
	void HelperForUpandDown(Node* up, Node* down);
	void ReadFile(string fileName);
	int GetMinCost(int start, int end);
	int manhattanDistance(int currnet, int destination) {
		return abs(destination - currnet);
	}
	int RecursizeHelper(Node* current, int end, bool upCheck, bool downCheck, int layer, int**& dpArray);
};
Transport_Cost_Calculator::Transport_Cost_Calculator() {
	MetroHead = nullptr;
	BusHead = nullptr;
	WalkHead = nullptr;
	UpDownCost = 5;
}
void Transport_Cost_Calculator::HelperForReadFile(Node* Head, int* stations, int size) {
	Node* temp = Head;
	temp->location = stations[0];
	for (int i = 1; i < size; i++) {
		temp->next = new Node;
		temp->next->location = stations[i];
		temp->next->prev = temp;
		temp = temp->next;
	}
}
void Transport_Cost_Calculator::HelperForUpandDown(Node* up, Node* down) {
	while (up && down) {
		while (down->location <= up->location) {
			if (down->location == up->location) {
				up->down = down;
				down->up = up;
			}
			else {
				up->down = nullptr;
				down->up = nullptr;
			}
			down = down->next;
			if (!down)
				break;

		}
		up = up->next;

	}
}
void Transport_Cost_Calculator::ReadFile(string fileName) {

	ifstream fin;
	fin.open(fileName);
	int n;
	fin >> n;
	totalLocations = n;
	int* Station = new int[n];
	for (int i = 0; i < n; i++) {
		Station[i] = i + 1;
	}
	MetroHead = new Node;
	Node* temp = MetroHead;
	BusHead = new Node;
	HelperForReadFile(temp, Station, n);
	temp = BusHead;
	HelperForReadFile(temp, Station, n);
	WalkHead = new Node;
	temp = WalkHead;
	HelperForReadFile(temp, Station, n);

	for (int i = 0; i < 3; i++) {
		if (i == 0)
			temp = MetroHead;
		else if (i == 1)
			temp = BusHead;
		else
			temp = WalkHead;
		for (int j = 0; j < n - 1; j++) {
			fin >> temp->actualCost;
			temp = temp->next;
		}
	}
	/*code to link up down*/
	temp = MetroHead;
	HelperForUpandDown(MetroHead, BusHead);
	HelperForUpandDown(BusHead, WalkHead);
	//print();
	fin.close();
}
int Transport_Cost_Calculator::RecursizeHelper(Node* current, int end, bool upCheck, bool downCheck, int layer, int**& dpArray) {

	int cost1 = -1;
	int cost2 = -1;
	int cost3 = -1;

	if (current->next) {
		if (current->next->location == end) {
			cost1 = current->actualCost;
			int c2;
			if (current->up) {
				c2 = current->up->actualCost + UpDownCost;
				if (cost1 > c2) {
					cost1 = c2;
				}
			}
			if (current->down) {
				c2 = current->down->actualCost + UpDownCost;
				if (cost1 > c2) {
					cost1 = c2;
				}
			}

		}
	}
	if (current->next) {
		if (current->next->location < end) {
			if (dpArray[layer - 1][current->next->location - 1] != -1) {
				cost1 = current->actualCost + dpArray[layer - 1][current->next->location - 1];
			}
			else {
				dpArray[layer - 1][current->next->location - 1] = RecursizeHelper(current->next, end, 1, 1, layer, dpArray);
				cost1 = current->actualCost + dpArray[layer - 1][current->next->location - 1];
			}
		}
	}
	if (current->down && downCheck) {
		if (dpArray[layer][current->down->location - 1] != -1) {
			cost2 = UpDownCost + dpArray[layer][current->down->location - 1];
		}
		else {
			dpArray[layer][current->down->location - 1] = RecursizeHelper(current->down, end, 0, 1, layer + 1, dpArray);
			cost2 = UpDownCost + dpArray[layer][current->down->location - 1];
		}
	}
	if (current->up && upCheck) {
		if (dpArray[layer - 2][current->up->location - 1] != -1) {
			cost3 = UpDownCost + dpArray[layer - 2][current->up->location - 1];
		}
		else {
			dpArray[layer - 2][current->up->location - 1] = RecursizeHelper(current->up, end, 1, 0, layer - 1, dpArray);
			cost3 = UpDownCost + dpArray[layer - 2][current->up->location - 1];
		}
	}
	int minCost = cost1;
	if ((minCost > cost2 || minCost == -1) && cost2 != -1)
		minCost = cost2;
	if ((minCost > cost3 || minCost == -1) && cost3 != -1)
		minCost = cost3;
	return minCost;

}
int Transport_Cost_Calculator::GetMinCost(int start, int end) {
	Node* currentLocation = MetroHead;
	if (start > end) {
		int temp = start;
		start = end;
		end = temp;

	}
	while (currentLocation->next) {
		if (currentLocation->location == start)
			break;
		currentLocation = currentLocation->next;
	}
	int layer = 1;
	int** dpArray = new int* [3];
	for (int i = 0; i < 3; i++) {
		dpArray[i] = new int[totalLocations];
		for (int j = 0; j < totalLocations; j++) {
			dpArray[i][j] = -1;
		}
	}

	int cost1 = RecursizeHelper(currentLocation, end, 1, 1, layer, dpArray);
	currentLocation = currentLocation->down;
	layer++;
	int cost2 = RecursizeHelper(currentLocation, end, 1, 1, layer, dpArray);
	currentLocation = currentLocation->down;
	layer++;
	int cost3 = RecursizeHelper(currentLocation, end, 1, 1, layer, dpArray);
	
	int minCost = cost1;
	if (minCost > cost2)
		minCost = cost2;
	if (minCost > cost3)
		minCost = cost3;

	return minCost;
}



