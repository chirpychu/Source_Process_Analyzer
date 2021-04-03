#pragma once

#include "Tokenizer.h"
#include <sstream>
#include <fstream>
#include <vector>
#include "Database.h"
#include "Tokenizer.h"
#include <stack>

using namespace std;

class verify {
public:
	static bool isNumber(string tokens)
	{
		for (int i = 0; i < tokens.length(); i++)
			if (isdigit(tokens[i]))
				return true;

		return false;
	}
	static bool isUnderscore(string tokens)
	{
		for (int i = 0; i < tokens.length(); i++) {
			if (tokens[i] == '_') {
				return true;
			}
		}
		return false;
	}
	static bool isSymbol(string tokens)
	{
		for (int i = 0; i < tokens.length(); i++) {
			if (tokens[i] == ',' || tokens[i] == '<' || tokens[i] == '>') {
				return true;
			}
		}
		return false;
	}
	static bool isAlpha(string program)
	{
		for (int i = 0; i < program.length(); i++)
			if (isalpha(program[i]) == false)
				return false;

		return true;
	}
};