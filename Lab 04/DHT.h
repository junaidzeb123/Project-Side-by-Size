#pragma once
#include"Machine.h"
#include "BigInt.h"
#include "sha1.hpp"
#include <string>
#include <iostream>
using  std::string;
using  std::cout;
using  std::cin;
using  std::endl;
#ifndef DHT_H
#define DHT_H


class DHT {
	Machine_list machines;
    int sizeofSpace = 0;
    int noofMachines = 0;
public:
	DHT() {
         string name = "";
        int choice = 0;

         cout << "\t\t\tWELLCOME TO INTERPLANETARY FILE SYSTEM\n";
         cout << "Please enter the size of identifier space you want to add\n";
         cin >> sizeofSpace;
        while (sizeofSpace <= 0) {
             cout << "please enter a positive size of bit Space\n";
             cin >> sizeofSpace;
        }

         cout << "enter the no of machines you want to add\n";
         cin >> noofMachines;
        while (noofMachines <= 0) {
             cout << "please enter a positive szieofSpace\n";
             cin >> noofMachines;
        }

         cout << "Do you want to give ids  or names  to each machine\n";
         cout << "1.Ids\n";
         cout << "2.Names\n";
         cin >> choice;
        while (choice != 1 && choice != 2) {
             cout << "Enter a valid choice\n";
             cin >> choice;
        }

        if (choice == 1) {
            Bigint_160*idsArry = new Bigint_160[noofMachines];
            for (int i = 0; i < noofMachines; i++) {
                bool repeated = false;
                 cout << "Please enter the id of machine " << i +1<< " \n";
                Bigint_160 ids;
                 cin >> ids;

                for (int j = 0; j < i; j++) {
                    if (idsArry[j] == ids) {
                         cout << "This machine name is already assigned to an another machines\n";
                         cout << "Pleae assign unique name to each machine\n";
                         cout << "Pleae enter the name againt";
                        repeated = true;
                        break;
                    }
                }

                if (repeated) {
                    i--;
                    continue;
                }
                idsArry[i] = ids;

                machines.AddMachine(ids);
            }
            delete[] idsArry;
        }
        else {
             string* names = new  string[noofMachines];
            for (int i = 0; i < noofMachines; i++) {
                bool repeated = false;
                 cout << "Please enter the name of machine " << i+1 << " \n";
                 string name;
                 cin >> name;

                for (int j = 0; j < i; j++) {
                    if (names[j] == name) {
                         cout << "This machine name is already assigned to an another machines\n";
                         cout << "Pleae assign unique name to each machine\n";
                         cout << "Pleae enter the name againt";
                        repeated = true;
                        break;
                    }
                }

                if (repeated) {
                    i--;
                    continue;
                }

                names[i] = name;
                SHA1 checksum;
                checksum.update(name);
                string hashedId = checksum.final();
                Bigint_160 ids(hashedId);
                ids = ids % sizeofSpace;
                machines.AddMachine(ids);
            }
            delete[]names;
        }
	}
};
#endif 