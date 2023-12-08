#pragma once
#include <sstream>
#include<cmath>
#include<bitset>

using  std::string;
using  std::cout;
using  std::endl;
#ifndef BIGINT_160_H
#define BIGINT_160_H



class Bigint_160 {
    unsigned int number[5];

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
            current = current << 32 - sizeofBits;
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
    int value(char bit) {
        return bit == '1' ? 1 : 0;
    }
    string multiplyingBypowerof2(string bit,int j) {
        for (int i = 0; i < j; i++)
            bit += '0';
        return bit;
    }
    string BinaryToDecimal(string binary) {
        string decimalNumber = "0";
        int j = 0; 
        for (int i = binary.length() - 1; i >= 0; i++) {
            short no = value(binary[i]);
            multiplyingBypowerof2(binary[i], j);
            j++;
        }
        return decimalNumber;
    }
  
    string to_string() {
        std:: stringstream stream;
        std::bitset<32> b0(number[0]), b1(number[1]), b2(number[2]), b3(number[3]), b4(number[4]);
        string binarynumber = "";
        binarynumber = b0.to_string() + b1.to_string() + b2.to_string() + b3.to_string() + b4.to_string();

        
        string str;
        string decimal;
        return decimal;
     
    }
    
    Bigint_160 operator+(const Bigint_160& num1) {
         Bigint_160 result;

         unsigned long long carry = 0;
         for (int i = 4; i >= 0; i--) {
             unsigned long long sum = static_cast<unsigned long long>(this->number[i]) + num1.number[i] + carry;
             result.number[i] = static_cast<unsigned int>(sum & 0xFFFFFFFF);
             carry = sum >> 32;
         }
                  
         std::stringstream str;
         for(int i = 0 ;i <5;i++)
             str << std::hex << result.number[i];
         cout << str.str() << endl;;
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