/*
 * INT.h
 *  Created on: 16-Nov-2016
 *  Last Modified: 29-Nov-2016
 *  Author: Abhay Jatin Doshi
 */

#ifndef INT_H_
#define INT_H_

#include <vector>
#include <string>

using namespace std;

class INT {

private:

	//used to store the sign of the number
	char sign;
	//actul place where the numerical data is stored
	vector<char> num;
	
	//private constructors
	INT(char sign,vector<char> num);

	//returns true if a > b
	bool compare(std::vector<char> a,vector<char> b);

	//for converting the string to INT of current instance
	void convert(string number);

	//[dangerous] adds two vectors
	vector<char> add(vector<char> a,vector<char> b);

	//[dangerous] subtracts two vectors
	vector<char> subtract(vector<char> a, vector<char> b);

	// multiplies two vectors
	vector<char> multiply(vector<char> a, vector<char> b);

	//used too remove redundant zeros
	vector<char> clean(vector<char> number);

	//[dangerous] increment/decrement vector by 1
	vector<char> increment(vector<char> number);
	vector<char> decrement(vector<char> number);

public:

	INT();
	virtual ~INT();

	//to use = operator for initializing the object
	INT(const char* str);
	INT(const string);

	//for converting the value to string
	string to_string();

	//input/output streams
	friend ostream& operator<<(ostream &output, const INT &obj);
	friend istream& operator>>(istream &input, INT &obj);

	//assignment operator
	void operator = (const char* str);
	void operator = (string number);

	//negate operator
	INT operator - ();

	//Comparison / Relative operators
	bool operator == (INT num1);
	bool operator != (INT num1);
	bool operator >  (INT num1);
	bool operator >= (INT num1);
	bool operator <  (INT num1);
	bool operator <= (INT num1);

	//Arithmetic operators
	INT operator + (INT num1);
	INT operator - (INT num1);
	INT operator * (INT num1);
	INT operator / (INT num1);
	INT operator % (INT num1);

	//Increment/Decrement operators
	INT operator ++();
	INT operator ++(int);
	INT operator --();
	INT operator --(int);

	//returns the length of the number
	int length();
};

#endif /* INT_H_ */
