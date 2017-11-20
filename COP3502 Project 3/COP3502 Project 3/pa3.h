//  pa3.h
//  COP3502 Project 3

#ifndef pa3_h
#define pa3_h
#include <string>
#include <iostream>

using namespace std;

class Stack {
	private :	string array[100];
				int top;
	
	public :	Stack();
				void push (string var);
				string pop ();
				bool isEmpty();
};

string* convertToArray(Stack* stack);

void print(int maxDepth, int paranthesis, string* keywords, string* identifiers, string* constants, string* operators, string* delimeters, string* syntaxErrors);

bool syntaxEmpty(string* syntaxErrors);

#endif pa3_h
