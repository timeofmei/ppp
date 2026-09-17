
/*
        calculator08buggy.cpp

        Helpful comments removed.

        We have inserted 3 bugs that the compiler will catch and 3 that it
   won't.
*/

#include "PPP.h"

struct Token {
    char kind;
    double value;
    string name;
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, double val) : kind(ch), value(val) {}
    Token(char ch, string n) : kind(ch), name(n) {}
};

class Token_stream {
    bool full;
    Token buffer;

  public:
    Token_stream() : full(0), buffer(0) {}

    Token get();
    void unget(Token t)
    {
        buffer = t;
        full = true;
    }

    void ignore(char);
};

Token_stream ts;

const char let = 'L';
const char quit = 'q';
const char output = ';';
const char number = '8';
const char name = 'a';
const char square_root = 'S';
const char assignment = '=';

Token Token_stream::get()
{
    if (full) {
        full = false;
        return buffer;
    }
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
    case '9': {
        cin.unget();
        double val;
        cin >> val;
        return Token(number, val);
    }
    default:
        if (isalpha(ch) || ch == '_') {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
                s += ch;
            cin.unget();
			if (s == "sqrt")
				return Token(square_root);
			if (s == "exit") return Token('q');
            return Token{name, s};
        } else if (ch == '#') {
			return Token(let);
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
        if (ch == c)
            return;
}

struct Variable {
    string name;
    double value;
    Variable(string n, double v) : name(n), value(v) {}
};

vector<Variable> names;

double get_value(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s)
            return names[i].value;
    error("get: undefined name ", s);
}

void set_value(string s, double d)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s) {
            names[i].value = d;
            return;
        }
    error("set: undefined name ", s);
}

bool is_declared(string s)
{
    for (int i = 0; i < names.size(); ++i)
        if (names[i].name == s)
            return true;
    return false;
}

double expression();

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(': {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') {
			ts.unget(t);
			error("')' expected");
		}
            
        return d;
    }
    case '-':
        return -primary();
	case '+':
		return primary();
    case number:
        return t.value;
    case name: {
		Token t2 = ts.get();
		if (t2.kind == assignment) {
			double d = expression();
			set_value(t.name, d);
			return d;
		}
		ts.unget(t2);
		return get_value(t.name);
	}
	case square_root: {
		t = ts.get();
		if (t.kind != '(') {
			ts.unget(t);
			error("'(' expected after sqrt");
		}

		double d = expression();

		t = ts.get();
		if (t.kind != ')') {
			ts.unget(t);
			error("') expected after sqrt");
		}

		if (d < 0)
			error("sqrt of negative number");

		return sqrt(d);
	}
    default:
		ts.unget(t);
        error("primary expected");
    }
}

double term()
{
    double left = primary();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
        case '*':
            left *= primary();
            break;
        case '/': {
            double d = primary();
            if (d == 0)
                error("divide by zero");
            left /= d;
            break;
        }
		case '%': {
			double d = primary();
			if (d == 0)
				error("%% by zero");
			left = fmod(left, d);
			break;
		}
        default:
            ts.unget(t);
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
            ts.unget(t);
            return left;
        }
    }
}

double define_name(string var, double val)
{
    if (is_declared(var))
        error(var, " declared twice");
    names.push_back(Variable{var, val});
    return val;
}

double declaration()
{
    Token t = ts.get();
    if (t.kind != 'a') {
		ts.unget(t);
		error("name expected in declaration");
	}
    string name = t.name;
    if (is_declared(name))
        error(name, " declared twice");
    Token t2 = ts.get();
    if (t2.kind != '=') {
		ts.unget(t2);
		error("= missing in declaration of ", name);
	}
    double d = expression();
    define_name(name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration();
    default:
        ts.unget(t);
        return expression();
    }
}

void clean_up_mess() { ts.ignore(output); }

const string prompt = "> ";
const string result = "= ";

void calculate()
{
    while (true)
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == output)
                t = ts.get();
            if (t.kind == quit)
                return;
            ts.unget(t);
            cout << result << statement() << endl;
        } catch (runtime_error &e) {
            cerr << e.what() << endl;
            clean_up_mess();
        }
}

int main()

try {
	define_name("k", 1000);
    calculate();
    return 0;
} catch (exception &e) {
    cerr << "exception: " << e.what() << endl;
    char c;
    while (cin >> c && c != ';')
        ;
    return 1;
} catch (...) {
    cerr << "exception\n";
    char c;
    while (cin >> c && c != ';')
        ;
    return 2;
}
