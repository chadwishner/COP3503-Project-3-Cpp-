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
	
	int depth = 0;
	int paranthesis = 0;
	
	Stack* keywords = new Stack();
	Stack* identifiers = new Stack();
	Stack* constants = new Stack();
	Stack* operators = new Stack();
	Stack* Delimiters = new Stack();
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
						depth ++;
					} else {
						errors -> push(nextExp);
					}
					state = FOR_OR_EXPRESS;
					break;
					
				case FOR_OR_EXPRESS:
					if (nextExp == "FOR"){
						keywords -> push("FOR");
						state = PARENTHESIS_VAR;
					} else{
						identifiers -> push(nextExp.substr(0, nextExp.find('=')));
						state = PARENTHESIS_VAR;
					}
					break;
					
				case EXPRESS_OPERATOR:

					break;
				case VAR_CONSTANT:

					break;
				case FOR_OR_END:

					break;
				case END:

					break;
			}
			//check for loops, if loop then check for begin, if begin then check for end
			
			
		}
	}
	
	
	return 0;
}

//use stack to hold syntax errors
//use stack to hold which keywords are used
//use stack to hold identifiers
//use stack to hold constants
//use stack to hold operators
//use stack to hold delimets
