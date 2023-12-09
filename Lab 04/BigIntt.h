#pragma once
#include<iostream>
using std::cout;
using std::cin;
using std::string;

class BigInt {
	string data;	

    string add(string num1, string num2) {
        if (num1.length() < num2.length()) {
            swap(num1, num2);
        }

        while (num2.length() != num1.length()) {
            num2 = "0" + num2;
        }

        string result = "";
        int carry = 0;
        int sumIndex = 0;

        for (int i = num1.length() - 1; i >= 0; i--) {
            sumIndex = (num1[i] - '0') + (num2[i] - '0') + carry;
            carry = sumIndex / 10;
            sumIndex = sumIndex % 10;
            result = std::to_string(sumIndex) + result;
        }

        if (carry != 0)
            result = std::to_string(carry) + result;

        return result;
    }
public:
	BigInt(string data) {
		this->data = data;
	}
    
    BigInt() {
        data = "";
    }
   
    BigInt operator+(BigInt num2){
   
        string data = this->data;
        string data2 = num2.data;
        if (data.length() < data2.length()) {
            swap(data, data2);
        }
        while (data2.length() != data.length()) {
            data2 = "0" + data2;
        }

        string result = "";
        int carry = 0;
        int sumIndex = 0;

        for (int i = data.length() - 1; i >= 0; i--) {
            sumIndex = (data[i] - '0') + (data2[i] - '0') + carry;
            carry = sumIndex / 10;
            sumIndex = sumIndex % 10;
            result = std::to_string(sumIndex) + result;
        }

        if (carry != 0)
            result = std::to_string(carry) + result;
        while (result[0] == '0')
        {
            result = result.substr(1, result.length() - 1);
        }
        BigInt b2(result);
        return b2;;
    }
    
    BigInt operator-(BigInt num2) {

        string data = this->data;
        string data2 = num2.data;
        if (data.length() < data2.length()) {
            swap(data, data2);
        }
        while (data2.length() != data.length()) {
            data2 = "0" + data2;
        }

        for (int i = 0; i < data2.length(); i++) {
            data2[i] = (9 - (data2[i] - '0') + '0');
        }
        data2 = add(data2 , "1");

        string result = add(data2 , data);
        while (result[0] == '0') {
            result = result.substr(1, result.length() - 1);
        }
        if (result.length() > data2.length() && result[0] == '1') {
            result = result.substr(1, result.length() - 1);
        }
        else {
            for (int i = 0; i < result.length(); i++) {
                result[i] = (9 - (result[i] - '0') + '0');
            }
            result = add(result , "1");
        }
        BigInt b2(result);
        return b2;
    }

    BigInt&operator++() {
        BigInt b("1");
        *this = *this + b;
        return *this;
    }

    BigInt& operator--() {
        BigInt b("1");
        *this = *this - b;
        return *this;
    }
    
    BigInt operator *( BigInt num2) {

        string data = this->data;
        string data2 = num2.data;

        if (data.length() > data2.length()) {
            swap(data, data2);
        }

        int carry = 0;
        string total = "";


        for (int i = data.length() - 1; i >= 0; i--) {
            string result = "";

            for (int j = data2.length() - 1; j >= 0; j--) {
                int n1 = data[i] - '0';
                int n2 = data2[j] - '0';
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

            total = add(total, result);
        }
        while (total[0] == '0' && total.length() != 1)
            total = total.substr(1, total.length() - 1);
        BigInt b2(total);
        return b2;
    }

    bool operator == (BigInt num2) {
        for (int i = 0; i < num2.data.length(); i++) {
            if (num2.data[i] < '0' || num2.data[i] > '9')
                return false;
        }

        string data = this->data;
        string data2 = num2.data;
        if (data.length() < data2.length()) {
            swap(data, data2);
        }

        while (data2.length() != data.length()) {
            data2 = "0" + data2;
        }

        for (int i = data2.length() - 1; i >= 0; i--) {
            if (data2[i] != data[i])
                return false;
        }

        return true;
    }

    bool operator != (BigInt num2) {
        return (!(*this == num2));
    }

    bool operator > (BigInt num2) {
 
        string data = this->data;
        string data2 = num2.data;
        while (data[0] == '0')
        {
            data = data.substr(1, data.length() - 1);
        }

        while (data2[0] == '0')
        {
            data2 = data2.substr(1, data2.length() - 1);
        }

        if (data.length() > data2.length())
            return true;
        else if (data.length() < data2.length())
            return false;

        for (int i = 0 ; i < data.length(); i++) {

            if (data[i] > data2[i])
                return true;

            else if (data[i] < data2[i])
                return false;

        }
        return false;
    }

    bool operator < (BigInt num2) {
        if (*this > num2 || *this == num2)
            return false;
        return true;
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

    bool operator == (string num2) {
        for (int i = 0; i < num2.length(); i++) {
            if (num2[i] < '0' || num2[i] > '9')
                return false;
        }

        string data = this->data;
        string data2 = data;
        if (data.length() < data2.length()) {
            swap(data, data2);
        }

        while (data2.length() != data.length()) {
            data2 = "0" + data2;
        }

        for (int i = data2.length() - 1; i >= 0; i--) {
            if (data2[i] != data[i])
                return false;
        }

        return true;
    }

    bool operator != (string num2) {
        return (!(*this == num2));
    }

    bool operator > (string num2) {

        string data = this->data;
        string data2 = num2;
        while (data[0] == '0')
        {
            data = data.substr(1, data.length() - 1);
        }

        while (data2[0] == '0')
        {
            data2 = data2.substr(1, data2.length() - 1);
        }

        if (data.length() > data2.length())
            return true;
        else if (data.length() < data2.length())
            return false;

        for (int i = 0; i < data.length(); i++) {

            if (data[i] > data2[i])
                return true;

            else if (data[i] < data2[i])
                return false;

        }
        return false;
    }

    bool operator < (string num2) {
        if (*this > num2 || *this == num2)
            return false;
        return true;
    }

    bool operator >= (string num2) {
        if (*this == num2 || *this > num2)
            return true;
        return false;
    }

    bool operator <= (string num2) {
        if (*this == num2 || *this < num2)
            return true;
        return false;
    }

    BigInt operator+ (string num2) {

        string data = this->data;
        string data2 = num2;
        if (data.length() < data2.length()) {
            swap(data, data2);
        }
        while (data2.length() != data.length()) {
            data2 = "0" + data2;
        }

        string result = "";
        int carry = 0;
        int sumIndex = 0;

        for (int i = data.length() - 1; i >= 0; i--) {
            sumIndex = (data[i] - '0') + (data2[i] - '0') + carry;
            carry = sumIndex / 10;
            sumIndex = sumIndex % 10;
            result = std::to_string(sumIndex) + result;
        }

        if (carry != 0)
            result = std::to_string(carry) + result;
        while (result[0] == '0')
        {
            result = result.substr(1, result.length() - 1);
        }
        BigInt b2(result);
        return b2;;
    }

    string getData() {
        return this->data;
    }
  
    friend  std::istream& operator >> (std::istream& in, BigInt& num);
    
    friend  std::ostream& operator << (std::ostream& out, BigInt& num);
};

std::istream& operator >> (std::istream& in, BigInt& num)
{
    in >> num.data;
    return in;
}

 std::ostream& operator << (std::ostream& out, BigInt& num) {
    out << num.data;
    return out;
}
