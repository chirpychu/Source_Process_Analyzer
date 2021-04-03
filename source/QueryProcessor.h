#pragma once

#include <string>
#include <vector>
#include "Database.h"

using namespace std;

class QueryProcessor {
public:
	// default constructor
	QueryProcessor();

	// destructor
	~QueryProcessor();

	// method for evaluating a query
	void evaluate(string query, vector<string>& results);

private:
	vector<string> selectedsyn;
	vector<vector<string>> selectedEntities;

	void getSelectedEntitiesResults();
};