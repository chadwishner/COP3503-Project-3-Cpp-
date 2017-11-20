// Chad Wishner
// COP3502 Project 3

#include "pa3.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Stack::Stack(){
	top = -1;
}

void Stack::push (string var){
	if (top == 99){
		cout << "Stack is full" << endl;
		return;
	}
	top++;
	array[top] = var;
}

bool Stack::isEmpty(){
	bool isTrue = true;
	if (top == -1){
		return false;
	}
	return isTrue;
}

string Stack::pop(){
	string pop;
	if (isEmpty()){
		pop = array[top];
		top--;
		return pop;
	} else {
		return "Stack Empty";
	}
}

string* convertToArray(Stack* stack){
	string* array = new string[10];
	string temp;
	bool alreadyThere = false;
	
	for (int x = 0; x < 10; x++){
		array[x] = "";
	}
	
	while (stack -> isEmpty()){
		temp = stack -> pop();
		alreadyThere = false;
		for (int x = 0; x < 10; x++){
			if (temp == array[x]){
				alreadyThere = true;
			}
		}
		for (int y = 0; y < 10; y++){
			if (array[y] == "" && !alreadyThere){
				array[y] = temp;
				alreadyThere = true;
			}
		}
		alreadyThere = false;
	}
	return array;
}

void print(int maxDepth, int paranthesis, int forAndEnds, string* keywords, string* identifiers, string* constants, string* operators, string* delimeters, string* syntaxErrors){
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
	
	if (syntaxEmpty(syntaxErrors)){
		cout << "NA" <<endl;
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
		if (forAndEnds > 0){
			cout << "END ";
		}
		cout << endl;
	}
}

bool syntaxEmpty(string* syntaxErrors){
	bool errorsOrNah = true;
	
	for (int x = 0; x < syntaxErrors -> length(); x++){
		if (syntaxErrors[x] != ""){
			errorsOrNah = false;
		}
	}
	
	return errorsOrNah;
}

int main(int argc, const char * argv[]) {
	ifstream file;
	string fileName = "";
	
	string line;
	string nextExp;
	
	int currentDepth = 0;
	int maxDepth = 0;
	
	int forAndEnds = 0;
	int paren = 0;
	
	Stack* paranthesis = new Stack();
	Stack* depth = new Stack();
	Stack* keywords = new Stack();
	Stack* identifiers = new Stack();
	Stack* constants = new Stack();
	Stack* operators = new Stack();
	Stack* delimiters = new Stack();
	Stack* errors = new Stack();
	
	cout << "Please enter the name of the input file: " << endl;
	cin >> fileName;
	
	file.open(fileName);
	if (!file) {
		cout << "Unable to open file";
		exit(1);
	} else if (file.is_open()){
		
		while (getline(file, line)){
			
			int counter = 0;
			
			line = line.c_str();
			
			while (line[counter] != NULL){
				
				if (line[counter] >= 'A' && line[counter] <= 'Z'){
					string temp = "";
					while (line[counter] >= 'A' && line[counter] <= 'Z'){
						temp += line[counter];
						counter ++;
					}
					
					if (temp == "FOR"){
						keywords -> push(temp);
					} else if (temp == "BEGIN"){
						depth -> push(temp);
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
							errors -> push("Extra End");
						}
						keywords -> push(temp);
					} else {
						errors -> push(temp);
					}
					
				} else if (line[counter] >= 'a' && line[counter] <= 'z'){
					string temp = "";
					
					while (line[counter] >= 'a' && line[counter] <= 'z'){
						temp += line[counter];
						counter ++;
					}
					identifiers -> push(temp);
					
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
				} else if (line[counter] >= '0' && line[counter] <= '9'){
					string temp = "";
					while (line[counter] >= '0' && line[counter] <= '9'){
						temp += line[counter];
						counter ++;
					}
					constants -> push(temp);
					
				} else if (line[counter] == '+' || line[counter] == '-' || line[counter] == '*' || line[counter] == '/' || line[counter] == '%'){
					string temp = "";
					while (line[counter] == '+' || line[counter] == '-' || line[counter] == '*' || line[counter] == '/' || line[counter] == '%'){
						temp += line[counter];
						counter ++;
					}
					
					operators -> push(temp);
					
				} else if (line[counter] == '='){
					string temp = "";
					operators -> push("=");
					counter ++;
					
				} else if (line[counter] == ',' ){
					delimiters -> push(",");
					counter ++;
				} else if (line[counter] == ';'){
					delimiters -> push(";");
					counter ++;
				} else {
					counter ++;
				}
			}
		}
		
	}
	
	if (depth -> isEmpty()){
		errors -> push("END");
	}
	
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
	
	print(maxDepth, paren, forAndEnds, keywordsString, identifiersString, constantsString, operatorsString, delimetersString, errorsString);
	
	return 0;
}
