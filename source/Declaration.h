#pragma once
#include <string>

using namespace std;

enum class declaretype {
	procedure,
	statement,
	read,
	print,
	whiles,
	ifs,
	variable,
	constant,
	assign,
	call,
	none
};

inline declaretype convertToken(const string& token) {
	if (token == "procedure") return declaretype::procedure;
	else if(token == "stmt") return declaretype::statement;
	else if (token == "read") return declaretype::read;
	else if (token == "print") return declaretype::print;
	else if (token == "while") return declaretype::whiles;
	else if (token == "if") return declaretype::ifs;
	else if (token == "variable") return declaretype::variable;
	else if (token == "constant") return declaretype::constant;
	else if (token == "assign") return declaretype::assign;
	else if(token == "call") return declaretype::call;
	else {
		return declaretype::none;
	}
}

enum class patterntype {
	pattern
};

inline patterntype convertpatternToken(const string& token) {
	if (token == "pattern") return patterntype::pattern;
}