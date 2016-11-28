/*
 * INT.h
 *
 *  Created on: 16-Nov-2016
 *      Author: Abhay
 */

#ifndef INT_H_
#define INT_H_

#include <vector>
#include <string>

using namespace std;

class INT {

private:
	/*
	 * [16-11-2016]
	 * sign -> used to store the sign of the number
	 * num -> actual place where the numerical data is stored
	 */

	char sign;
	vector<char> num;

	/*
	 * [16-11-2016]
	 * invalid_format exception
	 * to be thrown when the user input is invalidated to be wrong
	 */
	class invalid_format: public exception{
		virtual const char* what() const throw(){
			return "Assignment format is inappropriate";
		}
	} invalid_format;

	/*
	 * [18-11-2016]
	 * zero_divide exception
	 * to be thrown when dividing by zero occurs
	 */
	class zero_divide: public exception{
		virtual const char* what() const throw(){
			return "Divisor cannot be zero";
		}
	} zero_divide;

	/*
	 * [26-11-2016]
	 * limit_exceeded exception
	 * to be thrown when program may exceeded limit
	 */
	class limit_exceeded: public exception{
		virtual const char* what() const throw(){
			return "Digits limits reached";
		}
	}limit_exceeded;

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

	//used with parse function
	static bool is_operator(char ch);
	static bool is_number(char ch);
	static int priority(char c);
	static string to_postfix(string infix);

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

	//Exponent operator
	INT operator ^ (INT num);

	//parses a string expression
	static INT parse(string exp);
	//checks expression before parsing
	static bool check_expression(string exp);

	int length(){return num.size();}

	//[deprecated] used for lattice_multiplication method
	INT lattice_multiplication(INT num1);
};

#endif /* INT_H_ */
