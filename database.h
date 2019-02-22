#include <sstream>
#include <set>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include "webpage.h"

 using namespace std;

 class Database{
 public:
 	Database(string webpagelist, ofstream& output1, double e1, double T1);
 	~Database();
 	void searchword(string word);
	void intersectstrings(vector<string> words_to_intersect);
	void unionstrings(set<string> words_to_union);
	void printpage(string webpagename);
	void incomingpage(string webpagename);
	void outgoingpage(string webpagename);
	set<string> candidateset(set<string>& result);
vector<string> pagerank(set<string> result1);

	ofstream* output;

private:
	map<string, set<string> > words_map;
	map<string, Webpage*> findwebpage; //key= webpage name, value= pointer to the particular webpage obj
	vector<Webpage*> webpage_vector;
	double e;
	double T;

 };