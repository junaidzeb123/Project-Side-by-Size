#include"pch.h"
#include<iostream>
#include "BigIntt.h"
#include "DHT.h"
using std::cout;
using std::cin;
int main() {
	DHT dh;
	dh.machinesAndTablePrint();
	string id;
	cin >> id;
	while (id != "0") {
		dh.deleteMachine(id);
		dh.machinesAndTablePrint();
		cin >> id;
	}

}
//5 9 1 1 4 9 11 14 18 20 21 28
