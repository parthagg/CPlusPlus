//t+1/ t-1
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

template <class T>
set<T> intersectstrings(vector<T> words, map<T, set<T> > words_map)
{
	set<T> result;
	typename std::set<T>::iterator it;
	for(it=words_map[words[0]].begin();it!=words_map[words[0]].end();++it)
	{
		typename std::set<T>::iterator it1;
		for(it1=words_map[words[1]].begin();it1!=words_map[words[1]].end();++it1)
		{
			if(*it==*it1)
			{
				result.insert(*it);
			}
		}
	}
	set<T> temp;

	unsigned int count=2;
	while(count!=words.size())
	{
		typename std::set<T>::iterator it2;
		for(it2=result.begin();it2!=result.end();++it2)
		{
			bool flag=true;
		typename	std::set<T>::iterator it3;
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
	typename std::set<T>::iterator it7;
	for(it7=temp.begin();it7!=temp.end();++it7)
	{
		if(result.find(*it7)!=result.end()) result.erase(*it7);
	}
	return result;
}

template <class T>
set<T> unionstrings(set<T> words_to_union, map<T, set<T> > words_map)
{
	set<T> unionset;
	typename std::set<T>::iterator it;
	for(it=words_to_union.begin();it!=words_to_union.end();++it)
	{ //it is word whose set we need to union
		typename std::set<T>::iterator it1;
		for(it1=words_map[*it].begin();it1!=words_map[*it].end();++it1)
		{
		 unionset.insert(*it1);
		}	
	}
	return unionset;
}
