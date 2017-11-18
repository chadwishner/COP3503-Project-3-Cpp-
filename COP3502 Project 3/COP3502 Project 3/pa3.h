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

enum State {
	FOR,
	PARENTHESIS_VAR,
	CONSTANT,
	OPERATOR_PARENTHESIS,
	BEGIN,
	FOR_OR_EXPRESS,
	EXPRESS_OPERATOR,
	VAR_CONSTANT,
	FOR_OR_END_OR_EXP,
	END,
};

string* convertToArray(Stack* stack);

void print(int maxDepth, int paranthesis, int forAndEnds, string* keywords, string* identifiers, string* constants, string* operators, string* syntaxErrors);

bool syntaxEmpty(string* syntaxErrors);

#endif pa3_h
