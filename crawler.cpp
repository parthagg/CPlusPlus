#include "database.h"
#include <sstream>
#include <set>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <map>
//when templating the functions, make it into separate .h and .cpp, if yes, use that in database?
//does the way for handling 404 errors still work; I didnt do anything about it the last time??
void helper(string line1, set<string>& foundwebpages, ofstream& output1)
{
	ofstream* output=&output1;
	ifstream input(line1.c_str());
	string line;
	line="";
	while(getline(input,line))
	{
		for(int i=0;i<line.size();i++)
		{
			if (islower(line[i])||isupper(line[i])||isdigit(line[i]))
			{
				string word="";
				while((islower(line[i])||isupper(line[i])||isdigit(line[i])))
				{
					word=word+line[i];
					i++;
				}
				i--;
				//words.insert(tolowercase(word));
			}
			else if(line[i]=='[')
			{
				while(line[i]!=']')
				{
					i++;
					if (islower(line[i])||isupper(line[i])||isdigit(line[i]))
					{
						string word="";
						while(islower(line[i])||isupper(line[i])||isdigit(line[i]))
						{
							word=word+line[i];
							i++;
						}
						//words.insert(tolowercase(word));
					}
				}
			}
			else if(line[i]=='(')
			{
				i++;
				string out_link="";
				while(line[i]!=')')
				{
					out_link+=line[i];
					i++;
				}
				ifstream myFile((out_link).c_str());
				if(!(myFile.fail()))
				{
					set< string >::iterator it = foundwebpages.find(out_link);
					if (it == foundwebpages.end()) 
					{
						foundwebpages.insert(out_link);
							*output<<out_link<<endl;

						helper(out_link,foundwebpages, *output);
					}
				}
			}
			/*set< string >::iterator it = foundwebpages.find(out_link);
			if (it == foundwebpages.end()) 
				{
					foundwebpages.insert(out_link);
						*output<<out_link<<endl;

					helper(out_link,foundwebpages, *output);
				}*/
		}
	}
}

int main(int argc, char* argv[])
{
	string config_file, indexfile, outputfile;
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
					while((line1[i]!=' '))
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
				else if(parameter=="OUTPUT_FILE") outputfile=value;
				//add any more parameters here
				break; 
			}
		}
	}
	ifstream webpage_in(indexfile.c_str());
	ofstream webpage_out(outputfile.c_str());
	string line="";
	set<string> foundwebpages;
	while(getline(webpage_in,line))
	{
		set< string >::iterator it = foundwebpages.find(line);
		if (it == foundwebpages.end()) 
		{
			foundwebpages.insert(line);
			webpage_out<<line<<endl;
			helper(line, foundwebpages, webpage_out);
		}
	}
}