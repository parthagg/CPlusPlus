#include "database.h"
#include <sstream>
#include <set>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <map>

//understand dynamic memory, how to use webpages
//convert char* to string and vice versa
//what happens when you add a used key to map, set
//access specific elements of set, map
//access first 3/4 elements of string

using namespace std;

std::string tolowercase(string word)
{ int i=0;
		while (word[i])
		{
			if(isalpha(word[i])&&isupper(word[i]))
			{
				char c = word[i];
			 	word[i] = tolower(c);
			}
			i++;
		}
		return word;
}
int main(int argc, char* argv[])
{
	string config_file, indexfile, queryfile, outputfile;
	double e,T;
	if(argc<2) config_file="config.txt";
	else config_file=argv[1];
	ifstream config_in(config_file.c_str());
	string line1="";
	while(getline(config_in,line1))
	{
		for(int i=0;i<line1.size();i++)
		{
			if(line1[i]==' ');
			else if(line1[i]=='#') break;
			else
			{
				string parameter=""; string value="";

				while(line1[i]!='='&&line1[i]!=' ')
				{
					parameter+=line1[i];
					i++;
				} 
				if(line1[i]==' ')
				{
					while(line1[i]!='=') i++;
				}
				if(line1[i]=='=')
				{
					i++;
					while(line1[i]==' ') i++;
					while((line1[i]!=' ')&&(line1[i]!='#'))
					{
						value+=line1[i];
						i++;
						if(i==line1.size()-1) 
							{
								value+=line1[i];
								break;
							}

					}
				}
				if(parameter=="INDEX_FILE") indexfile=value;
				else if(parameter=="QUERY_FILE") queryfile=value;
				else if(parameter=="OUTPUT_FILE") outputfile=value;
				else if(parameter=="RESTART_PROBABILITY") e=atof(value.c_str());
				else if(parameter=="STEP_NUMBER") T=atof(value.c_str());
				//add any more parameters here
				break; 

			}
		}
	}

	ofstream output(outputfile.c_str());
	Database data(indexfile,output,e,T);
	ifstream query_in(queryfile.c_str());
	string line;
	line="";

	while(getline(query_in,line))
	{
		stringstream ss(line);
		string command;
		ss>>command;
		if(command=="AND")
		{
			if (ss.eof())
			{
				data.searchword(tolowercase(command));
			}
			else
			{
				vector<string> and_words;
				while(!ss.eof())
				{
					string word;
					ss>>word;
					and_words.push_back(tolowercase(word));
				}
				if (and_words.size()==1) data.searchword(and_words[0]);
				else data.intersectstrings(and_words);
			}
		}
		else if(command=="OR")
		{
			if (ss.eof())
			{
				data.searchword(tolowercase(command));
			}
			else
			{
				set<string> or_words;
				while(!ss.eof())
				{
					string word;
					ss>>word;
					or_words.insert(tolowercase(word));
				}
				data.unionstrings(or_words);			
			}
		}
		else if(command=="PRINT")
		{
			if (ss.eof())
			{
				data.searchword(command);
			}
			else
			{
				string word;
				ss>>word;
				if(!ss.eof()) 
				{
					output<<"Invalid query"<<endl;
					continue;
				}			
				data.printpage(word);
			}
		}
		else if(command=="INCOMING")
		{
			if (ss.eof())
			{
				data.searchword(tolowercase(command));
			}
			else
			{
				string word;
				ss>>word;
				if(!ss.eof()) 
				{ 
					output<<"Invalid query"<<endl;
					continue;
				}			
				data.incomingpage(word);
			}
		}
		else if(command=="OUTGOING")
		{
			if (ss.eof())
			{
				data.searchword(tolowercase(command));
			}
			else
			{
				string word;
				ss>>word;
				if(!ss.eof()) 
				{
					output<<"Invalid query"<<endl;
					continue;
				}
				data.outgoingpage(word);
			}
		}
		else
		{
			if(!ss.eof()) 
			{
				output<<"Invalid query"<<endl;
				continue;
			}			
			data.searchword(tolowercase(command));

		}

	}
	return 0;
}

