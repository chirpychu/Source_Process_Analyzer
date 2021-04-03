#include "Database.h"
#include <tuple>

sqlite3* Database::dbConnection;
vector<vector<string>> Database::dbResults;
char* Database::errorMessage;

// method to connect to the database and initialize tables in the database
void Database::initialize() {
	// open a database connection and store the pointer into dbConnection
	sqlite3_open("database.db", &dbConnection);

	// drop the existing procedure table (if any)
	string dropProcedureTableSQL = "DROP TABLE IF EXISTS procedures";
	sqlite3_exec(dbConnection, dropProcedureTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing variable table (if any)
	string dropVariableTableSQL = "DROP TABLE IF EXISTS variables";
	sqlite3_exec(dbConnection, dropVariableTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing print table (if any)
	string dropPrintTableSQL = "DROP TABLE IF EXISTS printTable";
	sqlite3_exec(dbConnection, dropPrintTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing constant table (if any)
	string dropConstantTableSQL = "DROP TABLE IF EXISTS constant";
	sqlite3_exec(dbConnection, dropConstantTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing read table (if any)
	string dropReadTableSQL = "DROP TABLE IF EXISTS read";
	sqlite3_exec(dbConnection, dropReadTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing assign table (if any)
	string dropAssignTableSQL = "DROP TABLE IF EXISTS assignment";
	sqlite3_exec(dbConnection, dropAssignTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing statement table (if any)
	string dropStmtTableSQL = "DROP TABLE IF EXISTS statement";
	sqlite3_exec(dbConnection, dropStmtTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing while table (if any)
	string dropWhileTableSQL = "DROP TABLE IF EXISTS while";
	sqlite3_exec(dbConnection, dropWhileTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropWhileconditionTableSQL = "DROP TABLE IF EXISTS whilecondition";
	sqlite3_exec(dbConnection, dropWhileconditionTableSQL.c_str(), NULL, 0, &errorMessage);

	// drop the existing if table (if any)
	string dropIfTableSQL = "DROP TABLE IF EXISTS iftable";
	sqlite3_exec(dbConnection, dropIfTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropIfconditionTableSQL = "DROP TABLE IF EXISTS ifcondition";
	sqlite3_exec(dbConnection, dropIfconditionTableSQL.c_str(), NULL, 0, &errorMessage);

	//string droppatternconditionTableSQL = "DROP TABLE IF EXISTS pattern";
	//sqlite3_exec(dbConnection, droppatternconditionTableSQL.c_str(), NULL, 0, &errorMessage);

	//string droppatternNumconditionTableSQL = "DROP TABLE IF EXISTS patternNumber";
	//sqlite3_exec(dbConnection, droppatternNumconditionTableSQL.c_str(), NULL, 0, &errorMessage);

	/*string dropfollowleftTableSQL = "DROP TABLE IF EXISTS followslefttable";
	sqlite3_exec(dbConnection, dropfollowleftTableSQL.c_str(), NULL, 0, &errorMessage);
	string dropfollowrightTableSQL = "DROP TABLE IF EXISTS followsrighttable";
	sqlite3_exec(dbConnection, dropfollowrightTableSQL.c_str(), NULL, 0, &errorMessage);*/

	//string dropparentleftTableSQL = "DROP TABLE IF EXISTS parentleft";
	//sqlite3_exec(dbConnection, dropparentleftTableSQL.c_str(), NULL, 0, &errorMessage);
	//string dropparentrightTableSQL = "DROP TABLE IF EXISTS parentright";
	//sqlite3_exec(dbConnection, dropparentrightTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropExprTableSQL = "DROP TABLE IF EXISTS expr";
	sqlite3_exec(dbConnection, dropExprTableSQL.c_str(), NULL, 0, &errorMessage);

	//string dropUsesTableSQL = "DROP TABLE IF EXISTS usesNum";
	//sqlite3_exec(dbConnection, dropUsesTableSQL.c_str(), NULL, 0, &errorMessage);
	//
	//string dropPUsesTableSQL = "DROP TABLE IF EXISTS stringuses";
	//sqlite3_exec(dbConnection, dropPUsesTableSQL.c_str(), NULL, 0, &errorMessage);

	//string dropmodifyintTableSQL = "DROP TABLE IF EXISTS modifyNum";
	//sqlite3_exec(dbConnection, dropmodifyintTableSQL.c_str(), NULL, 0, &errorMessage);

	//string dropmodifystringTableSQL = "DROP TABLE IF EXISTS modifystring";
	//sqlite3_exec(dbConnection, dropmodifystringTableSQL.c_str(), NULL, 0, &errorMessage);
	
	string dropexpressionTableSQL = "DROP TABLE IF EXISTS expressiontable";
	sqlite3_exec(dbConnection, dropexpressionTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropfollowstarTableSQL = "DROP TABLE IF EXISTS followstartable";
	sqlite3_exec(dbConnection, dropfollowstarTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropfollowsTableSQL = "DROP TABLE IF EXISTS followstable";
	sqlite3_exec(dbConnection, dropfollowsTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropparentstarTableSQL = "DROP TABLE IF EXISTS parentstarTable";
	sqlite3_exec(dbConnection, dropparentstarTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropparentTableSQL = "DROP TABLE IF EXISTS parentTable";
	sqlite3_exec(dbConnection, dropparentTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropmodifyTableSQL = "DROP TABLE IF EXISTS modifyTable";
	sqlite3_exec(dbConnection, dropmodifyTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropusesTableSQL = "DROP TABLE IF EXISTS usesTable";
	sqlite3_exec(dbConnection, dropusesTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropcallsTableSQL = "DROP TABLE IF EXISTS callsTable";
	sqlite3_exec(dbConnection, dropcallsTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropcallsStarTableSQL = "DROP TABLE IF EXISTS callsStarTable";
	sqlite3_exec(dbConnection, dropcallsStarTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropnextTableSQL = "DROP TABLE IF EXISTS nextTable";
	sqlite3_exec(dbConnection, dropnextTableSQL.c_str(), NULL, 0, &errorMessage);

	string dropnextStarTableSQL = "DROP TABLE IF EXISTS nextStarTable";
	sqlite3_exec(dbConnection, dropnextStarTableSQL.c_str(), NULL, 0, &errorMessage);
	//string droppatternstringTableSQL = "DROP TABLE IF EXISTS pattern";
	//sqlite3_exec(dbConnection, droppatternstringTableSQL.c_str(), NULL, 0, &errorMessage);

	//string droppatternNumTableSQL = "DROP TABLE IF EXISTS patternNumber";
	//sqlite3_exec(dbConnection, droppatternNumTableSQL.c_str(), NULL, 0, &errorMessage);

	// create a procedure table
	string createProcedureTableSQL = "CREATE TABLE procedures ( procedureNumber INTEGER ,procedureName VARCHAR(255) PRIMARY KEY);";
	sqlite3_exec(dbConnection, createProcedureTableSQL.c_str(), NULL, 0, &errorMessage);

	//create a variable table
	string createVariableTableSQL = "CREATE TABLE variables ( stmtLine INTEGER, variableName VARCHAR(255), procedureName VARCHAR(255), FOREIGN KEY(stmtLine, procedureName) REFERENCES statement(stmtNumber, procedureName));";
	sqlite3_exec(dbConnection, createVariableTableSQL.c_str(), NULL, 0, &errorMessage);

	//create a print table
	string createPrintTableSQL = "CREATE TABLE printTable ( printNumber INTEGER, printName VARCHAR(255), FOREIGN KEY(printNumber) REFERENCES statement(stmtNumber));";
	sqlite3_exec(dbConnection, createPrintTableSQL.c_str(), NULL, 0, &errorMessage);

	//create constant table
	string createConstantTableSQL = "CREATE TABLE constant ( stmtLine INTEGER, constantNumber INTEGER, FOREIGN KEY(stmtLine) REFERENCES statement(stmtNumber));";
	sqlite3_exec(dbConnection, createConstantTableSQL.c_str(), NULL, 0, &errorMessage);

	//create read table
	string createReadTableSQL = "CREATE TABLE read ( readNumber INTEGER, readName VARCHAR(255), FOREIGN KEY(readNumber) REFERENCES statement(stmtNumber));";
	sqlite3_exec(dbConnection, createReadTableSQL.c_str(), NULL, 0, &errorMessage);

	//create assignment table
	string createAssignTableSQL = "CREATE TABLE assignment ( assignNumber INTEGER, assignVar VARCHAR(255), FOREIGN KEY(assignNumber) REFERENCES statement(stmtNumber));";
	sqlite3_exec(dbConnection, createAssignTableSQL.c_str(), NULL, 0, &errorMessage);

	//create statement table
	string createStmtTableSQL = "CREATE TABLE statement ( stmtNumber INTEGER PRIMARY KEY, stmtType VARCHAR(255), stmtlist INTEGER, procedureName VARCHAR(255), parent VARCHAR(255), parentlvl INTEGER, nestinglvl INTEGER, callName VARCHAR(255), FOREIGN KEY(procedureName) REFERENCES procedures(procedureName));";
	sqlite3_exec(dbConnection, createStmtTableSQL.c_str(), NULL, 0, &errorMessage);

	//create while table
	string createWhileTableSQL = "CREATE TABLE while ( whileNumber INTEGER);";
	sqlite3_exec(dbConnection, createWhileTableSQL.c_str(), NULL, 0, &errorMessage);

	//create if table
	string createIfTableSQL = "CREATE TABLE iftable ( ifNumber INTEGER);";
	sqlite3_exec(dbConnection, createIfTableSQL.c_str(), NULL, 0, &errorMessage);

	//create ifcondition table
	string createIfconditionTableSQL = "CREATE TABLE ifcondition (stmtline INTEGER, condition VARCHAR(255));";
	sqlite3_exec(dbConnection, createIfconditionTableSQL.c_str(), NULL, 0, &errorMessage);

	//create whilecondition table
	string createwhileconditionTableSQL = "CREATE TABLE whilecondition (stmtline INTEGER, condition VARCHAR(255));";
	sqlite3_exec(dbConnection, createwhileconditionTableSQL.c_str(), NULL, 0, &errorMessage);

	//string createpatternTableSQL = "CREATE TABLE pattern (entref VARCHAR(255));";
	//sqlite3_exec(dbConnection, createpatternTableSQL.c_str(), NULL, 0, &errorMessage);

	//string createpatternNumberTableSQL = "CREATE TABLE patternNumber (entref INTEGER);";
	//sqlite3_exec(dbConnection, createpatternNumberTableSQL.c_str(), NULL, 0, &errorMessage);

	//string createfollowsrightTableSQL = "CREATE TABLE followsrighttable (lineNumber INTEGER, followsNumber INTEGER, nestinglvl INTEGER);";
	//sqlite3_exec(dbConnection, createfollowsrightTableSQL.c_str(), NULL, 0, &errorMessage);
	//string createfollowsleftTableSQL = "CREATE TABLE followslefttable (followsNumber INTEGER);";
	//sqlite3_exec(dbConnection, createfollowsleftTableSQL.c_str(), NULL, 0, &errorMessage);

	//string createparentrightTableSQL = "CREATE TABLE parentright (lineNumber INTEGER, parentNumber INTEGER, nestinglvl INTEGER);";
	//sqlite3_exec(dbConnection, createparentrightTableSQL.c_str(), NULL, 0, &errorMessage);
	//string createparentleftTableSQL = "CREATE TABLE parentleft (lineNumber INTEGER, parentNumber INTEGER, nestinglvl INTEGER);";
	//sqlite3_exec(dbConnection, createparentleftTableSQL.c_str(), NULL, 0, &errorMessage);

	string createExprTableSQL = "CREATE TABLE expr (stmtLine INTEGER,exprName VARCHAR(255), procedureName VARCHAR(255));";
	sqlite3_exec(dbConnection, createExprTableSQL.c_str(), NULL, 0, &errorMessage);

	string createExpressionTableSQL = "CREATE TABLE expressiontable (stmtLine INTEGER,rhs VARCHAR(255));";
	sqlite3_exec(dbConnection, createExpressionTableSQL.c_str(), NULL, 0, &errorMessage);

	//string createUsesTableSQL = "CREATE TABLE usesNum (lineNumber INTEGER, usesNumber INTEGER);";
	//sqlite3_exec(dbConnection, createUsesTableSQL.c_str(), NULL, 0, &errorMessage);

	//string createPUsesTableSQL = "CREATE TABLE stringuses (lineNumber INTEGER, Name VARCHAR(255));";
	//sqlite3_exec(dbConnection, createPUsesTableSQL.c_str(), NULL, 0, &errorMessage);

	//string createmodifyintTableSQL = "CREATE TABLE modifyNum (lineNumber INTEGER, modifyNumber INTEGER);";
	//sqlite3_exec(dbConnection, createmodifyintTableSQL.c_str(), NULL, 0, &errorMessage);
	//string createmodifystringTableSQL = "CREATE TABLE modifystring (lineNumber INTEGER, modifystring VARCHAR(256));";
	//sqlite3_exec(dbConnection, createmodifystringTableSQL.c_str(), NULL, 0, &errorMessage);

	string createfollowstartableSQL = "CREATE TABLE followstartable (ID INTEGER PRIMARY KEY AUTOINCREMENT,s1 INTEGER, s2 INTEGER);";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createfollowstartableSQL.c_str(), NULL, 0, &errorMessage);

	string createfollowstableSQL = "CREATE TABLE followstable (ID INTEGER PRIMARY KEY AUTOINCREMENT,s1 INTEGER, s2 INTEGER);";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createfollowstableSQL.c_str(), NULL, 0, &errorMessage);

	string createparentstarTableSQL = "CREATE TABLE parentstarTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,s1 INTEGER, s2 INTEGER);";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createparentstarTableSQL.c_str(), NULL, 0, &errorMessage);

	string createparentTableSQL = "CREATE TABLE parentTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,s1 INTEGER, s2 INTEGER);";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createparentTableSQL.c_str(), NULL, 0, &errorMessage);

	string createmodifyTableSQL = "CREATE TABLE modifyTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,entity VARCHAR(255), var VARCHAR(255));";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createmodifyTableSQL.c_str(), NULL, 0, &errorMessage);

	string createusesTableSQL = "CREATE TABLE usesTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,entity VARCHAR(255), var VARCHAR(255));";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createusesTableSQL.c_str(), NULL, 0, &errorMessage);

	string createcallTableSQL = "CREATE TABLE callsTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,p VARCHAR(255), q VARCHAR(255));";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createcallTableSQL.c_str(), NULL, 0, &errorMessage);

	string createcallStarTableSQL = "CREATE TABLE callsStarTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,p VARCHAR(255), q VARCHAR(255));";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createcallStarTableSQL.c_str(), NULL, 0, &errorMessage);

	string createNextTableSQL = "CREATE TABLE nextTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,n1 INTEGER, n2 INTEGER);";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createNextTableSQL.c_str(), NULL, 0, &errorMessage);

	string createNextStarTableSQL = "CREATE TABLE nextStarTable (ID INTEGER PRIMARY KEY AUTOINCREMENT,n1 INTEGER, n2 INTEGER);";//to make follows(s1,s2)
	sqlite3_exec(dbConnection, createNextStarTableSQL.c_str(), NULL, 0, &errorMessage);

	// initialize the result vector
	dbResults = vector<vector<string>>();
}

// method to close the database connection
void Database::close() {
	sqlite3_close(dbConnection);
}

//void Database::insertexpression(string stmtLine, vector<string> rhs) {
//	for (int p = 0; p < rhs.size(); p++) {
//		string insertexpressionSQL = "INSERT INTO expressiontable ('stmtLine','rhs') VALUES ('" + stmtLine + "','" + rhs[p] + "');";
//		sqlite3_exec(dbConnection, insertexpressionSQL.c_str(), NULL, 0, &errorMessage);
//	}
//}

void Database::insertexpression(string stmtLine, string rhs) {
		string insertexpressionSQL = "INSERT INTO expressiontable ('stmtLine','rhs') VALUES ('" + stmtLine + "','" + rhs + "');";
		sqlite3_exec(dbConnection, insertexpressionSQL.c_str(), NULL, 0, &errorMessage);
}

//make the 4 design abstraction tables
void Database::insertfollowstar(int s1, int s2) {
	string insertfollowstarrsSQL = "INSERT INTO followstartable('s1','s2') VALUES ('" + to_string(s1) + "','" + to_string(s2) + "');";
	sqlite3_exec(dbConnection, insertfollowstarrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertfollows(string s1, string s2) {
	string insertfollowsrsSQL = "INSERT INTO followstable(s1,s2) SELECT followstartable.s1, followstartable.s2 FROM followstartable WHERE followstartable.s1 = followstartable.s2 - 1;";
	sqlite3_exec(dbConnection, insertfollowsrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertmodifyassign2(string s1, string s2) {
	string insertmodifyassignrsSQL = "INSERT INTO modifyTable(entity,var) SELECT DISTINCT a.assignNumber, a.assignVar FROM assignment AS a, variables AS v WHERE a.assignVar = v.variableName;";
	sqlite3_exec(dbConnection, insertmodifyassignrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertmodifyread2(string s1, string s2) {
	string insertmodifyreadrsSQL = "INSERT INTO modifyTable(entity,var) SELECT DISTINCT read.readNumber, read.readName FROM read, variables AS v WHERE v.variableName = read.readName;";
	sqlite3_exec(dbConnection, insertmodifyreadrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertmodifycontstmt(string s1, string s2) {
	string insertmodifycontainmentstmtrsSQL = "INSERT INTO modifyTable(entity,var) SELECT DISTINCT v.stmtLine, v.variableName FROM statement, variables AS v WHERE v.stmtLine = statement.stmtNumber AND statement.stmtType = 'read' AND statement.stmtType ='assign' AND statement.parent = 'while' AND statement.parent = 'if';";
	sqlite3_exec(dbConnection, insertmodifycontainmentstmtrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertmodifywhilestmt(string s1, string s2) {
	string insertmodifycontainmentstmtrsSQL = "INSERT INTO modifyTable(entity,var) SELECT DISTINCT v.stmtLine, v.variableName FROM variables AS v, while WHERE v.stmtLine = while.whileNumber;";
	sqlite3_exec(dbConnection, insertmodifycontainmentstmtrsSQL.c_str(), NULL, 0, &errorMessage);
}


void Database::insertmodifyifstmt(string s1, string s2) {
	string insertmodifycontainmentstmtrsSQL = "INSERT INTO modifyTable(entity,var) SELECT DISTINCT v.stmtLine, v.variableName FROM variables AS v, iftable WHERE v.stmtLine = iftable.ifNumber;";
	sqlite3_exec(dbConnection, insertmodifycontainmentstmtrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertmodifyproc(string s1, string s2) {
	string insertmodifyprocrsSQL = "INSERT INTO modifyTable(entity, var) SELECT callsTable.p, modifyTable.var FROM callsTable, modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.procedureName = callsTable.q;";
	sqlite3_exec(dbConnection, insertmodifyprocrsSQL.c_str(), NULL, 0, &errorMessage);

	string insertmodifycallrsSQL = "INSERT INTO modifyTable(entity, var) SELECT callsTable.q, modifyTable.var FROM callsTable, modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'call' AND statement.procedureName = callsTable.p;";
	sqlite3_exec(dbConnection, insertmodifycallrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertassignUses2(string s1, string s2) {
	string insertmodifyassignrsSQL = "INSERT INTO usesTable(entity,var) SELECT DISTINCT expr.stmtLine, expr.exprName FROM expr, variables AS v WHERE expr.exprName = v.variableName;";
	sqlite3_exec(dbConnection, insertmodifyassignrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertprintUses2(string s1, string s2) {
	string insertprintrsSQL = "INSERT INTO usesTable(entity,var) SELECT DISTINCT printTable.printNumber, printTable.printName FROM printTable, variables AS v WHERE v.variableName = printTable.printName;";
	sqlite3_exec(dbConnection, insertprintrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertcontstmtUses2(string s1, string s2) {
	string insertusescontainmentstmtrsSQL = "INSERT INTO usesTable(entity,var) SELECT DISTINCT v.stmtLine, v.variableName FROM statement, variables AS v WHERE v.stmtLine = statement.stmtNumber AND statement.stmtType = 'print' AND statement.stmtType ='assign' AND statement.parent = 'while' AND statement.parent = 'if';";
	sqlite3_exec(dbConnection, insertusescontainmentstmtrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertuseswhilestmt(string s1, string s2) {
	string insertmodifycontainmentstmtrsSQL = "INSERT INTO usesTable(entity,var) SELECT DISTINCT v.stmtLine, v.variableName FROM variables AS v, while WHERE v.stmtLine = while.whileNumber;";
	sqlite3_exec(dbConnection, insertmodifycontainmentstmtrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertusesifstmt(string s1, string s2) {
	string insertmodifycontainmentstmtrsSQL = "INSERT INTO usesTable(entity,var) SELECT DISTINCT v.stmtLine, v.variableName FROM variables AS v, iftable WHERE v.stmtLine = iftable.ifNumber;";
	sqlite3_exec(dbConnection, insertmodifycontainmentstmtrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertparent(int s1, int s2) {
	string insertparentrsSQL = "INSERT INTO parentTable ('s1','s2') VALUES ('" + to_string(s1) + "','" + to_string(s2) + "');";
	sqlite3_exec(dbConnection, insertparentrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertparentstar(int s1, int s2) {
	string insertparentrsSQL = "INSERT INTO parentstarTable ('s1','s2') VALUES ('" + to_string(s1) + "','" + to_string(s2) + "');";
	sqlite3_exec(dbConnection, insertparentrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertcalltable(string s1, string s2) {
	string insertcallrsSQL = "INSERT INTO callsTable(p,q) SELECT p.procedureName, p.callName FROM statement AS p WHERE p.stmtType = 'call';";
	sqlite3_exec(dbConnection, insertcallrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertcallstartable(string s1, string s2) {
	string insertcallrsSQL = "INSERT INTO callsStarTable(p,q) SELECT p.procedureName, p.callName FROM statement AS p WHERE p.stmtType = 'call';";
	sqlite3_exec(dbConnection, insertcallrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertifcondition(string stmtline, string condition) {
		string insertIfconditionSQL = "INSERT INTO ifcondition ('stmtline','condition') VALUES ((SELECT iftable.ifNumber FROM iftable),'" + condition + "');";
		sqlite3_exec(dbConnection, insertIfconditionSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertwhilecondition(string stmtline, string condition) {
		string insertwhileconditionSQL = "INSERT INTO whilecondition ('stmtline','condition') VALUES ((SELECT while.whileNumber FROM while),'" + condition + "');";
		
		sqlite3_exec(dbConnection, insertwhileconditionSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertnextstartable(string s1, string s2) {
	string insertnextstarrsSQL = "INSERT INTO nextTable (n1,n2) SELECT n.n1,n.n2 FROM nextStarTable AS n WHERE n.n1 = n.n2;";
	sqlite3_exec(dbConnection, insertnextstarrsSQL.c_str(), NULL, 0, &errorMessage);
	string insertnextstarrs2SQL = "INSERT INTO nextTable (n1,n2) SELECT n.n1,n.n2 FROM nextStarTable AS n WHERE n.n2 = n.n1 +1;";
	sqlite3_exec(dbConnection, insertnextstarrs2SQL.c_str(), NULL, 0, &errorMessage);
	string insertnextstarrs3SQL = "INSERT INTO nextTable (n1,n2) SELECT n.n1,n.n2 FROM nextStarTable AS n WHERE n.n1 = n.n2 +1;";
	sqlite3_exec(dbConnection, insertnextstarrs3SQL.c_str(), NULL, 0, &errorMessage);
}

void Database::insertnextstartable2(int s1, int s2) {
	string insertnextstarrsSQL = "INSERT INTO nextStarTable('n1','n2') VALUES ('" + to_string(s1) + "','" + to_string(s2) + "');";
	sqlite3_exec(dbConnection, insertnextstarrsSQL.c_str(), NULL, 0, &errorMessage);


	string deletenextStarSQL = "DELETE FROM nextStarTable WHERE n2 IN(SELECT stmtNumber FROM statement WHERE stmtlist > 2);";
	sqlite3_exec(dbConnection, deletenextStarSQL.c_str(), callback, 0, &errorMessage);

}

void Database::insertnextstartablecall(string s1, string s2) {

	string insertnextstarcontstmtSQL = "INSERT INTO nextStarTable('n1','n2') SELECT s.stmtNumber, s2.stmtNumber FROM statement AS s, statement AS s2 WHERE s2.stmtType ='while' AND s.stmtlist > s2.stmtlist AND s.parentlvl = s2.parentlvl;";
	sqlite3_exec(dbConnection, insertnextstarcontstmtSQL.c_str(), NULL, 0, &errorMessage);

	//string insertnextstarcontstmt2SQL = "INSERT INTO nextStarTable('n1','n2') SELECT s.stmtNumber, s2.stmtNumber FROM statement AS s, statement AS s2 WHERE s2.stmtType ='if' AND s.stmtlist > s2.stmtlist AND s.parentlvl = s2.parentlvl;";
	//sqlite3_exec(dbConnection, insertnextstarcontstmt2SQL.c_str(), NULL, 0, &errorMessage);

	string insertnextstarcallSQL = "INSERT INTO nextStarTable('n1','n2') SELECT s.stmtNumber, s2.stmtNumber FROM statement AS s, statement AS s2 WHERE s.stmtType = 'call' AND s.stmtNumber = s2.stmtNumber; ";
	sqlite3_exec(dbConnection, insertnextstarcallSQL.c_str(), NULL, 0, &errorMessage);

}

// method to insert a procedure into the database
void Database::insertProcedure(string procedureNum,string procedureName) {
	string insertProcedureSQL = "INSERT INTO procedures ('procedureNumber','procedureName') VALUES ('" + procedureNum + "','" + procedureName + "');";
	sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

//method to insert a variable into the database
void Database::insertVariable(string stmtLine,string variableName, string procedureName) {
	string insertVariableSQL = "INSERT INTO variables ('stmtLine','variableName', 'procedureName') VALUES ('" + stmtLine + "','" + variableName + "','" + procedureName + "');";
	sqlite3_exec(dbConnection, insertVariableSQL.c_str(), NULL, 0, &errorMessage);
}

//method to insert a print value into the database
void Database::insertPrint(string printNumber, string printName) {
	string insertPrintSQL = "INSERT INTO printTable ('printNumber', 'printName') VALUES ('" + printNumber + "','" + printName + "');";
	sqlite3_exec(dbConnection, insertPrintSQL.c_str(), NULL, 0, &errorMessage);
}

//method to insert a constant value into the database
void Database::insertConstant(string stmtline, string constantNumber) {
	string insertConstantSQL = "INSERT INTO constant ('stmtline', 'constantNumber') VALUES ('" + stmtline + "','" + constantNumber + "');";
	sqlite3_exec(dbConnection, insertConstantSQL.c_str(), NULL, 0, &errorMessage);
}

//method to insert a read value into the database
void Database::insertRead(string readNumber, string readName) {
	string insertReadSQL = "INSERT INTO read ('readNumber', 'readName') VALUES ('" + readNumber + "','" + readName + "' );";
	sqlite3_exec(dbConnection, insertReadSQL.c_str(), NULL, 0, &errorMessage);
}

//method to insert a assignment value into the database
void Database::insertAssignment(string assignNumber, string assignVar) {
	string insertAssignmentSQL = "INSERT INTO assignment ('assignNumber','assignVar') VALUES ('" + assignNumber + "', '" + assignVar + "');";
	sqlite3_exec(dbConnection, insertAssignmentSQL.c_str(), NULL, 0, &errorMessage);
}

//method to insert statement number and type into the db
void Database::insertStatement(string stmtNumber, string stmtType, string stmtlist, string procedureName, string parent, string parentlvl, string nestinglvl, string callName) {
	string insertStatementSQL = "INSERT INTO statement ('stmtNumber', 'stmtType', 'stmtlist', 'procedureName' , 'parent', 'parentlvl', 'nestinglvl', 'callName') VALUES ('" + stmtNumber +"', '" + stmtType + "', '" + stmtlist + "' , '" + procedureName + "','" + parent + "','" + parentlvl + "','" + nestinglvl + "' ,'" + callName + "' );";
	sqlite3_exec(dbConnection, insertStatementSQL.c_str(), NULL, 0, &errorMessage);
}

//method to insert while line number into db
void Database::insertWhile(string whileNumber) {
	string insertWhileSQL = "INSERT INTO while ('whileNumber') VALUES ('" + whileNumber + "');";
	sqlite3_exec(dbConnection, insertWhileSQL.c_str(), NULL, 0, &errorMessage);
}


//all insert functions
void Database::insertIf(string ifNumber) {
	string insertIfSQL = "INSERT INTO iftable ('ifNumber') VALUES ('" + ifNumber + "');";
	sqlite3_exec(dbConnection, insertIfSQL.c_str(), NULL, 0, &errorMessage);
}

//void Database::insertpattern(string entref) {
//	string insertpatternSQL = "INSERT INTO pattern ('entref') VALUES ('" + entref + "');";
//	sqlite3_exec(dbConnection, insertpatternSQL.c_str(), NULL, 0, &errorMessage);
//}
//
//void Database::insertpatternconstant(string entref) {
//	string insertpatternSQL = "INSERT INTO patternNumber ('entref') VALUES ('" + entref + "');";
//	sqlite3_exec(dbConnection, insertpatternSQL.c_str(), NULL, 0, &errorMessage);
//}

//void Database::insertfollowsleft(string followsNumber) {
//	string insertfollowsleftSQL = "INSERT INTO followslefttable ('followsNumber') VALUES ('" + followsNumber + "');";
//	sqlite3_exec(dbConnection, insertfollowsleftSQL.c_str(), NULL, 0, &errorMessage);
//}
//
//void Database::insertfollowsright(string lineNumber, string followsNumber, string nestinglvl) {
//	string insertfollowsrightSQL = "INSERT INTO followsrighttable ('lineNumber', 'followsNumber') VALUES ('" + lineNumber + "','" + followsNumber + "');";
//	string insertnestinglvlSQL = "INSERT INTO followsrighttable ('nestinglvl') SELECT statement.stmtlist FROM statement, followsrighttable WHERE statement.stmtNumber = followsrighttable.followsNumber;";
//	sqlite3_exec(dbConnection, insertfollowsrightSQL.c_str(), NULL, 0, &errorMessage);
//	sqlite3_exec(dbConnection, insertnestinglvlSQL.c_str(), NULL, 0, &errorMessage);
//}

//void Database::insertparentright(string lineNumber, string parentNumber, string nestinglvl) {
//	string insertparentrightSQL = "INSERT INTO parentright ('lineNumber', 'parentNumber') VALUES ('" + lineNumber + "','" + parentNumber + "');";
//	string insertnestinglvlSQL = "INSERT INTO parentright ('nestinglvl') SELECT statement.stmtlist FROM statement, parentright WHERE statement.stmtNumber = parentright.parentNumber;";
//	sqlite3_exec(dbConnection, insertparentrightSQL.c_str(), NULL, 0, &errorMessage);
//	sqlite3_exec(dbConnection, insertnestinglvlSQL.c_str(), NULL, 0, &errorMessage);
//}

//void Database::insertparentleft(string lineNumber, string parentNumber, string nestinglvl) {
//	string insertparentleftSQL = "INSERT INTO parentleft ('lineNumber', 'parentNumber') VALUES ('" + lineNumber + "','" + parentNumber + "');";
//	string insertnestinglvlSQL = "INSERT INTO parentleft ('nestinglvl') SELECT statement.stmtlist FROM statement, parentleft WHERE statement.stmtNumber = parentleft.parentNumber;";
//	sqlite3_exec(dbConnection, insertparentleftSQL.c_str(), NULL, 0, &errorMessage);
//	sqlite3_exec(dbConnection, insertnestinglvlSQL.c_str(), NULL, 0, &errorMessage);
//}

//void Database::insertuses(string lineNumber, string usesNumber) {
//	string insertusesSQL = "INSERT INTO usesNum ('lineNumber', 'usesNumber') VALUES ('" + lineNumber + "','" + usesNumber + "');";
//	sqlite3_exec(dbConnection, insertusesSQL.c_str(), NULL, 0, &errorMessage);
//}
//
//void Database::insertstringuses(string lineNumber, string name) {
//	string insertstringusesSQL = "INSERT INTO stringuses ('lineNumber', 'Name') VALUES ('" + lineNumber + "','" + name + "');";
//	sqlite3_exec(dbConnection, insertstringusesSQL.c_str(), NULL, 0, &errorMessage);
//}

void Database::insertExpr(string stmtLine, string exprName, string procedureName) {
	string insertExprSQL = "INSERT INTO expr ('stmtLine','exprName', 'procedureName') VALUES ('" + stmtLine + "','" + exprName + "','" + procedureName + "');";
	sqlite3_exec(dbConnection, insertExprSQL.c_str(), NULL, 0, &errorMessage);
}

//void Database::insertmodifyinteger(string lineNumber, string number) {
//	string insertModifyintSQL = "INSERT INTO modifyNum ('lineNumber', 'modifyNumber') VALUES ('" + lineNumber + "','" + number + "');";
//	sqlite3_exec(dbConnection, insertModifyintSQL.c_str(), NULL, 0, &errorMessage);
//}
//
//void Database::insertmodifystring(string lineNumber, string modifystring) {
//	string insertModifystringSQL = "INSERT INTO modifystring ('lineNumber', 'modifystring') VALUES ('" + lineNumber + "','" + modifystring + "');";
//	sqlite3_exec(dbConnection, insertModifystringSQL.c_str(), NULL, 0, &errorMessage);
//}

//get design entity function

void Database::getProcedures(vector<string>& results){
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getProceduresSQL = "SELECT procedureName FROM procedures;";
	sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getVariables(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getVariableSQL = "SELECT DISTINCT variableName FROM variables;";
	sqlite3_exec(dbConnection, getVariableSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of variable names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getPrint(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variables from the variable table
	// The callback method is only used when there are results to be returned.
	string getPrintSQL = "SELECT printNumber FROM printTable;";
	sqlite3_exec(dbConnection, getPrintSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of print variables
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);

	}
}

void Database::getConstant(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getConstantSQL = "SELECT constantNumber FROM constant;";
	sqlite3_exec(dbConnection, getConstantSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of constant numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getRead(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getReadSQL = "SELECT readNumber FROM read;";
	sqlite3_exec(dbConnection, getReadSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternAssign(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternSQL = "SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getpatternSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternVar(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternSQL = "SELECT DISTINCT variables.variableName FROM variables, assignment AS a WHERE a.assignVar = '" + entref + "' AND a.assignVar = variables.variableName";
	sqlite3_exec(dbConnection, getpatternSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternAssignleftfollows(vector<string>& results) {//pattern at lhs
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternSQL = "SELECT b.assignNumber FROM assignment AS a, assignment AS b, pattern, statement WHERE pattern.entref = a.assignVar AND a.assignNumber = statement.stmtNumber AND b.assignNumber > a.assignNumber LIMIT 1;";//get the stmtnumber for sum

	sqlite3_exec(dbConnection, getpatternSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletepatternSQL = "DELETE FROM pattern;";
		sqlite3_exec(dbConnection, deletepatternSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getpatternAssignrightfollows(vector<string>& results) {//pattern at rhs
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternSQL = "SELECT b.stmtline FROM expr AS a, expr AS b, pattern, statement, statement AS s WHERE pattern.entref = a.exprName AND a.stmtLine = statement.stmtNumber AND statement.stmtlist = s.stmtlist AND b.stmtLine > a.stmtLine LIMIT 1;";//get the stmtnumber for sum

	sqlite3_exec(dbConnection, getpatternSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletepatternSQL = "DELETE FROM pattern;";
		sqlite3_exec(dbConnection, deletepatternSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getpatternAssignconstantrightfollows(vector<string>& results) {//pattern at rhs
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternSQL = "SELECT b.stmtline FROM expr AS a, expr AS b, patternNumber, statement, statement AS s WHERE patternNumber.entref = a.exprName AND a.stmtLine = statement.stmtNumber AND statement.stmtlist = s.stmtlist AND b.stmtLine > a.stmtLine LIMIT 1;";//get the stmtnumber for sum

	sqlite3_exec(dbConnection, getpatternSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletepatternSQL = "DELETE FROM patternNumber;";
		sqlite3_exec(dbConnection, deletepatternSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::compareResults(vector<string>& results, vector<string>& results2) {
	// clear the existing results
	dbResults.clear();
	string temp;
	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	for (size_t i = 0; i < results.size(); i++) {
		for (size_t j = 0; j < results2.size(); j++) {
			if (results[i] == results2[j])
			{
				temp.push_back(j);
			}
		}
	}
	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(temp);
	}
}

void Database::getpatternconstant(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternconstantSQL = "SELECT DISTINCT c.stmtLine FROM constant AS c, statement WHERE c.constantNumber = '" + entref + "' AND statement.stmtType = 'assign';";
	sqlite3_exec(dbConnection, getpatternconstantSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternexpr(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs = '" + entref + "' AND statement.stmtNumber = expressiontable.stmtLine;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternexpr2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT variables.stmtLine FROM variables, statement WHERE variables.stmtLine = statement.stmtNumber) AS query1 INTERSECT SELECT * FROM(SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs LIKE '%" + entref + "%' AND statement.stmtNumber = expressiontable.stmtLine) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}


void Database::getpatternC2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT constant.stmtLine FROM constant, statement WHERE constant.stmtLine = statement.stmtNumber) AS query1 INTERSECT SELECT * FROM(SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs LIKE '%" + entref + "%' AND statement.stmtNumber = expressiontable.stmtLine) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternNext2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'assign' AND nextStarTable.n1 = statement.stmtNumber) AS query1 INTERSECT SELECT * FROM(SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs LIKE '%" + entref + "%' AND statement.stmtNumber = expressiontable.stmtLine) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternNext3(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber) AS query1 INTERSECT SELECT * FROM(SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs LIKE '%" + entref + "%' AND statement.stmtNumber = expressiontable.stmtLine) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternNext4(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs LIKE '%" + entref + "%' AND statement.stmtNumber = expressiontable.stmtLine) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternS(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT statement.stmtNumber FROM statement) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternNext(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'assign' AND nextTable.n1 = statement.stmtNumber) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternNext5(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternNext6(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternNext7(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternN2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternN3(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternN4(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternN5(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternN6(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber)) AS query1 INTERSECT SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar = '" + entref + "' AND a.assignNumber = statement.stmtNumber) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternS2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT * FROM (SELECT statement.stmtNumber FROM statement) AS query1 INTERSECT SELECT * FROM(SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs LIKE '%" + entref + "%' AND statement.stmtNumber = expressiontable.stmtLine) AS query2;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternexprvar(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();
	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT DISTINCT variables.variableName FROM expressiontable, variables WHERE expressiontable.rhs = '" + entref + "' AND variables.stmtline = expressiontable.stmtLine;";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternpartialexpr(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT expressiontable.stmtLine FROM expressiontable WHERE expressiontable.rhs LIKE '%"+ entref +"%';";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternparentleft (vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT parentTable.s1 FROM parentTable WHERE s2 IN (SELECT assignment.assignNumber FROM assignment, statement WHERE assignment.assignVar = '" + entref + "' AND assignment.assignNumber = statement.stmtNumber AND statement.parent = 'while');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternparentleft2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT parentTable.s1 FROM parentTable WHERE s2 IN (SELECT assignment.assignNumber FROM assignment, statement WHERE assignment.assignVar = '" + entref + "' AND assignment.assignNumber = statement.stmtNumber AND statement.parent = 'if');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternparentleft3(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT parentTable.s1 FROM parentTable WHERE s2 IN (SELECT assignment.assignNumber FROM assignment WHERE assignment.assignVar = '" + entref + "');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternparentright(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT parentTable.s1 FROM parentTable WHERE s2 IN (SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs = '" + entref + "' AND expressiontable.stmtLine = statement.stmtNumber AND statement.parent = 'while');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternparentright2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT parentTable.s1 FROM parentTable WHERE s2 IN (SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs = '" + entref + "' AND expressiontable.stmtLine = statement.stmtNumber AND statement.parent = 'if');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternparentright3(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT parentTable.s1 FROM parentTable WHERE s2 IN (SELECT expressiontable.stmtLine FROM expressiontable WHERE expressiontable.rhs = '" + entref + "');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getAssign(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the assign lines from the assign table
	// The callback method is only used when there are results to be returned.
	string getAssignSQL = "SELECT assignNumber FROM assignment;";
	sqlite3_exec(dbConnection, getAssignSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of assign numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getStatement(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the stmt lines from the statement table
	// The callback method is only used when there are results to be returned.
	string getStatementSQL = "SELECT stmtNumber FROM statement;";
	sqlite3_exec(dbConnection, getStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getWhile(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getWhileSQL = "SELECT * FROM while;";
	sqlite3_exec(dbConnection, getWhileSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getIf(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getIfSQL = "SELECT * FROM iftable;";
	sqlite3_exec(dbConnection, getIfSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcall(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallstmtSQL = "SELECT stmtNumber FROM statement WHERE stmtType = 'call;";
	sqlite3_exec(dbConnection, getcallstmtSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

//all follows relations

void Database::getfollowsright(vector<string>& results, string stmtnumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	
	string getfollowsrightStatementSQL = "SELECT s2 FROM followstable WHERE s1 = '" + stmtnumber + "';";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarright(vector<string>& results, string stmtnumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT s2 FROM followstartable WHERE s1 = '" + stmtnumber + "';";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsright2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstable AS f ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarright2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsright3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstable AS f ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarright3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT f.s2 FROM followstartable AS f ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsTright(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsTrightStatementSQL = "SELECT a.stmtNumber FROM statement AS a, followslefttable, statement AS b WHERE b.stmtNumber = followslefttable.followsNumber \
AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist AND a.procedureName = b.procedureName ORDER BY a.stmtNumber ASC;";
	sqlite3_exec(dbConnection, getfollowsTrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletefollowsTleftSQL = "DELETE FROM followslefttable;";
		sqlite3_exec(dbConnection, deletefollowsTleftSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getfollowsleft(vector<string>& results, string stmtnumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT s1 FROM followstable WHERE s2 = '" + stmtnumber + "';";
		//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleft(vector<string>& results, string stmtnumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT s1 FROM followstartable WHERE s2 = '" + stmtnumber + "';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleft2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s1 FROM followstable AS f ORDER BY f.s1 ASC;";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleft2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f ORDER BY f.s1 ASC;";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleft3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftprint(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'print' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleftprint(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'print' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftread(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'read' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsrightread(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'read' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleftread(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'read' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightread(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'read' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsrightprint(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'print' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightprint(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'print' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftcall(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'call' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}


void Database::getfollowsStarleftcall(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'call' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightcall(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'call' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsrightcall(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'call' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftassign(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'assign' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsrightassign(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'assign' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleftassign(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE s.stmtNumber = f.s1 AND s.stmtType = 'assign' ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightassign(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'assign' ORDER BY f.s2 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftstmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s1 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'read';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleftstmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'read';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleftstmt2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'print';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleftstmt3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'call';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleftstmt4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'assign';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftstmt2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s1 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'print';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftstmt3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s1 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'call';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsleftstmt4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s1 FROM followstable AS f, statement AS s WHERE f.s2 = s.stmtNumber AND s.stmtType = 'assign';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}


void Database::getfollowsrightstmt4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s2 FROM followstable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'assign';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsrightstmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s2 FROM followstable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'read';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightstmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'read';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightstmt2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'print';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightstmt3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'call';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarrightstmt4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT DISTINCT f.s2 FROM followstartable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'assign';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsrightstmt2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s2 FROM followstable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'print';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsrightstmt3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getfollowsleftStatementSQL = "SELECT f.s2 FROM followstable AS f, statement AS s WHERE f.s1 = s.stmtNumber AND s.stmtType = 'print';";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getfollowsleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsStarleft3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsrightStatementSQL = "SELECT DISTINCT f.s1 FROM followstartable AS f ORDER BY f.s1 ASC;";
	//SELECT a.stmtNumber FROM statement AS a, statement AS b, followslefttable WHERE b.stmtNumber = followslefttable.followsNumber AND a.stmtNumber > b.stmtNumber AND a.stmtlist = b.stmtlist LIMIT 1;
	sqlite3_exec(dbConnection, getfollowsrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getfollowsTleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getfollowsTleftStatementSQL = "SELECT a.stmtNumber FROM statement AS a, followsrighttable, statement AS b WHERE b.stmtNumber = followsrighttable.followsNumber \
	AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist AND a.procedureName = b.procedureName ORDER BY a.stmtNumber ASC;";
	sqlite3_exec(dbConnection, getfollowsTleftStatementSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletefollowsTrightSQL = "DELETE FROM followsrighttable;";
		sqlite3_exec(dbConnection, deletefollowsTrightSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::gets1stmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string gets1SQL = "SELECT DISTINCT s1 FROM followstable ORDER BY s1 ASC;";
	sqlite3_exec(dbConnection, gets1SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::gets2Nextstarstmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string gets1SQL = "SELECT DISTINCT n2 FROM nextStartable ORDER BY n2 ASC;";
	sqlite3_exec(dbConnection, gets1SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::gets1Nextstarstmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string gets1SQL = "SELECT DISTINCT n1 FROM nextStartable ORDER BY n1 ASC;";
	sqlite3_exec(dbConnection, gets1SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::gets1stmtStar(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string gets1SQL = "SELECT DISTINCT s1 FROM followstartable ORDER BY s1 ASC;";
	sqlite3_exec(dbConnection, gets1SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::gets2stmt(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string gets1SQL = "SELECT DISTINCT s2 FROM followstable ORDER BY s2 ASC;";
	sqlite3_exec(dbConnection, gets1SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::gets2stmtStar(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string gets1SQL = "SELECT DISTINCT s2 FROM followstartable ORDER BY s2 ASC;";
	sqlite3_exec(dbConnection, gets1SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternfollowsleft(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT followsTable.s2 FROM followsTable WHERE s1 IN (SELECT assignment.assignNumber FROM assignment, statement WHERE assignment.assignVar = '" + entref + "' AND statement.stmtNumber = assignment.assignNumber AND statement.stmtType = 'assign' );";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternfollowsStarleft(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT followstarTable.s2 FROM followstarTable WHERE s1 IN (SELECT assignment.assignNumber FROM assignment, statement WHERE assignment.assignVar = '" + entref + "' AND statement.stmtNumber = assignment.assignNumber AND statement.stmtType = 'assign' );";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternfollowsright(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT followsTable.s2 FROM followsTable WHERE s1 IN (SELECT \
expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs = '" + entref + "' AND statement.stmtNumber = expressiontable.stmtLine AND  statement.stmtType = 'assign');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpartialpatternfollowsright(vector<string>& results, string entref) {//partial pattern
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT followsTable.s2 FROM followsTable WHERE s1 IN (SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs LIKE '%" + entref + "%' AND statement.stmtNumber = expressiontable.stmtLine AND  statement.stmtType = 'assign');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}


void Database::getpatternfollowsStarright(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// retrieve the variabels from the variable table
	// The callback method is only used when there are results to be returned.
	string getpatternrhsSQL = "SELECT followstarTable.s2 FROM followstarTable WHERE s1 IN (SELECT expressiontable.stmtLine FROM expressiontable, statement WHERE expressiontable.rhs = '" + entref + "' AND statement.stmtNumber = expressiontable.stmtLine AND  statement.stmtType = 'assign');";
	sqlite3_exec(dbConnection, getpatternrhsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of read
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

//to insert into parent table



void Database::getNestinglvl(vector<string>& results, int statementNo) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getnestinglvlSQL = "SELECT stmtlist FROM statement WHERE stmtNumber = '" + to_string(statementNo) + "' ;";
	sqlite3_exec(dbConnection, getnestinglvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getProcedure(vector<string>& results, int statementNo) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getnestinglvlSQL = "SELECT procedureName FROM statement WHERE stmtNumber = '" + to_string(statementNo) + "' ;";
	sqlite3_exec(dbConnection, getnestinglvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getid(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getnestinglvlSQL = "SELECT ID FROM callsTable;";
	sqlite3_exec(dbConnection, getnestinglvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getp(vector<string>& results, int statementNo) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getnestinglvlSQL = "SELECT p FROM callsTable WHERE ID = '" + to_string(statementNo) + "' ;";
	sqlite3_exec(dbConnection, getnestinglvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getq(vector<string>& results, int statementNo) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getnestinglvlSQL = "SELECT q FROM callsTable WHERE ID = '" + to_string(statementNo) + "' ;";
	sqlite3_exec(dbConnection, getnestinglvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::insertpq(int stmti, int stmtj) {
	string insertrsSQL = "INSERT INTO callsStarTable ('p','q') VALUES ((SELECT p FROM callsTable WHERE ID = '" + to_string(stmti) + "'), (SELECT q FROM callsTable WHERE ID = '" + to_string(stmtj) + "'));";
	sqlite3_exec(dbConnection, insertrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::getparentNestinglvl(vector<string>& results, int statementNo) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getnestinglvlSQL = "SELECT nestinglvl FROM statement WHERE stmtNumber = '" + to_string(statementNo) + "';";
	sqlite3_exec(dbConnection, getnestinglvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getParentLvl(vector<string>& results, int statementNo) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getparentlvlSQL = "SELECT parentlvl FROM statement WHERE stmtNumber = '" + to_string(statementNo) + "';";
	sqlite3_exec(dbConnection, getparentlvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getID(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getparentlvlSQL = "SELECT ID FROM callsTable;";
	sqlite3_exec(dbConnection, getparentlvlSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

//all parent relations
void Database::getparentStatement(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentleftStatementSQL = "SELECT stmtNumber FROM statement WHERE statement.parentlvl <> 0;";
	sqlite3_exec(dbConnection, getparentleftStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentleft(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentleftStatementSQL = "SELECT parentTable.s1 FROM parentTable WHERE parentTable.s2 = '" + stmtNumber + "';";
		//"SELECT a.stmtNumber FROM statement AS a, statement AS b, parentright WHERE b.stmtNumber = parentright.parentNumber AND a.stmtNumber < parentright.parentNumber AND a.stmtlist = 1 AND b.parent = a.parent ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getparentleftStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentTleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentTleftStatementSQL = "SELECT s.stmtNumber FROM statement AS s, statement AS b, parentright AS r WHERE s.stmtNumber < r.parentNumber \
		AND b.stmtNumber = r.parentNumber AND s.parent = b.parent ORDER BY s.stmtNumber ASC LIMIT 1;";
	sqlite3_exec(dbConnection, getparentTleftStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteparentTleftSQL = "DELETE FROM parentright;";
		sqlite3_exec(dbConnection, deleteparentTleftSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getparentright(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT a.stmtNumber FROM statement AS a, statement AS b, parentleft WHERE b.stmtNumber = parentleft.parentNumber \
		AND a.stmtNumber > parentleft.parentNumber AND a.stmtlist > b.stmtlist AND b.parent = a.parent ORDER BY a.stmtNumber ASC;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteparentrightSQL = "DELETE FROM parentleft;";
		sqlite3_exec(dbConnection, deleteparentrightSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getparenttableright(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();
	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s2 FROM parentTable WHERE parentTable.s1 = '" + stmtNumber + "' ORDER BY s2 ASC;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableright(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();
	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT s2 FROM parentStarTable WHERE s1 = '" + stmtNumber + "' ORDER BY s2 ASC;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableright2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s2 FROM parentTable;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableright2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentstarTable.s2 FROM parentstarTable;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableright3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s2 FROM parentTable, while, statement WHERE parentTable.s1 = while.whileNumber AND statement.stmtType = 'assign' AND statement.stmtNumber = parentTable.s2;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableright3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentStarTable.s2 FROM parentStarTable, while, statement WHERE parentStarTable.s1 = while.whileNumber AND statement.stmtType = 'assign' AND statement.stmtNumber = parentStarTable.s2;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableright4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s2 FROM parentTable, iftable, statement WHERE parentTable.s1 = iftable.ifNumber AND statement.stmtType = 'assign' AND statement.stmtNumber = parentTable.s2;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableright4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentStarTable.s2 FROM parentStarTable, iftable, statement WHERE parentStarTable.s1 = iftable.ifNumber AND statement.stmtType = 'assign' AND statement.stmtNumber = parentStarTable.s2;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableright5(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT s2 FROM parentTable, statement WHERE parentTable.s2 =statement.stmtNumber AND statement.stmtType ='assign';";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableright5(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentstarTable.s2 FROM parentstarTable, statement WHERE parentstarTable.s2 =statement.stmtNumber AND statement.stmtType ='assign';";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableleft(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentstarTable.s1 FROM parentstarTable WHERE parentstarTable.s2 = '" + stmtNumber + "' ORDER BY s1 ASC LIMIT 1;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableleft2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s1 FROM parentTable;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableleft2(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentstarTable.s1 FROM parentstarTable;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableleft3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s1 FROM parentTable, while WHERE while.whileNumber = parentTable.s1;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableleft3(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentStarTable.s1 FROM parentStarTable, while WHERE while.whileNumber = parentStarTable.s1;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableleft4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s1 FROM parentTable, iftable WHERE iftable.ifNumber = parentTable.s1;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableleft4(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentstarTable.s1 FROM parentStarTable, iftable WHERE iftable.ifNumber = parentStarTable.s1;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableleft5(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT s1 FROM parentTable;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableleft5(vector<string>& results) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT s1 FROM parentstarTable;";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableleft6(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s1 FROM parentTable, statement WHERE parentTable.s2 = '" + stmtNumber + "' AND statement.stmtNumber = parentTable.s2 AND statement.parent = 'if';";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableleft6(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentstarTable.s1 FROM parentstarTable, statement WHERE parentstarTable.s2 = '" + stmtNumber + "' AND statement.stmtNumber = parentstarTable.s2 AND statement.parent = 'if';";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparenttableleft7(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentTable.s1 FROM parentTable, statement WHERE parentTable.s2 = '" + stmtNumber + "' AND statement.stmtNumber = parentTable.s2 AND statement.parent = 'while';";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentStartableleft7(vector<string>& results, string stmtNumber) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentrightStatementSQL = "SELECT DISTINCT parentstarTable.s1 FROM parentstarTable, statement WHERE parentstarTable.s2 = '" + stmtNumber + "' AND statement.stmtNumber = parentstarTable.s2 AND statement.parent = 'while';";
	sqlite3_exec(dbConnection, getparentrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getparentTright(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getparentTrightStatementSQL = "SELECT s.stmtNumber FROM statement AS s, statement AS b, parentleft AS l WHERE s.stmtNumber > l.parentNumber AND b.stmtNumber = l.parentNumber AND s.parent = b.parent ORDER BY s.stmtNumber ASC;";
	sqlite3_exec(dbConnection, getparentTrightStatementSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteparentTrightSQL = "DELETE FROM parentleft;";
		sqlite3_exec(dbConnection, deleteparentTrightSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getparentwhilepatternleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getWhileSQL = "SELECT s.stmtNumber FROM assignment AS a, statement AS s, statement AS b, while AS w, \
		stringuses AS su WHERE a.assignVar = su.Name AND b.stmtNumber = a.assignNumber and s.stmtType = b.parent AND s.stmtNumber = w.whileNumber;";
	sqlite3_exec(dbConnection, getWhileSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletePUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deletePUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getparentwhilepatternright(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getWhileSQL = "SELECT s.stmtNumber FROM expr AS e, statement AS s, statement AS b, while AS w, stringuses AS su WHERE e.exprName = su.Name AND b.stmtNumber = e.stmtLine and s.stmtType = b.parent AND s.stmtNumber = w.whileNumber;";
	sqlite3_exec(dbConnection, getWhileSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletePUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deletePUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getparentifpatternleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getifpatternSQL = "SELECT s.stmtNumber FROM assignment AS a, statement AS s, statement AS b, iftable as i, \
		stringuses AS su WHERE a.assignVar = su.Name AND b.stmtNumber = a.assignNumber and s.stmtType = b.parent AND s.stmtNumber = i.ifNumber;";
	sqlite3_exec(dbConnection, getifpatternSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletePifUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deletePifUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getparentifpatternright(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getifpatternSQL = "SELECT s.stmtNumber FROM expr AS e, statement AS s, statement AS b, iftable as i, \
		stringuses AS su WHERE e.exprName = su.Name AND b.stmtNumber = e.stmtLine and s.stmtType = b.parent AND s.stmtNumber = i.ifNumber;";
	sqlite3_exec(dbConnection, getifpatternSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletePifUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deletePifUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getpatternParent(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT * FROM(SELECT e.stmtline FROM expressiontable AS e WHERE e.rhs LIKE '%" + entref + "%') AS query2 INTERSECT SELECT * FROM (SELECT DISTINCT parentstarTable.s2 FROM parentstarTable, statement WHERE parentstarTable.s2 =statement.stmtNumber AND statement.stmtType ='assign') AS query1;";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

//all uses relations

void Database::getUses(vector<string>& results) {
	// clear the existing results
	dbResults.clear();
	string getExprSQL;
	string getVariablesSQL;
	// The callback method is only used when there are results to be returned.
	string getUsesSQL;
	string statementtype = "SELECT DISTINCT statement.stmtType FROM statement, uses \
		WHERE usesNum.usesNumber = statement.stmtNumber;";
		
	if (statementtype == "assign") {
		getVariablesSQL = "SELECT variables.variableName FROM variables, uses WHERE usesNum.usesNumber = variables.stmtLine;";
		sqlite3_exec(dbConnection, getVariablesSQL.c_str(), callback, 0, &errorMessage);
	}
	else {
		getExprSQL = "SELECT expr.exprName FROM expr, usesNum WHERE usesNum.usesNumber = expr.stmtLine;";
		sqlite3_exec(dbConnection, getExprSQL.c_str(), callback, 0, &errorMessage);
	}

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
	string deleteUsesSQL = "DELETE FROM usesNum;";
	sqlite3_exec(dbConnection, deleteUsesSQL.c_str(), callback, 0, &errorMessage);
}

void Database::getprocedureUses(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprocedureUsesSQL = "SELECT procedureName FROM variables AS v, stringuses AS pu \
		WHERE pu.Name = v.variableName;";
	sqlite3_exec(dbConnection, getprocedureUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletePUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deletePUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getstmtUses(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getstmtUsesSQL = "SELECT s.stmtNumber FROM statement AS s, variables AS v, stringuses, expr AS e \
		WHERE e.exprName = v.variableName AND e.stmtline = v.stmtline AND s.stmtNumber = e.stmtline AND v.variableName = stringuses.Name;";
	sqlite3_exec(dbConnection, getstmtUsesSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletestmtUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deletestmtUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getprintUses(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT printTable.printNumber FROM printTable, stringuses WHERE stringuses.Name = printTable.printName;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteprintUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deleteprintUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getprintUses2(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'print' AND usesTable.var = '" + entity + "';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprintUses3(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'print';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprintUses4(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT usesTable.var FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'print';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprintUses5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT usesTable.var FROM usesTable;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getentityUses(vector<string>& results, string variable) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT usesTable.var FROM usesTable WHERE usesTable.entity = '" + variable + "';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getassignUses(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT assignNumber FROM assignment, stringuses WHERE assignNumber IN (SELECT stmtLine FROM expr WHERE exprName= stringuses.Name);";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteprintUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deleteprintUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getassignUses1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT DISTINCT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'assign';";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getassignUses2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT DISTINCT usesTable.var FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'assign';";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getassignUses3(vector<string>& results, string variable) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'assign' AND usesTable.var = '" + variable + "';";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getassignUses5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT usesTable.var FROM usesTable;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses6(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'while';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'if';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcUsesSQL = "SELECT DISTINCT var FROM usesTable WHERE entity IN(SELECT stmtNumber FROM statement WHERE parent = 'if');";
	sqlite3_exec(dbConnection, getcUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses3(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT var FROM usesTable;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses4(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.parent <> 0 AND usesTable.var = '" + entity + "' ORDER BY stmtNumber ASC;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses7(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT var FROM usesTable WHERE entity IN(SELECT stmtNumber FROM statement WHERE parent = 'while');";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses8(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT var FROM usesTable;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses9(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
		string getcontUsesSQL = "SELECT DISTINCT entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.parent<> 0 ORDER BY stmtNumber ASC;";
		sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtUses10(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT var FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.parent<> 0;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getUsespatternvariable(vector<string>& results)
{
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignpatternUsesSQL = "SELECT a.assignNumber FROM statement AS s, statement AS b, assignment AS a, expr, stringuses WHERE a.assignVar = stringuses.Name AND s.stmtNumber = a.assignNumber\
AND expr.exprName = stringuses.Name AND b.stmtNumber = expr.stmtLine AND s.stmtNumber = b.stmtNumber;";
	sqlite3_exec(dbConnection, getassignpatternUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletestringUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deletestringUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getassignUsespatternvariableright(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getpatternUsesSQL = "SELECT expr.stmtLine FROM statement AS s, statement AS b, assignment AS a, expr, stringuses WHERE a.assignVar = stringuses.Name AND s.stmtNumber = a.assignNumber\
AND expr.exprName = stringuses.Name AND b.stmtNumber = expr.stmtLine AND s.stmtNumber = b.stmtNumber;";
	sqlite3_exec(dbConnection, getpatternUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteUsesSQL = "DELETE FROM stringuses;";
		sqlite3_exec(dbConnection, deleteUsesSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getpatternUsesleft2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT usesTable.entity FROM usesTable, assignment, statement WHERE assignment.assignVar = usesTable.var AND statement.stmtNumber = usesTable.entity AND statement.stmtType = 'assign' AND statement.stmtNumber = assignment.assignNumber;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternUsesleft(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT usesTable.entity FROM usesTable, assignment, statement WHERE assignment.assignVar = '" + entref + "' AND usesTable.var = '" + entref + "' AND statement.stmtNumber = usesTable.entity AND statement.stmtType = '" + entref + "' AND statement.stmtNumber = assignment.assignNumber;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::insertUsesproc(string s1, string s2) {
	string insertprocrsSQL = "INSERT INTO usesTable(entity, var) SELECT callsTable.p, usesTable.var FROM callsTable, usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.procedureName = callsTable.q;";
	sqlite3_exec(dbConnection, insertprocrsSQL.c_str(), NULL, 0, &errorMessage);

	string insertcallprocrsSQL = "INSERT INTO usesTable(entity, var) SELECT callsTable.q, usesTable.var FROM callsTable, usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'call' AND statement.procedureName = callsTable.p;";
	sqlite3_exec(dbConnection, insertcallprocrsSQL.c_str(), NULL, 0, &errorMessage);
}

void Database::getprocuses1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT usesTable.entity FROM usesTable, procedures WHERE procedures.procedureName = usesTable.entity;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprocUses2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getUsesSQL = "SELECT DISTINCT usesTable.var FROM usesTable, procedures WHERE procedures.procedureName = usesTable.entity;";
	sqlite3_exec(dbConnection, getUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprocUses4(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getstmtusesSQL = "SELECT DISTINCT usesTable.entity FROM usesTable, procedures WHERE usesTable.var = '" + entity + "' AND usesTable.entity = procedures.procedureName;";
	sqlite3_exec(dbConnection, getstmtusesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcalluses2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT usesTable.var FROM usesTable, procedures WHERE procedures.procedureName = usesTable.entity;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcallUses1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT DISTINCT statement.stmtNumber FROM statement,usesTable, procedures WHERE usesTable.entity = statement.callName AND procedures.procedureName = usesTable.entity;";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	string getcall2SQL = "SELECT DISTINCT statement.stmtNumber FROM statement,usesTable, procedures WHERE usesTable.entity = statement.procedureName AND statement.stmtType = 'call' AND procedures.procedureName = usesTable.entity;";
	sqlite3_exec(dbConnection, getcall2SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcallUses4(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getstmtSQL = "SELECT DISTINCT statement.stmtNumber FROM usesTable , procedures, statement WHERE usesTable.var = '" + entity + "' AND usesTable.entity = procedures.procedureName AND usesTable.entity = statement.callName;";
	sqlite3_exec(dbConnection, getstmtSQL.c_str(), callback, 0, &errorMessage);

	string getstmt2SQL = "SELECT DISTINCT statement.stmtNumber FROM usesTable , procedures, statement WHERE usesTable.var = '" + entity + "' AND usesTable.entity = procedures.procedureName AND usesTable.entity = statement.procedureName and statement.stmtType = 'call';";
	sqlite3_exec(dbConnection, getstmt2SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternUses(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT * FROM(SELECT e.stmtline FROM expressiontable AS e WHERE e.rhs LIKE '%" + entref + "%') AS query2 EXCEPT SELECT * FROM (SELECT usesTable.entity FROM usesTable, statement WHERE usesTable.entity = statement.stmtNumber AND statement.stmtType = 'assign') AS query1;";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

//modify relations

void Database::getpatternModifiesleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT modifyTable.entity FROM modifyTable, expr, statement WHERE expr.exprName = modifyTable.var AND statement.stmtNumber = modifyTable.entity AND statement.stmtType = 'assign' AND statement.stmtNumber = expr.stmtLine;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternModifiesleft2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT modifyTable.entity FROM modifyTable, expr, statement WHERE expr.exprName = '" + entref + "' AND modifyTable.var = '" + entref + "' AND statement.stmtNumber = modifyTable.entity AND statement.stmtType = 'assign' AND statement.stmtNumber = expr.stmtline;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getModifyVar(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string modifyVarSQL = "SELECT v.variableName FROM assignment AS a, modifyNum AS m , variables AS v WHERE a.assignNumber = m.ModifyNumber AND v.stmtLine = m.ModifyNumber AND a.assignNumber = v.stmtLine;";
	
	sqlite3_exec(dbConnection, modifyVarSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletemodifynumSQL = "DELETE FROM modifyNum;";
		sqlite3_exec(dbConnection, deletemodifynumSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getModifyAssign(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string modifyAssignSQL = "SELECT a.assignNumber FROM assignment AS a, modifystring AS m , expr AS e WHERE a.assignVar = m.modifystring AND a.assignVar = e.exprName AND e.exprName = m.modifystring AND a.assignNumber = e.stmtLine;";

	sqlite3_exec(dbConnection, modifyAssignSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletemodifystringSQL = "DELETE FROM modifystring;";
		sqlite3_exec(dbConnection, deletemodifystringSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getassignModifiespatternvariableleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getpatternModifySQL = "SELECT a.assignNumber FROM statement AS s, statement AS b, assignment AS a, expr, modifystring WHERE a.assignVar = modifystring.modifystring AND s.stmtNumber = a.assignNumber AND expr.exprName = modifystring.modifystring AND b.stmtNumber = expr.stmtLine AND s.stmtNumber = b.stmtNumber;";
	sqlite3_exec(dbConnection, getpatternModifySQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteMpatternSQL = "DELETE FROM modifystring;";
		sqlite3_exec(dbConnection, deleteMpatternSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getassignModifiespatternvariableright(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getpatternModifySQL = "SELECT expr.stmtLine FROM statement AS s, statement AS b, assignment AS a, expr, modifystring WHERE a.assignVar = modifystring.modifystring AND s.stmtNumber = a.assignNumber AND expr.exprName = modifystring.modifystring AND b.stmtNumber = expr.stmtLine AND s.stmtNumber = b.stmtNumber;";
	sqlite3_exec(dbConnection, getpatternModifySQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deleteMpatternSQL = "DELETE FROM modifystring;";
		sqlite3_exec(dbConnection, deleteMpatternSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getModifyRead(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string modifyReadSQL = "SELECT read.readNumber FROM read, modifystring AS m , expr AS e, variables AS v WHERE read.readName = m.modifystring AND v.variableName = m.modifystring AND e.exprName = m.modifystring LIMIT 1;";

	sqlite3_exec(dbConnection, modifyReadSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletemodifystringSQL = "DELETE FROM modifystring;";
		sqlite3_exec(dbConnection, deletemodifystringSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getModifyprocedure(vector<string>& results) {//for 3rd iteration
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string modifyProcedureSQL = "SELECT s.procedureName FROM statement AS s, modifystring AS ms, read AS r, variables AS v WHERE ms.modifystring = r.readName AND v.variableName = ms.modifystring AND v.stmtLine = s.stmtNumber AND r.readNumber = s.stmtNumber;";

	sqlite3_exec(dbConnection, modifyProcedureSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletemodifystringSQL = "DELETE FROM modifystring;";
		sqlite3_exec(dbConnection, deletemodifystringSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getModifystmt(vector<string>& results) {//for 3rd iteration
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string modifystmtSQL = "SELECT s.stmtNumber FROM statement AS s, assignment AS a, modifystring AS ms, expr AS e \
		WHERE ms.modifystring = a.assignVar AND ms.modifystring = e.exprName AND e.stmtLine = a.assignNumber AND s.stmtNumber = e.stmtline;";

	sqlite3_exec(dbConnection, modifystmtSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
		string deletemodifystringSQL = "DELETE FROM modifystring;";
		sqlite3_exec(dbConnection, deletemodifystringSQL.c_str(), callback, 0, &errorMessage);
	}
}

void Database::getassignModifies1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignSQL = "SELECT DISTINCT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'assign';";
	sqlite3_exec(dbConnection, getassignSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getassignModifies3(vector<string>& results, string variable) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignSQL = "SELECT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'assign' AND modifyTable.var = '" + variable + "';";
	sqlite3_exec(dbConnection, getassignSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getassignModifies2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT DISTINCT modifyTable.var FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'assign';";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternM(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT * FROM(SELECT a.assignNumber FROM assignment AS a, statement WHERE a.assignVar LIKE '%" + entref + "%' AND a.assignNumber = statement.stmtNumber) AS query2 INTERSECT SELECT * FROM (SELECT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'assign') AS query1;";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	string getfinalMSQL = "SELECT variableName FROM variables WHERE variables.stmtLine = '" + getassignUsesSQL + "';";
	sqlite3_exec(dbConnection, getfinalMSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpatternM2(vector<string>& results, string entref) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getassignUsesSQL = "SELECT * FROM(SELECT e.stmtline FROM expressiontable AS e WHERE e.rhs LIKE '%" + entref + "%') AS query2 INTERSECT SELECT * FROM (SELECT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'assign') AS query1;";
	sqlite3_exec(dbConnection, getassignUsesSQL.c_str(), callback, 0, &errorMessage);

	string getfinalMSQL = "SELECT variableName FROM variables WHERE variables.stmtLine = '" + getassignUsesSQL + "';";
	sqlite3_exec(dbConnection, getfinalMSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}


void Database::getassignModifies5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT modifyTable.var FROM modifyTable;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getreadModifies2(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'read' AND modifyTable.var = '" + entity + "';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getreadModifies1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'read';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getreadModifies4(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT modifyTable.var FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'read';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getentityModifies(vector<string>& results, string variable) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT modifyTable.var FROM modifyTable WHERE modifyTable.entity = '" + variable + "';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getreadModifies5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT modifyTable.var FROM modifyTable;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies6(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'while';";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies7(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT var FROM modifyTable WHERE entity IN(SELECT stmtNumber FROM statement WHERE parent = 'while');";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies8(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT var FROM modifyTable;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies9(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.parent<> 0 ORDER BY stmtNumber ASC;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies10(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcontUsesSQL = "SELECT DISTINCT var FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.parent<> 0;";
	sqlite3_exec(dbConnection, getcontUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies4(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getstmtmodifySQL = "SELECT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.parent < > 0 AND modifyTable.var = '" + entity + "' ORDER BY stmtNumber ASC;";
	sqlite3_exec(dbConnection, getstmtmodifySQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getMSQL = "SELECT DISTINCT modifyTable.entity FROM modifyTable, statement WHERE modifyTable.entity = statement.stmtNumber AND statement.stmtType = 'if';";
	sqlite3_exec(dbConnection, getMSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcontstmtModifies2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getMsSQL = "SELECT DISTINCT var FROM modifyTable WHERE entity IN(SELECT stmtNumber FROM statement WHERE parent = 'if');";
	sqlite3_exec(dbConnection, getMsSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprocModifies1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT modifyTable.entity FROM modifyTable, procedures WHERE procedures.procedureName = modifyTable.entity;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcallModifies1(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.

	string getcall2SQL = "SELECT DISTINCT statement.stmtNumber FROM statement,modifyTable, procedures WHERE modifyTable.entity = statement.procedureName AND statement.stmtType = 'call' AND procedures.procedureName = modifyTable.entity;";
	sqlite3_exec(dbConnection, getcall2SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprocModifies2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getprintUsesSQL = "SELECT DISTINCT modifyTable.var FROM modifyTable, procedures WHERE procedures.procedureName = modifyTable.entity;";
	sqlite3_exec(dbConnection, getprintUsesSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getprocModifies4(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getstmtmodifySQL = "SELECT DISTINCT modifyTable.entity FROM modifyTable , procedures WHERE modifyTable.var = '" + entity + "' AND modifyTable.entity = procedures.procedureName;";
	sqlite3_exec(dbConnection, getstmtmodifySQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcallModifies4(vector<string>& results, string entity) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getstmtmodifySQL = "SELECT DISTINCT statement.stmtNumber FROM modifyTable , procedures, statement WHERE modifyTable.var = '" + entity + "' AND modifyTable.entity = procedures.procedureName AND modifyTable.entity = statement.callName;";
	sqlite3_exec(dbConnection, getstmtmodifySQL.c_str(), callback, 0, &errorMessage);

	string getstmtmodify2SQL = "SELECT DISTINCT statement.stmtNumber FROM modifyTable , procedures, statement WHERE modifyTable.var = '" + entity + "' AND modifyTable.entity = procedures.procedureName AND modifyTable.entity = statement.procedureName and statement.stmtType = 'call';";
	sqlite3_exec(dbConnection, getstmtmodify2SQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

//calls relations

void Database::getcalls(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT DISTINCT p FROM callsTable;";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcalls2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT DISTINCT q FROM callsTable;";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcalls3(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT p,q FROM callsTable;";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcalls4(vector<string>& results, string proc) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT p FROM callsTable WHERE q = '" + proc + "';";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcalls5(vector<string>& results, string proc) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT q FROM callsTable WHERE q = '" + proc + "';";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}
//calls*relation


void Database::getcallsstar(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT DISTINCT p FROM callsStarTable;";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcallsstar2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT DISTINCT q FROM callsStarTable;";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcallsstar4(vector<string>& results, string proc) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT DISTINCT p FROM callsStarTable WHERE q = '" + proc + "';";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getcallsstar5(vector<string>& results, string proc) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getcallSQL = "SELECT DISTINCT q FROM callsStarTable WHERE q = '" + proc + "';";
	sqlite3_exec(dbConnection, getcallSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

//next* relation
void Database::getNextstar(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n1 FROM nextStarTable ORDER BY n1 ASC;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNext(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n1 FROM nextTable ORDER BY n1 ASC;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstar2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n2 FROM nextStarTable ORDER BY n2 ASC;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNext2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n2 FROM nextTable ORDER BY n2 ASC;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'read' AND nextStarTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'read' AND nextTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleftR(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'read' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleftR(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'read' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleftP(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'print' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleftP(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'print' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleftC(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'call' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleftC(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'call' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleftW(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'while' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleftW(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'while' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleftI(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'if' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleftI(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'if' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleftA(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'assign' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleftA(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'assign' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable, statement WHERE statement.stmtType = 'read' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable, statement WHERE statement.stmtType = 'read' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRightR(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRightR(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND nextTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRightP(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRightP(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND nextTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRightC(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRightC(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND nextTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRightW(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRightW(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND nextTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRightI(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRightI(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND nextTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRightA(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRightA(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'print' AND nextStarTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'print' AND nextTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft2R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft2R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft2P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft2P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft2C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft2C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft2W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft2W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft2I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft2I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft2A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft2A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'read' AND a.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable, statement WHERE statement.stmtType = 'print' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight2(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable, statement WHERE statement.stmtType = 'print' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight2R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight2R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight2P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight2P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight2C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight2C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight2W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight2W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight2I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight2I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight2A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight2A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'read' AND b.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft3(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'call' AND nextStarTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft3(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'call' AND nextTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft3R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft3R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft3P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft3P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft3C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft3C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft3W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft3W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft3I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft3I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft3A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft3A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'print' AND a.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight3(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable, statement WHERE statement.stmtType = 'call' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight3(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable, statement WHERE statement.stmtType = 'call' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight3R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight3R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight3P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight3P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight3C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight3C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight3W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight3W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight3I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight3I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight3A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight3A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'print' AND b.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft4(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'assign' AND nextStarTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft4(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'assign' AND nextTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft4R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft4R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft4P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft4P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft4C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft4C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft4W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft4W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft4I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft4I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'assign' AND a.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft4A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft4A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight4(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable, statement WHERE statement.stmtType = 'assign' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight4(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable, statement WHERE statement.stmtType = 'assign' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight4R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight4R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight4P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight4P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight4C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight4C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight4W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight4W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight4I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight4I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'assign' AND b.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight4A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight4A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'while' AND nextStarTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'while' AND nextTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft5R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft5R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft5P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft5P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft5C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft5C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft5W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft5W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft5I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft5I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft5A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft5A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'call' AND a.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable, statement WHERE statement.stmtType = 'while' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight5(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable, statement WHERE statement.stmtType = 'while' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight5R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight5R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight5P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight5P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight5C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight5C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight5W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight5W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight5I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight5I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight5A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight5A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'call' AND b.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft6(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable, statement WHERE statement.stmtType = 'if' AND nextStarTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft6(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable, statement WHERE statement.stmtType = 'if' AND nextTable.n2 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft6R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft6R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft6P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft6P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft6C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft6C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft6W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft6W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'if' AND a.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft6I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft6I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft6A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n1 FROM nextStarTable WHERE nextStarTable.n1 IN(SELECT nextStarTable.n1 FROM nextStarTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft6A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n1 FROM nextTable WHERE nextTable.n1 IN(SELECT nextTable.n1 FROM nextTable, statement AS a, statement AS b WHERE b.stmtType = 'while' AND a.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight6(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable, statement WHERE statement.stmtType = 'if' AND nextStarTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight6(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable, statement WHERE statement.stmtType = 'if' AND nextTable.n1 = statement.stmtNumber;";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight6R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'read' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight6R(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'read' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight6P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'print' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight6P(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'print' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight6C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'call' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight6C(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'call' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight6W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'while' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight6W(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'if' AND b.stmtType = 'while' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight6I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'if' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight6I(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'if' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight6A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextStarTable.n2 FROM nextStarTable WHERE nextStarTable.n2 IN(SELECT nextStarTable.n2 FROM nextStarTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'assign' AND nextStarTable.n2 = b.stmtNumber AND nextStarTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight6A(vector<string>& results) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT nextTable.n2 FROM nextTable WHERE nextTable.n2 IN(SELECT nextTable.n2 FROM nextTable, statement AS a, statement AS b WHERE a.stmtType = 'while' AND b.stmtType = 'assign' AND nextTable.n2 = b.stmtNumber AND nextTable.n1 = a.stmtNumber);";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarleft7(vector<string>& results, string n2) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n1 FROM nextStarTable WHERE n2 = '" + n2 + "';";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextleft7(vector<string>& results, string n2) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n1 FROM nextTable WHERE n2 = '" + n2 + "';";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextstarRight7(vector<string>& results, string n1) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n2 FROM nextStarTable WHERE n1 = '" + n1 + "';";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getNextRight7(vector<string>& results, string n1) {
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getNSQL = "SELECT DISTINCT n2 FROM nextTable WHERE n1 = '" + n1 + "';";
	sqlite3_exec(dbConnection, getNSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of while line numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

void Database::getpattern1(vector<string>& results, string entref) {//clear
	// clear the existing results
	dbResults.clear();

	// The callback method is only used when there are results to be returned.
	string getpatternSQL = "SELECT assignNumber from assignment WHERE assignVar = '" + entref + "' ORDER BY assignNumber ASC;";
	//"SELECT a.stmtNumber FROM statement AS a, statement AS b, followsrighttable WHERE b.stmtNumber = followsrighttable.followsNumber AND a.stmtNumber < b.stmtNumber AND a.stmtlist = b.stmtlist ORDER BY a.stmtNumber DESC LIMIT 1;";
	sqlite3_exec(dbConnection, getpatternSQL.c_str(), callback, 0, &errorMessage);
	// postprocess the results from the database so that the output is just a vector of statement numbers
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	NotUsed = 0;
	vector<string> dbRow;

	// argc is the number of columns for this row of results
	// argv contains the values for the columns
	// Each value is pushed into a vector.
	for (int i = 0; i < argc; i++) {
		dbRow.push_back(argv[i]);
	}

	// The row is pushed to the vector for storing all rows of results 
	dbResults.push_back(dbRow);

	return 0;
}
