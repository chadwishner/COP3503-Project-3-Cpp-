// Chad Wishner
// COP3502 Project 3

#include "pa3.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* Stack Constructor
 */
Stack::Stack(){
	top = -1;
}

/* Stack Push function
 @param string
 */
void Stack::push (string var){
	if (top == 99){
		cout << "Stack is full" << endl;
		return;
	}
	//increment top
	top++;
	
	//add string to top
	array[top] = var;
}

/* Stack Check if empty function
 True when stack has elements
 False when stack is empty
 @return bool
 */
bool Stack::isEmpty(){
	
	//initialize bool to true
	bool isTrue = true;
	
	//if empty make bool false
	if (top == -1){
		return false;
	}
	
	//return bool
	return isTrue;
}

/* Stack Pop function
 @return string
 */
string Stack::pop(){
	
	//create string to pop
	string pop;
	
	//if not empty then pop and decrement index
	if (isEmpty()){
		pop = array[top];
		top--;
		return pop;
	
	//if stack is empty
	} else {
		return "Stack Empty";
	}
}

/* Convert Stack to array with no duplicates function
 @param Stack*
 @return String array *
 */
string* convertToArray(Stack* stack){
	
	//initialize array, string temp, and bool to check if the popped string is already there
	string* array = new string[10];
	string temp;
	bool alreadyThere = false;
	
	//make all indexes ""
	for (int x = 0; x < 10; x++){
		array[x] = "";
	}
	
	//loop until stack is empty
	while (stack -> isEmpty()){
		
		//save popped string to temp
		temp = stack -> pop();
		alreadyThere = false;
		
		//if temp is already in array, make bool true
		for (int x = 0; x < 10; x++){
			if (temp == array[x]){
				alreadyThere = true;
			}
		}
		
		//increment through array
		for (int y = 0; y < 10; y++){
			
			//find the first empty slot and place string if it is not already placed
			if (array[y] == "" && !alreadyThere){
				array[y] = temp;
				alreadyThere = true;
			}
		}
		alreadyThere = false;
	}
	return array;
}

/* Print function
 @param int maxDepth, int paranthesis, string* keywords, string* identifiers, string* constants, string* operators, string* delimeters, string* syntaxErrors
 */
void print(int maxDepth, int paranthesis, string* keywords, string* identifiers, string* constants, string* operators, string* delimeters, string* syntaxErrors){
	
	if (maxDepth < 0){
		maxDepth = 0;
	}
	
	//print correct format
	int x = 0;
	cout << "The depth of nested loop(s) is " << maxDepth << endl;
	cout << "\nKeywords: ";
	while (keywords[x] != ""){
		cout << keywords[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Identifiers: ";
	while (identifiers[x]!= ""){
		cout << identifiers[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Constants: ";
	while (constants[x] != ""){
		cout << constants[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Operators: ";
	while (operators[x] != ""){
		cout << operators[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Delimiters: ";
	while (delimeters[x] != ""){
		cout << delimeters[x] << " ";
		x ++;
	}
	
	cout << endl;
	x = 0;
	cout << "\nSyntax Errors(s): ";
	
	//use helper function to check if the array is empty, if so, print NA
	if (syntaxEmpty(syntaxErrors) && paranthesis == 0){
		cout << "NA" <<endl;
	
	//else print the proper errors
	} else {
		while (syntaxErrors[x] != ""){
			cout << syntaxErrors[x] << " ";
			x ++;
		}
		if (paranthesis < 0){
			cout << ") ";
		} else if (paranthesis > 0){
			cout << "( ";
		}
		cout << endl;
	}
}

/* Check if syntax array is empty helper function
 True if not empty
 False if empty
 @param string*
 @return bool
 */
bool syntaxEmpty(string* syntaxErrors){
	bool errorsOrNah = true;
	
	//if the array has anything in it, make it false
	for (int x = 0; x < syntaxErrors -> length(); x++){
		if (syntaxErrors[x] != ""){
			errorsOrNah = false;
		}
	}
	
	return errorsOrNah;
}
/* Main
 */
int main(int argc, const char * argv[]) {
	
	//create file
	ifstream file;
	string fileName = "";
	string line;
	
	//create ints for depth
	int currentDepth = -1;
	int maxDepth = -1;
	
	//create int for paranthesis
	int paren = 0;
	
	
	//create stacks
	Stack* paranthesis = new Stack();
	Stack* depth = new Stack();
	Stack* keywords = new Stack();
	Stack* identifiers = new Stack();
	Stack* constants = new Stack();
	Stack* operators = new Stack();
	Stack* delimiters = new Stack();
	Stack* errors = new Stack();
	
	//take in user input to open file
	cout << "Please enter the name of the input file: " << endl;
	cin >> fileName;
	
	file.open(fileName);
	if (!file) {
		cout << "Unable to open file";
		exit(1);
	} else if (file.is_open()){
		
		while (getline(file, line)){
			
			//intialize counter every line
			int counter = 0;
			
			//convert to cstring so it ends in NULL
			line = line.c_str();
			
			//go line by line
			while (line[counter] != NULL){
				
				//if it is capital we know it is a keyword, and we can apheand the string with characters
				if (line[counter] >= 'A' && line[counter] <= 'Z'){
					string temp = "";
					while (line[counter] >= 'A' && line[counter] <= 'Z'){
						temp += line[counter];
						counter ++;
					}
					
					//check to get proper keyword, then do proper steps
					if (temp == "FOR"){
						keywords -> push(temp);
						depth -> push(temp);
					} else if (temp == "BEGIN"){
						currentDepth ++;
						keywords -> push(temp);
					} else if (temp == "END"){
						if (depth -> isEmpty()){
							depth -> pop();
							
							if (maxDepth < currentDepth){
								maxDepth = currentDepth;
							}
							
							currentDepth --;
						} else {
							errors -> push("Extra END");
						}
						keywords -> push(temp);
					} else {
						errors -> push(temp);
					}
				
				//if it is lower case we know it is an identifier, and we can apheand the string with characters
				} else if (line[counter] >= 'a' && line[counter] <= 'z'){
					string temp = "";
					
					while (line[counter] >= 'a' && line[counter] <= 'z'){
						temp += line[counter];
						counter ++;
					}
					identifiers -> push(temp);
				
				//parenthesis
				} else if (line[counter] == '('){
					paranthesis -> push("(");
					paren ++;
					counter ++;
				} else if (line[counter] == ')'){
					if (paranthesis -> isEmpty()){
						paranthesis -> pop();
					}
					paren --;
					counter ++;
				
				//constants
				} else if (line[counter] >= '0' && line[counter] <= '9'){
					string temp = "";
					while (line[counter] >= '0' && line[counter] <= '9'){
						temp += line[counter];
						counter ++;
					}
					constants -> push(temp);
					
				//operators
				} else if (line[counter] == '+' || line[counter] == '-' || line[counter] == '*' || line[counter] == '/' || line[counter] == '%'){
					string temp = "";
					while (line[counter] == '+' || line[counter] == '-' || line[counter] == '*' || line[counter] == '/' || line[counter] == '%'){
						temp += line[counter];
						counter ++;
					}
					
					operators -> push(temp);
				
				//equal sign
				} else if (line[counter] == '='){
					string temp = "";
					operators -> push("=");
					counter ++;
				
				//delimiters
				} else if (line[counter] == ',' ){
					delimiters -> push(",");
					counter ++;
				} else if (line[counter] == ';'){
					delimiters -> push(";");
					counter ++;
				
				//skip space
				} else {
					counter ++;
				}
			}
		}
		
	}
	
	//if there is a missing end push END to errors
	if (depth -> isEmpty()){
		errors -> push("END");
	}
	
	//create string arrays and convert the stacks to arrays
	string* keywordsString = new string[10];
	string* identifiersString = new string[10];
	string* constantsString = new string[10];
	string* operatorsString = new string[10];
	string* delimetersString = new string[10];
	string* errorsString = new string[10];
	
	keywordsString = convertToArray(keywords);
	identifiersString = convertToArray(identifiers);
	constantsString = convertToArray(constants);
	operatorsString = convertToArray(operators);
	delimetersString = convertToArray(delimiters);
	errorsString = convertToArray(errors);
	
	//call print function
	print(maxDepth, paren, keywordsString, identifiersString, constantsString, operatorsString, delimetersString, errorsString);
	
	return 0;
}
