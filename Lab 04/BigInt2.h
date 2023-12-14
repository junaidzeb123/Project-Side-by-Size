#pragma once
#include<iostream>
using std::cout;
using std::cin;
using std::string;

class BigInt {
	string data;
	
public:
	BigInt(string data) {
		this.data = data;
	}
  
    BigInt operator+(BigInt num2){

  
        while (num2.data.length() != data.length()) {
            num2.data = "0" + num2.data;
        }

        string result = "";
        int carry = 0;
        int sumIndex = 0;

        for (int i = data.length() - 1; i >= 0; i--) {
            sumIndex = (data[i] - '0') + (num2.data[i] - '0') + carry;
            carry = sumIndex / 10;
            sumIndex = sumIndex % 10;
            result = std::to_string(sumIndex) + result;
        }

        if (carry != 0)
            result = std::to_string(carry) + result;

        BigInt b2(result);
        return b2;;
    }

    BigInt&operator++() {
        BigInt b("1");
        *this = *this + b;
        return *this;
    }

  /*  BigInt operator *( BigInt num2) {
        string data = this->data;
        if (data.length() > num2.data.length()) {
            swap(data, num2.data);
        }

        int carry = 0;
        string total = "";
        
        for (int i = data.length() - 1; i >= 0; i--) {
            string result = "";

            for (int j = num2.data.length() - 1; j >= 0; j--) {

                int n1 = data[i] - '0';
                int n2 = num2.data[j] - '0';
                int current = n1 * n2 + carry;
                carry = (current / 10);

                if (current % 10 == 0) {
                    result = '0' + result;
                }
                else {
                    result = std::to_string(current % 10) + result;
                }
            }
            if (carry != 0)
                result = std::to_string(carry) + result;
            carry = 0;

            for (int j = data.length() - 1; j > i; j--)
                result = result + '0';

            total = total +  result;
        }

        BigInt b2(total);
        return b2;
    }*/

    bool operator == (BigInt num2) {
        for (int i = 0; i < num2.data.length(); i++) {
            if (num2.data[i] < '0' || num2.data[i] > '9')
                return false;
        }

        if (num2.data.length() != num2.data.length())
            return false;
        

        for (int i = num2.data.length() - 1; i >= 0; i--) {
            if (num2.data[i] != data[i])
                return false;
        }

        return true;
    }

    bool operator != (BigInt num2) {
        for (int i = 0; i < num2.data.length(); i++) {
            if (num2.data[i] < '0' || num2.data[i] > '9')
                return false;
        }

        if (num2.data.length() != num2.data.length())
            return true;


        for (int i = num2.data.length() - 1; i >= 0; i--) {
            if (num2.data[i] != data[i])
                return true;
        }

        return false;
    }

    bool operator > (BigInt num2) {
 

        if (num2.data.length() > data.length())
            return false;


        if (data.length() > num2.data.length())
            return true;

        for (int i = data.length() - 1; i >= 0; i--) {

            if (data[i] > num2.data[i])
                return true;

            else if (data[i] < num2.data[i])
                return false;

        }
        return false;
    }

    bool operator < (BigInt num2) {


        if (num2.data.length() < data.length())
            return false;


        if (data.length() < num2.data.length())
            return true;

        for (int i = data.length() - 1; i >= 0; i--) {

            if (data[i] < num2.data[i])
                return true;

            else if (data[i] > num2.data[i])
                return false;

        }
        return false;
    }

    bool operator >= (BigInt num2) {
        if (*this == num2 || *this > num2)
            return true;
        return false;            
    }

    bool operator <= (BigInt num2) {
        if (*this == num2 || *this < num2)
            return true;
        return false;
    }

}
