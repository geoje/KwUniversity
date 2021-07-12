/*
calculator_buggy.cpp
*/

#include "std_lib_facilities.h"

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), name(n) { }
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void putback(Token t) { buffer = t; full = true; }

	void ignore(char);
};

const char let = 'L';
const char set = 'S'; //Add definition
const char clear = 'C';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const string funcNames[] = { "sqrt", "sin", "cos", "tan", "ln", "log" }; //Add mathematical functions

const double pi = 3.14159; //Pre-decleare 'pi'
const double e = 2.71828; //Pre-decleare 'e'

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case '!': //Add a factorial operator
	case '^': //Add a square operator
	case '|': //Add a absolute operator
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.unget();
		double val;
		cin >> val;
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == "let") return Token(let);
			if (s == "set") return Token(set); //Add definition
			if (s == "clear") return Token(clear);
			if (s == "quit") return Token(quit);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

int factorial(int n) {
	return n == 0 ? 1 : n * factorial(n - 1);
}
//Add mathematical functions
double func(string fname, double fvalue) {
	if (fname == "sqrt") {
		//Catch negative number for sqrt()
		if (fvalue < 0)
			error("sqrt() function cannot calculate a negative number.");
		return sqrt(fvalue);
	}
	else if (fname == "sin")
		return sin(fvalue);
	else if (fname == "cos")
		return cos(fvalue);
	else if (fname == "tan") {
		double temp = fvalue / pi + 0.5;
		double offset = abs(temp - (int)temp);
		cout << "offset: " << offset << endl;
		if (offset < 0.0001 || offset > 0.9999) //result of tan(pi) is not excatly
			error("tan() function cannot calculate a (pi/2)+(n*pi/2).");
		return tan(fvalue);
	}
	else if (fname == "ln") {//Add ln
		if (fvalue <= 0)
			error("ln() function cannot calculate a negative number and zero.");
		return log(fvalue);
	}
	else if (fname == "log") {//Add log
		if (fvalue <= 0)
			error("log() function cannot calculate a negative number and zero.");
		return log10(fvalue);
	}
}

//This function calculate '!' or '^' operator
double cal_value_next(double left);

double expression();

double primary()
{
	Token t = ts.get(), t2 = NULL; //t2 is about variables and mathematical functions
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') {
		ts.putback(t);
		error("')' expected");
	}
	//We can calculate (2*3)!
	return cal_value_next(d); //Fix logical error
	}
	case '|': //Add absolute
	{	double d = abs(expression());
	t = ts.get();
	if (t.kind != '|') {
		ts.putback(t);
		error("close'|' expected");
	}
	//We can calculate |2*3|!
	return cal_value_next(d);
	}
	case '-':
		return -primary();
	case '+': //Extend unary plus
		return primary();
	case number:
		//We can calculate 2*4! (rather than (2*3)!)
		return cal_value_next(t.value);
	case name:
		//Add mathematical functions
		for (string funcName : funcNames)
			if (t.name == funcName) {
				t2 = ts.get();
				if (t2.kind != '(') //This code makes the function name available to you as the variable name
				{
					ts.putback(t2);
					break;
				}
				ts.putback(t2);
				return func(t.name, primary()); //We can calculate sin(pi*(1/3))
			}
		return cal_value_next(get_value(t.name));
	default:
		ts.putback(t);
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '(': //We can calculate (2)(4)
			ts.putback(t);
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%': //Add a modulo operator (Consider the quotient to be a natural number)
		{	double d = primary();
		left -= d * (int)(left / d);
		break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double cal_value_next(double left) {
	Token t = ts.get();
	switch (t.kind)
	{
	case '!': //Add a factorial operator
		return factorial((int)abs(left));
	case '^': //Add a square operator
		return pow(left, primary());
	default:
		ts.putback(t);
		return left;
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

//definition
double definition() {
	Token t = ts.get();
	if (t.kind != name) error("name expected in definition");
	string name = t.name;
	if (!is_declared(name)) error(name, " is not declared");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in definition of ", name);
	double d = expression();
	set_value(name, d);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	case set: //Add definition
		return definition();
	default:
		ts.putback(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

int calculate()
{
	cout << prompt;
	while (true) try {
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == clear) {
			system("cls");
			cout << prompt;
			continue;
		}
		if (t.kind == quit) return 0;
		ts.putback(t);
		cout << result << statement() << endl;
		if (cin.get() == '\n')
			cout << prompt;
		cin.unget();
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
		cout << prompt;
	}
}

int main()
try
{
	names.push_back(Variable("pi", pi)); //Pre-decleare 'pi'
	names.push_back(Variable("e", e)); //Pre-decleare 'e'
	return calculate();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "exception\n";
	return 2;
}
