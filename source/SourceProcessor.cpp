#include "SourceProcessor.h"
#include "postfix.h"

//helper functions 
bool isNumber(string program)
{
	for (int i = 0; i < program.length(); i++)
		if (isdigit(program[i]) == false)
			return false;

	return true;
}

bool isAlpha(string program)
{
	for (int i = 0; i < program.length(); i++)
		if (isalpha(program[i]) == false)
			return false;

	return true;
}

bool isSymbol(string program)
{
	for (int i = 0; i < program.length(); i++)
		if (program[i] == '*' || program[i] == '+' || program[i] == '-' || program[i] == '/' || program[i] == '%')
			return true;

	return false;
}

//string convertPostfix(string infix) {
//	int i;  // Variable declarations
//	char mychar;
//	string postfix = "";
//	stack<char> char_stack;
//
//	for (i = 0; i < infix.length(); i++) {  // Iterate through all the characters
//		mychar = infix[i];  // temp_storage
//
//		if (IsOpeningBracket(mychar)) {
//			// If the character is opening bracket then push it onto stack.
//			char_stack.push(mychar);
//		}
//		else if (IsClosingBracket(mychar)) {
//			// If it is closing bracket then then do the following things from the 
//			// stack.
//			// 1. Pop all elements until opening bracket is encountered or stack 
//			// becomes empty.
//			while (!IsOpeningBracket(char_stack.top())) {
//				postfix += char_stack.top();
//				char_stack.pop();
//				if (char_stack.empty()) {
//					break;
//				}
//			}
//			// 2. Popping the opening bracket after handling segmentation fault. 
//			if (!char_stack.empty()) {
//				char_stack.pop();
//			}
//		}
//		else if (IsNumber(mychar)) {
//			// If the character is a number.
//			postfix += mychar;
//		}
//		else if (isalpha(mychar)) {
//			postfix += mychar;
//		}
//		else if (IsOperator(mychar)) {
//			// If the chacter is an operator then do this.
//			if (char_stack.empty() || IsOpeningBracket(char_stack.top())) {
//				char_stack.push(mychar);
//				continue;
//			}
//
//			// Check for the precedence first then do the approprite thing.
//			if (CheckPrecedence(mychar, char_stack.top())) {
//				char_stack.push(mychar);
//			}
//			else {
//				while (!IsOpeningBracket(char_stack.top())) {
//					postfix += char_stack.top();
//					char_stack.pop();
//					if (char_stack.empty()) {
//						break;
//					}
//				}
//				char_stack.push(mychar);
//			}
//		}
//	}
//
//	// If the stack is still not empty and contain some characters then do this.
//	while (!char_stack.empty()) {
//		postfix += char_stack.top();
//		char_stack.pop();
//	}
//	return postfix;
//}

// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplifed logic.
// You should modify this method to complete the logic for handling all the required syntax.

void SourceProcessor::process(string program) {
	// initialize the datbase
	Database::initialize();

	// tokenize the program
	Tokenizer tk;
	vector<string> tokens;
	tk.tokenize(program, tokens);

	// This logic is highly simplified based on iteration 1 requirements and 
	// the assumption that the programs are valid.
	int tempr = 0;
	int tempbracket = 0;
	int parentNumber = 0;
	int procedure = 0;
	string procedureNumber, procedureName;
	string variableName;
	string printNumber;
	string constantNumber;
	string readName;
	string readNumber;
	string assignNumber;
	string statementNumber;
	string statementType;
	string stmtlist;
	string assignVar;
	string callName;
	int statementNum = 1;
	int procedureNum = 0;
	stack<string> temp;
	int ifstmtlist;
	int whilestmtlist;
	vector<string> rhs;
	int nestinglvl = 0;
	stack<string> ifelse;
	stack<string> whileline;
	vector<string> whilecondition;
	vector<string> ifcondition;
	string wordcondition;
	int count = 0;
	string parentName = to_string(0);
	int parent = 0;
	string parentlvl = to_string(0);
	string nest = to_string(0);
	int parentnest = 0;
	/*if (tokens[i] == "=") {
	string temp;
	while (tokens[i] != ";") {
		i++;
		rhs.push_back(tokens[i]);
	}
	statementNumber = to_string(statementNum);
	Database::insertexpression(statementNumber, rhs);
}*/
	for (int i = 0; i < tokens.size(); i++) {

		if (tokens[i] == "procedure") {
			procedure++;
			procedureName = tokens[i + 1];
			procedureNum++;
			procedureNumber = to_string(procedureNum);
			// insert the procedure into the database
			Database::insertProcedure(procedureNumber, procedureName);

		}
		else if (tokens[i] == "while") {
			whileline.push(tokens[i]);
			statementType = "while";
			statementNumber = to_string(statementNum);
			Database::insertWhile(statementNumber);
			parentName = "while";
			callName = "";
			parent++;
			parentlvl = to_string(parent);
			//insert statement number into db
			Database::insertStatement(statementNumber, statementType, stmtlist, procedureName, parentName, parentlvl, nest, callName);

			int j = 0;
			j = i + 1;
			while (tokens[j] != ")") {
				if (isAlpha(tokens[j])) {
					variableName = tokens[j];
					Database::insertVariable(statementNumber, variableName, procedureName);
				}
				j++;
			}
		}
		else if (tokens[i] == "if") {
			parentName = "if";
			callName = "";
			parent++;
			parentlvl = to_string(parent);
			ifelse.push(tokens[i]);
			statementType = "if";
			statementNumber = to_string(statementNum);
			//insert statement number into db
			Database::insertIf(statementNumber);
			Database::insertStatement(statementNumber, statementType, stmtlist, procedureName, parentName, parentlvl, nest, callName);

			int j = 0;
			j = i + 1;
			while (tokens[j] != ")") {
				if (isAlpha(tokens[j])) {
					variableName = tokens[j];
					Database::insertVariable(statementNumber, variableName, procedureName);
				}
				j++;
			}
		}
		else if (tokens[i] == "=" && tokens[i - 1] != "=") {

			variableName = tokens[i - 1];

			//convert int to string
			assignNumber = to_string(statementNum);

			if (ifelse.empty() || whileline.empty()) {

				assignVar = tokens[i - 1];
				//store the assign statement line number to db
				Database::insertAssignment(assignNumber, assignVar);

				statementType = "assign";

				statementNumber = to_string(statementNum);
				callName = "";
				//insert the variable into the database
				Database::insertVariable(statementNumber, variableName, procedureName);
				//insert statement number into db
				Database::insertStatement(statementNumber, statementType, stmtlist, procedureName, parentName, parentlvl, nest, callName);
				if (tokens[i] == "=") {
					int j = i + 1;
					string rhs = "";
					while (tokens[j] != ";") {
						rhs = rhs + tokens[j];
						j++;
					}
					string temp = rhs;
					Database::insertexpression(statementNumber, temp);
				}
				if (isAlpha(tokens[i + 1])) {
					variableName = tokens[i + 1];
					Database::insertExpr(statementNumber, variableName, procedureName);
				}
			}
			else {
				ifelse.pop();
				whileline.pop();
			}
		}
		else if (isSymbol(tokens[i])) {
			variableName = tokens[i + 1];
			Database::insertExpr(statementNumber, variableName, procedureName);
		}
		else if (tokens[i] == "print") {
			callName = "";

			//convert int to string
			printNumber = to_string(statementNum);
			string printName = tokens[i + 1];
			variableName = tokens[i + 1];
			Database::insertVariable(printNumber, variableName, procedureName);
			//insert the print into the database
			Database::insertPrint(printNumber, printName);

			statementType = "print";
			statementNumber = to_string(statementNum);
			//insert statement number into db
			Database::insertStatement(statementNumber, statementType, stmtlist, procedureName, parentName, parentlvl, nest, callName);
		}
		else if (tokens[i] == "read") {
			callName = "";
			readName = tokens[i + 1];

			readNumber = to_string(statementNum);

			//insert the read as variable into the database
			Database::insertVariable(readNumber, readName, procedureName);

			//insert the read into the db
			Database::insertRead(readNumber, readName);
			statementType = "read";
			statementNumber = to_string(statementNum);
			//insert statement number into db
			Database::insertStatement(statementNumber, statementType, stmtlist, procedureName, parentName, parentlvl, nest, callName);
		}
		if (tokens[i] == "call") {
			callName = tokens[i + 1];
			statementNumber = to_string(statementNum);
			statementType = "call";
			Database::insertStatement(statementNumber, statementType, stmtlist, procedureName, parentName, parentlvl, nest, callName);
		}
		if (isNumber(tokens[i])) {
			//the token will be the constant value
			constantNumber = tokens[i];
			//insert the constant value into the db
			statementNumber = to_string(statementNum);
			Database::insertConstant(statementNumber, constantNumber);
		}

		if (tokens[i] == "if" || tokens[i] == ";" || tokens[i] == "while") {
			statementNum++;

			if (tokens[i] == "if") {
				parentName = "if";
				parentlvl = to_string(parent);
				
				parentnest++;
				parentNumber = parentnest;
				nest = to_string(parentnest);
			}
			else if (tokens[i] == "while") {
				parentName = "while";

				parentnest++;

				nest = to_string(parentnest);
			}
		}

		if (tokens[i] == "procedure" || tokens[i] == "while" || tokens[i] == "then" || tokens[i] == "else") {
			temp.push(tokens[i]);
			nestinglvl++;

		}
		else if (tokens[i] == "while") {
			tempbracket++;
		}
		else if (temp.top() == "else") {
			
			parentName = "if";
			parentlvl = to_string(parent);
			nestinglvl++;
			tempr = nestinglvl;
			temp.pop();
			count++;
		}
		else if (tokens[i] == "}") {
			parentName = to_string(0);
			parentlvl = to_string(0);
			if (count == 1) {
				nestinglvl = ifstmtlist;
				parentnest = 0;
				nest = to_string(parentnest);
				count = 0;
			}
			else if (tempbracket == 1) {
				nestinglvl = whilestmtlist;
				parentnest = 0;
				nest = to_string(parentnest);
				tempbracket = 0;
			}
			else {
				nestinglvl--;
			}
			temp.push(tokens[i]);

		}
		if (tokens[i] == "if") {
			ifstmtlist = nestinglvl;
		}
		if (tokens[i] == "while") {
			whilestmtlist = nestinglvl;
		}
		stmtlist = to_string(nestinglvl);
	}
	for (int i = 0; i < tokens.size(); i++) {
		int j = i;
		string ifcondition = "";
		string whilecondition = "";
		string stmtnumber;
		if (tokens[i] == "while") {
			j = i + 1;
			while (tokens[j] != "{") {
				whilecondition = whilecondition + tokens[j];//store while(condition)
				j++;
			}
			Database::insertwhilecondition(stmtnumber, whilecondition);
		}
		else if (tokens[i] == "if") {
			j = i + 1;
			while (tokens[j] != "then") {
				ifcondition = ifcondition + tokens[j];//store if(condition)
				j++;
			}
			Database::insertifcondition(stmtnumber, ifcondition);
		}
	}
	vector<string> output;
	vector<string> databaseResults;
	Database::getStatement(databaseResults);
	for (string databaseResult : databaseResults) {
		output.push_back(databaseResult);
	}
	for (int i = 1; i <= output.size(); i++) {
		for (int j = i + 1; j <= output.size(); j++) {
			vector<string> procedureResultS1, procedureResultS2, nestingnumberS1, nestingnumberS2, parentResultS1, parentResultS2, parentnestinglvlS1, parentnestinglvlS2;
			Database::getNestinglvl(nestingnumberS1, i);
			Database::getNestinglvl(nestingnumberS2, j);
			Database::getparentNestinglvl(parentnestinglvlS1, i);
			Database::getparentNestinglvl(parentnestinglvlS2, j);
			Database::getParentLvl(parentResultS1, i);
			Database::getParentLvl(parentResultS2, j);
			Database::getProcedure(procedureResultS1, i);
			Database::getProcedure(procedureResultS2, j);
			if (procedureNum > 1) {
				if (procedureResultS1.at(0) == procedureResultS2.at(0)) {
					Database::insertnextstartable2(i, j);
				}
				if ((nestingnumberS1.at(0) == nestingnumberS2.at(0)) && (procedureResultS1.at(0) == procedureResultS2.at(0))) {
					Database::insertfollowstar(i, j);//populate follows*

				}
				if ((parentnestinglvlS1.at(0) < parentnestinglvlS2.at(0)) && (parentResultS1.at(0) == parentResultS2.at(0)) && (procedureResultS1.at(0) == procedureResultS2.at(0))) {
					Database::insertparent(i, j);
					Database::insertparentstar(i, j);
				}
			}
			else if(procedureNum == 1){
				Database::insertnextstartable2(i, j);
				if ((nestingnumberS1.at(0) == nestingnumberS2.at(0))) {
					Database::insertfollowstar(i, j);//populate follows*
				}
				if ((parentnestinglvlS1.at(0) < parentnestinglvlS2.at(0)) && (parentResultS1.at(0) == parentResultS2.at(0))) {
					Database::insertparent(i, j);
					Database::insertparentstar(i, j);
				}
				
			}
		}
	}

	string s1, s2;
	Database::insertcalltable(s1, s2);//populate call table
	Database::insertfollows(s1, s2);//populate followstable
	Database::insertmodifyassign2(s1, s2);//populate modifyassign to modifytable
	Database::insertmodifyread2(s1, s2);//populate modifyread to modifytable
	Database::insertmodifycontstmt(s1, s2);//populate modifycontstmt to modifytable
	Database::insertmodifywhilestmt(s1, s2);//populate modifywhile to modifytable
	Database::insertmodifyifstmt(s1, s2);//populate modifyif to modifytable
	Database::insertmodifyproc(s1, s2);//populate modifies procedure to modifytable
	Database::insertassignUses2(s1, s2);//populate uses assign
	Database::insertprintUses2(s1, s2);//populate print uses
	Database::insertcontstmtUses2(s1, s2);//populate contstmt
	Database::insertuseswhilestmt(s1, s2);//populate uses with while stmt
	Database::insertusesifstmt(s1, s2);//populate uses with if stmt
	Database::insertUsesproc(s1, s2);//populate uses procedure to usestable
	Database::insertnextstartablecall(s1, s2);//populate nextstar table
	Database::insertnextstartable(s1, s2);//populate nextstar table

	vector<string> finaloutput;
	vector<string> callsResults;
	Database::getid(callsResults);
	for (string callsResults : callsResults) {
		finaloutput.push_back(callsResults);
	}
	for (int i = 1; i <= finaloutput.size(); i++) {
		for (int j = i + 1; j <= finaloutput.size(); j++) {
			vector<string> callprocS1, callprocS2;
			Database::getp(callprocS2, j);
			Database::getq(callprocS1, i);
			if (callprocS1.at(0) == callprocS2.at(0)) {
				Database::insertpq(i, j);
			}
		}
	}
	Database::insertcallstartable(s1, s2);
	
}