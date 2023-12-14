#include"pch.h"
#include <iostream>
#include "BigInt.h"
using namespace std;
BigInt BigInt:: mul(const BigInt&val)const{
    BigInt temp ;
    int s = val.size;
    int *t = new int[s];
       if(size >=s && s <=8){
        int mul=1;
        int k =0;
        int run =0;
        for(int i = s-1;i>= 0 ;i--){            
            run = mul*val.ptr[i];            
            for(int j = 0 ;j<run; j++){            
                temp += *this;
                k++;
            }
            mul*=10;
        }
    }
    else if(s <= 8){
         int mul=1;
        int k =0;
        int run =0;
        for(int i = size-1;i>= 0 ;i--){            
            run = mul*ptr[i];            
            for(int j = 0 ;j<run; j++){            
                temp += val;
                k++;
            }
            mul*=10;
        }
    }
    return temp;
}
BigInt BigInt::add(const BigInt&val)const{
     BigInt temp;
    delete[] temp.ptr;
    temp.ptr = new int[size];
    int s = val.size;
    int *t = new int[s];
    for (int i = 0; i < val.size; i++)
            t[i] = val.ptr[i];
   
   
    temp.ptr = new int[s];
    temp.size = s;
    // for(int i =0 ;i<s;i++)
    //     temp.ptr[i]= t[i];
   
    int carry = 0;
    int j = s - 1;
    {
    if (size >= s)
    {
    	temp.ptr = new int [size];
        for (int i = size - 1; i >= 0; i--)
        {
            if (j >= 0)
            {
                temp.ptr[i] = this->ptr[i] + t[j] + carry;
                carry = temp.ptr[i] / 10;

                if (carry != 0)
                {
                    temp.ptr[i] = temp.ptr[i] % 10;
                }
                j--;
            }
            else
            {
                temp.ptr[i] = ptr[i] + carry;
                carry = temp.ptr[i] / 10;
                if (carry != 0)
                {
                    temp.ptr[i] = temp.ptr[i] % 10;
                }
            }
        }
        temp.size = size;
       
       
    }
   
   else
    {
        temp.ptr = new int[s];
        j = size - 1;
        for (int i = s - 1; i >= 0; i--)
        {
            if (j >= 0)
            {
                temp.ptr[i] = this->ptr[j] + t[i] + carry;
                carry = temp.ptr[i] / 10;
                if (carry != 0)
                {
                    temp.ptr[i] = temp.ptr[i] % 10;
                }
                j--;
            }
            else
            {
                temp.ptr[i] = t[i] + carry;
                carry = temp.ptr[i] / 10;
                if (carry != 0)
                {
                    temp.ptr[i] = temp.ptr[i] % 10;
                }
            }
        }

        temp.size = s;
    }
    if(carry != 0 && size >=s){
        delete[] t;
        t = new int[size+1 ];
        for (int i = 0; i <= size; i++)
        {
            if (i == 0)
                t[i] = carry;
            else
            {
                t[i] = temp.ptr[i - 1];
            }
        }
        delete []temp.ptr;
        temp.ptr = t;
        temp.size = size+1;
       
    }
    else if(carry !=0 ){
        delete[]t;
        t = new int[s+1];
         for (int i = 0; i < s + 1; i++)
        {
            if (i == 0)
                t[i] = carry;
            else
            {
                t[i] = temp.ptr[i - 1];
            }
        }
         delete[] temp.ptr;
        temp.ptr = new int[s + 1];
        temp.size = s + 1;
        temp.ptr = t;


    }
    }
   
    return temp;
}
BigInt BigInt::sub(const BigInt&val)const{
     BigInt temp;
    delete[]temp.ptr;
    int s = val.size;
    int *t = new int[s];
  
   if(s == size ){
     for(int i = 0 ;i<s;i++) 
       t[i] = val.ptr[i];
    for(int i = 0 ;i < s;i++)
       t[i] = 9 - t[i];  
       temp.size = s;
        temp.ptr = new int[s];
        for(int i = 0 ; i < temp.size;i++){
        temp.ptr[i] = t[i];
         }
         temp = temp+1;
         temp = temp+*this;
          delete[]t;
        t = temp.ptr;
        if(temp.size>1){
        temp.ptr = new int[temp.size-1];
        for(int i = 1 ; i<temp.size; i++){
            temp.ptr[i-1] = t[i];
         }
         temp.size-=1;
        }
          while (temp.ptr[0] == 0)   {
           delete[]t;
        t = temp.ptr;
        if(temp.size>1){
        temp.ptr = new int[temp.size-1];
        for(int i = 1 ; i<temp.size; i++){
            temp.ptr[i-1] = t[i];
         }
         temp.size-=1;
        }
          }
      } 
    else if(size>s){
       for(int i = 0 ;i<s;i++) 
       t[i] = val.ptr[i];
         int d = size - s;
        int* t1 = new int [size];
        for(int i = 0 ;i<size;i++){
            if(i < d)
                t1[i] = 0;
            else
             t1[i] = t[i-d];
        } 
           delete []t;
            t = t1;
            s = size; 
            for(int i = 0 ;i < s;i++)
                    t[i] = 9 - t[i];  
            temp.size = size;
            temp.ptr = new int[temp.size];
            for(int i = 0 ; i < temp.size;i++){
              temp.ptr[i] = t[i];
             }
            temp=temp+1;
            temp = temp+*this;
             delete[]t;
        t = temp.ptr;
        if(temp.size>1){
        temp.ptr = new int[temp.size-1];
        for(int i = 1 ; i<temp.size; i++){
            temp.ptr[i-1] = t[i];
         }
         temp.size-=1;
        }
         while (temp.ptr[0] == 0 )   {
           delete[]t;
        t = temp.ptr;
        if(temp.size>1){
        temp.ptr = new int[temp.size-1];
        for(int i = 1 ; i<temp.size; i++){
            temp.ptr[i-1] = t[i];
         }
         temp.size-=1;
        }
          }
    }  
    else if(s>size){
       for(int i = 0 ;i<s;i++){
            BigInt temp1;
            temp1.size = val.size;
            temp1.sign = 1;
            for(int i = 0 ;i<val.size ; i++)
                temp1.ptr[i] = val.ptr[i];
            BigInt temp2;
            temp2.size = size;
            temp2.sign = 0;
            for(int i =  0 ;i<size;i++)
                temp2.ptr[i] = ptr[i];
            
            return temp1+temp2;

       } 


    }
 return temp;
}
BigInt::BigInt(int val)
{
    
    int num = val;
    int i = 0;
    sign = 0 ;
    
    if(val<0){
        sign=1;
        num =-val;
        val=-val;
    }
    while (num > 0)
    {
        num /= 10;

        i++;
    }

    ptr = new int[i];
    num = val;
    size = i;
    if(val==0){
      size = 1;
    }
        
   i =0 ;
    for (i = size - 1; i >= 0; i--)
    {
        int a = num % 10;
        num /= 10;
        ptr[i] = a;
    }
   
   
}
BigInt::BigInt(string text)
{
   
    char *a = &text[0];
    int i = 0;
    sign = 0;
    if(*a=='-'){
        sign = 1;
        a++;
    }
    while (*a)
    {
        i++;
        a++;
    }  
     ptr = new int[i];
     size = i;
      a = &text[0];
      if(*a=='-')
          a++;
    i = 0;
    while (*a)
    {
        
        if (*a == '0')
            ptr[i] = 0;
        if (*a == '1')
            ptr[i] = 1;
        if (*a == '2')
            ptr[i] = 2;
        if (*a == '3')
            ptr[i] = 3;
        if (*a == '4')
            ptr[i] = 4;
        if (*a == '5')
            ptr[i] = 5;
        if (*a == '6')
            ptr[i] = 6;
        if (*a == '7')
            ptr[i] = 7;
        if (*a == '8')
            ptr[i] = 8;
        if (*a == '9')
            ptr[i] = 9;
        a++;
        i++;
    }

}
BigInt::BigInt(const BigInt &copy)
{
    size = copy.size;
    sign = copy.sign;
    ptr = new int[size];
    for (int i = 0; i < size; i++)
    {
        ptr[i] = copy.ptr[i];
    }
}

BigInt::operator string()
{
     char *temp ;
    int i = 0;
    int j =0;
    int s = size;
   
    if(sign == 0)
   temp = new char[size];
   else if(sign ==1) {
        temp = new char[size+1];
        temp[0]='-';
        j++;
        s= size+1;
   }
    for (; i < size; i++)
    {
       
        if (ptr[i] == 0)
            temp[j] = '0';
        else if (ptr[i] == 1)
            temp[j] = '1';
        else if (ptr[i] == 2)
            temp[j] = '2';
        else if (ptr[i] == 3)
            temp[j] = '3';
        else if (ptr[i] == 4)
            temp[j] = '4';
        else if (ptr[i] == 4)
            temp[j] = '4';
        else if (ptr[i] == 5)
            temp[j] = '5';
        else if (ptr[i] == 6)
            temp[j] = '6';
        else if (ptr[i] == 7)
            temp[j] = '7';
        else if (ptr[i] == 8)
            temp[j] = '8';
        else if (ptr[i] == 9)
            temp[j] = '9';
            j++;
    }
    temp[j] = '\0';
    return temp;
}

BigInt BigInt:: operator-(){
   if(sign==0)
    sign =1;
    else 
    sign = 0;
    return *this;
}
BigInt &BigInt::operator=(const BigInt &b)
{
    size = b.size;
    sign = b.sign;
    // cout<<"size= "<<b.size;
    ptr = new int[size];
    for (int i = 0; i < size; i++)
    {
        ptr[i] = b.ptr[i];
    }
    return *this;
}
/// @brief 
/// @param val 
/// @return /
BigInt BigInt::operator+(int val) const
{
    BigInt temp;
    delete[] temp.ptr;
     int num = val;
    int s = 0;
    if(val<0)
     num=-num;
    while (num > 0)
    {
        num /= 10;
        s++;
    }
    
    int *t = new int[s];
    num = val;
  
  
     
    for (int i = s - 1; i >= 0; i--)
    {
        int a = num % 10;
        num /= 10;
        t[i] = a;
    }
    temp.ptr = t;
    temp.size = s;
    temp.sign = 0 ;
    return *this + temp;
    
}
////////////////////////
/// /////

BigInt BigInt::operator+(const BigInt &val) const
{
    BigInt temp1 = *this;
    BigInt temp2 = val;
   
    if(sign == 0 && val.sign == 0){
        return temp1.add(temp2);
    }
    if(this->sign==1 && val.sign == 0){
        temp1.sign= 0 ;
         temp2.sign= 0 ;
        return -(temp1.sub(temp2));
    }
    else if(this->sign==0 && val.sign ==1){
        temp1.sign= 0 ;
         temp2.sign= 0 ;
        return temp1.sub(temp2);
    }
    else if(this->sign==1 && val.sign == 1){
           temp1.sign= 0 ;
         temp2.sign= 0 ;
        return -(temp1.add(temp2));
    }
   return temp1;
}
// //
BigInt BigInt::operator+=(const BigInt &val)
{
    BigInt temp = *this + val;
    size = temp.size;
        for (int i = 0; i < size; i++)
    {
        ptr[i] = temp.ptr[i];
    }
    return *this;
}
//////////////////////
BigInt BigInt:: operator-(int val) const{
    BigInt temp;
    delete[]temp.ptr;
    int num = val;
    int s = 0;
   
    while (num > 0)
    {
        num /= 10;
        s++;
    }
    int *t = new int[s];
    num = val;
    for (int i = s - 1; i >=0; i--)
    {
        int a = num % 10;
        num /= 10;
        t[i] = a;
    }
    temp.ptr = t; 
    temp.size = s;
    temp.sign = 0;
    return *this - temp;
    
    }
/////////
BigInt BigInt::operator-(const BigInt& val) const{
     BigInt temp1 = *this;
    BigInt temp2 = val;
    if(sign == 0 && val.sign==0){
       return  temp1.sub(temp2);
    }
   if(this->sign==1 && val.sign == 0){
        temp1.sign = 0 ;
        temp2.sign = 0 ;
        return -(temp1.add(temp2));
   }
   else if(this->sign==0 && val.sign == 1){
         temp1.sign = 0 ;
        temp2.sign = 0 ;
        return (temp1.add(temp2));
    }
   else if(this->sign==1 && val.sign == 1){
         temp1.sign = 0 ;
        temp2.sign = 0 ;
        return -(temp1.sub(temp2));
    }
    return temp1;
}
BigInt BigInt:: operator-=(const BigInt& rhs){
    BigInt temp =rhs;
    temp = *this - rhs;
    *this = temp;
    return *this;
}
bool BigInt::operator==(const BigInt &val) const
{
    if (size != val.size)
        return 0;
    for (int i = 0; i < size; i++)
    {
        if (ptr[i] != val.ptr[i])
            return false;
    }
    return true;
}
////
bool BigInt::operator!=(const BigInt &val) const
{
    if (*this == val)
        return false;
    return true;
}
//////
bool BigInt::operator<(const BigInt &val) const
{
    if (*this == val)
        return false;

    if (size < val.size)
        return true;
    if (size > val.size)
        return false;
    for (int i = 0; i < size; i++)
    {
        if (ptr[i] < val.ptr[i])
        {
            return true;
        }
    }

    return false;
}
/// @brief //////////////////////////////
/// @return /
bool BigInt::operator>(const BigInt &val) const
{
    if (*this == val)
        return false;
    if (*this < val)
        return false;
    return true;
}
/// @brief ///////
bool BigInt::operator<=(const BigInt &val) const
{
    if (*this == val)
        return true;
    if (*this < val)
        return true;
    return false;
}
/// @return /
bool BigInt::operator>=(const BigInt &val) const
{
    if (*this == val)
        return true;
    if (*this > val)
        return true;
    return false;
}
/// @brief //////
bool BigInt::operator==(const char *val) const
{
    BigInt temp = *this;
    string s = (string)temp;
    if (s == val)
        return true;
    return false;
}
/// @return /
BigInt&BigInt:: operator++(){
        *this = *this +1;
        return *this;
}
BigInt BigInt::operator++(int){
        BigInt temp = *this;
        *this = *this +1;
        return temp;
}
BigInt& BigInt::operator--(){
         *this = *this -1;
        return *this;
}
BigInt BigInt::operator--( int ){
     BigInt temp = *this;
        *this = *this -1;
        return temp;
}
//////////
BigInt BigInt::operator*(const BigInt& val) const{
    BigInt temp1 = *this;
    BigInt temp2 = val;
    if(val.size <8){
    if(sign == 0 && val.sign == 0){
        return temp1.mul(temp2);
    }
    if(this->sign==1 && val.sign == 0){
        temp1.sign= 0 ;
         temp2.sign= 0 ;
        return -(temp1.mul(temp2));
    }
    else if(this->sign==0 && val.sign ==1){
        temp1.sign= 0 ;
         temp2.sign= 0 ;
        return -(temp1.mul(temp2));
    }
    else if(this->sign==1 && val.sign == 1){
           temp1.sign= 0 ;
         temp2.sign= 0 ;
        return (temp1.mul(temp2));
    }
    }

    return temp1;

}
///////////////////
BigInt BigInt:: operator*=(const BigInt& rhs){
   if(rhs.size >=8)
   return rhs;
    *this = *this*rhs;
    return *this;
}
/////
BigInt::operator int(){
    return size-1;
}
// BigInt::~BigInt(){
//     delete[]ptr;
// } // destructor
ostream& operator<<(ostream& output, const BigInt& val){ // outputs the BigInt
   BigInt t = val;
    output<<(string)t;
    return output;
}
istream& operator>>(istream& input, BigInt& val) // inputs the BigInt
{
    string s;
    input>>s;
    BigInt b(s);
    val=b;
    return input;
}
 int main()
 {

    BigInt a("-123456789");
     BigInt b("-987654321");
     a *= b;
     cout<<a;

 }
