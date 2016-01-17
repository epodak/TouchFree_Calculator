#ifndef CALCULATOR_HEADER
#define CALCULATOR_HEADER
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <string.h>
using namespace std;
class Calculator
{
private:
	int result = 0;
	bool isOperator(char ch);
	int getWeight(char ch);
	void infix2postfix(char infix[], char postfix[], int size);
	int performOperation(int op1, int op2, char op);

public:
	void calculate(const char* operatiions);
	void reset();
	int getResult();
	Calculator();
	~Calculator();
};
#endif

