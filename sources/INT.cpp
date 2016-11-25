/*
 * INT.cpp
 *
 *  Created on: 16-Nov-2016
 *      Author: Abhay
 */

#include "INT.h"
#include <iostream>
#include <cmath>
#include <stack>

//PRIVATE METHODS

bool INT::compare(vector<char> a, vector<char> b){
	/*
	 * [16-11-2016]
	 * minimized version of a >= b
	 * returns true if a >= b
	 * else returns false
	 * [18-11-2016]
	 * added clean to remove redundant zeros
	 */

	//removes redundant zeros
	a = clean(a);
	b = clean(b);

	//compares size
	if(a.size() > b.size()) return true;
	if(a.size() < b.size()) return false;

	//checks numbers
	for(int i = 0; i < (int)a.size(); i++){
		if(a[i] > b[i]) return true;
		if(a[i] < b[i]) return false;
	}

	//finally they are equal
	return true;
}

void INT::convert(string number){
	/*
	 * [16-11-2016]
	 * This function is programmed to assign value to INT type using string
	 * input: string form of the number with or without sign
	 * output: an instance of class INT assigned with that number
	 * constraints:
	 * 		number[0]-> '+' or '-' or ('0' to '9')
	 * 		number[1 to length()] -> '0' to '9'
	 * 		size of number -> 268435455(2^28)
	 * 	exception:
	 * 		invalid_format: thrown if the above constraint is not met
	 *
	 * [18-11-2016]
	 * added clean to remove redundant zeros
	 */

	//validates the first char to be '+','-','0'-'9'
	if(!(number[0] == '+' || number [0] == '-' || (number[0] >= '0' && number[0] <= '9')))
		throw invalid_format;

	//clearing previous data of num
	num.clear();

	//condition to check if sign is specified
	if(number[0] == '+' || number[0] == '-'){
		sign = number[0];
		number.erase(number.begin());
	}
	else sign = '+';

	//after removal if sign(if exists) checks if all characters are numeric and length of the number is valid.
	if(!(number.find_first_not_of("0123456789") == std::string::npos) || number.length() < 1 || number.length() > pow(2,28)) throw invalid_format;

	//scanning the digits and assigning to the class instance
	std::copy(number.begin(),number.end(),std::back_inserter(num));

	//removes redundant zeros
	num = clean(num);

	//makes the sign positive when number is zero
	if(num[0] == '0') sign='+';
}

vector<char> INT::add(vector<char> a, vector<char> b){
	/*
	 * [16-11-2016]
	 * DANGEROUS!! BE CAUTIOUS!!
	 * adds two vector<char> and returns the answer as the same type
	 * it doesn't checks and validates the numbers
	 * make sure that a>b before invoking this function
	 *
	 * [18-11-2016]
	 * added clean to remove redundant zeros
	 */

	//copies a to sum
	vector<char> sum = a;

	//extra zero added at the beginning if sum exceeds maximum digits
	sum.insert(sum.begin(),'0');
	int i = a.size();
	int k;
	//adds the numbers from the last digits
	for(int j = b.size()-1; j>=0; j--){
		//adds the digit from b and carry if any
		sum[i]+=b[j]-'0';

		//calculates if carry is necessary
		k = i;
		while(sum[k] > '9'){
			sum[k-1]+= (sum[k]-'0')/10;
			sum[k] = ((sum[k]-'0')%10)+'0';
			k--;
		}
		i--;
	}

	//clean() removes redundant zeros
	return clean(sum);
}

vector<char> INT::subtract(vector<char> a, vector<char> b){
	/*
	 * [16-11-2016]
	 * DANGEROUS!! BE CAUTIOUS!!
	 * subtracts two vector<char> and returns the answer as the same type
	 * it doesn't checks and validates the numbers
	 * make sure that a>b before invoking this function
	 *
	 * [20-11-2016]
	 * corrected the positive negative problem Ex: 5-10 = 5 and not -5
	 */

	//copies the number a to answer
	vector<char> ans = a;
	int i=a.size()-1,k;

	for(int j=b.size()-1; j >= 0 ; j--){
		//subtract b and borrow(if any) from ans
		ans[i] -= b[j]-'0';

		k = i;
		//checks if there is any borrow
		while(ans[k]< '0'){
			ans[k-1]-=1;
			ans[k]+=10;
			k--;
		}
		i--;
	}
	return clean(ans);
}

vector<char> INT::clean(vector<char> number){
	/*
	 * [18-11-2016]
	 * clean function is used to remove the redundant zeros
	 * redundant zeros in this context means leading zeros
	 */

	bool a=false;
	vector<char> clean;
	for(char ch:number){
		if(ch != '0') a = true;
		if(a)clean.push_back(ch);
	}

	//if the number becomes empty it adds a single zero
	if(clean.size() <= 0) clean.push_back('0');
	return clean;
}

bool INT::is_operator(char ch){
	/*
	 * [19-11-2016]
	 * is_operator is function used in to_postfix and parse operation
	 * it returns true if the character is an operator
	 */
	if(ch == '+'|| ch == '-' || ch == '*' || ch == '/' || ch == '%') return true;
	return false;
}

bool INT::is_number(char ch){
	if(ch >= '0' && ch <= '9') return true;
	return false;
}

int INT::priority(char c){
	/*
	 * [19-11-2016]
	 * returns a number according to the priority to compare the operators
	 * used in to_postfix function
	 */
	if(c == '+' || c == '-') return 1;
	if(c == '*' || c == '/' || c == '%') return 2;
	return 0;
}

bool INT::check_expression(string exp){
	if(is_operator(exp[exp.size()-1]) || exp.size() <= 0) return false;
	stack<char> brackets;
	if(!(is_number(exp[0]) || exp[0] == '-')) return false;
	for(int i = 1; i < (int)exp.size(); i++){
		if(exp[i] == '('){
			if(exp[i+1] == ')') return false;
			brackets.push(exp[i]);
		}
		else if(exp[i] == ')'){
			if(exp[i+1] == '(') return false;
			if(brackets.empty()) return false;
			else brackets.pop();
		}
		else if(is_operator(exp[i])){
			if(exp[i-1] == '(' && exp[i] != '-') return false;
			if(exp[i+1] == ')') return false;
			if(is_operator(exp[i+1])||is_operator(exp[i-1])) return false;
		}
		else if(is_number(exp[i])){
			if(exp[i-1] == ')') return false;
			if(exp[i+1] == '(') return false;
		}
		else
			return false;
	}
	return brackets.empty();
}

string INT::to_postfix(string infix){
	/*
	 * [19-11-2016]
	 * to_postfix converts a normal expression to
	 * postfix expression, yet to add validation
	 */

	//stores the postfix form of the expression given
	string postfix = "";
	//stack for storing operators and pop at right positions
	vector<char> operators;

	//iterates through every character of infix string
	for(int i = 0 ; i < (int)infix.length() ; i++){

		//checks for operators
		if(is_operator(infix[i])){
			//checks for unary minus operator
			if(infix[i]=='-' && !is_number(infix[i-1]) && infix[i-1] != ')'){
				//adds a comma before unary negative operator.
				postfix+=",-";
			}
			else{
				//pops out the operators that are of higher precedence than current operators
				while(operators.size() != 0 && priority(operators.back()) >= priority(infix[i])){
					postfix+=operators.back();
					operators.pop_back();
				}

				//pushes the current operator to stack
				operators.push_back(infix[i]);
			}
		}

		//pushes the open parentheses into the operators stack
		else if(infix[i] == '(') operators.push_back('(');

		//Recognizes the close parentheses
		else if(infix[i] == ')'){

			//pops out all the operators until open parentheses is found
			while(operators.back() != '('){
				postfix+=operators.back();
				operators.pop_back();
			}

			//pops of open parentheses that was in stack
			operators.pop_back();
		}

		//stores number suffixed with character _ to separate numbers
		else{

			//moves the number to postfix
			while(infix[i] >= '0' && infix[i] <= '9'){
				postfix+=infix[i];
				i++;
			}

			//suffixing underscore
			postfix+="_";
			//reduces i by 1 to bring it to sync
			i--;
		}
	}

	//pops out all the remaining operators
	while(operators.size() != 0){
		postfix+=operators.back();
		operators.pop_back();
	}

	return postfix;
}


//CONSTRUCTORS

INT::INT() {
	/*
	 * [16-11-2016]
	 * the number is initialized to 0 with a positive sign
	 */
	sign ='+';
	num.push_back('0');
}

INT::~INT() {
	// TODO Auto-generated destructor stub
}

INT::INT(const char* str){
	/*
	 * [16-11-2016]
	 * is used to initialise the object with a char* input
	 */
	string number = str;
	this->convert(str);
}

INT::INT(const string number){
	/*
	 * [24-11-2016]
	 * is used to initialise the INT data if input is considered as char
	 */
	this->convert(number);
}

//ASSIGNMENT AND I/O STREAMS

string INT::to_string(){
	/*
	 * [16-11-2016]
	 * used to get the string format of the number stored in INT
	 * input: none
	 * output: string
	 */
	//copying the stream from vector to string
	string number(num.begin(),num.end());

	//adding a negative sign if sign = '-'
	if(sign == '-') number.insert(0,"-");

	return number;
}

ostream& operator<<(ostream &output, const INT &obj){
	/*
	 * [17-11-2016]
	 * Overloading << operator so that it can be used smoothly with cout operation
	 */
	if(obj.sign == '-') output<<'-';
	for(char ch: obj.num) output<<ch;
	return output;
}

istream& operator>>(istream &input, INT &obj){
	/*
	 * [17-11-2016]
	 * Overloading >> operator so that it can be used smoothly with cin operation
	 */
	string number;
	input>>number;
	obj.convert(number);
	return input;
}

void INT::operator = (const char* str){
	/*
	 * [17-11-2016]
	 * when creating a string using " " the string is considered as char*
	 * and so overloaded the equal operator for both char* and string
	 */
	string number = str;
	convert(number);
}

void INT::operator = (string number){
	/*
	 * [16-11-2016]
	 * allows to assign the object with string type data
	 */
	convert(number);
}

//UNARY OPERATORS

INT INT::operator - (){
	/*
	 * [16-11-2016]
	 * this is a negate operator that is used to return the opposite sign
	 */
	INT number;
	number.sign = sign=='+'?'-':'+';
	number.num = num;
	return number;
}

//RELATIVE OPERATORS

bool INT::operator == (INT num1){
	/*
	 * [16-11-2016]
	 * overloaded comparison == operator
	 */
	//checks sign
	if(sign != num1.sign) return false;

	//checks number of digits
	if(num.size() != num1.num.size()) return false;

	//checks the digits
	for(int i = 0; i < (int)num.size() ; i++)
		if(num[i]!=num1.num[i]) return false;

	//finally they are equal
	return true;
}

bool INT::operator != (INT num1){
	/*
	 * [16-11-2016]
	 * overloaded comparison != operator
	 */
	//checks sign
	if(sign != num1.sign) return true;

	//checks number of digits
	if(num.size() != num1.num.size()) return true;

	//checks the digits
	for(int i = 0; i < (int)num.size() ; i++)
		if(num[i]!=num1.num[i]) return true;

	//finally they are not equal
	return false;
}

bool INT::operator > (INT num1){
	/*
	 * [16-11-2016]
	 * overloaded comparison > operator
	 */
	//checks signs
	if(sign == '+' && num1.sign == '-') return true;
	if(sign == '-' && num1.sign == '+') return false;

	//checks size
	if(num.size() > num1.num.size()) return true;
	if(num.size() < num1.num.size()) return false;

	//compares numbers
	for(int i = 0 ; i < (int)num.size() ; i++){
		// a > b
		if(num[i] > num1.num[i]){
			//both have positive signs so greater
			if(sign=='+') return true;
			//both negative signs so lesser
			else return false;
		}
		// a < b
		else if(num[i] < num1.num[i]){
			//both have negative signs so greater
			if(sign == '-')return true;
			//both have positive signs so it is lesser
			else return false;
		}
	}
	//if they are equal in all terms
	return false;
}

bool INT::operator >= (INT num1){
	/*
	 * [16-11-2016]
	 * overloaded comparison >= operator
	 */

	//checks signs
	if(sign == '+' && num1.sign == '-') return true;
	if(sign == '-' && num1.sign == '+') return false;

	//checks size
	if(num.size() > num1.num.size()) return true;
	if(num.size() < num1.num.size()) return false;

	//compares numbers
	for(int i = 0 ; i < (int)num.size() ; i++){
		// a > b
		if(num[i] > num1.num[i]){
			//both have positive signs so greater
			if(sign=='+') return true;
			//both negative signs so lesser
			else return false;
		}
		// a < b
		else if(num[i] < num1.num[i]){
			//both have negative signs so greater
			if(sign == '-')return true;
			//both have positive signs so it is lesser
			else return false;
		}
	}
	//if they are equal in all terms
	return true;
}

bool INT::operator < (INT num1){
	/*
	 * [16-11-2016]
	 * overloaded comparison < operator
	 */

	//checks signs
	if(sign == '+' && num1.sign == '-') return false;
	if(sign == '-' && num1.sign == '+') return true;

	//checks size
	if(num.size() > num1.num.size()) return false;
	if(num.size() < num1.num.size()) return true;

	//compares numbers
	for(int i = 0 ; i < (int)num.size() ; i++){
		// a > b
		if(num[i] > num1.num[i]){
			//both have positive signs so greater
			if(sign=='+') return false;
			//both negative signs so lesser
			else return true;
		}
		// a < b
		else if(num[i] < num1.num[i]){
			//both have negative signs so greater
			if(sign == '-')return false;
			//both have positive signs so it is lesser
			else return true;
		}
	}
	//if they are equal in all terms
	return false;
}

bool INT::operator <= (INT num1){
	/*
	 * [16-11-2016]
	 * overloaded comparison <= operator
	 */

	//checks signs
	if(sign == '+' && num1.sign == '-') return false;
	if(sign == '-' && num1.sign == '+') return true;

	//checks size
	if(num.size() > num1.num.size()) return false;
	if(num.size() < num1.num.size()) return true;

	//compares numbers
	for(int i = 0 ; i < (int)num.size() ; i++){
		// a > b
		if(num[i] > num1.num[i]){
			//both have positive signs so greater
			if(sign=='+') return false;
			//both negative signs so lesser
			else return true;
		}
		// a < b
		else if(num[i] < num1.num[i]){
			//both have negative signs so greater
			if(sign == '-')return false;
			//both have positive signs so it is lesser
			else return true;
		}
	}
	//if they are equal in all terms
	return true;
}

//ARTHIMETIC OPERATORS

INT INT::operator + (INT num1){
	/*
	 * [16-11-2016]
	 * This operator is used to add two INT data types
	 */
	INT ans;

	//checks if a>=b
	if(compare(num,num1.num)){

		//assigns the sign of bigger number to answer
		ans.sign=sign;

		//addition if signs are same
		if(sign==num1.sign)
			ans.num=add(num,num1.num);
		//subtraction if signs are different
		else
			ans.num=subtract(num,num1.num);
	}
	//number b is greater than a
	else{

		//assigns the sign of bigger number to answer
		ans.sign=num1.sign;

		//addition if signs are same
		if(sign==num1.sign)
			ans.num=add(num1.num,num);
		//subtraction if signs are different
		else
			ans.num=subtract(num1.num,num);
	}

	//makes the sign positive when number is zero
	if(ans.num[0] == '0' && ans.num.size() == 1) ans.sign='+';

	return ans;
}

INT INT::operator - (INT num1){
	/*
	 * [16-11-2016]
	 * This operator is used to subtract two INT data types
	 */
	INT ans;

	//checks if a>=b
	if(compare(num,num1.num)){

		//assigns the sign of bigger number to answer
		ans.sign=sign;

		//subtraction if signs are same
		if(sign==num1.sign)
			ans.num=subtract(num,num1.num);
		//addition if signs are different
		else
			ans.num=add(num,num1.num);
	}
	//number b is greater than a
	else{

		//assigns the sign opposite to bigger number
		ans.sign=(num1.sign=='+')?'-':'+';

		//subtraction if signs are same
		if(sign==num1.sign)
			ans.num=subtract(num1.num,num);
		//addition if signs are different
		else
			ans.num=add(num1.num,num);
	}

	//makes the sign positive when number is zero
	if(ans.num[0] == '0' && ans.num.size() == 1) ans.sign='+';

	return ans;
}

INT INT::operator *(INT num1){
	/*
	 * [17-11-2016]
	 * This * operator is overloaded to multiply two INT data
	 * supports multiplication of numbers upto 32768 (2^15) digits
	 */
	INT product;
	int i,j,k;

	//declaring int vectors since in char type limits exceeds while calculations
	vector<int> ans(num1.num.size()+1,0);
	vector<int> a,b;

	//initializing the vectors
	for(i = 0; i < (int)num.size() ; i++) a.push_back(num[i]-'0');
	for(i = 0; i < (int)num1.num.size() ; i++) b.push_back(num1.num[i]-'0');

	//long multiplication method
	for(i = 0 ;i <(int)a.size() ; i++){
		for(j = b.size()-1 ; j>= 0 ;j--){

			//multiplying single digits
			ans[i+j+1] += a[i]*b[j];

			//processing carry if any exists
			k = i+j+1;
			//looping given since the carry needs to be checked till the end
			while(ans[k] > 9){
				ans[k-1]+=ans[k]/10;
				ans[k]%=10;
				k--;
			}
		}

		//adding a 0 at the end for multiplying with the next digit
		if(i != (int)a.size()-1)
			ans.push_back(0);
	}

	//clearing the previous data
	product.num.clear();

	//converting the vector<int> to vector<char> and removind redundant zeros
	for(int i = 0; i < (int)ans.size() ; i++) product.num.push_back(ans[i]+'0');
	product.num = clean(product.num);

	//multiplying the sign
	if(sign != num1.sign && product.num[0]!='0') product.sign='-';

	return product;
}

INT INT::operator / (INT num1){
	//checks and throws zero divide error
	if(num1.num[0] == '0' && num1.num.size() == 1) throw zero_divide;

	//returns zero if dividend is zero
	if(num[0] == '0' && num.size() == 1) return INT("0");

	INT quotient;
	vector<char> num = this->num;
	//checks if the quotient is 0 or 1
	if(compare(num1.num,num)){
		// returns 0 if dividend is greater than divisor
		if(num1.num != num) return INT("0");
		//quotient is 1 if they are equal
		quotient.num[0] = '1';
		//assigns the sign to the answer
		if(num1.sign != sign) quotient.sign = '-';
		//returns the answer only when it is 1
		return quotient;
	}

	//t acts as a buffer when subtracting values from dividend
	vector<char> t;
	int i,count;

	//takes the first set of values where no. of digits are size of divisor
	for(i = 0; i < (int)num1.num.size() ; i++) t.push_back(num[i]);
	//erases the taken digits from dividend
	num.erase(num.begin(),num.begin()+num1.num.size());

	while(true){
		//count is used to count the no. of subtractions
		count=0;

		//subtracts divisor from dividend buffer t
		//until it is lesser than divisor
		//and cleans to remove redundant zeros
		while(compare(t,num1.num)){
			t=subtract(t,num1.num);
			t=clean(t);
			count++;
		}

		//pushes the count to the quotient
		quotient.num.push_back(count+'0');

		//checks for 0 in dividend and adds it to the quotient as it is
		//main purpose of this block is to reduce CPU time
		while(num[0] == '0'&&num.size() > 0 &&t.size()==1&&t[0] == '0'){
			num.erase(num.begin());
			quotient.num.push_back('0');
		}

		//breaks the loop when dividend becomes empty
		if(num.size()==0)break;

		//gets another number from dividend to bufer
		t.push_back(num[0]);
		//erases the number from dividend
		num.erase(num.begin());

		//checks number size and dividend buffer for
		//exit condition and breaks the loop
		if(!compare(t,num1.num)&&num.size()==0) break;
	}

	//removes the redundant zeros
	quotient.num = clean(quotient.num);
	return quotient;
}

INT INT::operator % (INT num1){
	//checks and throws zero divide error
	if(num1.num[0] == '0' && num1.num.size() == 1) throw zero_divide;

	//returns zero if dividend is zero
	if(num[0] == '0' && num.size() == 1) return INT("0");

	INT reminder;
	vector<char> num = this->num;
	//checks if the reminder is zero
	if(compare(num1.num,num)){
		// returns 0 if dividend and divisor are equal
		if(num1.num == num) return INT("0");
		//reminder is dividend if divisor is greater
		reminder.num = num;
		//assigns the sign to the answer
		if(sign == '-') reminder.sign = '-';
		//returns the reminder when it is equal to the dividend
		return reminder;
	}

	//t acts as a buffer when subtracting values from dividend
	vector<char> t;
	int i,count;

	//takes the first set of values where no. of digits are size of divisor
	for(i = 0; i < (int)num1.num.size() ; i++) t.push_back(num[i]);
	//erases the taken digits from dividend
	num.erase(num.begin(),num.begin()+num1.num.size());

	while(true){

		//subtracts divisor from dividend buffer t
		//until it is lesser than divisor
		//and cleans to remove redundant zeros
		while(compare(t,num1.num)){
			t=subtract(t,num1.num);
			t=clean(t);
			count++;
		}
		//checks for 0 in dividend and adds it to the quotient as it is
		//main purpose of this block is to reduce CPU time
		while(num[0] == '0'&&num.size() > 0 &&t.size()==1&&t[0] == '0'){
			num.erase(num.begin());
		}

		//breaks the loop when dividend becomes empty
		if(num.size()==0)break;

		//gets another number from dividend to bufer
		t.push_back(num[0]);
		//erases the number from dividend
		num.erase(num.begin());

		//checks number size and dividend buffer for
		//exit condition and breaks the loop
		if(!compare(t,num1.num)&&num.size()==0) break;
	}

	//removes the redundant zeros and assigns the reminder
	reminder.num = clean(t);
	return reminder;
}

INT INT::parse(string exp){
	/*
	 * [19-11-2016]
	 * parse function is used to execute to_postfix expression
	 * and fetch result as a INT type data
	 */
	//stack to store INT numbers and process the results
	vector<INT> ans;
	string postfix = to_postfix(exp);

	//used to indicate unary minus or negative numbers
	bool neg = false;

	//iterates through each character in postfix expression
	for(int i = 0 ; i < (int)postfix.length() ; i++){

		//checks for operators
		if(is_operator(postfix[i])){

			//if operators are found the result is computed and merged to a single element
			switch(postfix[i]){
			case '+':
				ans[ans.size()-2] = ans[ans.size()-2] + ans[ans.size()-1];
				break;
			case '-':
				ans[ans.size()-2] = ans[ans.size()-2] - ans[ans.size()-1];
				break;
			case '*':
				ans[ans.size()-2] = ans[ans.size()-2] * ans[ans.size()-1];
				break;
			case '/':
				ans[ans.size()-2] = ans[ans.size()-2] / ans[ans.size()-1];
				break;
			case '%':
				ans[ans.size()-2] = ans[ans.size()-2] % ans[ans.size()-1];
				break;
			}

			//clears the last element since the result is merged to the previous element
			ans.pop_back();
		}

		//checks for numbers
		else if(postfix[i] >= '0' && postfix[i] <='9'){

			//creates a string to assign to INT
			string num ="";
			//gets numbers until suffixed char _ is found
			while(postfix[i] != '_'){
				num+=postfix[i];
				i++;
			}

			//checks unary minus or negative numbers
			if(neg) num = '-'+num;
			neg=false;

			//creates a new INT and pushes to the stack
			INT a=num;
			ans.push_back(a);
		}
		else if(postfix[i] == ','){
			neg = true;
			i++;
		}
	}

	//final answer will be the only element in the stack
	return ans[0];
}
