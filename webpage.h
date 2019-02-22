#include <sstream>
#include <set>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Webpage {
public: 
	Webpage(string webpagename);
	~Webpage();
	void parser();
	void printpage(ofstream& output);
	std::set<string>& get_words();
	std::set<string> get_out_links();
	std::string tolowercase(string word);
	std::set<string>& get_in_links();
	std::string get_name();

private:
	string name;
	set<string> words;
	set<string> out_links;
	set<string> in_links;
	
};
