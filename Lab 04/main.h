#include<iostream>
#include "BigInt.h"
#include"DHT.h"
using  std::string;
using  std::cout;
using  std::endl;

int main()
{
    
  //  DHT dh;
    //dh.machinesAndTablePrint();
    Bigint_160 b1("BBBBBBBBBB");
    Bigint_160 b2("AAAAAAAAAA");
    Bigint_160 b3 = b1 + b2;
    cout << b3.to_string();
}


//5 9 1 1  4 9 11 14 18 20 21