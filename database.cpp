#include "database.h"
#include <sstream>
#include <set>
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
 using namespace std;
Database::Database(string index, ofstream& output1, double e1, double T1)
{
	output= &output1;
	e=e1;
	T=T1;
	ifstream webpage_in(index.c_str());
	int countwebpage=0;
	string line="";
	while(getline(webpage_in,line))
	{
		webpage_vector.push_back(new Webpage(line));
		countwebpage++;
	}
	//making findwebpage
	for(unsigned int k=0;k<webpage_vector.size();k++)
	{
		findwebpage.insert(std::make_pair(webpage_vector[k]->get_name(), webpage_vector[k]));
	}
	//adding incoming links
	for(unsigned int j=0;j<webpage_vector.size();j++)
	{
		webpage_vector[j]->parser();
		set<string> out_links=webpage_vector[j]->get_out_links();
		std::set<string>::iterator it;
		for(it=out_links.begin();it!=out_links.end();++it)
		{
			for(unsigned int i=0;i<webpage_vector.size();i++)
			{
				if(webpage_vector[i]->get_name()==*it)
				{
					webpage_vector[i]->get_in_links().insert(webpage_vector[j]->get_name());
				}
			}
		}
	}
//MAP
	 for(unsigned int i=0;i<webpage_vector.size();i++)
	 {
		 std::set<string>::iterator it;
		for (it = (webpage_vector[i]->get_words()).begin(); it !=(webpage_vector[i]->get_words()).end(); ++it)//every it is a word from that webpage
		{
			if(words_map.find(*it)==words_map.end())//word not in map
			{
				set<string> webpages_set; webpages_set.insert(webpage_vector[i]->get_name());
				words_map.insert(std::make_pair(*it , webpages_set));
			}
			else
			{
				words_map[*it].insert(webpage_vector[i]->get_name());
			}
		}
	 }
}

Database::~Database()
{
	for(unsigned int i=0;i<webpage_vector.size();i++)
	{
		delete webpage_vector[i];
	}
}

//put check for word not found
void Database::searchword(string word)
{

	std::set<string>::iterator it;
	if(words_map.find(word)==words_map.end()) //word not found
	{
		*output<<0<<endl;
	}
	else
	{ set<string> result=words_map[word];
	set<string> result2=candidateset(result);
		*output<<result2.size()<<endl;
		if(result2.size()>1)
		{

			vector<string> result3= pagerank(result2);
			for(int i=0;i<result3.size(); ++i)
		 	 {
		 	 	*output<<result3[i]<<endl;
		 	 }
		}
		else 
		{
			for(it=result2.begin();it!=result2.end(); ++it)
		 	 {
		 	 	*output<<*it<<endl;
		 	 }
		}
 	}
}

void Database::intersectstrings(vector<string> words)
{
	set<string> result;
	std::set<string>::iterator it;
	for(it=words_map[words[0]].begin();it!=words_map[words[0]].end();++it)
	{
		std::set<string>::iterator it1;
		for(it1=words_map[words[1]].begin();it1!=words_map[words[1]].end();++it1)
		{
			if(*it==*it1)
			{
				result.insert(*it);
			}
		}
	}
				set<string> temp;

	unsigned int count=2;
	while(count!=words.size())
	{
		std::set<string>::iterator it2;
		for(it2=result.begin();it2!=result.end();++it2)
		{

			bool flag=true;
			std::set<string>::iterator it3;
			for(it3=words_map[words[count]].begin();it3!=words_map[words[count]].end();++it3)
			{
				if(*it2==*it3)
				{

					flag=false;
				}

			}
			if (flag) 
				{
					temp.insert(*it2);
				}
		}
		count++;
	}
			std::set<string>::iterator it7;


	for(it7=temp.begin();it7!=temp.end();++it7)
	{
		std::set<string>::iterator it8;
		if(result.find(*it7)!=result.end()) result.erase(*it7);
	}

	set<string> result2=candidateset(result);
	if(result2.size()>1)
	{
		vector<string> result3=pagerank(result2);
		*output<<result3.size()<<endl;
		for(unsigned int it4=0;it4<result3.size();it4++)
		{
			*output<<result3[it4]<<endl;
		}
	}
	else
	{
		*output<<result2.size()<<endl;
		std::set<string>::iterator it4;
		for(it4=result2.begin();it4!=result2.end();++it4)
		{
			*output<<*it4<<endl;
		}
	}
}

void Database::unionstrings(set<string> words_to_union)
{
	set<string> unionset;
	std::set<string>::iterator it;
	for(it=words_to_union.begin();it!=words_to_union.end();++it)
	{ //it is word whose set we need to union
		std::set<string>::iterator it1;
		for(it1=words_map[*it].begin();it1!=words_map[*it].end();++it1)
		{
		 unionset.insert(*it1);
		}	
	}
	/*candidateset(unionset);
	*output<<unionset.size()<<endl;
	std::set<string>::iterator it2;
	for(it2=unionset.begin();it2!=unionset.end();++it2)
	{
		*output<<*it2<<endl;
	}*/
	set<string> result2=candidateset(unionset);
	if(result2.size()>1)
	{
		vector<string> result3=pagerank(result2);
		*output<<result3.size()<<endl;
		for(unsigned int it4=0;it4<result3.size();it4++)
		{
			*output<<result3[it4]<<endl;
		}
	}
	else
	{
		std::set<string>::iterator it4;
		for(it4=result2.begin();it4!=result2.end();++it4)
		{
			*output<<*it4<<endl;
		}
	}
}

void Database::printpage(string webpagename)
{
	for(unsigned int i=0;i<webpage_vector.size();i++)
	{
		if(webpage_vector[i]->get_name()==webpagename)
		{
			webpage_vector[i]->printpage(*output);
		}
	}
}

void Database::incomingpage(string webpagename)
{
	bool flag=true;
	for(unsigned int i=0;i<webpage_vector.size();i++)
	{
		if(webpage_vector[i]->get_name()==webpagename)//finding webpage which matches
		{
			flag=false;
			set<string> in_links=webpage_vector[i]->get_in_links();
			std::set<string>::iterator it;
			*output<<in_links.size()<<endl;
			for(it=in_links.begin();it!=in_links.end();++it)
			{
				*output<<*it<<endl;
			}
		}
	}
	if(flag) *output<<"Invalid query"<<endl;
}

void Database::outgoingpage(string webpagename)
{
	bool flag=true;
	for(unsigned int i=0;i<webpage_vector.size();i++)
	{
		if(webpage_vector[i]->get_name()==webpagename)
		{
			flag=false;
			set<string> out_links=webpage_vector[i]->get_out_links();
			std::set<string>::iterator it;
			*output<<out_links.size()<<endl;
			for(it=out_links.begin();it!=out_links.end();++it)
			{
				*output<<*it<<endl;
			}
		}
	}
	if(flag) *output<<"Invalid query"<<endl;
}

set<string> Database::candidateset(set<string>& result)
{
	set<string> result1=result;
	set<string>::iterator it;
	for(it=result.begin();it!=result.end();it++)
	{
				set<string> out_links=findwebpage[*it]->get_out_links();
				set<string>::iterator it1;
				for(it1=out_links.begin();it1!=out_links.end();it1++)
				{
					ifstream myFile((*it1).c_str());
   					if(!(myFile.fail()))
   					{
						result1.insert(*it1);
    				}
				}
				set<string> in_links=findwebpage[*it]->get_in_links();
				set<string>::iterator it2;
				for(it2=in_links.begin();it2!=in_links.end();it2++)
				{
					ifstream myFile((*it2).c_str());
   					if(!(myFile.fail()))
   					{
						result1.insert(*it2);
    				}
				}
	}
	return result1;
}

vector<string> Database::pagerank(set<string> result1)
{
	vector<string> result(result1.begin(),result1.end());
	//std::copy(result1.begin(), result1.end(), std::back_inserter(result));
	vector<vector<double> > adjacency_matrix(result1.size(), std::vector<double>(result1.size(), 0.0f));
	for(unsigned int i=0;i<result.size();i++)
	{
		for(unsigned int j=0;j<result.size();j++)
		{
			double count=0;//number of elements in outgoing set within candidate set ONLY
			set<string>::iterator it;
			set<string> asd=findwebpage[result[j]]->get_out_links();
			set<string>::iterator it1=asd.begin();
			for(it1=asd.begin();it1!=asd.end();++it1)
			{
				if(result1.find(*it1)!=result1.end())
					count++;
			}
			if(i==j)
			{
				
				adjacency_matrix[i][j]=1.0/(count+1.0);

			}
			else if(asd.find(result[i])!=asd.end())
				{
					adjacency_matrix[i][j]=1.0/(count+1.0);
				}
			else adjacency_matrix[i][j]=0.0;
		}
	}
	//adjacency matrix is made
		vector<double > prev_matrix(result1.size(), 1.0/result.size());

	//matrix multiplication
		vector<double > ans(result1.size(), 0.0);
	for(int t=0;t<T;t++)
	{	
		for(size_t m = 0; m<result1.size(); ++m)
    		ans[m]=0.0;


		for (unsigned int a3 = 0; a3 < result.size(); a3++)
	    {
	        for (unsigned int a4 = 0; a4 < result.size(); a4++)
	        {
	            ans[a3]+= adjacency_matrix[a3][a4] * prev_matrix[a4];
	        }	    }	

	    for(unsigned int a5=0;a5<result.size();a5++)
	    {
	    	ans[a5]=(ans[a5]*(1.0-e))+(e/result.size());
	    }

	    prev_matrix=ans;
	}
	//sort result
    for (unsigned int a6 = 0; a6 < result.size()-1; a6++)      
    {
    	for (unsigned int a7 = 0; a7 < result.size()-a6-1; a7++)
    	{
    		if (ans[a7] < ans[a7+1])
    		{
    			double temp=ans[a7];
    			ans[a7]=ans[a7+1];
    			ans[a7+1]=temp;

    			string temp1=result[a7];
    			result[a7]=result[a7+1];
    			result[a7+1]=temp1;
    		}
    	}
    }
    return result;
}