#pragma once
#include"Machine.h"
#include "BigInt.h"

#ifndef DHT_H
#define DHT_H
std::string hashFunction(std::string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return (std::to_string(hash_value));
}

class DHT {
	Machine_list machines;
    int sizeofSpace = 0;
    int noofMachines = 0;
public:
	DHT() {
        std::string name = "";
        int choice = 0;

        std::cout << "\t\t\tWELLCOME TO INTERPLANETARY FILE SYSTEM\n";
        std::cout << "Please enter the size of identifier space you want to add\n";
        std::cin >> sizeofSpace;
        while (sizeofSpace <= 0) {
            std::cout << "please enter a positive size of bit Space\n";
            std::cin >> sizeofSpace;
        }

        std::cout << "enter the no of machines you want to add\n";
        std::cin >> noofMachines;
        while (noofMachines <= 0) {
            std::cout << "please enter a positive szieofSpace\n";
            std::cin >> noofMachines;
        }

        std::cout << "Do you want to give ids  or names  to each machine\n";
        std::cout << "1.Ids\n";
        std::cout << "2.Names\n";
        std::cin >> choice;
        while (choice != 1 && choice != 2) {
            std::cout << "Enter a valid choice\n";
            std::cin >> choice;
        }

        if (choice == 1) {
            Bigint_160*idsArry = new Bigint_160[noofMachines];
            for (int i = 0; i < noofMachines; i++) {
                bool repeated = false;
                std::cout << "Please enter the id of machine " << i +1<< " \n";
                Bigint_160 ids;
                std::cin >> ids;

                for (int j = 0; j < i; j++) {
                    if (idsArry[j] == ids) {
                        std::cout << "This machine name is already assigned to an another machines\n";
                        std::cout << "Pleae assign unique name to each machine\n";
                        std::cout << "Pleae enter the name againt";
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
            std::string* names = new std::string[noofMachines];
            for (int i = 0; i < noofMachines; i++) {
                bool repeated = false;
                std::cout << "Please enter the name of machine " << i+1 << " \n";
                std::string name;
                std::cin >> name;

                for (int j = 0; j < i; j++) {
                    if (names[j] == name) {
                        std::cout << "This machine name is already assigned to an another machines\n";
                        std::cout << "Pleae assign unique name to each machine\n";
                        std::cout << "Pleae enter the name againt";
                        repeated = true;
                        break;
                    }
                }

                if (repeated) {
                    i--;
                    continue;
                }
                names[i] = name;
                std::string hashedId = hashFunction(name);
                Bigint_160 ids(hashedId);
                ids = ids % sizeofSpace;
                machines.AddMachine(ids);
            }
            delete[]names;
        }


	}
};
#endif 