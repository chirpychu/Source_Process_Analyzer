#include "Tokenizer.h"
#include <iostream>

// constructor
Tokenizer::Tokenizer() {}

// destructor
Tokenizer::~Tokenizer() {}

// method to tokenize a program / query string
// it currently tokenizes the string into a vector of 
// words (any alphanumeric sequence of characters starting with a letter, e.g., "num1"),
// numbers (any numeric sequence of characters, e.g., "1001"),
// and punctuations ("=", ";", "{", "}").
// it should be extended as needed to handle additional SIMPLE / PQL grammar rules.
void Tokenizer::tokenize(string text, vector<string>& tokens) {
	tokens.clear();
	string token;
	
	unsigned int i = 0;
	while (i < text.length()) {
		char ch = text.at(i);
		
		if (isdigit(ch)) { // scan for a numeric sequence
			token.push_back(ch);
			i++;

			while (i < text.length()) {
				ch = text.at(i);
				if (isdigit(ch)) {
					token.push_back(ch);
					i++;
				}
				else {
					break;
				}
			}

			tokens.push_back(token);
			token.clear();
		}
		else if (isalpha(ch)) { // scan for an alphanumeric sequence starting with a letter 
			
			token.push_back(ch);
			i++;

			while (i < text.length()) {
				ch = text.at(i);
				if (isalpha(ch) || isdigit(ch) || ch == '*' || ch == '+' || ch == '-' || ch == '%' || ch == '/') {
					token.push_back(ch);
					i++;
				}
				else {
					break;
				}
			}

			tokens.push_back(token); 
			token.clear();
		}
		else if (ch == '=' || ch == ';' || ch == '{' || ch == '}' || ch == '+' || ch == '-' || ch == '*' || ch == '<' || ch == '>' || ch == '!' || ch == '(' || ch == ')' || ch == '%' || ch == '/') { // scan for punctuations
			token.push_back(ch);
			i++;

			tokens.push_back(token);
			token.clear();
		}
		else if (ch == '_') { 

			token.push_back(ch);
			i++;

			while (i < text.length()) {
				ch = text.at(i);
				if (ch == '_') {
					token.push_back(ch);
					i++;
				}
				else {
					break;
				}
			}

			tokens.push_back(token);
			token.clear();
		}
		else {
			i++;
		}
	}
}
