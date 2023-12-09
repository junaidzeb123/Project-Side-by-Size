#pragma once
#include <sstream>
#include<cmath>
using  std::string;
using  std::cout;
using  std::endl;
#ifndef BIGINT_160_H
#define BIGINT_160_H



class Bigint_160 {
    unsigned int number[5];
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

    string multiplication(string num1, string num2) {
        if (num1.length() > num2.length()) {
            swap(num1, num2);
        }

        int carry = 0;
        string total = "";

        for (int i = num1.length() - 1; i >= 0; i--) {
            string result = "";

            for (int j = num2.length() - 1; j >= 0; j--) {
                int n1 = num1[i] - '0';
                int n2 = num2[j] - '0';
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

            for (int j = num1.length() - 1; j > i; j--)
                result = result + '0';

            total = add(total, result);
        }

        return total;
    }

    string powerOf16(int j) {
        string no = "1";

        for (int i = 0; i < j; i++) {
            no = multiplication(no, "16");
        }

        return no;
    }

    string hexToDecimal(string hex) {
        string decimal = "";
        int j = 0;
        bool sign = 0;

        if (hex[0] == '-') {
            sign = 1;
            hex = hex.substr(1, hex.length() - 1);
        }

        for (int i = hex.length() - 1; i >= 0; i--) {
            int digit;
            char c = hex[i];

            if (c >= '0' && c <= '9') {
                digit = c - '0';
            }
            else if (c >= 'A' && c <= 'F') {
                digit = c - 'A' + 10;
            }
            else if (c >= 'a' && c <= 'f') {
                digit = c - 'a' + 10;
            }
            else {
                return "Invalid input";
            }

            decimal = add(decimal, multiplication((std::to_string(digit)), powerOf16(j)));
            j++;
        }

        if (sign) {
            decimal = "-" + decimal;
        }

        return decimal;
    }

public:
    Bigint_160() {
        for (int i = 0; i < 5; i++) {
            number[i] = 0;
        }
    }

    Bigint_160( string numberHex) {
        AssignNumberInHex(numberHex);
    }
    
    void AssignNumberInHex( string numberHex) {
        int digitValue = 0;
        int digitCount = 0;
        for (int i = 0; i < 5; i++) {
            number[i] = 0;
        }
        while (numberHex.length() < 40){
            numberHex = '0' + numberHex;
        }
        for (char hexChar : numberHex) {
            if (isdigit(hexChar)) {
                digitValue = hexChar - '0';
            }
            else {
                digitValue =  tolower(hexChar) - 'a' + 10;
            }
            if (digitCount < 8) {
                number[0] <<= 4;
                number[0] += digitValue;
            }
            else if (digitCount < 16) {
                number[1] <<= 4;
                number[1] += digitValue;
            }
            else if (digitCount < 24) {
                number[2] <<= 4;
                number[2] += digitValue;
            }
            else if (digitCount < 32) {
                number[3] <<= 4;
                number[3] += digitValue;
            }
            else {
                number[4] <<= 4;
                number[4] += digitValue;
            }

            digitCount++;
        }
    }
  
    Bigint_160 operator%(int sizeofBits) {
      std::   stringstream stream;
        stream << "";
        unsigned   int current = 0;
        if (sizeofBits <= 32 && sizeofBits != 0) {
            current = number[4];
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream <<  std::hex << current;
        }
        else if (sizeofBits <= 64 && sizeofBits != 0) {
            current = number[3];
            sizeofBits -= 32;
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream <<  std::hex << current;
            stream <<  std::hex << number[4];
        }
        else if (sizeofBits <= 96 && sizeofBits != 0) {
            current = number[2];
            sizeofBits -= 64;
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream <<  std::hex << current;
            stream <<  std::hex << number[3];
            stream <<  std::hex << number[4];
        }
        else if (sizeofBits <= 128 && sizeofBits != 0) {
            current = number[1];
            sizeofBits -= 96;
            current = current << 32 - sizeofBits;
            current = current >> (32 - sizeofBits);
            stream <<  std::hex << current;
            stream <<  std::hex << number[2];
            stream <<  std::hex << number[3];
            stream <<  std::hex << number[4];
        }
        else if (sizeofBits != 0 && sizeofBits < 160) {
            current = number[0];
            sizeofBits -= 128;
            current = current << (32 - sizeofBits);
            current = current >> (32 - sizeofBits);
            stream <<  std::hex << current;
            for (int i = 1; i < 5; i++) {
                stream << std:: hex << number[i];
            }
        }
        else if (sizeofBits != 0) {
            for (int i = 0; i < 5; i++) {
               stream <<  std::hex << number[i];

            }
        }
        int length = stream.str().length();
        std:: stringstream stream2;
        while (stream2.str().length() < 40 - length)
           stream2 << 0;
        stream2 << stream.str();
        return Bigint_160(stream2.str());
    }
   
    bool operator == (Bigint_160& num1) {
        for (int i = 0; i < 5; i++) {
            if (this->number[i] != num1.number[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator < (Bigint_160& num1) {
        for (int i = 0; i < 5; i++) {
            if (this->number[i] >= num1.number[i] && (this->number[i] != 0 || num1.number[i] !=0)) {
                return false;
            }
        }
        return true;
    }
    
    bool operator > (Bigint_160& num1) {
        for (int i = 0; i < 5; i++) {
            if (this->number[i] <= num1.number[i] && (this->number[i] != 0 || num1.number[i] != 0)) {
                return false;
            }
        }
        return true;
    }

    Bigint_160 &operator++() {
        bool carry = 0;
        for (int i = 4; i >= 0; i--) {
            if (number[i] < std:: numeric_limits<unsigned int>::max() - 1) {
                number[i]++;
                carry = 1;
                break;
            }
            else {
                number[i] = 0;
            }
        }
        return *this;
    }
    string to_string() {
        std:: stringstream stream;
        for (int i = 0; i < 5; i++) {
            stream <<std::hex <<number[i];
        }
        string str = stream.str();
        while (str[0] == '0') {
            str = str.substr(1, str.length() - 1);
        }
        str = hexToDecimal(str);
        return str;
    }
     Bigint_160 operator+(const Bigint_160& num1) {
         Bigint_160 result;

         unsigned long long carry = 0;
         for (int i = 4; i >= 0; i--) {
             unsigned long long sum = static_cast<unsigned long long>(this->number[i]) + num1.number[i] + carry;
             result.number[i] = static_cast<unsigned int>(sum & 0xFFFFFFFF);
             carry = sum >> 32;
         }

         // If there's a carry in the highest digit, it means overflow
         if (carry != 0) {
             // Handle overflow situation here
         }
         return result;
     }

    friend  std::istream& operator >> ( std::istream& in, Bigint_160& num);
    
};

 string decimalToHex(const  string& decimalStr) {
    unsigned long long  decimalValue;
     std::stringstream ss(decimalStr);

    // Convert decimal string to integer
    ss >> decimalValue;
    // Convert integer to hexadecimal string
     std::stringstream hexStream;
    hexStream << std:: hex << decimalValue;
     string hexStr = hexStream.str();

    return hexStr;
}

 std::istream& operator >> ( std::istream& in, Bigint_160& num)
{
     string numstr;
    in >> numstr;
    string hexString = decimalToHex(numstr);
    num.AssignNumberInHex(hexString);
    return in;
}
 
#endif 