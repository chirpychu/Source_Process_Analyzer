#include "QueryProcessor.h"
#include "Tokenizer.h"
#include "Verification.h"
#include "Declaration.h"
#include <map>
#include <algorithm>
#include "postfix.h"
// constructor
QueryProcessor::QueryProcessor() {}

// destructor
QueryProcessor::~QueryProcessor() {}

//helper function to convert pattern into postfix form

//string convert(string infix) {
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
//				if (char_stack.empty()) break;
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
//					if (char_stack.empty()) break;
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



// method to evaluate a query
// This method currently only handles queries for getting all the procedure names,
// using some highly simplifed logic.
// You should modify this method to complete the logic for handling all required queries.
void QueryProcessor::evaluate(string query, vector<string>& output) {
	// clear the output vector
	output.clear();

	// tokenize the query
	Tokenizer tk;
	vector<string> tokens;
	tk.tokenize(query, tokens);

	// check what type of synonym is being declared
	string stmtType = tokens.at(0);
	string stmtType2 = tokens.at(3);
	// create a vector for storing the results from database
	vector<string> databaseResults;
	vector<string> patternResults;
	vector<string> relationResults;
	vector<string> tempResults;
	int numofSynType = 0;
	int patterncount = 0;
	int count = 0;
	bool istuple = false;
	//for (int i = 0; i < tokens.size(); i++) {
	//	if (tokens[i] == "such") {//find the relation of such that
	//		count = 1;
	//	}
	//}
	string relarg1;
	string relarg2;
	bool patternExist = false;
	bool suchthtExist = false;
	for (size_t c = 0; c < tokens.size(); c++) {
		if (tokens[c] == "such") {//find the relation of such that
			count = 1;
			suchthtExist = true;
		}
		if (tokens[c] == "pattern") {
			patternExist = true;
		}
		if (tokens[c] == "Follows" || tokens[c] == "Follows*" || tokens[c] == "Modifies" || tokens[c] == "Parent" || tokens[c] == "Parent*" || tokens[c] == "Uses" || tokens[c] == "Next*" || tokens[c] == "Next" || tokens[c] == "Calls" || tokens[c] == "Calls*") {
			relarg1 = tokens[c + 2];//follows(relarg1,_)
			relarg2 = tokens[c + 3];//follows(_,relarg2)
		}

	}
	vector<string>::iterator result = find(tokens.begin(), tokens.end(), "pattern");
	vector<string>::iterator suchthat = find(tokens.begin(), tokens.end(), "such");
	map<string, declaretype> declaration;
	unsigned int j;
	for (j = 0; j < tokens.size() && tokens[j] != "Select" ; j++) {
		declaretype tokentype = convertToken(tokens[j]);//convert stmt
		int i = j;
		while (tokens[i] != ";") {//stmt s1, s2;
			if (tokentype != declaretype::none) {
				declaration.insert(pair<string, declaretype>(tokens[i + 1], tokentype));//convert s1
			}
			else if (tokens[i] == ",") {
				declaration.insert(pair<string, declaretype>(tokens[i + 1], tokentype));//convert s2
			}
			i++;
		}
	}

	for (int j = 0; j < tokens.size(); j++) {
	
		if (tokens[j] == "Select") {
			string argtype;
			declaretype querytype = declaration[argtype];
			if (tokens[j + 1] != "<") {
				istuple = false;
				argtype = tokens[j + 1];
				querytype = declaration[argtype];
			}
			if (tokens[j + 1] == "<") {
				istuple = true;
				int i = j + 1;
				while (tokens[i] != ">") {
					if (verify::isSymbol(tokens[i]) == false) {
						argtype = tokens[i];
						querytype = declaration[argtype];
					}
					i++;
				}
			}
			if (suchthtExist == false) {

						if (querytype == declaretype::procedure) {
							Database::getProcedures(databaseResults);
						}
						else if (querytype == declaretype::variable) {
							if (patternExist == true) {//find pattern word
								string entref;
								if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
									entref = tokens[j + 5];
									//Database::insertpattern(entref);
									Database::getpatternVar(databaseResults, entref);
								}	
								else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
									entref = tokens[j + 6];
									string temp = entref;
									Database::getpatternexpr2(databaseResults, temp);
								}
								else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
									entref = tokens[j + 7];
									string temp = entref;
									Database::getpatternexpr2(databaseResults, temp);
								}
							}
							else {
								Database::getVariables(databaseResults);
							}
						}
						else if (querytype == declaretype::constant) {
							if (patternExist == true) {//find pattern word
								string entref;
								if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
									entref = tokens[j + 6];
									string temp = entref;
									Database::getpatternC2(databaseResults, temp);
								}
								else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
									entref = tokens[j + 7];
									string temp = entref;
									Database::getpatternC2(databaseResults, temp);
								}
							}
							else {
								Database::getConstant(databaseResults);
							}
						}
						else if (querytype == declaretype::print) {
							Database::getPrint(databaseResults);
						}
						else if (querytype == declaretype::read) {
								Database::getRead(databaseResults);
						}
						else if (querytype == declaretype::assign) {
							if (patternExist == true) {//find pattern word
								string entref;
								if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
									entref = tokens[j + 5];
									//Database::insertpattern(entref);
									Database::getpatternAssign(databaseResults, entref);
								}
								else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
									entref = tokens[j + 6];
									string temp = entref;
									Database::getpatternexpr(databaseResults, temp);
								}
								else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
									entref = tokens[j + 7];
									string temp = entref;
									Database::getpatternpartialexpr(databaseResults, temp);
								}
							}
							else {
								Database::getAssign(databaseResults);
							}
						}
						else if (querytype == declaretype::statement) {
							if (patternExist == true) {//find pattern word
								string entref;
								if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
									entref = tokens[j + 5];
									//Database::insertpattern(entref);
									Database::getpatternS(databaseResults, entref);
								}
								else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
									entref = tokens[j + 6];
									string temp = entref;
									Database::getpatternS2(databaseResults, temp);
								}
								else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
									entref = tokens[j + 7];
									string temp = entref;
									Database::getpatternS2(databaseResults, temp);
								}
							}
							else {
								Database::getStatement(databaseResults);
							}
						}
						else if (querytype == declaretype::whiles) {
							Database::getWhile(databaseResults);
						}
						else if (querytype == declaretype::ifs) {
							Database::getIf(databaseResults);
						}
						else if (querytype == declaretype::call) {
							Database::getcall(databaseResults);
						}
				
			}
			else if(suchthtExist == true){
				
				for (int i = 0; i < tokens.size(); i++) {
					if (tokens[i] == "Follows") {
						if (patternExist == false) {//if no pattern
							//follow right unknown follows(2,s2)/follows(_,s2)/follows(5,_)
						
								if (verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//follow(_,s2) select s2
									Database::getfollowsright3(databaseResults);
								}
								else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//follows(2, s2) select s2
									string var = tokens[i + 2];
									Database::getfollowsright(databaseResults, var);
								}
								else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3]) && querytype == declaretype::statement) {//follows(5,_) select s2/ s1
									Database::getfollowsright2(databaseResults);
								}

								if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for follows(s1,s2)

									if (argtype == relarg2) {//select s2
										Database::gets2stmt(databaseResults);
									}
									else if (argtype == relarg1) {//select s1
										Database::gets1stmt(databaseResults);
									}
								}

							//follow left unknown follows(s1,_)/follows(s1,5)/follows(_,5)

								if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows(s1,_) select s1
									Database::getfollowsleft3(databaseResults);
								}
								else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows(s1, 5) select s1
									string var = tokens[i + 3];
									Database::getfollowsleft(databaseResults, var);
								}
								else if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2]) && querytype == declaretype::statement) {//follows(_,5) select s1/s2
									Database::getfollowsleft2(databaseResults);
								}

								//if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for follows(s1,s2)
								//	if (argtype == relarg1) {//select s1
								//		Database::gets1stmt(databaseResults);
								//	}
								//}
								else if (querytype == declaretype::statement) {//select s
									if (declaration[tokens[i + 3]] == declaretype::read) {//follows(s ,re)
										Database::getfollowsleftstmt(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::read) {//follows(re,s)
										Database::getfollowsrightstmt(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::print) {//follows(s,pn)
										Database::getfollowsleftstmt2(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::read) {//follows(pn, s)
										Database::getfollowsrightstmt2(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::call) {//follows(s,c)
										Database::getfollowsleftstmt3(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::call) {//follows (c,s)
										Database::getfollowsrightstmt3(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::assign) {//follows (a,s)
										Database::getfollowsrightstmt4(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::assign) {//follows (s,a)
										//string entref;
										//if (patternExist == true){
										//	if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8]) == false) {//if rhs of pattern is _
										//		entref = tokens[i + 8];

										//		Database::getfollowsleftstmt4(relationResults);
										//		Database::getpattern1(patternResults, entref);
										//		for (int i = 0; i < relationResults.size(); i++)
										//		{
										//			if (relationResults[i] == patternResults[i]) // .size() should be used
										//			{
										//				tempResults.push_back(relationResults[i]);
										//			}

										//		}
										//		databaseResults = tempResults;
										//	}
										//}else if (patternExist == false){
											Database::getfollowsleftstmt4(databaseResults);
										/*}*/
									}
								}
								else if (querytype == declaretype::print) {//select pn
									if (verify::isUnderscore(tokens[i + 3])) {//follows(pn, _)
										Database::getfollowsleftprint(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(pn,s2) select pn
										Database::getfollowsleftprint(databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,pn)
										Database::getfollowsrightprint(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,pn)
										Database::getfollowsrightprint(databaseResults);
									}
								}
								else if (querytype == declaretype::read) {//select r
									if (verify::isUnderscore(tokens[i + 3])) {//follows(r, _)
										Database::getfollowsleftread(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(r,s2)
										Database::getfollowsleftread(databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,r)
										Database::getfollowsrightread(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,r)
										Database::getfollowsrightread(databaseResults);
									}
								}
								else if (querytype == declaretype::call) {
									if (verify::isUnderscore(tokens[i + 3])) {//follows(c, _)
										Database::getfollowsleftcall(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(c,s2)
										Database::getfollowsleftcall (databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,c)
										Database::getfollowsrightcall(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,c)
										Database::getfollowsrightcall(databaseResults);
									}
								}
								else if (querytype == declaretype::assign) {
									if (verify::isUnderscore(tokens[i + 3])) {//follows(a, _)
										Database::getfollowsleftassign(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(a,s2)
										Database::getfollowsleftassign(databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,a)
										Database::getfollowsrightassign(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,a)
										Database::getfollowsrightassign(databaseResults);
									}
								}


						}
						else {
							//vector<string> finalResults;
							//vector<string> finalResults2;
							//	if (querytype == declaretype::statement) {
							//		if (declaration[tokens[i + 3]] == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//follows (s,a)
							//			
							//				string entref;
							//				//if (patternExist == true) {
							//				if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8]) == false) {//if rhs of pattern is _
							//					entref = tokens[i + 8];

							//					Database::getfollowsleftstmt4(relationResults);
							//					Database::getpattern1(patternResults, entref);
							//					Database::compareResults(relationResults, patternResults);
							//					/*for (string relationResults : relationResults) {
							//						finalResults.push_back(relationResults);
							//					}
							//					for (string patternResults : patternResults) {
							//						finalResults2.push_back(patternResults);
							//					}
							//					for (size_t i = 0; i < finalResults.size(); i++)
							//					{
							//						for (size_t j = 0; j < finalResults2.size(); j++) {
							//							if (finalResults[i] == finalResults2[j])
							//							{
							//								tempResults.push_back(finalResults[i]);
							//							}
							//							else {
							//								break;
							//							}
							//						}

							//					}*/
							//					//databaseResults = tempResults;
							//				}
							//			//}
							//		}
							//	}
							
							if (declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::assign) {//follows(s,a) select a with pattern
								if (result != tokens.end()) {//find pattern word
									string entref;
									if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i+8]) == false) {//if rhs of pattern is _
										entref = tokens[i + 8];
										//Database::insertpattern(entref);
										Database::getpatternfollowsleft(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[i + 8]) && verify::isUnderscore(tokens[i+9]) == false) {//if lhs of pattern is _
										entref = tokens[i + 9];
										string temp = entref;
										Database::getpatternfollowsright(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[i+8]) && verify::isUnderscore(tokens[i+9])) {//if pattern a (_,_"something")
										entref = tokens[i + 10];
										string temp = entref;
										Database::getpartialpatternfollowsright(databaseResults, temp);
									}
								}
							}
						}
						//not cfm
						//else if (querytype == declaretype::assign && result != tokens.end()) {//assign plus pattern
						//	if (verify::isUnderscore(tokens[i + 9])) {//if rhs of pattern is _
						//		string entref = tokens[i + 8];
						//		Database::insertpattern(entref);
						//		Database::getpatternAssignleftfollows(databaseResults);
						//	}
						//	else if (verify::isUnderscore(tokens[i + 8])) {//if lhs of pattern is _
						//		if (verify::isNumber(tokens[i + 9])) {//if it is string of words
						//			string entref = tokens[i + 9];
						//			Database::insertpatternconstant(entref);
						//			Database::getpatternAssignconstantrightfollows(databaseResults);
						//		}
						//		else if (verify::isNumber(tokens[i + 9]) == false) {//if it is not constant
						//			string entref = tokens[i + 9];
						//			Database::insertpattern(entref);
						//			Database::getpatternAssignrightfollows(databaseResults);
						//		}
						//	}
						//}
					}
					else if (tokens[i] == "Follows*") {
						if (result == tokens.end()) {//if no pattern
							//follow right unknown follows*(2,s2)/follows*(_,s2)/follows*(5,_)

								if (querytype == declaretype::statement && verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement) {//follows*(_,s2)
									Database::getfollowsStarright3(databaseResults);
								}
								else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//follows*(2, s2)
									string var = tokens[i + 2];
									Database::getfollowsStarright(databaseResults, var);
								}
								else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3]) && querytype == declaretype::statement) {//follows*(5,_)
									Database::getfollowsStarright2(databaseResults);
								}

								if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for follows*(s1,s2)

									if (argtype == relarg2) {//select s2
										Database::gets2stmtStar(databaseResults);
									}else if (argtype == relarg1) {//select s1
										Database::gets1stmtStar(databaseResults);
									}
								}
							//follow left unknown follows*(s1,_)/follows*(s1,5)/follows*(_,5)


								else if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows*(s1,_)
									Database::getfollowsStarleft3(databaseResults);
								}
								else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows*(s1, 5)
									string var = tokens[i + 3];
									Database::getfollowsStarleft(databaseResults, var);
								}
								if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2]) && querytype == declaretype::statement) {//follows*(_,5)
									Database::getfollowsStarleft2(databaseResults);
								}

								//if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//for follows*(s1,s2)
								//	if (argtype == tokens[i + 2]) {//select s1
								//		Database::gets1stmtStar(databaseResults);
								//	}
								//}
								else if (querytype == declaretype::statement) {//select s
									if (declaration[tokens[i + 3]] == declaretype::read) {//follows*(s ,re)
										Database::getfollowsStarleftstmt(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::read) {//follows*(re,s)
										Database::getfollowsStarrightstmt(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::print) {//follows*(s,pn)
										Database::getfollowsStarleftstmt2(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::read) {//follows*(pn, s)
										Database::getfollowsStarrightstmt2(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::call) {//follows*(s,c)
										Database::getfollowsStarleftstmt3(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::call) {//follows* (c,s)
										Database::getfollowsStarrightstmt3(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::assign) {//follows *(a,s)
										Database::getfollowsStarrightstmt4(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::assign) {//follows* (s,a)
										Database::getfollowsStarleftstmt4(databaseResults);
									}
								}
								else if (querytype == declaretype::print) {//select pn
									if (verify::isUnderscore(tokens[i + 3])) {//follows*(pn, _)
										Database::getfollowsStarleftprint(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(pn,s2) select pn
										Database::getfollowsStarleftprint(databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,pn)
										Database::getfollowsStarrightprint(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,pn)
										Database::getfollowsStarrightprint(databaseResults);
									}
								}
								else if (querytype == declaretype::read) {//select r
									if (verify::isUnderscore(tokens[i + 3])) {//follows*(r, _)
										Database::getfollowsStarleftread(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(r,s2)
										Database::getfollowsStarleftread(databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,r)
										Database::getfollowsStarrightread(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,r)
										Database::getfollowsStarrightread(databaseResults);
									}
								}
								else if (querytype == declaretype::call) {
									if (verify::isUnderscore(tokens[i + 3])) {//follows*(c, _)
										Database::getfollowsStarleftcall(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(c,s2)
										Database::getfollowsStarleftcall(databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,c)
										Database::getfollowsStarrightcall(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,c)
										Database::getfollowsStarrightcall(databaseResults);
									}
								}
								else if (querytype == declaretype::assign) {
									if (verify::isUnderscore(tokens[i + 3])) {//follows*(a, _)
										Database::getfollowsStarleftassign(databaseResults);
									}
									else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(a,s2)
										Database::getfollowsStarleftassign(databaseResults);
									}
									else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,a)
										Database::getfollowsStarrightassign(databaseResults);
									}
									else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,a)
										Database::getfollowsStarrightassign(databaseResults);
									}
								}
						}
						else {
							if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s,a) select a with pattern
								if (result != tokens.end()) {//find pattern word
									if (verify::isUnderscore(tokens[i + 9])) {//if rhs of pattern is _
										string entref = tokens[i + 8];
										//Database::insertpattern(entref);
										Database::getpatternfollowsStarleft(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[i + 8])) {//if lhs of pattern is _
										string entref = tokens[i + 9];
										string temp = entref;
										Database::getpatternfollowsStarright(databaseResults, temp);
									}
								}
							}
						}
						//old codes
						//if (querytype != declaretype::none && verify::isNumber(tokens[i + 2])) {//followsright unknown
						//	string lineNumber = to_string(1);
						//	string nestinglvl;
						//	Database::insertfollowsleft(lineNumber, tokens[i + 2], nestinglvl);
						//	Database::getfollowsTright(databaseResults);
						//}
						//else if (querytype != declaretype::none && verify::isNumber(tokens[i + 3])) {//followleft unknown
						//	string lineNumber = to_string(1);
						//	string nestinglvl;
						//	Database::insertfollowsright(lineNumber, tokens[i + 3], nestinglvl);
						//	Database::getfollowsTleft(databaseResults);

						//}else if(verify::isUnderscore(tokens[i + 2])) {
						//	string lineNumber = to_string(1);
						//	string nestinglvl;
						//	Database::insertfollowsright(lineNumber, tokens[i + 3], nestinglvl);
						//	Database::getfollowsTleft(databaseResults);
						//}else if (verify::isUnderscore(tokens[i + 3])) {
						//	string lineNumber = to_string(1);
						//	string nestinglvl;

						//	Database::insertfollowsleft(lineNumber, tokens[i + 2], nestinglvl);
						//	Database::getfollowsTright(databaseResults);
						//}
						//if (stmtType == "stmt" && stmtType2 == "stmt") {//for follows(s1,s2)
						//	if (argtype == relarg1) {//select s1
						//		Database::gets1stmt(databaseResults);
						//	}
						//	else if (argtype == relarg2) {//select s2
						//		Database::gets2stmt(databaseResults);
						//	}
						//}
					}
					else if (tokens[i] == "Parent") {
						//if (result == tokens.end()) {//if no pattern
						if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 2]) || verify::isNumber(tokens[i + 2])) {//parent right unknown Parent(8,s2)/Parent(_,S2)/Parent(8,_)
							if (verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent(_,s2)
								Database::getparenttableright2(databaseResults);
							}
							else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent(8, s2)
								//Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
								string var = tokens[i + 2];
								Database::getparenttableright(databaseResults, var);
							}
							else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3])) {//Parent(8,_)
								Database::getparenttableright2(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {//Parent(w,a) select a
								if (result != tokens.end()) {//find pattern word
									if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
										string entref = tokens[j + 5];
										//Database::insertpattern(entref);
										Database::getpatternparentleft(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
										string entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternparentright(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5])) {
										string entref = tokens[j + 7];
										string temp = entref;

									}
								}
								else {
									Database::getparenttableright3(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {//Parent(ifs,a) select a
								if (result != tokens.end()) {//find pattern word
									if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
										string entref = tokens[j + 5];
										//Database::insertpattern(entref);
										Database::getpatternparentleft2(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
										string entref = tokens[j + 6];
										Database::getpatternparentright2(databaseResults, entref);
									}
								}
								else {
									Database::getparenttableright4(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//Parent(s,a) select a
								if (result != tokens.end()) {//find pattern word
									if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
										string entref = tokens[j + 5];
										//Database::insertpattern(entref);
										Database::getpatternparentleft3(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
										string entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternparentright3(databaseResults, temp);
									}
								}
								else {
									Database::getparenttableright5(databaseResults);
								}
							}

						}
						if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 3]) || verify::isNumber(tokens[i + 3])) {//parent left unknown Parent(s1,12)/Parent(S1,_)/Parent(_,12)
							if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent(S1,_)
								Database::getparenttableleft2(databaseResults);
							}
							else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent(s1,12)
								//Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
								string var = tokens[i + 3];
								Database::getparentleft(databaseResults, var);
							}
							else if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2])) {//Parent(_,12)
								Database::getparenttableleft2(databaseResults);
							}

							else if (querytype == declaretype::ifs && verify::isNumber(tokens[i + 3])) {//parent(i,3) select if
								//Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
								string var = tokens[i + 3];
								Database::getparenttableleft6(databaseResults, var);
							}
							else if (querytype == declaretype::whiles && verify::isNumber(tokens[i + 3])) {//parent(w,3) select w
							   //Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
								string var = tokens[i + 3];
								Database::getparenttableleft7(databaseResults, var);
							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {//Parent(w,a) select w
								Database::getparenttableleft3(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {//Parent(ifs,a) select ifs
								Database::getparenttableleft4(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {//Parent(s,a) select s
								Database::getparenttableleft5(databaseResults);
							}
						}
						//}
						//old codes
						//if (querytype != declaretype::none && verify::isNumber(tokens[i + 2])) {//parent right unknown
						//	string lineNumber = to_string(1);
						//	string nestinglvl;
						//	Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
						//	if (verify::isUnderscore(tokens[i + 3])) {
						//		Database::getparentTright(databaseResults);
						//	}
						//	else {
						//		Database::getparentright(databaseResults);
						//	}
						//}
						//else if (querytype != declaretype::none && verify::isNumber(tokens[i + 3])) {//parent left unknown
						//	string lineNumber = to_string(1);
						//	string nestinglvl;
						//	Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
						//	Database::getparentleft(databaseResults);
						//	if (verify::isUnderscore(tokens[i + 2])) {
						//		Database::getparentTleft(databaseResults);
						//	}
						//	else {
						//		Database::getparentleft(databaseResults);
						//	}
						//}
						//not cfm
						//else if (querytype == declaretype::whiles && result != tokens.end()) {//parent(w,a)
						//		if (verify::isUnderscore(tokens[i + 9])) {
						//			string lineNumber = to_string(1);
						//			Database::insertstringuses(lineNumber, tokens[i + 8]);
						//			Database::getparentwhilepatternleft(databaseResults);
						//		}
						//		else if (verify::isUnderscore(tokens[i + 8])) {
						//			string lineNumber = to_string(1);
						//			Database::insertstringuses(lineNumber, tokens[i + 9]);
						//			Database::getparentwhilepatternright(databaseResults);
						//		}
						//}
						//else if (querytype == declaretype::ifs && result != tokens.end()) {//parent(ifs,a)
						//		if (verify::isUnderscore(tokens[i + 9])) {
						//			string lineNumber = to_string(1);
						//			Database::insertstringuses(lineNumber, tokens[i + 8]);
						//			Database::getparentifpatternleft(databaseResults);
						//		}
						//		else if (verify::isUnderscore(tokens[i + 8])) {
						//			string lineNumber = to_string(1);
						//			Database::insertstringuses(lineNumber, tokens[i + 9]);
						//			Database::getparentifpatternright(databaseResults);
						//		}
						//}
					}
					else if (tokens[i] == "Parent*") {
						//if (result == tokens.end()) {//if no pattern
						if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 2]) || verify::isNumber(tokens[i + 2])) {//parent* right unknown Parent*(8,s2)/Parent*(_,S2)/Parent*(8,_)

							if (verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(_,s2)
								Database::getparentStartableright2(databaseResults);
							}
							else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(8, s2)
								//Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
								string var = tokens[i + 2];
								Database::getparentStartableright(databaseResults, var);
							}
							else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3])) {//Parent*(8,_)
								Database::getparentStartableright2(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {//Parent*(w,a) select a
								if (result != tokens.end()) {//find pattern word
									if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
										string entref = tokens[j + 5];
										//Database::insertpattern(entref);
										Database::getpatternparentleft(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
										string entref = tokens[j + 6];
										Database::getpatternparentright(databaseResults, entref);
									}
								}
								else {
									Database::getparentStartableright3(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {//Parent*(ifs,a) select a
								if (result != tokens.end()) {//find pattern word
									if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
										string entref = tokens[j + 5];
										//Database::insertpattern(entref);
										Database::getpatternparentleft2(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
										string entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternparentright2(databaseResults, temp);
									}
								}
								else {
									Database::getparentStartableright4(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//Parent*(s,a) select a
								if (patternExist == true) {//find pattern word
									if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
										string entref = tokens[j + 5];
										//Database::insertpattern(entref);
										Database::getpatternparentleft3(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
										string entref = tokens[j + 6];
										Database::getpatternparentright3(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8])) { //partial pattern
										string entref = tokens[i + 10];
										string temp = entref;
										Database::getpatternParent(databaseResults, temp);
									}
								}
								else {
									Database::getparentStartableright5(databaseResults);
								}

							}

						}
						if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 3]) || verify::isNumber(tokens[i + 3])) {//parent* left unknown Parent*(s1,12)/Parent*(S1,_)/Parent*(_,12)

							if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(S1,_)
								Database::getparentStartableleft2(databaseResults);
							}
							else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(s1,12)
								//Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
								string var = tokens[i + 3];
								Database::getparentStartableleft(databaseResults, var);
							}
							else if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2])) {//Parent*(_,12)
								Database::getparentStartableleft2(databaseResults);
							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {//Parent*(w,a) select w
								Database::getparentStartableleft3(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {//Parent*(ifs,a) select ifs
								Database::getparentStartableleft4(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {//Parent*(s,a) select s
								Database::getparentStartableleft5(databaseResults);
							}
							else if (querytype == declaretype::ifs && verify::isNumber(tokens[i + 3])) {//parent*(i,3) select if
							   //Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
								string var = tokens[i + 3];
								Database::getparentStartableleft6(databaseResults, var);
							}
							else if (querytype == declaretype::whiles && verify::isNumber(tokens[i + 3])) {//parent*(w,3) select w
							   //Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
								string var = tokens[i + 3];
								Database::getparentStartableleft7(databaseResults, var);
							}
						}
						//}
						/*if (querytype != declaretype::none && verify::isNumber(tokens[i + 2])) {
							string lineNumber = to_string(1);
							string nestinglvl;
							Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
							Database::getparentTright(databaseResults);
						}
						else if (querytype != declaretype::none && verify::isNumber(tokens[i + 3])) {
							string lineNumber = to_string(1);
							string nestinglvl;
							Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
							Database::getparentTleft(databaseResults);
						}*/
						//pattern but not cfm
						/*else if (querytype == declaretype::whiles && result != tokens.end()) {
								if (verify::isUnderscore(tokens[i + 9])) {
									string lineNumber = to_string(1);
									Database::insertstringuses(lineNumber, tokens[i + 8]);
									Database::getparentwhilepatternleft(databaseResults);
								}
								else if(verify::isUnderscore(tokens[i + 8])) {
									string lineNumber = to_string(1);
									Database::insertstringuses(lineNumber, tokens[i + 9]);
									Database::getparentwhilepatternright(databaseResults);
								}
						}
						else if (querytype == declaretype::ifs && result != tokens.end()) {
								if (verify::isUnderscore(tokens[i + 9])) {
									string lineNumber = to_string(1);
									Database::insertstringuses(lineNumber, tokens[i + 8]);
									Database::getparentifpatternleft(databaseResults);
								}
								else if (verify::isUnderscore(tokens[i + 8])) {
									string lineNumber = to_string(1);
									Database::insertstringuses(lineNumber, tokens[i + 9]);
									Database::getparentifpatternright(databaseResults);
								}
						}*/
					}
					else if (tokens[i] == "Uses") {
						//if (querytype == declaretype::assign) {
						//	//pattern
						//	if (result != tokens.end()) {
						//		if (verify::isAlpha(tokens[i + 8])) {//if rhs is _
						//			string lineNumber = to_string(1);
						//			Database::insertstringuses(lineNumber, tokens[i + 8]);
						//			Database::getUsespatternvariable(databaseResults);
						//		}
						//		else if (verify::isUnderscore(tokens[i + 8])) {//if lhs is _
						//			string lineNumber = to_string(1);
						//			Database::insertstringuses(lineNumber, tokens[i + 9]);
						//			Database::getassignUsespatternvariableright(databaseResults);
						//		}
						//	}
							//no patten
								/*string lineNumber = to_string(1);
								Database::insertstringuses(lineNumber, tokens[i + 3]);
								Database::getassignUses(databaseResults);*/
								//if (result == tokens.end()) {//if no pattern
						if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::variable) {//uses(a,v) select a
							if (patternExist == true) {// if pattern
								if (verify::isUnderscore(tokens[i + 9]) && declaration[tokens[i + 8]] != declaretype::variable) {//if rhs of pattern is _
									string entref = tokens[i + 8];
									//Database::insertpattern(entref);
									Database::getpatternUsesleft(databaseResults, entref); //select a pattern("index", _)
								}
								else if (verify::isUnderscore(tokens[i + 9]) && declaration[tokens[i + 8]] == declaretype::variable) {//uses(a,v) select a pattern (v,_)
									//Database::insertpattern(entref);
									Database::getpatternUsesleft2(databaseResults);
								}
								else if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8])) { //partial pattern
									string entref = tokens[i + 10];
									string temp = entref;
									Database::getpatternUses(databaseResults, temp);
								}
							}
							else {
								Database::getassignUses1(databaseResults);
							}
						}
						else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::assign) {//uses(a,v) select v
							Database::getassignUses2(databaseResults);
						}
						else if (querytype == declaretype::assign && declaration[tokens[i + 3]] != declaretype::variable) {//uses(a,"cenx") select a
							string var = tokens[i + 3];
							Database::getassignUses3(databaseResults, var);
						}
						else if (querytype == declaretype::assign && verify::isUnderscore(tokens[i + 3])) {//uses(a,_) select v
							Database::getassignUses5(databaseResults);
						}
						else if (querytype == declaretype::print && declaration[tokens[i + 3]] != declaretype::variable) {//uses(pn, "CenX") select pn
							string var = tokens[i + 3];
							Database::getprintUses2(databaseResults, var);
						}
						else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::variable) {//uses(pn, v) select pn 
						   //string lineNumber = to_string(1);
							Database::getprintUses3(databaseResults);
						}
						else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::print) {//uses (pn,v) select v

							Database::getprintUses4(databaseResults);
						}
						else if (querytype == declaretype::variable && verify::isNumber(tokens[i + 2])) {//uses(10, v) select v
							string entity = tokens[i + 2];
							Database::getentityUses(databaseResults, entity);
						}
						else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::print) {//uses(pn,_) select v
							Database::getprintUses5(databaseResults);
						}
						else if (declaration[tokens[i + 2]] == declaretype::whiles) {//containment stmt
							if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::whiles) {//uses(w,v) select w
								Database::getcontstmtUses6(databaseResults);
							}
							else if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::variable) {//uses(w,v) select v
								Database::getcontstmtUses7(databaseResults);
							}
							else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(w,_) select v
								Database::getcontstmtUses3(databaseResults);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::statement) {
							if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(s,_) select v
								Database::getcontstmtUses8(databaseResults);
							}
							else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(s,v) select v
								Database::getcontstmtUses10(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::variable) {//uses(s,v) select s
								
									Database::getcontstmtUses9(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] != declaretype::variable) {//uses(s,"v") select s
								string var = tokens[i + 3];
								Database::getcontstmtUses4(databaseResults, var);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::ifs) {
							if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::variable) {//uses(if,v) select if
								Database::getcontstmtUses1(databaseResults);
							}
							else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(if, v) select v
								Database::getcontstmtUses2(databaseResults);
							}
							else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(if,_) select v
								Database::getcontstmtUses3(databaseResults);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::procedure) {
							if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(p,v) select v
								Database::getprocUses2(databaseResults);
							}
							else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] == declaretype::variable) {//uses(p,v) select p
								Database::getprocuses1(databaseResults);

							}
							else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(p,_) select v
								Database::getcontstmtModifies8(databaseResults);
							}
							else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//uses(p,"something") select p
								string var = tokens[i + 3];
								Database::getprocUses4(databaseResults, var);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::call) {
							if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(c,v) select v
								Database::getcalluses2(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::variable) {//uses(c,v) select c
								Database::getcallUses1(databaseResults);
							}
							else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(c,_) select v
								Database::getcontstmtModifies8(databaseResults);
							}
							else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//uses(c,"something") select c
								string var = tokens[i + 3];
								Database::getcallUses4(databaseResults, var);
							}
						}
						//}
						//old codes
						//else if (querytype == declaretype::statement || querytype == declaretype::whiles || querytype == declaretype::ifs) {
						//	/*string lineNumber = to_string(1);
						//	Database::insertstringuses(lineNumber, tokens[i + 3]);
						//	Database::getstmtUses(databaseResults);*/
						//}
						//else if (querytype == declaretype::procedure) {
						//	/*string lineNumber = to_string(1);
						//	Database::insertstringuses(lineNumber, tokens[i + 3]);
						//	Database::getprocedureUses(databaseResults);*/
						//}
						//else if (querytype == declaretype::variable) {
						//	/*string lineNumber = to_string(1);
						//	Database::insertuses(lineNumber, tokens[i + 2]);
						//	Database::getUses(databaseResults);*/
						//}
					}
					else if (tokens[i] == "Modifies") {
						//if (result == tokens.end()) {//if no pattern word
						if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(a,v) select a
							if (result != tokens.end()) {// if pattern
								if (verify::isUnderscore(tokens[i + 8]) && declaration[tokens[i + 9]] != declaretype::variable) {
									string entref = tokens[i + 9];
									
									//Database::insertpattern(entref);
									Database::getpatternModifiesleft2(databaseResults, entref); //select a pattern(_,"index")
								}
								else if (verify::isUnderscore(tokens[i + 9]) && declaration[tokens[i + 8]] == declaretype::variable) {//modifies(a,v) select a pattern (_,v)
									//Database::insertpattern(entref);
									Database::getpatternModifiesleft(databaseResults);
								}
							}
							else {
								Database::getassignModifies1(databaseResults);
							}
						}
						else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::assign && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(a,v) select v
							int pattern = 0;
							string entref;
							if (result != tokens.end()) {//find pattern word
								if (verify::isUnderscore(tokens[i+9])) {//if rhs of pattern is _
									entref = tokens[i+8];
									Database::getpatternM(databaseResults, entref);
								}
								else if (verify::isUnderscore(tokens[i + 8])) {//if lhs of pattern is _
									entref = tokens[i + 9];
									string temp = entref;
									Database::getpatternM2(databaseResults, temp);
								}
								//else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
								//	entref = tokens[j + 7];
								//	string temp = convert(entref);
								//	Database::getpatternS2(databaseResults, temp);
								//}
							}
							else {
								Database::getassignModifies2(databaseResults);
							}
						}
						else if (querytype == declaretype::assign && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(a,"cenx") select a
							string var = tokens[i + 3];
							Database::getassignModifies3(databaseResults, var);
						}
						else if (querytype == declaretype::assign && verify::isUnderscore(tokens[i + 3])) {//modifies(a,_) select v
							Database::getassignModifies5(databaseResults);
						}
						else if (querytype == declaretype::read && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(r, "CenX") select r
							string var = tokens[i + 3];
							Database::getreadModifies2(databaseResults, var);
						}
						else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(r, v) select r 
							Database::getreadModifies1(databaseResults);
						}
						else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::read) {//modifies (r,v) select v

							Database::getreadModifies4(databaseResults);
						}
						else if (querytype == declaretype::variable && verify::isNumber(tokens[i + 2])) {//modifies(10, v) select v// like modifies(procedureName,v)
							string entity = tokens[i + 2];
							Database::getentityModifies(databaseResults, entity);
						}
						else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::read) {//modifies(r,_) select v
							Database::getreadModifies5(databaseResults);
						}
						else if (declaration[tokens[i + 2]] == declaretype::whiles) {//containment stmt
							if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::whiles) {//modifies(w,v) select w
								Database::getcontstmtModifies6(databaseResults);
							}
							else if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::variable) {//modifies(w,v) select v
								Database::getcontstmtModifies7(databaseResults);
							}
							else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(w,_) select v
								Database::getcontstmtModifies8(databaseResults);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::statement) {
							if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(s,_) select v
								Database::getcontstmtModifies8(databaseResults);
							}
							else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(s,v) select v
								Database::getcontstmtModifies10(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(s,v) select s
								Database::getcontstmtModifies9(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(s,"v") select s
								string var = tokens[i + 3];
								Database::getcontstmtModifies4(databaseResults, var);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::ifs) {
							if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(if,v) select if
								Database::getcontstmtModifies1(databaseResults);
							}
							else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(if, v) select v
								Database::getcontstmtModifies2(databaseResults);
							}
							else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(if,_) select v
								Database::getcontstmtModifies8(databaseResults);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::procedure) {
							if(querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(p,v) select v
								Database::getprocModifies2(databaseResults);
							}
							else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(p,v) select p
								Database::getprocModifies1(databaseResults);

							}
							else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(p,_) select v
								Database::getcontstmtModifies8(databaseResults);
							}
							else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(p,"something") select p
								string var = tokens[i + 3]; 
								Database::getprocModifies4(databaseResults, var);
							}
						}
						else if (declaration[tokens[i + 2]] == declaretype::call) {
							if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(c,v) select v
								Database::getprocModifies2(databaseResults);
							}
							if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(c,v) select c
								Database::getcallModifies1(databaseResults);
							}
							if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(c,_) select v
								Database::getcontstmtModifies8(databaseResults);
							}
							if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(c,"something") select c
								string var = tokens[i + 3];
								Database::getcallModifies4(databaseResults, var);
							}
						}

						//}
						//if (querytype == declaretype::variable) {
						//	string lineNumber = to_string(1);
						//	Database::insertmodifyinteger(lineNumber, tokens[i + 2]);
						//	Database::getModifyVar(databaseResults);
						//}
						//if (verify::isNumber(tokens[i + 2]) == false) {
						//	if (querytype == declaretype::assign) {
						//		if (result != tokens.end()) {
						//			if (verify::isAlpha(tokens[i + 9])) {//if lhs is _
						//				string lineNumber = to_string(1);
						//				Database::insertmodifystring(lineNumber, tokens[i + 9]);
						//				Database::getassignModifiespatternvariableleft(databaseResults);
						//			}
						//			if(verify::isUnderscore(tokens[i + 9])){//if rhs is _
						//				string lineNumber = to_string(1);
						//				Database::insertmodifystring(lineNumber, tokens[i + 8]);
						//				Database::getassignModifiespatternvariableright(databaseResults);
						//			}
						//		}
						//		else{
						//			string lineNumber = to_string(1);
						//			Database::insertmodifystring(lineNumber, tokens[i + 3]);
						//			Database::getModifyAssign(databaseResults);
						//		}
						//	}
						//	else if (querytype == declaretype::read) {
						//		string lineNumber = to_string(1);
						//		Database::insertmodifystring(lineNumber, tokens[i + 3]);
						//		Database::getModifyRead(databaseResults);
						//	}
						//	else if (querytype == declaretype::procedure) {
						//		string lineNumber = to_string(1);
						//		Database::insertmodifystring(lineNumber, tokens[i + 3]);
						//		Database::getModifyprocedure(databaseResults);
						//	}
						//	else if (querytype == declaretype::statement || querytype == declaretype::whiles || querytype == declaretype::ifs) {
						//		string lineNumber = to_string(1);
						//		Database::insertmodifystring(lineNumber, tokens[i + 3]);
						//		Database::getModifystmt(databaseResults);
						//	}
						//}
					}
					else if (tokens[i] == "Calls") {
						//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] == argtype) {//Calls(p,_) select p
						//	Database::getcalls(databaseResults);
						//}
						//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] != argtype) {//calls(p,_) select q
						//	Database::getcalls2(databaseResults);
						//}
						//if (querytype == declaretype::procedure && tokens[i + 2] == argtype && declaration[tokens[i + 3]] == declaretype::procedure) {//calls(p,q) select p
						//	Database::getcalls(databaseResults);
						//}
						//if (querytype == declaretype::procedure && tokens[i + 3] == argtype && declaration[tokens[i + 2]] == declaretype::procedure) {//calls(p,q) select q
						//	Database::getcalls2(databaseResults);
						//}
						//if (querytype == declaretype::procedure && tokens[i + 3] != argtype && declaration[tokens[i + 3]] == declaretype::none) {//Calls(p, "result") select p
						//	string proc = tokens[i + 3];
						//	Database::getcalls4(databaseResults, proc);
						//}
						//if (querytype == declaretype::procedure && tokens[i + 2] != argtype && declaration[tokens[i + 2]] == declaretype::none) {//Calls(something, q) select q
						//	string proc = tokens[i + 2];
						//	Database::getcalls5(databaseResults, proc);
						//}

						if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//calls*(_,s) select s calls*(2, _)	calls*(_, 2) //calls*(s,_) select s
							if (verify::isUnderscore(tokens[i + 3])) {
								Database::getcalls(databaseResults);
							}
							else if (verify::isUnderscore(tokens[i + 2])) {
								Database::getcalls2(databaseResults);
							}
						}
						else if (argtype == relarg1 && declaration[tokens[i + 3]] == declaretype::procedure) {
							Database::getcalls(databaseResults);
						}
						else if (argtype == relarg2 && declaration[tokens[i + 2]] == declaretype::procedure) {
							Database::getcalls2(databaseResults);
						}
						else if (argtype == relarg1 && declaration[tokens[i + 3]] != declaretype::procedure) {
							string proc = tokens[i + 3];
							Database::getcalls4(databaseResults, proc);
						}
						else if (argtype == relarg2 && declaration[tokens[i + 2]] != declaretype::procedure) {
							string proc = tokens[i + 2];
							Database::getcalls5(databaseResults, proc);
						}

					}
					else if (tokens[i] == "Calls*") {
						//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] == argtype) {//Calls*(p,_) select p
						//	Database::getcallsstar(databaseResults);
						//}
						//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] != argtype && declaration[tokens[i + 3]] == declaretype::none) {//Calls*(p,_) select q
						//	Database::getcallsstar2(databaseResults);
						//}
						//if (querytype == declaration[tokens[i + 2]] && declaration[tokens[i + 2]] == declaretype::procedure && declaration[tokens[i + 2]] == declaretype::procedure) {//Calls*(p,q) select p 
						//	Database::getcallsstar(databaseResults); 
						//}
						//if (querytype == declaretype::procedure && tokens[i + 3] == argtype && verify::isUnderscore(tokens[i + 3]) == false) {//Calls*(p,q) select q
						//	Database::getcallsstar2(databaseResults);
						//}
						//if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::procedure && declaration[tokens[i + 2]] == declaretype::procedure) {//calls*(p,result") select p
						//	string proc = tokens[i + 3];
						//	Database::getcallsstar4(databaseResults, proc);
						//}
						//if (querytype == declaretype::procedure && tokens[i + 2] != argtype) {//Calls*(something, q) select q
						//	string proc = tokens[i + 2];
						//	Database::getcallsstar5(databaseResults, proc);
						//}

						if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//calls*(_,s) select s calls*(2, _)	calls*(_, 2) //calls*(s,_) select s
							if (verify::isUnderscore(tokens[i + 3])) {
								Database::getcallsstar(databaseResults);
							}
							else if (verify::isUnderscore(tokens[i + 2])) {
								Database::getcallsstar2(databaseResults);
							}
						}
						else if (argtype == relarg1 && declaration[tokens[i + 3]] == declaretype::procedure) {
							Database::getcallsstar(databaseResults);
						}
						else if (argtype == relarg2 && declaration[tokens[i + 2]] == declaretype::procedure) {
							Database::getcallsstar(databaseResults);
						}
						else if (argtype == relarg1 && declaration[tokens[i + 3]] != declaretype::procedure) {
							string proc = tokens[i + 3];
							Database::getcallsstar4(databaseResults, proc);
						}
						else if (argtype == relarg2 && declaration[tokens[i + 2]] != declaretype::procedure) {
							string proc = tokens[i + 2];
							Database::getcallsstar5(databaseResults, proc);
						}

					}
					else if (tokens[i] == "Next*") {
						if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//next*(_,s) select s next*(2, _)	next*(_, 2) //next*(s,_) select s
							if (verify::isUnderscore(tokens[i + 3])) {
								Database::getNextstar(databaseResults);
							}
							else if (verify::isUnderscore(tokens[i + 2])) {
								Database::getNextstar2(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for next*(s1,s2)

							if (argtype == relarg2) {//select s2
								Database::gets2Nextstarstmt(databaseResults);
							}
							if (argtype == relarg1) {//select s1
								Database::gets1Nextstarstmt(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::statement) {//next*(s, syno) select s
							if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextstarleft(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextstarleft2(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextstarleft3(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextstarleft4(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextstarleft5(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextstarleft6(databaseResults);
							}
							else if (querytype == declaretype::statement && verify::isNumber(tokens[i+3])) {//next*(s, 4)
								string var = tokens[i + 3];
								Database::getNextstarleft7(databaseResults, var);
							}

						}
						if (declaration[tokens[i + 3]] == declaretype::statement) {//next*(syno, s) select s
							if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextstarRight(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextstarRight2(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextstarRight3(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextstarRight4(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextstarRight5(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextstarRight6(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::none) {//next*(4, s)
								string var = tokens[i + 2];
								Database::getNextstarRight7(databaseResults, var);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::read) {//next*(read, s) select read
							if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::statement){
								Database::getNextstarleftR(databaseResults);
							}
							else if(querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::print){//next*(r, print) select read
								Database::getNextstarleft2R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextstarleft3R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextstarleft4R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextstarleft5R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextstarleft6R(databaseResults);
							}

						}
						if (declaration[tokens[i + 3]] == declaretype::read) {//next*(s,read) select read
							if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextstarRightR(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {//next*(print, r) select read
								Database::getNextstarRight2R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextstarRight3R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextstarRight4R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextstarRight5R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextstarRight6R(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::print) {//next*(print, s) select print
							if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::statement) {
								Database::getNextstarleftP(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::read) {//next*(print, r) select print
								Database::getNextstarleft2P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextstarleft3P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextstarleft4P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextstarleft5P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextstarleft6P(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::print) {//next*(s,print)
							if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextstarRightP(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextstarRight2P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextstarRight3P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextstarRight4P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextstarRight5P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextstarRight6P(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::call) {//next*(call, s) select call
							if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::statement) {
								Database::getNextstarleftC(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextstarleft2C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextstarleft3C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextstarleft4C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextstarleft5C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextstarleft6C(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::call) {//next*(s,call)
							if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextstarRightC(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextstarRight2C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextstarRight3C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextstarRight4C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextstarRight5C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextstarRight6C(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::whiles) {//next*(w, s) select call
							if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::statement) {
								Database::getNextstarleftW(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextstarleft2W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextstarleft3W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextstarleft4W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextstarleft5W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextstarleft6W(databaseResults);

							}
						}
						if (declaration[tokens[i + 3]] == declaretype::whiles) {//next*(s,while) select w
							if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextstarRightW(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextstarRight2W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextstarRight3W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextstarRight4W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextstarRight5W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextstarRight6W(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::ifs) {//next*(if, s) select if
							if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::statement) {//
								Database::getNextstarleftI(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextstarleft2I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextstarleft3I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextstarleft4I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextstarleft5I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextstarleft6I(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::ifs) {//next*(s,if)
							if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextstarRightI(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextstarRight2I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextstarRight3I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextstarRight4I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextstarRight5I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextstarRight6I(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::assign) {//next*(a, s) select s
							if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::statement) {//
								if (patternExist == true) {//find pattern word
									string entref;
									if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
										entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternNext2(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
										entref = tokens[j + 5];
										Database::getpatternNext(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
										entref = tokens[j + 7];
										string temp = entref;
										Database::getpatternNext2(databaseResults, temp);
									}
								}
								else {
									Database::getNextstarleftA(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::read) {
								if (patternExist == true) {//find pattern word
									string entref;
									if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
										entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternNext3(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
										entref = tokens[j + 5];
										Database::getpatternN2(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
										entref = tokens[j + 7];
										string temp = entref;
										Database::getpatternNext3(databaseResults, temp);
									}
								}
								else {
									Database::getNextstarleft2A(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::print) {
								if (patternExist == true) {//find pattern word
									string entref;
									if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
										entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternNext4(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
										entref = tokens[j + 5];
										Database::getpatternN3(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
										entref = tokens[j + 7];
										string temp = entref;
										Database::getpatternNext4(databaseResults, temp);
									}
								}
								else {
									Database::getNextstarleft3A(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::ifs) {
								if (patternExist == true) {//find pattern word
									string entref;
									if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
										entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternNext5(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
										entref = tokens[j + 5];
										Database::getpatternN4(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
										entref = tokens[j + 7];
										string temp = entref;
										Database::getpatternNext5(databaseResults, temp);
									}
								}
								else {
									Database::getNextstarleft4A(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::call) {
								if (patternExist == true) {//find pattern word
									string entref;
									if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
										entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternNext6(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
										entref = tokens[j + 5];
										Database::getpatternN5(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
										entref = tokens[j + 7];
										string temp = entref;
										Database::getpatternNext6(databaseResults, temp);
									}
								}
								else {
									Database::getNextstarleft5A(databaseResults);
								}
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::whiles) {
								if (patternExist == true) {//find pattern word
									string entref;
									if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
										entref = tokens[j + 6];
										string temp = entref;
										Database::getpatternNext7(databaseResults, temp);
									}
									else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
										entref = tokens[j + 5];
										Database::getpatternN6(databaseResults, entref);
									}
									else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
										entref = tokens[j + 7];
										string temp = entref;
										Database::getpatternNext7(databaseResults, temp);
									}
								}
								else {
									Database::getNextstarleft6A(databaseResults);//cont pattern here
								}
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::assign) {//next*(if,a)
							if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextstarRightA(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextstarRight2A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextstarRight3A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextstarRight4A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextstarRight5A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextstarRight6A(databaseResults);
							}
						}
						//if (declaration[tokens[i + 2]] == declaretype::statement && declaration[tokens[i + 3]] == declaretype::statement) {//next*(s1,s2) select s1/s2
						//	if (querytype == declaration[tokens[i + 2]]) {
						//		Database::getNextstar(databaseResults);
						//	}
						//	else if (querytype == declaration[tokens[i + 3]]) {
						//		Database::getNextstar2(databaseResults);
						//	}
						//}

					}
					else if (tokens[i] == "Next") {
						if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//next(_,s) select s next(2, _)	next(_, 2) //next(s,_) select s
							if (verify::isUnderscore(tokens[i + 3])) {
								Database::getNext(databaseResults);
							}
							else if (verify::isUnderscore(tokens[i + 2])) {
								Database::getNext2(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::statement) {//next(s, syno) select s
							if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextleft(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextleft2(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextleft3(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextleft4(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextleft5(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextleft6(databaseResults);
							}
							else if (querytype == declaretype::statement && verify::isNumber(tokens[i + 3])) {//next*(s, 4)
								string var = tokens[i + 3];
								Database::getNextleft7(databaseResults, var);
							}

						}
						if (declaration[tokens[i + 3]] == declaretype::statement) {//next*(syno, s) select s
							if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextRight(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextRight2(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextRight3(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextRight4(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextRight5(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextRight6(databaseResults);
							}
							else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::none) {//next*(4, s)
								string var = tokens[i + 2];
								Database::getNextRight7(databaseResults, var);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::read) {//next*(read, s) select read
							if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::statement) {
								Database::getNextleftR(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::print) {//next*(r, print) select read
								Database::getNextleft2R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextleft3R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextleft4R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextleft5R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextleft6R(databaseResults);
							}

						}
						if (declaration[tokens[i + 3]] == declaretype::read) {//next*(s,read) select read
							if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextRightR(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {//next*(print, r) select read
								Database::getNextRight2R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextRight3R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextRight4R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextRight5R(databaseResults);
							}
							else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextRight6R(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::print) {//next*(print, s) select print
							if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::statement) {
								Database::getNextleftP(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::read) {//next*(print, r) select print
								Database::getNextleft2P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextleft3P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextleft4P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextleft5P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextleft6P(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::print) {//next*(s,print)
							if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextRightP(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextRight2P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextRight3P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextRight4P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextRight5P(databaseResults);
							}
							else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextRight6P(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::call) {//next*(call, s) select call
							if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::statement) {
								Database::getNextleftC(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextleft2C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextleft3C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextleft4C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextleft5C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextleft6C(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::call) {//next*(s,call)
							if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextRightC(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextRight2C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextRight3C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextRight4C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextRight5C(databaseResults);
							}
							else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextRight6C(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::whiles) {//next*(w, s) select call
							if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::statement) {
								Database::getNextleftW(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextleft2W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextleft3W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextleft4W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextleft5W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextleft6W(databaseResults);

							}
						}
						if (declaration[tokens[i + 3]] == declaretype::whiles) {//next*(s,while) select w
							if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextRightW(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextRight2W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextRight3W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextRight4W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextRight5W(databaseResults);

							}
							else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextRight6W(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::ifs) {//next*(if, s) select if
							if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::statement) {//
								Database::getNextleftI(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextleft2I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextleft3I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {
								Database::getNextleft4I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextleft5I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextleft6I(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::ifs) {//next*(s,if)
							if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextRightI(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextRight2I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextRight3I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::assign) {
								Database::getNextRight4I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextRight5I(databaseResults);
							}
							else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextRight6I(databaseResults);
							}
						}
						if (declaration[tokens[i + 2]] == declaretype::assign) {//next*(a, s) select if
							if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::statement) {//
								Database::getNextleftA(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::read) {
								Database::getNextleft2A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::print) {
								Database::getNextleft3A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::ifs) {
								Database::getNextleft4A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::call) {
								Database::getNextleft5A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::whiles) {
								Database::getNextleft6A(databaseResults);
							}
						}
						if (declaration[tokens[i + 3]] == declaretype::assign) {//next*(if,a)
							if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {
								Database::getNextRightA(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::read) {
								Database::getNextRight2A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::print) {
								Database::getNextRight3A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {
								Database::getNextRight4A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::call) {
								Database::getNextRight5A(databaseResults);
							}
							else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {
								Database::getNextRight6A(databaseResults);
							}
						}
						//if (declaration[tokens[i + 2]] == declaretype::statement && declaration[tokens[i + 3]] == declaretype::statement) {//next*(s1,s2) select s1/s2
						//	if (querytype == declaration[tokens[i + 2]]) {
						//		Database::getNext(databaseResults);
						//	}
						//	else if (querytype == declaration[tokens[i + 3]]) {
						//		Database::getNext2(databaseResults);
						//	}
						//}
						if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for next*(s1,s2)

							if (argtype == relarg2) {//select s2
								Database::getNext2(databaseResults);
							}
							if (argtype == relarg1) {//select s1
								Database::getNext(databaseResults);
							}
						}
					}
				}
				
			}
		}
		//else if (tokens[j] == "Select" && tokens[j + 1] == "<") {
		//int i = j + 1;
		//declaretype querytype;
		//string argtype;
		//	while (tokens[i] != ">") {
		//		if (verify::isSymbol(tokens[i]) == false) {
		//			argtype = tokens[i];
		//			querytype = declaration[argtype];
		//		}
		//		i++;
		//	}
		//	for (int i = 0; i < tokens.size(); i++) {
		//		if (suchthtExist == false) {
		//			if (querytype == declaretype::procedure) {
		//				Database::getProcedures(databaseResults);
		//			}
		//			else if (querytype == declaretype::variable) {
		//				if (patternExist == true) {//find pattern word
		//					string entref;
		//					if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
		//						entref = tokens[j + 5];
		//						//Database::insertpattern(entref);
		//						Database::getpatternVar(databaseResults, entref);
		//					}
		//					else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
		//						entref = tokens[j + 6];
		//						string temp = convert(entref);
		//						Database::getpatternexpr2(databaseResults, temp);
		//					}
		//					else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
		//						entref = tokens[j + 7];
		//						string temp = convert(entref);
		//						Database::getpatternexpr2(databaseResults, temp);
		//					}
		//				}
		//				else {
		//					Database::getVariables(databaseResults);
		//				}
		//			}
		//			else if (querytype == declaretype::constant) {
		//				if (patternExist == true) {//find pattern word
		//					string entref;
		//					if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
		//						entref = tokens[j + 6];
		//						string temp = convert(entref);
		//						Database::getpatternC2(databaseResults, temp);
		//					}
		//					else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
		//						entref = tokens[j + 7];
		//						string temp = convert(entref);
		//						Database::getpatternC2(databaseResults, temp);
		//					}
		//				}
		//				else {
		//					Database::getConstant(databaseResults);
		//				}
		//			}
		//			else if (querytype == declaretype::print) {
		//				Database::getPrint(databaseResults);
		//			}
		//			else if (querytype == declaretype::read) {
		//				Database::getRead(databaseResults);
		//			}
		//			else if (querytype == declaretype::assign) {
		//				if (patternExist == true) {//find pattern word
		//					string entref;
		//					if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
		//						entref = tokens[j + 5];
		//						//Database::insertpattern(entref);
		//						Database::getpatternAssign(databaseResults, entref);
		//					}
		//					else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
		//						entref = tokens[j + 6];
		//						string temp = convert(entref);
		//						Database::getpatternexpr(databaseResults, temp);
		//					}
		//					else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
		//						entref = tokens[j + 7];
		//						string temp = convert(entref);
		//						Database::getpatternpartialexpr(databaseResults, temp);
		//					}
		//				}
		//				else {
		//					Database::getAssign(databaseResults);
		//				}
		//			}
		//			else if (querytype == declaretype::statement) {
		//				if (patternExist == true) {//find pattern word
		//					string entref;
		//					if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5]) == false) {//if rhs of pattern is _
		//						entref = tokens[j + 5];
		//						//Database::insertpattern(entref);
		//						Database::getpatternS(databaseResults, entref);
		//					}
		//					else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6]) == false) {//if lhs of pattern is _
		//						entref = tokens[j + 6];
		//						string temp = convert(entref);
		//						Database::getpatternS2(databaseResults, temp);
		//					}
		//					else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
		//						entref = tokens[j + 7];
		//						string temp = convert(entref);
		//						Database::getpatternS2(databaseResults, temp);
		//					}
		//				}
		//				else {
		//					Database::getStatement(databaseResults);
		//				}
		//			}
		//			else if (querytype == declaretype::whiles) {
		//				Database::getWhile(databaseResults);
		//			}
		//			else if (querytype == declaretype::ifs) {
		//				Database::getIf(databaseResults);
		//			}
		//			else if (querytype == declaretype::call) {
		//				Database::getcall(databaseResults);
		//			}

		//		}else{
		//			if (tokens[i] == "Calls") {
		//				//select <p,q> calls(p,q)
		//				Database::getcalls3(databaseResults);
		//			
		//			}
		//			else if (tokens[i] == "Follows") {
		//				if (patternExist == false) {//if no pattern
		//					//follow right unknown follows(2,s2)/follows(_,s2)/follows(5,_)

		//					if (verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//follow(_,s2) select s2
		//						Database::getfollowsright3(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//follows(2, s2) select s2
		//						string var = tokens[i + 2];
		//						Database::getfollowsright(databaseResults, var);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3]) && querytype == declaretype::statement) {//follows(5,_) select s2/ s1
		//						Database::getfollowsright2(databaseResults);
		//					}

		//					if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for follows(s1,s2)

		//						if (argtype == relarg2) {//select s2
		//							Database::gets2stmt(databaseResults);
		//						}
		//					}

		//					//follow left unknown follows(s1,_)/follows(s1,5)/follows(_,5)

		//					if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows(s1,_) select s1
		//						Database::getfollowsleft3(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows(s1, 5) select s1
		//						string var = tokens[i + 3];
		//						Database::getfollowsleft(databaseResults, var);
		//					}
		//					else if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2]) && querytype == declaretype::statement) {//follows(_,5) select s1/s2
		//						Database::getfollowsleft2(databaseResults);
		//					}

		//					else if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for follows(s1,s2)
		//						if (argtype == relarg1) {//select s1
		//							Database::gets1stmt(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::statement) {//select s
		//						if (declaration[tokens[i + 3]] == declaretype::read) {//follows(s ,re)
		//							Database::getfollowsleftstmt(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::read) {//follows(re,s)
		//							Database::getfollowsrightstmt(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::print) {//follows(s,pn)
		//							Database::getfollowsleftstmt2(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::read) {//follows(pn, s)
		//							Database::getfollowsrightstmt2(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::call) {//follows(s,c)
		//							Database::getfollowsleftstmt3(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::call) {//follows (c,s)
		//							Database::getfollowsrightstmt3(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::assign) {//follows (a,s)
		//							Database::getfollowsrightstmt4(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::assign) {//follows (s,a)
		//							//string entref;
		//							//if (patternExist == true){
		//							//	if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8]) == false) {//if rhs of pattern is _
		//							//		entref = tokens[i + 8];

		//							//		Database::getfollowsleftstmt4(relationResults);
		//							//		Database::getpattern1(patternResults, entref);
		//							//		for (int i = 0; i < relationResults.size(); i++)
		//							//		{
		//							//			if (relationResults[i] == patternResults[i]) // .size() should be used
		//							//			{
		//							//				tempResults.push_back(relationResults[i]);
		//							//			}

		//							//		}
		//							//		databaseResults = tempResults;
		//							//	}
		//							//}else if (patternExist == false){
		//							Database::getfollowsleftstmt4(databaseResults);
		//							/*}*/
		//						}
		//					}
		//					else if (querytype == declaretype::print) {//select pn
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows(pn, _)
		//							Database::getfollowsleftprint(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(pn,s2) select pn
		//							Database::getfollowsleftprint(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,pn)
		//							Database::getfollowsrightprint(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,pn)
		//							Database::getfollowsrightprint(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::read) {//select r
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows(r, _)
		//							Database::getfollowsleftread(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(r,s2)
		//							Database::getfollowsleftread(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,r)
		//							Database::getfollowsrightread(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,r)
		//							Database::getfollowsrightread(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::call) {
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows(c, _)
		//							Database::getfollowsleftcall(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(c,s2)
		//							Database::getfollowsleftcall(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,c)
		//							Database::getfollowsrightcall(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,c)
		//							Database::getfollowsrightcall(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::assign) {
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows(a, _)
		//							Database::getfollowsleftassign(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows(a,s2)
		//							Database::getfollowsleftassign(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows(_,a)
		//							Database::getfollowsrightassign(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows(s1,a)
		//							Database::getfollowsrightassign(databaseResults);
		//						}
		//					}


		//				}
		//				else {
		//					//vector<string> finalResults;
		//					//vector<string> finalResults2;
		//					//	if (querytype == declaretype::statement) {
		//					//		if (declaration[tokens[i + 3]] == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//follows (s,a)
		//					//			
		//					//				string entref;
		//					//				//if (patternExist == true) {
		//					//				if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8]) == false) {//if rhs of pattern is _
		//					//					entref = tokens[i + 8];

		//					//					Database::getfollowsleftstmt4(relationResults);
		//					//					Database::getpattern1(patternResults, entref);
		//					//					Database::compareResults(relationResults, patternResults);
		//					//					/*for (string relationResults : relationResults) {
		//					//						finalResults.push_back(relationResults);
		//					//					}
		//					//					for (string patternResults : patternResults) {
		//					//						finalResults2.push_back(patternResults);
		//					//					}
		//					//					for (size_t i = 0; i < finalResults.size(); i++)
		//					//					{
		//					//						for (size_t j = 0; j < finalResults2.size(); j++) {
		//					//							if (finalResults[i] == finalResults2[j])
		//					//							{
		//					//								tempResults.push_back(finalResults[i]);
		//					//							}
		//					//							else {
		//					//								break;
		//					//							}
		//					//						}

		//					//					}*/
		//					//					//databaseResults = tempResults;
		//					//				}
		//					//			//}
		//					//		}
		//					//	}

		//					if (declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::assign) {//follows(s,a) select a with pattern
		//						if (result != tokens.end()) {//find pattern word
		//							string entref;
		//							if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8]) == false) {//if rhs of pattern is _
		//								entref = tokens[i + 8];
		//								//Database::insertpattern(entref);
		//								Database::getpatternfollowsleft(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[i + 8]) && verify::isUnderscore(tokens[i + 9]) == false) {//if lhs of pattern is _
		//								entref = tokens[i + 9];
		//								string temp = convert(entref);
		//								Database::getpatternfollowsright(databaseResults, temp);
		//							}
		//							else if (verify::isUnderscore(tokens[i + 8]) && verify::isUnderscore(tokens[i + 9])) {//if pattern a (_,_"something")
		//								entref = tokens[i + 10];
		//								string temp = convert(entref);
		//								Database::getpartialpatternfollowsright(databaseResults, temp);
		//							}
		//						}
		//					}
		//				}
		//				//not cfm
		//				//else if (querytype == declaretype::assign && result != tokens.end()) {//assign plus pattern
		//				//	if (verify::isUnderscore(tokens[i + 9])) {//if rhs of pattern is _
		//				//		string entref = tokens[i + 8];
		//				//		Database::insertpattern(entref);
		//				//		Database::getpatternAssignleftfollows(databaseResults);
		//				//	}
		//				//	else if (verify::isUnderscore(tokens[i + 8])) {//if lhs of pattern is _
		//				//		if (verify::isNumber(tokens[i + 9])) {//if it is string of words
		//				//			string entref = tokens[i + 9];
		//				//			Database::insertpatternconstant(entref);
		//				//			Database::getpatternAssignconstantrightfollows(databaseResults);
		//				//		}
		//				//		else if (verify::isNumber(tokens[i + 9]) == false) {//if it is not constant
		//				//			string entref = tokens[i + 9];
		//				//			Database::insertpattern(entref);
		//				//			Database::getpatternAssignrightfollows(databaseResults);
		//				//		}
		//				//	}
		//				//}
		//			}
		//			else if (tokens[i] == "Follows*") {
		//				if (result == tokens.end()) {//if no pattern
		//					//follow right unknown follows*(2,s2)/follows*(_,s2)/follows*(5,_)

		//					if (querytype == declaretype::statement && verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement) {//follows*(_,s2)
		//						Database::getfollowsStarright3(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//follows*(2, s2)
		//						string var = tokens[i + 2];
		//						Database::getfollowsStarright(databaseResults, var);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3]) && querytype == declaretype::statement) {//follows*(5,_)
		//						Database::getfollowsStarright2(databaseResults);
		//					}

		//					if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement) {//for follows*(s1,s2)

		//						if (argtype == relarg2) {//select s2
		//							Database::gets2stmtStar(databaseResults);
		//						}
		//					}
		//					//follow left unknown follows*(s1,_)/follows*(s1,5)/follows*(_,5)


		//					else if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows*(s1,_)
		//						Database::getfollowsStarleft3(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//follows*(s1, 5)
		//						string var = tokens[i + 3];
		//						Database::getfollowsStarleft(databaseResults, var);
		//					}
		//					if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2]) && querytype == declaretype::statement) {//follows*(_,5)
		//						Database::getfollowsStarleft2(databaseResults);
		//					}

		//					if (declaration[tokens[i + 3]] == declaretype::statement && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//for follows*(s1,s2)
		//						if (argtype == relarg1) {//select s1
		//							Database::gets1stmtStar(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::statement) {//select s
		//						if (declaration[tokens[i + 3]] == declaretype::read) {//follows*(s ,re)
		//							Database::getfollowsStarleftstmt(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::read) {//follows*(re,s)
		//							Database::getfollowsStarrightstmt(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::print) {//follows*(s,pn)
		//							Database::getfollowsStarleftstmt2(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::read) {//follows*(pn, s)
		//							Database::getfollowsStarrightstmt2(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::call) {//follows*(s,c)
		//							Database::getfollowsStarleftstmt3(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::call) {//follows* (c,s)
		//							Database::getfollowsStarrightstmt3(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::assign) {//follows *(a,s)
		//							Database::getfollowsStarrightstmt4(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::assign) {//follows* (s,a)
		//							Database::getfollowsStarleftstmt4(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::print) {//select pn
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows*(pn, _)
		//							Database::getfollowsStarleftprint(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(pn,s2) select pn
		//							Database::getfollowsStarleftprint(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,pn)
		//							Database::getfollowsStarrightprint(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,pn)
		//							Database::getfollowsStarrightprint(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::read) {//select r
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows*(r, _)
		//							Database::getfollowsStarleftread(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(r,s2)
		//							Database::getfollowsStarleftread(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,r)
		//							Database::getfollowsStarrightread(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,r)
		//							Database::getfollowsStarrightread(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::call) {
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows*(c, _)
		//							Database::getfollowsStarleftcall(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(c,s2)
		//							Database::getfollowsStarleftcall(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,c)
		//							Database::getfollowsStarrightcall(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,c)
		//							Database::getfollowsStarrightcall(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::assign) {
		//						if (verify::isUnderscore(tokens[i + 3])) {//follows*(a, _)
		//							Database::getfollowsStarleftassign(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 3]] == declaretype::statement) {//follows*(a,s2)
		//							Database::getfollowsStarleftassign(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 2])) {//follows*(_,a)
		//							Database::getfollowsStarrightassign(databaseResults);
		//						}
		//						else if (declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s1,a)
		//							Database::getfollowsStarrightassign(databaseResults);
		//						}
		//					}
		//				}
		//				else {
		//					if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//follows*(s,a) select a with pattern
		//						if (result != tokens.end()) {//find pattern word
		//							if (verify::isUnderscore(tokens[i + 9])) {//if rhs of pattern is _
		//								string entref = tokens[i + 8];
		//								//Database::insertpattern(entref);
		//								Database::getpatternfollowsStarleft(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[i + 8])) {//if lhs of pattern is _
		//								string entref = tokens[i + 9];
		//								string temp = convert(entref);
		//								Database::getpatternfollowsStarright(databaseResults, temp);
		//							}
		//						}
		//					}
		//				}
		//				//old codes
		//				//if (querytype != declaretype::none && verify::isNumber(tokens[i + 2])) {//followsright unknown
		//				//	string lineNumber = to_string(1);
		//				//	string nestinglvl;
		//				//	Database::insertfollowsleft(lineNumber, tokens[i + 2], nestinglvl);
		//				//	Database::getfollowsTright(databaseResults);
		//				//}
		//				//else if (querytype != declaretype::none && verify::isNumber(tokens[i + 3])) {//followleft unknown
		//				//	string lineNumber = to_string(1);
		//				//	string nestinglvl;
		//				//	Database::insertfollowsright(lineNumber, tokens[i + 3], nestinglvl);
		//				//	Database::getfollowsTleft(databaseResults);

		//				//}else if(verify::isUnderscore(tokens[i + 2])) {
		//				//	string lineNumber = to_string(1);
		//				//	string nestinglvl;
		//				//	Database::insertfollowsright(lineNumber, tokens[i + 3], nestinglvl);
		//				//	Database::getfollowsTleft(databaseResults);
		//				//}else if (verify::isUnderscore(tokens[i + 3])) {
		//				//	string lineNumber = to_string(1);
		//				//	string nestinglvl;

		//				//	Database::insertfollowsleft(lineNumber, tokens[i + 2], nestinglvl);
		//				//	Database::getfollowsTright(databaseResults);
		//				//}
		//				//if (stmtType == "stmt" && stmtType2 == "stmt") {//for follows(s1,s2)
		//				//	if (argtype == relarg1) {//select s1
		//				//		Database::gets1stmt(databaseResults);
		//				//	}
		//				//	else if (argtype == relarg2) {//select s2
		//				//		Database::gets2stmt(databaseResults);
		//				//	}
		//				//}
		//			}
		//			else if (tokens[i] == "Parent") {
		//				//if (result == tokens.end()) {//if no pattern
		//				if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 2]) || verify::isNumber(tokens[i + 2])) {//parent right unknown Parent(8,s2)/Parent(_,S2)/Parent(8,_)
		//					if (verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent(_,s2)
		//						Database::getparenttableright2(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent(8, s2)
		//						//Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
		//						string var = tokens[i + 2];
		//						Database::getparenttableright(databaseResults, var);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3])) {//Parent(8,_)
		//						Database::getparenttableright2(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {//Parent(w,a) select a
		//						if (result != tokens.end()) {//find pattern word
		//							if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
		//								string entref = tokens[j + 5];
		//								//Database::insertpattern(entref);
		//								Database::getpatternparentleft(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
		//								string entref = tokens[j + 6];
		//								string temp = convert(entref);
		//								Database::getpatternparentright(databaseResults, temp);
		//							}
		//							else if (verify::isUnderscore(tokens[j + 6]) && verify::isUnderscore(tokens[j + 5])) {
		//								string entref = tokens[j + 7];
		//								string temp = convert(entref);

		//							}
		//						}
		//						else {
		//							Database::getparenttableright3(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {//Parent(ifs,a) select a
		//						if (result != tokens.end()) {//find pattern word
		//							if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
		//								string entref = tokens[j + 5];
		//								//Database::insertpattern(entref);
		//								Database::getpatternparentleft2(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
		//								string entref = tokens[j + 6];
		//								Database::getpatternparentright2(databaseResults, entref);
		//							}
		//						}
		//						else {
		//							Database::getparenttableright4(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//Parent(s,a) select a
		//						if (result != tokens.end()) {//find pattern word
		//							if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
		//								string entref = tokens[j + 5];
		//								//Database::insertpattern(entref);
		//								Database::getpatternparentleft3(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
		//								string entref = tokens[j + 6];
		//								string temp = convert(entref);
		//								Database::getpatternparentright3(databaseResults, temp);
		//							}
		//						}
		//						else {
		//							Database::getparenttableright5(databaseResults);
		//						}
		//					}

		//				}
		//				if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 3]) || verify::isNumber(tokens[i + 3])) {//parent left unknown Parent(s1,12)/Parent(S1,_)/Parent(_,12)
		//					if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent(S1,_)
		//						Database::getparenttableleft2(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent(s1,12)
		//						//Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//						string var = tokens[i + 3];
		//						Database::getparentleft(databaseResults, var);
		//					}
		//					else if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2])) {//Parent(_,12)
		//						Database::getparenttableleft2(databaseResults);
		//					}

		//					else if (querytype == declaretype::ifs && verify::isNumber(tokens[i + 3])) {//parent(i,3) select if
		//						//Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//						string var = tokens[i + 3];
		//						Database::getparenttableleft6(databaseResults, var);
		//					}
		//					else if (querytype == declaretype::whiles && verify::isNumber(tokens[i + 3])) {//parent(w,3) select w
		//					   //Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//						string var = tokens[i + 3];
		//						Database::getparenttableleft7(databaseResults, var);
		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {//Parent(w,a) select w
		//						Database::getparenttableleft3(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {//Parent(ifs,a) select ifs
		//						Database::getparenttableleft4(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {//Parent(s,a) select s
		//						Database::getparenttableleft5(databaseResults);
		//					}
		//				}
		//				//}
		//				//old codes
		//				//if (querytype != declaretype::none && verify::isNumber(tokens[i + 2])) {//parent right unknown
		//				//	string lineNumber = to_string(1);
		//				//	string nestinglvl;
		//				//	Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
		//				//	if (verify::isUnderscore(tokens[i + 3])) {
		//				//		Database::getparentTright(databaseResults);
		//				//	}
		//				//	else {
		//				//		Database::getparentright(databaseResults);
		//				//	}
		//				//}
		//				//else if (querytype != declaretype::none && verify::isNumber(tokens[i + 3])) {//parent left unknown
		//				//	string lineNumber = to_string(1);
		//				//	string nestinglvl;
		//				//	Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//				//	Database::getparentleft(databaseResults);
		//				//	if (verify::isUnderscore(tokens[i + 2])) {
		//				//		Database::getparentTleft(databaseResults);
		//				//	}
		//				//	else {
		//				//		Database::getparentleft(databaseResults);
		//				//	}
		//				//}
		//				//not cfm
		//				//else if (querytype == declaretype::whiles && result != tokens.end()) {//parent(w,a)
		//				//		if (verify::isUnderscore(tokens[i + 9])) {
		//				//			string lineNumber = to_string(1);
		//				//			Database::insertstringuses(lineNumber, tokens[i + 8]);
		//				//			Database::getparentwhilepatternleft(databaseResults);
		//				//		}
		//				//		else if (verify::isUnderscore(tokens[i + 8])) {
		//				//			string lineNumber = to_string(1);
		//				//			Database::insertstringuses(lineNumber, tokens[i + 9]);
		//				//			Database::getparentwhilepatternright(databaseResults);
		//				//		}
		//				//}
		//				//else if (querytype == declaretype::ifs && result != tokens.end()) {//parent(ifs,a)
		//				//		if (verify::isUnderscore(tokens[i + 9])) {
		//				//			string lineNumber = to_string(1);
		//				//			Database::insertstringuses(lineNumber, tokens[i + 8]);
		//				//			Database::getparentifpatternleft(databaseResults);
		//				//		}
		//				//		else if (verify::isUnderscore(tokens[i + 8])) {
		//				//			string lineNumber = to_string(1);
		//				//			Database::insertstringuses(lineNumber, tokens[i + 9]);
		//				//			Database::getparentifpatternright(databaseResults);
		//				//		}
		//				//}
		//			}
		//			else if (tokens[i] == "Parent*") {
		//				//if (result == tokens.end()) {//if no pattern
		//				if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 2]) || verify::isNumber(tokens[i + 2])) {//parent* right unknown Parent*(8,s2)/Parent*(_,S2)/Parent*(8,_)

		//					if (verify::isUnderscore(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(_,s2)
		//						Database::getparentStartableright2(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && declaration[tokens[i + 3]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(8, s2)
		//						//Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
		//						string var = tokens[i + 2];
		//						Database::getparentStartableright(databaseResults, var);
		//					}
		//					else if (verify::isNumber(tokens[i + 2]) && verify::isUnderscore(tokens[i + 3])) {//Parent*(8,_)
		//						Database::getparentStartableright2(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {//Parent*(w,a) select a
		//						if (result != tokens.end()) {//find pattern word
		//							if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
		//								string entref = tokens[j + 5];
		//								//Database::insertpattern(entref);
		//								Database::getpatternparentleft(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
		//								string entref = tokens[j + 6];
		//								Database::getpatternparentright(databaseResults, entref);
		//							}
		//						}
		//						else {
		//							Database::getparentStartableright3(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {//Parent*(ifs,a) select a
		//						if (result != tokens.end()) {//find pattern word
		//							if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
		//								string entref = tokens[j + 5];
		//								//Database::insertpattern(entref);
		//								Database::getpatternparentleft2(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
		//								string entref = tokens[j + 6];
		//								string temp = convert(entref);
		//								Database::getpatternparentright2(databaseResults, temp);
		//							}
		//						}
		//						else {
		//							Database::getparentStartableright4(databaseResults);
		//						}
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {//Parent*(s,a) select a
		//						if (patternExist == true) {//find pattern word
		//							if (verify::isUnderscore(tokens[j + 6])) {//if rhs of pattern is _
		//								string entref = tokens[j + 5];
		//								//Database::insertpattern(entref);
		//								Database::getpatternparentleft3(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[j + 5])) {//if lhs of pattern is _
		//								string entref = tokens[j + 6];
		//								Database::getpatternparentright3(databaseResults, entref);
		//							}
		//							else if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8])) { //partial pattern
		//								string entref = tokens[i + 10];
		//								string temp = convert(entref);
		//								Database::getpatternParent(databaseResults, temp);
		//							}
		//						}
		//						else {
		//							Database::getparentStartableright5(databaseResults);
		//						}

		//					}

		//				}
		//				if (querytype != declaretype::none || verify::isUnderscore(tokens[i + 3]) || verify::isNumber(tokens[i + 3])) {//parent* left unknown Parent*(s1,12)/Parent*(S1,_)/Parent*(_,12)

		//					if (verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(S1,_)
		//						Database::getparentStartableleft2(databaseResults);
		//					}
		//					else if (verify::isNumber(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::statement && querytype == declaretype::statement) {//Parent*(s1,12)
		//						//Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//						string var = tokens[i + 3];
		//						Database::getparentStartableleft(databaseResults, var);
		//					}
		//					else if (verify::isNumber(tokens[i + 3]) && verify::isUnderscore(tokens[i + 2])) {//Parent*(_,12)
		//						Database::getparentStartableleft2(databaseResults);
		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {//Parent*(w,a) select w
		//						Database::getparentStartableleft3(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {//Parent*(ifs,a) select ifs
		//						Database::getparentStartableleft4(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {//Parent*(s,a) select s
		//						Database::getparentStartableleft5(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && verify::isNumber(tokens[i + 3])) {//parent*(i,3) select if
		//					   //Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//						string var = tokens[i + 3];
		//						Database::getparentStartableleft6(databaseResults, var);
		//					}
		//					else if (querytype == declaretype::whiles && verify::isNumber(tokens[i + 3])) {//parent*(w,3) select w
		//					   //Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//						string var = tokens[i + 3];
		//						Database::getparentStartableleft7(databaseResults, var);
		//					}
		//				}
		//				//}
		//				/*if (querytype != declaretype::none && verify::isNumber(tokens[i + 2])) {
		//					string lineNumber = to_string(1);
		//					string nestinglvl;
		//					Database::insertparentleft(lineNumber, tokens[i + 2], nestinglvl);
		//					Database::getparentTright(databaseResults);
		//				}
		//				else if (querytype != declaretype::none && verify::isNumber(tokens[i + 3])) {
		//					string lineNumber = to_string(1);
		//					string nestinglvl;
		//					Database::insertparentright(lineNumber, tokens[i + 3], nestinglvl);
		//					Database::getparentTleft(databaseResults);
		//				}*/
		//				//pattern but not cfm
		//				/*else if (querytype == declaretype::whiles && result != tokens.end()) {
		//						if (verify::isUnderscore(tokens[i + 9])) {
		//							string lineNumber = to_string(1);
		//							Database::insertstringuses(lineNumber, tokens[i + 8]);
		//							Database::getparentwhilepatternleft(databaseResults);
		//						}
		//						else if(verify::isUnderscore(tokens[i + 8])) {
		//							string lineNumber = to_string(1);
		//							Database::insertstringuses(lineNumber, tokens[i + 9]);
		//							Database::getparentwhilepatternright(databaseResults);
		//						}
		//				}
		//				else if (querytype == declaretype::ifs && result != tokens.end()) {
		//						if (verify::isUnderscore(tokens[i + 9])) {
		//							string lineNumber = to_string(1);
		//							Database::insertstringuses(lineNumber, tokens[i + 8]);
		//							Database::getparentifpatternleft(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 8])) {
		//							string lineNumber = to_string(1);
		//							Database::insertstringuses(lineNumber, tokens[i + 9]);
		//							Database::getparentifpatternright(databaseResults);
		//						}
		//				}*/
		//			}
		//			else if (tokens[i] == "Uses") {
		//				//if (querytype == declaretype::assign) {
		//				//	//pattern
		//				//	if (result != tokens.end()) {
		//				//		if (verify::isAlpha(tokens[i + 8])) {//if rhs is _
		//				//			string lineNumber = to_string(1);
		//				//			Database::insertstringuses(lineNumber, tokens[i + 8]);
		//				//			Database::getUsespatternvariable(databaseResults);
		//				//		}
		//				//		else if (verify::isUnderscore(tokens[i + 8])) {//if lhs is _
		//				//			string lineNumber = to_string(1);
		//				//			Database::insertstringuses(lineNumber, tokens[i + 9]);
		//				//			Database::getassignUsespatternvariableright(databaseResults);
		//				//		}
		//				//	}
		//					//no patten
		//						/*string lineNumber = to_string(1);
		//						Database::insertstringuses(lineNumber, tokens[i + 3]);
		//						Database::getassignUses(databaseResults);*/
		//						//if (result == tokens.end()) {//if no pattern
		//				if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::variable) {//uses(a,v) select a
		//					if (patternExist == true) {// if pattern
		//						if (verify::isUnderscore(tokens[i + 9]) && declaration[tokens[i + 8]] != declaretype::variable) {//if rhs of pattern is _
		//							string entref = tokens[i + 8];
		//							//Database::insertpattern(entref);
		//							Database::getpatternUsesleft(databaseResults, entref); //select a pattern("index", _)
		//						}
		//						else if (verify::isUnderscore(tokens[i + 9]) && declaration[tokens[i + 8]] == declaretype::variable) {//uses(a,v) select a pattern (v,_)
		//							//Database::insertpattern(entref);
		//							Database::getpatternUsesleft2(databaseResults);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 9]) && verify::isUnderscore(tokens[i + 8])) { //partial pattern
		//							string entref = tokens[i + 10];
		//							string temp = convert(entref);
		//							Database::getpatternUses(databaseResults, temp);
		//						}
		//					}
		//					else {
		//						Database::getassignUses1(databaseResults);
		//					}
		//				}
		//				else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::assign) {//uses(a,v) select v
		//					Database::getassignUses2(databaseResults);
		//				}
		//				else if (querytype == declaretype::assign && declaration[tokens[i + 3]] != declaretype::variable) {//uses(a,"cenx") select a
		//					string var = tokens[i + 3];
		//					Database::getassignUses3(databaseResults, var);
		//				}
		//				else if (querytype == declaretype::assign && verify::isUnderscore(tokens[i + 3])) {//uses(a,_) select v
		//					Database::getassignUses5(databaseResults);
		//				}
		//				else if (querytype == declaretype::print && declaration[tokens[i + 3]] != declaretype::variable) {//uses(pn, "CenX") select pn
		//					string var = tokens[i + 3];
		//					Database::getprintUses2(databaseResults, var);
		//				}
		//				else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::variable) {//uses(pn, v) select pn 
		//				   //string lineNumber = to_string(1);
		//					Database::getprintUses3(databaseResults);
		//				}
		//				else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::print) {//uses (pn,v) select v

		//					Database::getprintUses4(databaseResults);
		//				}
		//				else if (querytype == declaretype::variable && verify::isNumber(tokens[i + 2])) {//uses(10, v) select v
		//					string entity = tokens[i + 2];
		//					Database::getentityUses(databaseResults, entity);
		//				}
		//				else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::print) {//uses(pn,_) select v
		//					Database::getprintUses5(databaseResults);
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::whiles) {//containment stmt
		//					if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::whiles) {//uses(w,v) select w
		//						Database::getcontstmtUses6(databaseResults);
		//					}
		//					else if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::variable) {//uses(w,v) select v
		//						Database::getcontstmtUses7(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(w,_) select v
		//						Database::getcontstmtUses3(databaseResults);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::statement) {
		//					if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(s,_) select v
		//						Database::getcontstmtUses8(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(s,v) select v
		//						Database::getcontstmtUses10(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::variable) {//uses(s,v) select s

		//						Database::getcontstmtUses9(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] != declaretype::variable) {//uses(s,"v") select s
		//						string var = tokens[i + 3];
		//						Database::getcontstmtUses4(databaseResults, var);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::ifs) {
		//					if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::variable) {//uses(if,v) select if
		//						Database::getcontstmtUses1(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(if, v) select v
		//						Database::getcontstmtUses2(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(if,_) select v
		//						Database::getcontstmtUses3(databaseResults);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::procedure) {
		//					if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(p,v) select v
		//						Database::getprocUses2(databaseResults);
		//					}
		//					else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] == declaretype::variable) {//uses(p,v) select p
		//						Database::getprocuses1(databaseResults);

		//					}
		//					else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(p,_) select v
		//						Database::getcontstmtModifies8(databaseResults);
		//					}
		//					else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//uses(p,"something") select p
		//						string var = tokens[i + 3];
		//						Database::getprocUses4(databaseResults, var);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::call) {
		//					if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//uses(c,v) select v
		//						Database::getcalluses2(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::variable) {//uses(c,v) select c
		//						Database::getcallUses1(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//uses(c,_) select v
		//						Database::getcontstmtModifies8(databaseResults);
		//					}
		//					else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//uses(c,"something") select c
		//						string var = tokens[i + 3];
		//						Database::getcallUses4(databaseResults, var);
		//					}
		//				}
		//				//}
		//				//old codes
		//				//else if (querytype == declaretype::statement || querytype == declaretype::whiles || querytype == declaretype::ifs) {
		//				//	/*string lineNumber = to_string(1);
		//				//	Database::insertstringuses(lineNumber, tokens[i + 3]);
		//				//	Database::getstmtUses(databaseResults);*/
		//				//}
		//				//else if (querytype == declaretype::procedure) {
		//				//	/*string lineNumber = to_string(1);
		//				//	Database::insertstringuses(lineNumber, tokens[i + 3]);
		//				//	Database::getprocedureUses(databaseResults);*/
		//				//}
		//				//else if (querytype == declaretype::variable) {
		//				//	/*string lineNumber = to_string(1);
		//				//	Database::insertuses(lineNumber, tokens[i + 2]);
		//				//	Database::getUses(databaseResults);*/
		//				//}
		//			}
		//			else if (tokens[i] == "Modifies") {
		//				//if (result == tokens.end()) {//if no pattern word
		//				if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(a,v) select a
		//					if (result != tokens.end()) {// if pattern
		//						if (verify::isUnderscore(tokens[i + 8]) && declaration[tokens[i + 9]] != declaretype::variable) {
		//							string entref = tokens[i + 9];

		//							//Database::insertpattern(entref);
		//							Database::getpatternModifiesleft2(databaseResults, entref); //select a pattern(_,"index")
		//						}
		//						else if (verify::isUnderscore(tokens[i + 9]) && declaration[tokens[i + 8]] == declaretype::variable) {//modifies(a,v) select a pattern (_,v)
		//							//Database::insertpattern(entref);
		//							Database::getpatternModifiesleft(databaseResults);
		//						}
		//					}
		//					else {
		//						Database::getassignModifies1(databaseResults);
		//					}
		//				}
		//				else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::assign && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(a,v) select v
		//					int pattern = 0;
		//					string entref;
		//					if (result != tokens.end()) {//find pattern word
		//						if (verify::isUnderscore(tokens[i + 9])) {//if rhs of pattern is _
		//							entref = tokens[i + 8];
		//							Database::getpatternM(databaseResults, entref);
		//						}
		//						else if (verify::isUnderscore(tokens[i + 8])) {//if lhs of pattern is _
		//							entref = tokens[i + 9];
		//							string temp = convert(entref);
		//							Database::getpatternM2(databaseResults, temp);
		//						}
		//						//else if (verify::isUnderscore(tokens[j + 5]) && verify::isUnderscore(tokens[j + 6])) {//partial pattern rhs 
		//						//	entref = tokens[j + 7];
		//						//	string temp = convert(entref);
		//						//	Database::getpatternS2(databaseResults, temp);
		//						//}
		//					}
		//					else {
		//						Database::getassignModifies2(databaseResults);
		//					}
		//				}
		//				else if (querytype == declaretype::assign && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(a,"cenx") select a
		//					string var = tokens[i + 3];
		//					Database::getassignModifies3(databaseResults, var);
		//				}
		//				else if (querytype == declaretype::assign && verify::isUnderscore(tokens[i + 3])) {//modifies(a,_) select v
		//					Database::getassignModifies5(databaseResults);
		//				}
		//				else if (querytype == declaretype::read && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(r, "CenX") select r
		//					string var = tokens[i + 3];
		//					Database::getreadModifies2(databaseResults, var);
		//				}
		//				else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(r, v) select r 
		//					Database::getreadModifies1(databaseResults);
		//				}
		//				else if (querytype == declaretype::variable && declaration[tokens[i + 2]] == declaretype::read) {//modifies (r,v) select v

		//					Database::getreadModifies4(databaseResults);
		//				}
		//				else if (querytype == declaretype::variable && verify::isNumber(tokens[i + 2])) {//modifies(10, v) select v// like modifies(procedureName,v)
		//					string entity = tokens[i + 2];
		//					Database::getentityModifies(databaseResults, entity);
		//				}
		//				else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3]) && declaration[tokens[i + 2]] == declaretype::read) {//modifies(r,_) select v
		//					Database::getreadModifies5(databaseResults);
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::whiles) {//containment stmt
		//					if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::whiles) {//modifies(w,v) select w
		//						Database::getcontstmtModifies6(databaseResults);
		//					}
		//					else if (declaration[tokens[i + 3]] == declaretype::variable && querytype == declaretype::variable) {//modifies(w,v) select v
		//						Database::getcontstmtModifies7(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(w,_) select v
		//						Database::getcontstmtModifies8(databaseResults);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::statement) {
		//					if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(s,_) select v
		//						Database::getcontstmtModifies8(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(s,v) select v
		//						Database::getcontstmtModifies10(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(s,v) select s
		//						Database::getcontstmtModifies9(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(s,"v") select s
		//						string var = tokens[i + 3];
		//						Database::getcontstmtModifies4(databaseResults, var);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::ifs) {
		//					if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(if,v) select if
		//						Database::getcontstmtModifies1(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(if, v) select v
		//						Database::getcontstmtModifies2(databaseResults);
		//					}
		//					else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(if,_) select v
		//						Database::getcontstmtModifies8(databaseResults);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::procedure) {
		//					if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(p,v) select v
		//						Database::getprocModifies2(databaseResults);
		//					}
		//					else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(p,v) select p
		//						Database::getprocModifies1(databaseResults);

		//					}
		//					else if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(p,_) select v
		//						Database::getcontstmtModifies8(databaseResults);
		//					}
		//					else if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(p,"something") select p
		//						string var = tokens[i + 3];
		//						Database::getprocModifies4(databaseResults, var);
		//					}
		//				}
		//				else if (declaration[tokens[i + 2]] == declaretype::call) {
		//					if (querytype == declaretype::variable && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(c,v) select v
		//						Database::getprocModifies2(databaseResults);
		//					}
		//					if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::variable) {//modifies(c,v) select c
		//						Database::getcallModifies1(databaseResults);
		//					}
		//					if (querytype == declaretype::variable && verify::isUnderscore(tokens[i + 3])) {//modifies(c,_) select v
		//						Database::getcontstmtModifies8(databaseResults);
		//					}
		//					if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::variable) {//modifies(c,"something") select c
		//						string var = tokens[i + 3];
		//						Database::getcallModifies4(databaseResults, var);
		//					}
		//				}

		//				//}
		//				//if (querytype == declaretype::variable) {
		//				//	string lineNumber = to_string(1);
		//				//	Database::insertmodifyinteger(lineNumber, tokens[i + 2]);
		//				//	Database::getModifyVar(databaseResults);
		//				//}
		//				//if (verify::isNumber(tokens[i + 2]) == false) {
		//				//	if (querytype == declaretype::assign) {
		//				//		if (result != tokens.end()) {
		//				//			if (verify::isAlpha(tokens[i + 9])) {//if lhs is _
		//				//				string lineNumber = to_string(1);
		//				//				Database::insertmodifystring(lineNumber, tokens[i + 9]);
		//				//				Database::getassignModifiespatternvariableleft(databaseResults);
		//				//			}
		//				//			if(verify::isUnderscore(tokens[i + 9])){//if rhs is _
		//				//				string lineNumber = to_string(1);
		//				//				Database::insertmodifystring(lineNumber, tokens[i + 8]);
		//				//				Database::getassignModifiespatternvariableright(databaseResults);
		//				//			}
		//				//		}
		//				//		else{
		//				//			string lineNumber = to_string(1);
		//				//			Database::insertmodifystring(lineNumber, tokens[i + 3]);
		//				//			Database::getModifyAssign(databaseResults);
		//				//		}
		//				//	}
		//				//	else if (querytype == declaretype::read) {
		//				//		string lineNumber = to_string(1);
		//				//		Database::insertmodifystring(lineNumber, tokens[i + 3]);
		//				//		Database::getModifyRead(databaseResults);
		//				//	}
		//				//	else if (querytype == declaretype::procedure) {
		//				//		string lineNumber = to_string(1);
		//				//		Database::insertmodifystring(lineNumber, tokens[i + 3]);
		//				//		Database::getModifyprocedure(databaseResults);
		//				//	}
		//				//	else if (querytype == declaretype::statement || querytype == declaretype::whiles || querytype == declaretype::ifs) {
		//				//		string lineNumber = to_string(1);
		//				//		Database::insertmodifystring(lineNumber, tokens[i + 3]);
		//				//		Database::getModifystmt(databaseResults);
		//				//	}
		//				//}
		//			}
		//			else if (tokens[i] == "Calls") {
		//				//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] == argtype) {//Calls(p,_) select p
		//				//	Database::getcalls(databaseResults);
		//				//}
		//				//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] != argtype) {//calls(p,_) select q
		//				//	Database::getcalls2(databaseResults);
		//				//}
		//				//if (querytype == declaretype::procedure && tokens[i + 2] == argtype && declaration[tokens[i + 3]] == declaretype::procedure) {//calls(p,q) select p
		//				//	Database::getcalls(databaseResults);
		//				//}
		//				//if (querytype == declaretype::procedure && tokens[i + 3] == argtype && declaration[tokens[i + 2]] == declaretype::procedure) {//calls(p,q) select q
		//				//	Database::getcalls2(databaseResults);
		//				//}
		//				//if (querytype == declaretype::procedure && tokens[i + 3] != argtype && declaration[tokens[i + 3]] == declaretype::none) {//Calls(p, "result") select p
		//				//	string proc = tokens[i + 3];
		//				//	Database::getcalls4(databaseResults, proc);
		//				//}
		//				//if (querytype == declaretype::procedure && tokens[i + 2] != argtype && declaration[tokens[i + 2]] == declaretype::none) {//Calls(something, q) select q
		//				//	string proc = tokens[i + 2];
		//				//	Database::getcalls5(databaseResults, proc);
		//				//}

		//				if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//calls*(_,s) select s calls*(2, _)	calls*(_, 2) //calls*(s,_) select s
		//					if (verify::isUnderscore(tokens[i + 3])) {
		//						Database::getcalls(databaseResults);
		//					}
		//					else if (verify::isUnderscore(tokens[i + 2])) {
		//						Database::getcalls2(databaseResults);
		//					}
		//				}
		//				else if (querytype == declaration[tokens[i + 2]] && declaration[tokens[i + 3]] == declaretype::procedure) {
		//					Database::getcalls(databaseResults);
		//				}
		//				else if (querytype == declaration[tokens[i + 3]] && declaration[tokens[i + 2]] == declaretype::procedure) {
		//					Database::getcalls2(databaseResults);
		//				}
		//				else if (querytype == declaration[tokens[i + 2]] && declaration[tokens[i + 3]] != declaretype::procedure) {
		//					string proc = tokens[i + 3];
		//					Database::getcalls4(databaseResults, proc);
		//				}
		//				else if (querytype == declaration[tokens[i + 3]] && declaration[tokens[i + 2]] != declaretype::procedure) {
		//					string proc = tokens[i + 2];
		//					Database::getcalls5(databaseResults, proc);
		//				}
		//			}
		//			else if (tokens[i] == "Calls*") {
		//				//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] == argtype) {//Calls*(p,_) select p
		//				//	Database::getcallsstar(databaseResults);
		//				//}
		//				//if (querytype == declaretype::procedure && verify::isUnderscore(tokens[i + 3]) && tokens[i + 2] != argtype && declaration[tokens[i + 3]] == declaretype::none) {//Calls*(p,_) select q
		//				//	Database::getcallsstar2(databaseResults);
		//				//}
		//				//if (querytype == declaration[tokens[i + 2]] && declaration[tokens[i + 2]] == declaretype::procedure && declaration[tokens[i + 2]] == declaretype::procedure) {//Calls*(p,q) select p 
		//				//	Database::getcallsstar(databaseResults); 
		//				//}
		//				//if (querytype == declaretype::procedure && tokens[i + 3] == argtype && verify::isUnderscore(tokens[i + 3]) == false) {//Calls*(p,q) select q
		//				//	Database::getcallsstar2(databaseResults);
		//				//}
		//				//if (querytype == declaretype::procedure && declaration[tokens[i + 3]] != declaretype::procedure && declaration[tokens[i + 2]] == declaretype::procedure) {//calls*(p,result") select p
		//				//	string proc = tokens[i + 3];
		//				//	Database::getcallsstar4(databaseResults, proc);
		//				//}
		//				//if (querytype == declaretype::procedure && tokens[i + 2] != argtype) {//Calls*(something, q) select q
		//				//	string proc = tokens[i + 2];
		//				//	Database::getcallsstar5(databaseResults, proc);
		//				//}

		//				if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//calls*(_,s) select s calls*(2, _)	calls*(_, 2) //calls*(s,_) select s
		//					if (verify::isUnderscore(tokens[i + 3])) {
		//						Database::getcallsstar(databaseResults);
		//					}
		//					else if (verify::isUnderscore(tokens[i + 2])) {
		//						Database::getcallsstar2(databaseResults);
		//					}
		//				}
		//				else if (querytype == declaration[tokens[i + 2]] && declaration[tokens[i + 3]] == declaretype::procedure) {
		//					Database::getcallsstar(databaseResults);
		//				}
		//				else if (querytype == declaration[tokens[i + 3]] && declaration[tokens[i + 2]] == declaretype::procedure) {
		//					Database::getcallsstar(databaseResults);
		//				}
		//				else if (querytype == declaration[tokens[i + 2]] && declaration[tokens[i + 3]] != declaretype::procedure) {
		//					string proc = tokens[i + 3];
		//					Database::getcallsstar4(databaseResults, proc);
		//				}
		//				else if (querytype == declaration[tokens[i + 3]] && declaration[tokens[i + 2]] != declaretype::procedure) {
		//					string proc = tokens[i + 2];
		//					Database::getcallsstar5(databaseResults, proc);
		//				}

		//			}
		//			else if (tokens[i] == "Next*") {
		//				if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//next*(_,s) select s next*(2, _)	next*(_, 2) //next*(s,_) select s
		//					if (verify::isUnderscore(tokens[i + 3])) {
		//						Database::getNextstar(databaseResults);
		//					}
		//					else if (verify::isUnderscore(tokens[i + 2])) {
		//						Database::getNextstar2(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::statement) {//next*(s, syno) select s
		//					if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextstarleft(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextstarleft2(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextstarleft3(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextstarleft4(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextstarleft5(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextstarleft6(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && verify::isNumber(tokens[i + 3])) {//next*(s, 4)
		//						string var = tokens[i + 3];
		//						Database::getNextstarleft7(databaseResults, var);
		//					}

		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::statement) {//next*(syno, s) select s
		//					if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextstarRight(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextstarRight2(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextstarRight3(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextstarRight4(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextstarRight5(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextstarRight6(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::none) {//next*(4, s)
		//						string var = tokens[i + 2];
		//						Database::getNextstarRight7(databaseResults, var);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::read) {//next*(read, s) select read
		//					if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextstarleftR(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::print) {//next*(r, print) select read
		//						Database::getNextstarleft2R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextstarleft3R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextstarleft4R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextstarleft5R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextstarleft6R(databaseResults);
		//					}

		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::read) {//next*(s,read) select read
		//					if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextstarRightR(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {//next*(print, r) select read
		//						Database::getNextstarRight2R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextstarRight3R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextstarRight4R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextstarRight5R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextstarRight6R(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::print) {//next*(print, s) select print
		//					if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextstarleftP(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::read) {//next*(print, r) select print
		//						Database::getNextstarleft2P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextstarleft3P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextstarleft4P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextstarleft5P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextstarleft6P(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::print) {//next*(s,print)
		//					if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextstarRightP(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextstarRight2P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextstarRight3P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextstarRight4P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextstarRight5P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextstarRight6P(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::call) {//next*(call, s) select call
		//					if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextstarleftC(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextstarleft2C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextstarleft3C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextstarleft4C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextstarleft5C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextstarleft6C(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::call) {//next*(s,call)
		//					if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextstarRightC(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextstarRight2C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextstarRight3C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextstarRight4C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextstarRight5C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextstarRight6C(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::whiles) {//next*(w, s) select call
		//					if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextstarleftW(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextstarleft2W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextstarleft3W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextstarleft4W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextstarleft5W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextstarleft6W(databaseResults);

		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::whiles) {//next*(s,while) select w
		//					if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextstarRightW(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextstarRight2W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextstarRight3W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextstarRight4W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextstarRight5W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextstarRight6W(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::ifs) {//next*(if, s) select if
		//					if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::statement) {//
		//						Database::getNextstarleftI(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextstarleft2I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextstarleft3I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextstarleft4I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextstarleft5I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextstarleft6I(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::ifs) {//next*(s,if)
		//					if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextstarRightI(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextstarRight2I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextstarRight3I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextstarRight4I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextstarRight5I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextstarRight6I(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::assign) {//next*(a, s) select if
		//					if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::statement) {//
		//						Database::getNextstarleftA(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextstarleft2A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextstarleft3A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextstarleft4A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextstarleft5A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextstarleft6A(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::assign) {//next*(if,a)
		//					if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextstarRightA(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextstarRight2A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextstarRight3A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextstarRight4A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextstarRight5A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextstarRight6A(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::statement && declaration[tokens[i + 3]] == declaretype::statement) {//next*(s1,s2) select s1/s2
		//					if (querytype == declaration[tokens[i + 2]]) {
		//						Database::getNextstar(databaseResults);
		//					}
		//					else if (querytype == declaration[tokens[i + 3]]) {
		//						Database::getNextstar2(databaseResults);
		//					}
		//				}

		//			}
		//			else if (tokens[i] == "Next") {
		//				if (verify::isUnderscore(tokens[i + 3]) || verify::isUnderscore(tokens[i + 2])) {//next(_,s) select s next(2, _)	next(_, 2) //next(s,_) select s
		//					if (verify::isUnderscore(tokens[i + 3])) {
		//						Database::getNext(databaseResults);
		//					}
		//					else if (verify::isUnderscore(tokens[i + 2])) {
		//						Database::getNext2(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::statement) {//next(s, syno) select s
		//					if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextleft(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextleft2(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextleft3(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextleft4(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextleft5(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextleft6(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && verify::isNumber(tokens[i + 3])) {//next*(s, 4)
		//						string var = tokens[i + 3];
		//						Database::getNextleft7(databaseResults, var);
		//					}

		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::statement) {//next*(syno, s) select s
		//					if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextRight(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextRight2(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextRight3(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextRight4(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextRight5(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextRight6(databaseResults);
		//					}
		//					else if (querytype == declaretype::statement && declaration[tokens[i + 3]] == declaretype::none) {//next*(4, s)
		//						string var = tokens[i + 2];
		//						Database::getNextRight7(databaseResults, var);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::read) {//next*(read, s) select read
		//					if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextleftR(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::print) {//next*(r, print) select read
		//						Database::getNextleft2R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextleft3R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextleft4R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextleft5R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextleft6R(databaseResults);
		//					}

		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::read) {//next*(s,read) select read
		//					if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextRightR(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::print) {//next*(print, r) select read
		//						Database::getNextRight2R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextRight3R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextRight4R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextRight5R(databaseResults);
		//					}
		//					else if (querytype == declaretype::read && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextRight6R(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::print) {//next*(print, s) select print
		//					if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextleftP(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::read) {//next*(print, r) select print
		//						Database::getNextleft2P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextleft3P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextleft4P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextleft5P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextleft6P(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::print) {//next*(s,print)
		//					if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextRightP(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextRight2P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextRight3P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextRight4P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextRight5P(databaseResults);
		//					}
		//					else if (querytype == declaretype::print && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextRight6P(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::call) {//next*(call, s) select call
		//					if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextleftC(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextleft2C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextleft3C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextleft4C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextleft5C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextleft6C(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::call) {//next*(s,call)
		//					if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextRightC(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextRight2C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextRight3C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextRight4C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextRight5C(databaseResults);
		//					}
		//					else if (querytype == declaretype::call && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextRight6C(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::whiles) {//next*(w, s) select call
		//					if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::statement) {
		//						Database::getNextleftW(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextleft2W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextleft3W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextleft4W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextleft5W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextleft6W(databaseResults);

		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::whiles) {//next*(s,while) select w
		//					if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextRightW(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextRight2W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextRight3W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextRight4W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextRight5W(databaseResults);

		//					}
		//					else if (querytype == declaretype::whiles && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextRight6W(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::ifs) {//next*(if, s) select if
		//					if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::statement) {//
		//						Database::getNextleftI(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextleft2I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextleft3I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::assign) {
		//						Database::getNextleft4I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextleft5I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextleft6I(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::ifs) {//next*(s,if)
		//					if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextRightI(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextRight2I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextRight3I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::assign) {
		//						Database::getNextRight4I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextRight5I(databaseResults);
		//					}
		//					else if (querytype == declaretype::ifs && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextRight6I(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::assign) {//next*(a, s) select if
		//					if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::statement) {//
		//						Database::getNextleftA(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::read) {
		//						Database::getNextleft2A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::print) {
		//						Database::getNextleft3A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::ifs) {
		//						Database::getNextleft4A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::call) {
		//						Database::getNextleft5A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 3]] == declaretype::whiles) {
		//						Database::getNextleft6A(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 3]] == declaretype::assign) {//next*(if,a)
		//					if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::statement) {
		//						Database::getNextRightA(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::read) {
		//						Database::getNextRight2A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::print) {
		//						Database::getNextRight3A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::ifs) {
		//						Database::getNextRight4A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::call) {
		//						Database::getNextRight5A(databaseResults);
		//					}
		//					else if (querytype == declaretype::assign && declaration[tokens[i + 2]] == declaretype::whiles) {
		//						Database::getNextRight6A(databaseResults);
		//					}
		//				}
		//				if (declaration[tokens[i + 2]] == declaretype::statement && declaration[tokens[i + 3]] == declaretype::statement) {//next*(s1,s2) select s1/s2
		//					if (querytype == declaration[tokens[i + 2]]) {
		//						Database::getNext(databaseResults);
		//					}
		//					else if (querytype == declaration[tokens[i + 3]]) {
		//						Database::getNext2(databaseResults);
		//					}
		//				}

		//			}
		//		}
		//	}
		//}

	}


	// post process the results to fill in the output vector
	for (string databaseResult : databaseResults) {
		output.push_back(databaseResult);
	}
}