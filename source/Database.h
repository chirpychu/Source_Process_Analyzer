#pragma once

#include <string>
#include <vector>
#include "sqlite3.h"

using namespace std;


// The Database has to be a static class due to various constraints.
// It is advisable to just add the insert / get functions based on the given examples.
class Database {
public:
	// method to connect to the database and initialize tables in the database
	static void initialize();

	// method to close the database connection
	static void close();

	// method to insert a procedure into the database
	static void insertProcedure(string procedureNum, string procedureName);

	// method to get all the procedures from the database
	static void getProcedures(vector<string>& results);

	//method to insert a variable into database
	static void insertVariable(string stmtLine, string variableName, string procedureName);

	//method to insert a expr into database
	static void insertExpr(string stmtLine, string exprName, string procedureName);

	//method to get all variables from the database
	static void getVariables(vector<string>& results);

	//method to insert print numbers into database
	static void insertPrint(string printNumber, string printName);

	//method to get all print numbers from the database
	static void getPrint(vector<string>& results);

	//method to insert constant numbers into database
	static void insertConstant(string stmtline, string constantNumber);

	//method to get all constant numbers from the database
	static void getConstant(vector<string>& results);

	//method to insert read into database
	static void insertRead(string readNumber, string readName);

	//method to get all read from the database
	static void getRead(vector<string>& results);

	static void getcall(vector<string>& results);

	//method to insert assignment numbers into database
	static void insertAssignment(string assignmentName, string assignVar);
	static void insertexpression(string stmtLine, string rhs);
	//method to get all read from the database
	static void compareResults(vector<string>& results1, vector<string>& results2);
	static void getAssign(vector<string>& results);
	static void getpatternAssign(vector<string>& results, string entref);
	static void getpatternVar(vector<string>& results, string entref);
	static void getpatternC(vector<string>& results, string entref);
	static void getpatternC2(vector<string>& results, string entref);
	static void getpatternS(vector<string>& results, string entref);
	static void getpatternS2(vector<string>& results, string entref);
	static void insertpatternconstant(string entref);
	static void getpatternconstant(vector<string>& results, string entref);
	static void getpatternexpr(vector<string>& results, string entref);
	static void getpatternexpr2(vector<string>& results, string entref);
	static void getpatternexprvar(vector<string>& results, string entref);
	static void getpatternpartialexpr(vector<string>& results, string entref);
	static void getpatternparentleft(vector<string>& results, string entref);
	static void getpatternparentright(vector<string>& results, string entref);
	static void getpatternparentleft2(vector<string>& results, string entref);
	static void getpatternparentright2(vector<string>& results, string entref);
	static void getpatternparentleft3(vector<string>& results, string entref);
	static void getpatternparentright3(vector<string>& results, string entref);
	static void getpatternfollowsleft(vector<string>& results, string entref);
	static void getpatternfollowsright(vector<string>& results, string entref);
	static void getpatternfollowsStarleft(vector<string>& results, string entref);
	static void getpatternfollowsStarright(vector<string>& results, string entref);
	static void getpatternUsesleft2(vector<string>& results);
	static void getpatternUsesleft(vector<string>& results, string entref);
	static void getpatternModifiesleft(vector<string>& results);
	static void getpatternModifiesleft2(vector<string>& results, string entref);
	static void getpartialpatternfollowsright(vector<string>& results, string entref);

	//method to insert statement numbers and type into database
	static void insertStatement(string stmtName, string stmtType, string stmtlist, string procedureNum, string parent, string parentlvl, string nestinglvl, string callName);

	//method to get all read from the database
	static void getStatement(vector<string>& results);

	//method to insert while lines into the db
	static void insertWhile(string whileNumber);

	//method to get all while lines from the database
	static void getWhile(vector<string>& results);

	static void insertwhilecondition(string stmtline, string condition);

	//method to insert if lines into the db
	static void insertIf(string ifNumber);

	static void getIf(vector<string>& results);

	static void insertifcondition(string stmtline, string condition);

	static void insertpattern(string entref);

	//static void insertfollowsright(string lineNumber, string followsNumber, string nestinglvl);//no use
	//static void insertfollowsleft(string followsNumber);//no use
	static void getfollowsright(vector<string>& results, string stmtnumber);
	static void getfollowsStarright(vector<string>& results, string stmtnumber);
	static void getfollowsright2(vector<string>& results);
	static void getfollowsStarright2(vector<string>& results);
	static void getfollowsright3(vector<string>& results);
	static void getfollowsleft(vector<string>& results, string stmtnumber);
	static void getfollowsStarleft(vector<string>& results, string stmtnumber);
	static void getfollowsleft2(vector<string>& results);
	static void getfollowsStarleft2(vector<string>& results);
	static void getfollowsleft3(vector<string>& results);
	static void getfollowsStarleft3(vector<string>& results);
	static void getfollowsTleft(vector<string>& results);
	static void getfollowsTright(vector<string>& results);
	static void getfollowsStarright3(vector<string>& results);
	static void getpatternAssignleftfollows(vector<string>& results);
	static void getpatternAssignrightfollows(vector<string>& results);
	static void getpatternAssignconstantrightfollows(vector<string>& results);
	static void getfollowsleftprint(vector<string>& results);
	static void getfollowsrightprint(vector<string>& results);
	static void getfollowsleftread(vector<string>& results);
	static void getfollowsrightread(vector<string>& results);
	static void getfollowsleftcall(vector<string>& results);
	static void getfollowsrightcall(vector<string>& results);
	static void getfollowsleftassign(vector<string>& results);
	static void getfollowsrightassign(vector<string>& results);
	static void getfollowsleftstmt(vector<string>& results);
	static void getfollowsrightstmt(vector<string>& results);
	static void getfollowsleftstmt2(vector<string>& results);
	static void getfollowsrightstmt2(vector<string>& results);
	static void getfollowsleftstmt3(vector<string>& results);
	static void getfollowsrightstmt3(vector<string>& results);
	static void getfollowsleftstmt4(vector<string>& results);
	static void getfollowsrightstmt4(vector<string>& results);
	static void getfollowsStarleftstmt(vector<string>& results);
	static void getfollowsStarleftstmt2(vector<string>& results);
	static void getfollowsStarleftstmt3(vector<string>& results);
	static void getfollowsStarleftstmt4(vector<string>& results);
	static void getfollowsStarrightstmt(vector<string>& results);
	static void getfollowsStarrightstmt2(vector<string>& results);
	static void getfollowsStarrightstmt3(vector<string>& results);
	static void getfollowsStarrightstmt4(vector<string>& results);
	static void getfollowsStarleftprint(vector<string>& results);
	static void getfollowsStarrightprint(vector<string>& results);
	static void getfollowsStarleftcall(vector<string>& results);
	static void getfollowsStarrightcall(vector<string>& results);
	static void getfollowsStarleftassign(vector<string>& results);
	static void getfollowsStarrightassign(vector<string>& results);
	static void getfollowsStarleftread(vector<string>& results);
	static void getfollowsStarrightread(vector<string>& results);

	//static void insertparentright(string lineNumber, string parentNumber, string nestinglvl);
	//static void insertparentleft(string lineNumber, string parentNumber, string nestinglvl);
	
	static void getparentleft(vector<string>& results, string stmtNumber);
	static void getparentTleft(vector<string>& results);
	static void getparentright(vector<string>& results);
	static void getparenttableright(vector<string>& results, string stmtNumber);
	static void getparentStartableright(vector<string>& results, string stmtNumber);
	static void getparenttableright2(vector<string>& results);
	static void getparentStartableright2(vector<string>& results);
	static void getparenttableright3(vector<string>& results);
	static void getparentStartableright3(vector<string>& results);
	static void getparenttableright4(vector<string>& results);
	static void getparentStartableright4(vector<string>& results);
	static void getparenttableright5(vector<string>& results);
	static void getparentStartableright5(vector<string>& results);
	static void getparenttableleft(vector<string>& results);
	static void getparentStartableleft(vector<string>& results, string stmtNumber);
	static void getparenttableleft2(vector<string>& results);
	static void getparentStartableleft2(vector<string>& results);
	static void getparenttableleft3(vector<string>& results);
	static void getparentStartableleft3(vector<string>& results);
	static void getparenttableleft4(vector<string>& results);
	static void getparentStartableleft4(vector<string>& results);
	static void getparentStartableleft5(vector<string>& results);
	static void getparenttableleft5(vector<string>& results);
	static void getparenttableleft6(vector<string>& results, string stmtNumber);
	static void getparentStartableleft6(vector<string>& results, string stmtNumber);
	static void getparentStartableleft7(vector<string>& results, string stmtNumber);
	static void getparenttableleft7(vector<string>& results, string stmtNumber);
	static void getparentTright(vector<string>& results);
	static void gets1stmt(vector<string>& results);
	static void gets1stmtStar(vector<string>& results);
	static void gets2stmt(vector<string>& results);
	static void gets2stmtStar(vector<string>& results);
	static void getpatternParent(vector<string>& results, string entref);
	static void getpatternNext(vector<string>& results, string entref);
	static void getpatternNext2(vector<string>& results, string entref);
	static void getpatternN2(vector<string>& results, string entref);
	static void getpatternN3(vector<string>& results, string entref);
	static void getpatternN4(vector<string>& results, string entref);
	static void getpatternN5(vector<string>& results, string entref);
	static void getpatternN6(vector<string>& results, string entref);
	static void getpatternNext3(vector<string>& results, string entref);
	static void getpatternNext4(vector<string>& results, string entref);
	static void getpatternNext5(vector<string>& results, string entref);
	static void getpatternNext6(vector<string>& results, string entref);
	static void getpatternNext7(vector<string>& results, string entref);
	static void getparentwhilepatternleft(vector<string>& results);
	static void getparentwhilepatternright(vector<string>& results);
	static void getparentifpatternleft(vector<string>& results);
	static void getparentifpatternright(vector<string>& results);

	//static void insertuses(string lineNumber, string usesNumber);

	static void getUses(vector<string>& results);

	//static void insertstringuses(string lineNumber, string name);

	static void getprocedureUses(vector<string>& results);
	static void getprintUses(vector<string>& results);
	static void getprintUses4(vector<string>& results);
	static void getprintUses2(vector<string>& results, string entity);
	static void getprintUses3(vector<string>& results);
	static void getprintUses5(vector<string>& results);
	static void getentityUses(vector<string>& results, string variable);
	static void getstmtUses(vector<string>& results);
	static void getassignUses(vector<string>& results);
	static void getassignUses1(vector<string>& results);
	static void getassignUses2(vector<string>& results);
	static void getassignUses5(vector<string>& results);
	static void getcontstmtUses1(vector<string>& results);
	static void getcontstmtUses2(vector<string>& results);
	static void getcontstmtUses3(vector<string>& results);
	static void getcontstmtUses6(vector<string>& results);
	static void getcontstmtUses7(vector<string>& results);
	static void getcontstmtUses8(vector<string>& results);
	static void getcontstmtUses9(vector<string>& results);
	static void getcontstmtUses10(vector<string>& results);
	static void getcontstmtUses4(vector<string>& results, string var);
	static void getassignUses3(vector<string>& results, string variable);
	static void insertassignUses2(string s1, string s2);
	static void insertprintUses2(string s1, string s2);
	static void insertcontstmtUses2(string s1, string s2);
	static void insertuseswhilestmt(string s1, string s2);
	static void insertusesifstmt(string s1, string s2);
	static void insertUsesproc(string s1, string s2);
	static void getUsespatternvariable(vector<string>& results);
	static void getassignUsespatternvariableright(vector<string>& results);
	static void getprocUses2(vector<string>& results);
	static void getcalluses2(vector<string>& results);
	static void getprocuses1(vector<string>& results);
	static void getprocUses4(vector<string>& results, string entity);
	static void getcallUses1(vector<string>& results);
	static void getcallUses4(vector<string>& results, string entity);
	static void getpatternUses(vector<string>& results, string entref);


	static void insertmodifyinteger(string lineNumber, string number);
	static void insertmodifystring(string lineNumber, string modifystring);

	static void getModifyVar(vector<string>& results);
	static void getModifyAssign(vector<string>& results);
	static void insertmodifyassign2(string s1, string s2);
	static void insertmodifyread2(string s1, string s2);
	static void insertmodifycontstmt(string s1, string s2);
	static void insertmodifywhilestmt(string s1, string s2);
	static void insertmodifyifstmt(string s1, string s2);
	static void getModifyRead(vector<string>& results);
	static void getModifyprocedure(vector<string>& results);
	static void getModifystmt(vector<string>& results);
	static void getassignModifies1(vector<string>& results);
	static void getassignModifies2(vector<string>& results);
	static void getpatternM(vector<string>& results, string entref);
	static void getpatternM2(vector<string>& results, string entref);
	static void getassignModifies5(vector<string>& results);
	static void getassignModifies3(vector<string>& results, string variable);
	static void getreadModifies2(vector<string>& results, string entity);
	static void getreadModifies1(vector<string>& results);
	static void getreadModifies4(vector<string>& results);
	static void getentityModifies(vector<string>& results, string variable);
	static void getreadModifies5(vector<string>& results);
	static void getcontstmtModifies6(vector<string>& results);
	static void getcontstmtModifies7(vector<string>& results);
	static void getcontstmtModifies8(vector<string>& results);
	static void getcontstmtModifies9(vector<string>& results);
	static void getcontstmtModifies10(vector<string>& results);
	static void getcontstmtModifies1(vector<string>& results);
	static void getcontstmtModifies2(vector<string>& results);
	static void getcontstmtModifies4(vector<string>& results, string entity);
	static void getprocModifies1(vector<string>& results);
	static void getcallModifies1(vector<string>& results);
	static void getprocModifies2(vector<string>& results);
	static void getprocModifies4(vector<string>& results, string entity);
	static void getcallModifies4(vector<string>& results, string entity);
	static void getcallsstar(vector<string>& results);
	static void getcallsstar2(vector<string>& results);
	static void getcallsstar4(vector<string>& results, string proc);
	static void getcallsstar5(vector<string>& results, string proc);

	static void getassignModifiespatternvariableleft(vector<string>& results);
	static void getassignModifiespatternvariableright(vector<string>& results);

	static void getcalls(vector<string>& results);
	static void getcalls2(vector<string>& results);
	static void getcalls3(vector<string>& results);
	static void getcalls4(vector<string>& results, string proc);
	static void getcalls5(vector<string>& results, string proc);
	static void insertmodifyproc(string s1, string s2);
	static void gets1Nextstarstmt(vector<string>& results);
	static void gets2Nextstarstmt(vector<string>& results);
	static void getNextstar(vector<string>& results);
	static void getNextstar2(vector<string>& results);
	static void getNextstarleft(vector<string>& results);
	static void getNextstarleft2(vector<string>& results);
	static void getNextstarleft3(vector<string>& results);
	static void getNextstarleft4(vector<string>& results);
	static void getNextstarleft5(vector<string>& results);
	static void getNextstarleft6(vector<string>& results);
	static void getNextstarleft7(vector<string>& results, string n2);
	static void getNextstarRight(vector<string>& results);
	static void getNextstarRight2(vector<string>& results);
	static void getNextstarRight3(vector<string>& results);
	static void getNextstarRight4(vector<string>& results);
	static void getNextstarRight5(vector<string>& results);
	static void getNextstarRight6(vector<string>& results);
	static void getNextstarRight7(vector<string>& results, string n1);
	static void getNextstarleftR(vector<string>& results);
	static void getNextstarleft2R(vector<string>& results);
	static void getNextstarleft3R(vector<string>& results);
	static void getNextstarleft4R(vector<string>& results);
	static void getNextstarleft5R(vector<string>& results);
	static void getNextstarleft6R(vector<string>& results);
	static void getNextstarRightR(vector<string>& results);
	static void getNextstarRight2R(vector<string>& results);
	static void getNextstarRight3R(vector<string>& results);
	static void getNextstarRight4R(vector<string>& results);
	static void getNextstarRight5R(vector<string>& results);
	static void getNextstarRight6R(vector<string>& results);
	static void getNextstarleftP(vector<string>& results);
	static void getNextstarleft2P(vector<string>& results);
	static void getNextstarleft3P(vector<string>& results);
	static void getNextstarleft4P(vector<string>& results);
	static void getNextstarleft5P(vector<string>& results);
	static void getNextstarleft6P(vector<string>& results);
	static void getNextstarRightP(vector<string>& results);
	static void getNextstarRight2P(vector<string>& results);
	static void getNextstarRight3P(vector<string>& results);
	static void getNextstarRight4P(vector<string>& results);
	static void getNextstarRight5P(vector<string>& results);
	static void getNextstarRight6P(vector<string>& results);
	static void getNextstarleftC(vector<string>& results);
	static void getNextstarleft2C(vector<string>& results);
	static void getNextstarleft3C(vector<string>& results);
	static void getNextstarleft4C(vector<string>& results);
	static void getNextstarleft5C(vector<string>& results);
	static void getNextstarleft6C(vector<string>& results);
	static void getNextstarRightC(vector<string>& results);
	static void getNextstarRight2C(vector<string>& results);
	static void getNextstarRight3C(vector<string>& results);
	static void getNextstarRight4C(vector<string>& results);
	static void getNextstarRight5C(vector<string>& results);
	static void getNextstarRight6C(vector<string>& results);
	static void getNextstarleftW(vector<string>& results);
	static void getNextstarleft2W(vector<string>& results);
	static void getNextstarleft3W(vector<string>& results);
	static void getNextstarleft4W(vector<string>& results);
	static void getNextstarleft5W(vector<string>& results);
	static void getNextstarleft6W(vector<string>& results);
	static void getNextstarRightW(vector<string>& results);
	static void getNextstarRight2W(vector<string>& results);
	static void getNextstarRight3W(vector<string>& results);
	static void getNextstarRight4W(vector<string>& results);
	static void getNextstarRight5W(vector<string>& results);
	static void getNextstarRight6W(vector<string>& results);
	static void getNextstarleftI(vector<string>& results);
	static void getNextstarleft2I(vector<string>& results);
	static void getNextstarleft3I(vector<string>& results);
	static void getNextstarleft4I(vector<string>& results);
	static void getNextstarleft5I(vector<string>& results);
	static void getNextstarleft6I(vector<string>& results);
	static void getNextstarRightI(vector<string>& results);
	static void getNextstarRight2I(vector<string>& results);
	static void getNextstarRight3I(vector<string>& results);
	static void getNextstarRight4I(vector<string>& results);
	static void getNextstarRight5I(vector<string>& results);
	static void getNextstarRight6I(vector<string>& results);
	static void getNextstarleftA(vector<string>& results);
	static void getNextstarleft2A(vector<string>& results);
	static void getNextstarleft3A(vector<string>& results);
	static void getNextstarleft4A(vector<string>& results);
	static void getNextstarleft5A(vector<string>& results);
	static void getNextstarleft6A(vector<string>& results);
	static void getNextstarRightA(vector<string>& results);
	static void getNextstarRight2A(vector<string>& results);
	static void getNextstarRight3A(vector<string>& results);
	static void getNextstarRight4A(vector<string>& results);
	static void getNextstarRight5A(vector<string>& results);
	static void getNextstarRight6A(vector<string>& results);

	static void getNext(vector<string>& results);
	static void getNext2(vector<string>& results);
	static void getNextleft(vector<string>& results);
	static void getNextleft2(vector<string>& results);
	static void getNextleft3(vector<string>& results);
	static void getNextleft4(vector<string>& results);
	static void getNextleft5(vector<string>& results);
	static void getNextleft6(vector<string>& results);
	static void getNextleft7(vector<string>& results, string n2);
	static void getNextRight(vector<string>& results);
	static void getNextRight2(vector<string>& results);
	static void getNextRight3(vector<string>& results);
	static void getNextRight4(vector<string>& results);
	static void getNextRight5(vector<string>& results);
	static void getNextRight6(vector<string>& results);
	static void getNextRight7(vector<string>& results, string n1);
	static void getNextleftR(vector<string>& results);
	static void getNextleft2R(vector<string>& results);
	static void getNextleft3R(vector<string>& results);
	static void getNextleft4R(vector<string>& results);
	static void getNextleft5R(vector<string>& results);
	static void getNextleft6R(vector<string>& results);
	static void getNextRightR(vector<string>& results);
	static void getNextRight2R(vector<string>& results);
	static void getNextRight3R(vector<string>& results);
	static void getNextRight4R(vector<string>& results);
	static void getNextRight5R(vector<string>& results);
	static void getNextRight6R(vector<string>& results);
	static void getNextleftP(vector<string>& results);
	static void getNextleft2P(vector<string>& results);
	static void getNextleft3P(vector<string>& results);
	static void getNextleft4P(vector<string>& results);
	static void getNextleft5P(vector<string>& results);
	static void getNextleft6P(vector<string>& results);
	static void getNextRightP(vector<string>& results);
	static void getNextRight2P(vector<string>& results);
	static void getNextRight3P(vector<string>& results);
	static void getNextRight4P(vector<string>& results);
	static void getNextRight5P(vector<string>& results);
	static void getNextRight6P(vector<string>& results);
	static void getNextleftC(vector<string>& results);
	static void getNextleft2C(vector<string>& results);
	static void getNextleft3C(vector<string>& results);
	static void getNextleft4C(vector<string>& results);
	static void getNextleft5C(vector<string>& results);
	static void getNextleft6C(vector<string>& results);
	static void getNextRightC(vector<string>& results);
	static void getNextRight2C(vector<string>& results);
	static void getNextRight3C(vector<string>& results);
	static void getNextRight4C(vector<string>& results);
	static void getNextRight5C(vector<string>& results);
	static void getNextRight6C(vector<string>& results);
	static void getNextleftW(vector<string>& results);
	static void getNextleft2W(vector<string>& results);
	static void getNextleft3W(vector<string>& results);
	static void getNextleft4W(vector<string>& results);
	static void getNextleft5W(vector<string>& results);
	static void getNextleft6W(vector<string>& results);
	static void getNextRightW(vector<string>& results);
	static void getNextRight2W(vector<string>& results);
	static void getNextRight3W(vector<string>& results);
	static void getNextRight4W(vector<string>& results);
	static void getNextRight5W(vector<string>& results);
	static void getNextRight6W(vector<string>& results);
	static void getNextleftI(vector<string>& results);
	static void getNextleft2I(vector<string>& results);
	static void getNextleft3I(vector<string>& results);
	static void getNextleft4I(vector<string>& results);
	static void getNextleft5I(vector<string>& results);
	static void getNextleft6I(vector<string>& results);
	static void getNextRightI(vector<string>& results);
	static void getNextRight2I(vector<string>& results);
	static void getNextRight3I(vector<string>& results);
	static void getNextRight4I(vector<string>& results);
	static void getNextRight5I(vector<string>& results);
	static void getNextRight6I(vector<string>& results);
	static void getNextleftA(vector<string>& results);
	static void getNextleft2A(vector<string>& results);
	static void getNextleft3A(vector<string>& results);
	static void getNextleft4A(vector<string>& results);
	static void getNextleft5A(vector<string>& results);
	static void getNextleft6A(vector<string>& results);
	static void getNextRightA(vector<string>& results);
	static void getNextRight2A(vector<string>& results);
	static void getNextRight3A(vector<string>& results);
	static void getNextRight4A(vector<string>& results);
	static void getNextRight5A(vector<string>& results);
	static void getNextRight6A(vector<string>& results);

	static void getNestinglvl(vector<string>& results, int statementNo);
	static void insertfollowstar(int s1, int s2);
	static void insertfollows(string s1, string s2);
	static void insertcalltable(string s1, string s2);
	static void getParentLvl(vector<string>& results, int statementNo);
	static void getparentNestinglvl(vector<string>& results, int statementNo);
	static void insertparent(int s1, int s2);
	static void insertparentstar(int s1, int s2);
	static void getparentStatement(vector<string>& results);
	static void getProcedure(vector<string>& results, int statementNo);
	static void getstmtlist(vector<string>& results, int statementNo);
	static void getID(vector<string>& results);
	static void insertnextstartable(string s1, string s2);
	static void insertnextstartablecall(string s1, string s2);//populate nextstar table
	static void insertnextstartable2(int s1, int s2);
	static void getid(vector<string>& results);
	static void getp(vector<string>& results, int statementNo);
	static void getq(vector<string>& results, int statementNo);
	static void insertpq(int stmti, int stmtj);
	static void insertcallstartable(string s1, string s2);
	static void getpattern1(vector<string>& results, string entref);

	// the connection pointer to the database
	static sqlite3* dbConnection; 
	// a vector containing the results from the database
	static vector<vector<string>> dbResults; 
	// the error message from the database
	static char* errorMessage;
	// callback method to put one row of results from the database into the dbResults vector
	// This method is called each time a row of results is returned from the database
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};

