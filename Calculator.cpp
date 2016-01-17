#include "Calculator.h"


Calculator::Calculator()
{
}


Calculator::~Calculator()
{
}



// birinci sayiya atama yapilacak
void Calculator::calculate(const char *operations){
	char postfix[20] , buffer[15];
	stack<int> s;
	char infix[20];
	strcpy(infix, operations);
	infix2postfix(infix, postfix, strlen(operations));
	int i, op1, op2, len, j, x;
	len = strlen(postfix);
	j = 0;

	for (i = 0; i<len; i++){

		if (postfix[i] >= '0' && postfix[i] <= '9'){
			buffer[j++] = postfix[i];
		}
		else if (postfix[i] == ' '){
			if (j>0){
				buffer[j] = '\0';
				x = atoi(buffer);
				s.push(x);
				j = 0;
			}
		}

		else if (isOperator(postfix[i])){
			op1 = s.top();
			s.pop();
			op2 = s.top();
			s.pop();
			s.push(performOperation(op1, op2, postfix[i]));
		}
	}
	result = s.top();
}

void Calculator::reset(){
}


int Calculator::getWeight(char ch) {
	switch (ch) {
	case '/':
	case '*': return 2;
	case '+':
	case '-': return 1;
	default: return 0;
	}
}


int Calculator::getResult(){
	return result;
}

// convert infix expression to postfix using a stack
void Calculator::infix2postfix(char infix[], char postfix[], int size) {
	stack<char> s;
	int weight;
	int i = 0;
	int k = 0;
	char ch;
	// iterate over the infix expression   
	while (i < size) {
		ch = infix[i];

		weight = getWeight(ch);
		if (weight == 0) {
			// we saw an operand
			// simply append it to postfix expression
			postfix[k++] = ch;
		}
		else {
			postfix[k++] = ' ';
			// we saw an operator
			if (s.empty()) {
				// simply push the operator onto stack if
				// stack is empty
				s.push(ch);

			}
			else {
				// pop of all the operators from the stack and
				// append it to the postfix expression till we
				// see an operator with a lower precedence that
				// the current 
				while (!s.empty() && s.top() != '(' &&
					weight <= getWeight(s.top())) {
					postfix[k++] = s.top();
					s.pop();

				}

				// push the current operator onto stack
				s.push(ch);
			}

		}
		i++;
	}
	// pop of the remaining operators present in the stack
	// and append it to postfix expression 
	while (!s.empty()) {
		postfix[k++] = ' ';
		postfix[k++] = s.top();
		s.pop();
	}
	postfix[k] = 0; // null terminate the postfix expression 
}


bool Calculator::isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	else
		return false;
}


int Calculator::performOperation(int op1, int op2, char op)
{
	int ans;
	switch (op){
	case '+':
		ans = op2 + op1;
		break;
	case '-':
		ans = op2 - op1;
		break;
	case '*':
		ans = op2 * op1;
		break;
	case '/':
		ans = op2 / op1;
		break;
	}
	return ans;
}