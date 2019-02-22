#include "webpage.h"
#include <fstream>
#include <cstring>


Webpage::Webpage(string webpagename)
{
	name=webpagename;
}
Webpage::~Webpage()
{

}
std::set<string>& Webpage::get_words()
{
	return words;
}

std::string Webpage::get_name()
{
	return name;
}
std::set<string> Webpage::get_out_links()
{
	return out_links;
}
std::set<string>& Webpage::get_in_links()
{
	return in_links;
}
std::string Webpage::tolowercase(string word)
{
	int i=0;
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
void Webpage::parser()
{
	ifstream input(name.c_str());
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
				words.insert(tolowercase(word));
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
						words.insert(tolowercase(word));
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
				out_links.insert(out_link);
			}
		}
	}
}
void Webpage::printpage(ofstream& output)
{
	ifstream input(name.c_str());
	output<<name<<endl;
	string line;
	line="";
	while(getline(input,line))
	{
		for(int i=0;i<line.size();i++)
		{ 		
			if(line[i]=='(')
			{
				while(line[i]!=')')
				{
					i++;
				}
			}
			else
			{
				output<<line[i];
			}
		}
		output<<endl;
	}
}


