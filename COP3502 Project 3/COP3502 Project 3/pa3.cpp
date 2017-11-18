// Chad Wishner
// COP3502 Project 3


#include "pa3.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//string keywords[] = {"BEGIN", "END", "FOR"};
//string operators[] = {"&&", "||", "=", "<", ">", "<=", ">=", "==","!","!=", "--", "++", "+", "-", "*", "/"};
//string delimiters[] = {"(",")",",",";"};


int paran = 0;

int main(int argc, const char * argv[]) {
	ifstream file;
	string fileName = "";
	
	string line;
	string nextExp;
	
	int forAndEnds = 0;
	int currentDepth = 0;
	int maxDepth = 0;
	int paranthesis = 0;
	
	Stack* keywords = new Stack();
	Stack* identifiers = new Stack();
	Stack* constants = new Stack();
	Stack* operators = new Stack();
//	Stack* Delimiters = new Stack();
	Stack* errors = new Stack();
	
	cout << "Please enter the name of the input file: " << endl;
	cin >> fileName;
	
	file.open(fileName);
	if (!file) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	} else if (file.is_open()){
		State state = FOR;
		
		while (file.good()){
			file >> nextExp;
			
			int index;
			string var;
			
			switch(state){
				case FOR:
					keywords -> push("FOR");
					forAndEnds ++;
					state = PARENTHESIS_VAR;
					break;
					
				case PARENTHESIS_VAR:
					index = 0;
					var = "";
					while (nextExp[index] == '(' || index != nextExp.length() - 1){
							paranthesis ++;
							if (index < nextExp.length() - 1){
								index ++;
							}
						}
					while (nextExp[index] !=  ',' || index != nextExp.length() - 1){
						var += nextExp[index];
						if (index < nextExp.length() - 1){
							index ++;
						}
					}
					identifiers -> push(var);
					
					state = CONSTANT;
					break;
					
				case CONSTANT:
					index = 0;
					var = "";
					while (nextExp[index] !=  ',' || index != nextExp.length() - 1){
						var += nextExp[index];
						if (index < nextExp.length() - 1){
							index ++;
						}
					}
					
					constants -> push(var);
					state = OPERATOR_PARENTHESIS;
					break;
					
				case OPERATOR_PARENTHESIS:
					index = 0;
					if (nextExp.substr(0, 2) == "++"){
						operators -> push("++");
						index = 2;
					} else if (nextExp.substr(0, 2) == "--"){
						operators -> push("--");
						index = 2;
					}
					while (nextExp[index] == ')' || index != nextExp.length() - 1){
						paranthesis --;
						if (index < nextExp.length() - 1){
							index ++;
						}
					}
					state = BEGIN;
					break;
					
				case BEGIN:
					if (nextExp == "BEGIN"){
						keywords -> push("BEGIN");
						currentDepth ++;
						if (currentDepth > maxDepth){
							maxDepth = currentDepth;
						}
					} else {
						errors -> push(nextExp);
					}
					state = FOR_OR_EXPRESS;
					break;
					
				case FOR_OR_EXPRESS:
					if (nextExp == "FOR"){
						keywords -> push("FOR");
						forAndEnds ++;
						state = PARENTHESIS_VAR;
					} else{
						identifiers -> push(nextExp.substr(0, nextExp.find('=')));
						state = PARENTHESIS_VAR;
					}
					break;
					
				case EXPRESS_OPERATOR:
					operators -> push(nextExp);
					state = VAR_CONSTANT;
					break;
					
				case VAR_CONSTANT:
					constants -> push(nextExp);
					state = FOR_OR_END_OR_EXP;
					break;
					
				case FOR_OR_END_OR_EXP:
					if (nextExp == "FOR"){
						keywords -> push("FOR");
						forAndEnds ++;
						state = PARENTHESIS_VAR;
					} else if (nextExp == "END"){
						keywords -> push("END");
						forAndEnds --;
						currentDepth --;
					} else if (nextExp == "+" || nextExp == "-" || nextExp == "/" || nextExp == "*" || nextExp == "%"){
						operators -> push(nextExp);
						state = VAR_CONSTANT;
					} else if (!file.good()){
						break;
					}
					break;

					//is this thing even necessary
				case END:

					break;
			}
		}
	}
	string* keywordsString = new string[10];
	string* identifiersString = new string[10];
	string* constantsString = new string[10];
	string* operatorsString = new string[10];
	string* errorsString = new string[10];
	
	keywordsString = convertToArray(keywords);
	identifiersString = convertToArray(identifiers);
	constantsString = convertToArray(constants);
	operatorsString = convertToArray(operators);
	errorsString = convertToArray(errors);
	
	print(maxDepth, keywordsString, identifiersString, constantsString, operatorsString, errorsString);

	return 0;
}

string* convertToArray(Stack stack){
	string* array = new string[10];
	string temp;
	bool alreadyThere = false;
	
	while (stack.isEmpty()){
		temp = stack.pop();
		for (int x = 0; x < array -> length(); x++){
			if (temp == array[x]){
				alreadyThere = true;
			}
		}
		for (int y = 0; y < array -> length(); y++){
			if (array[y].compare(NULL) == 0 && !alreadyThere){
				array[y] = temp;
			}
		}
		alreadyThere = false;
	}
	return array;
}

void print(int maxDepth, int paranthesis, int forAndEnds, string* keywords, string* identifiers, string* constants, string* operators, string* syntaxErrors){
	int x = 0;
	cout << "The depth of nested loop(s) is " << maxDepth << endl;
	cout << "Keywords: ";
	while (keywords[x].compare(NULL) != 0){
		cout << keywords[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Identifiers: ";
	while (identifiers[x].compare(NULL) != 0){
		cout << identifiers[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Constants: ";
	while (constants[x].compare(NULL) != 0){
		cout << constants[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Operators: ";
	while (constants[x].compare(NULL) != 0){
		cout << constants[x] << " ";
		x ++;
	}
	cout << endl;
	x = 0;
	cout << "Delimiters: ; ," << endl;
	cout << "Syntax Errors(s): ";
	
	if (syntaxEmpty(syntaxErrors)){
		cout << "NA" <<endl;
	} else {
		while (syntaxErrors[x].compare(NULL) != 0){
			cout << syntaxErrors[x] << " ";
			x ++;
		}
		if (paranthesis < 0){
			cout << "( ";
		} else if (paranthesis > 0){
			cout << ") ";
		}
		if (forAndEnds < 0){
			cout << "Exatra END ";
		} else if (forAndEnds > 0){
			cout << "END ";
		}
		cout << endl;
	}
}

bool syntaxEmpty(string* syntaxErrors){
	bool errorsOrNah = false;
	
	for (int x = 0; x < syntaxErrors -> length(); x++){
		if (syntaxErrors[x].compare(NULL) == 0){
			errorsOrNah = true;
		}
	}
	
	return errorsOrNah;
}

//fix syntax errors, must count paranthesis, must count ends, if nothing then must print NA
