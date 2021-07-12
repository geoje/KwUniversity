#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stack>
#include <string>
#include <vector>
using namespace std;

static const char* OPERANDS = "abc";
static const char* OPERATIONS = "@#&";
static const char* LEFT_PARENTHESIS = "({[";
static const char* RIGHT_PARENTHESIS = ")}]";
static const char* END_OF_INPUT = "EOI";
static char opr_result[3][3][3];

char evaluate_stack(stack<char>& operands, stack<char>& operations) {
	int opr, row, col;
	const char* p_ptr = strchr(OPERATIONS, operations.top());
	if (p_ptr == NULL)
		return 0;
	opr = p_ptr - OPERATIONS;
	operations.pop();
	col = strchr(OPERANDS, operands.top()) - OPERANDS;
	operands.pop();
	row = strchr(OPERANDS, operands.top()) - OPERANDS;
	operands.pop();
	operands.push(opr_result[opr][row][col]);
	return opr_result[opr][row][col];
}
char read_and_evaluate(const string& exp) {
	stack<char> operands, operations;
	const char* p_ptr;

	for (int idx = 0; idx < (int)exp.size(); idx++) {
		if (strchr(OPERANDS, exp.at(idx)) != NULL)
			operands.push(exp.at(idx));
		else if (strchr(OPERATIONS, exp.at(idx)) != NULL) {
			if (!operations.empty() && (exp.at(idx) == OPERATIONS[2]
				? operations.top() == OPERATIONS[2]
				: strchr(OPERATIONS, operations.top()) != NULL))
				evaluate_stack(operands, operations);
			operations.push(exp.at(idx));
		}
		else if (strchr(LEFT_PARENTHESIS, exp.at(idx)) != NULL)
			operations.push(exp.at(idx));
		else if ((p_ptr = strchr(RIGHT_PARENTHESIS, exp.at(idx))) != NULL) {
			int idx_par = p_ptr - RIGHT_PARENTHESIS;
			while (1) {
				if (operations.empty())
					return 0;
				if (operations.top() == LEFT_PARENTHESIS[idx_par]) {
					operations.pop();
					break;
				}
				if (evaluate_stack(operands, operations) == 0)
					return 0;
			}
		}
	}
	while (!operations.empty() && operands.size() > 1)
		if (evaluate_stack(operands, operations) == 0) return 0;
	return operands.empty() || !operations.empty() ? 0 : operands.top();
}
void read_opr_result() {
	FILE* f;
	const char* p_ptr;
	char buf;
	int opr, i, j;

	//f = fopen("operations.txt", "r");
	fopen_s(&f, "operations.txt", "r");
	if (f == NULL)
		cout << "File Open Error!" << endl;

	while((buf = fgetc(f)) != EOF) {
		if (buf == ' ' || buf == '\n')
			continue;
		if ((p_ptr = strchr(OPERATIONS, buf)) != NULL) {
			opr = p_ptr - OPERATIONS;
			i = 0; j = 0;
			continue;
		}
		if (strchr(OPERANDS, buf) != NULL) {
			opr_result[opr][i][j] = buf;
			if (++j > 2) { i++; j = 0; }
		}
	}
	fclose(f);
}

int main() {
	vector<string> expressions;
	char result;
	string exp_temp;
	read_opr_result();

	for (int used = 0; ; used++) {
		getline(cin, exp_temp);
		if (!exp_temp.compare(END_OF_INPUT))
			break;
		expressions.push_back(exp_temp);
	}
	cout << endl;
	for (string exp : expressions) {
		result = read_and_evaluate(exp);
		if (result == 0) cout << "Error!" << endl;
		else cout << result << endl;
	}
}