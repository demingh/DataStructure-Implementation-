// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
using namespace std; 

WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return this->words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
	/*Swapping each adjacent pair of characters in the word*/
	vector<std::string> suggestion;
	
	for( int i=0; i<word.size()-1; i++)
	{
		string copy1=word; 
		char temp=copy1[i];
		copy1[i]=copy1[i+1];
		copy1[i+1]=temp; 
		bool itemfound=(find(suggestion.begin(), suggestion.end(),copy1)!=suggestion.end());
		if(wordExists(copy1)&&(!itemfound))
		{
			suggestion.push_back(copy1);
		}
	}

	/*in between each adjacent pair of characters in the word insert letter 'A' through 'Z' */
	for(int i=0; i<=word.size();i++) 
	{
		char letter='A'; 
		while(letter<='Z')
		{
			string copy2=word; 
			copy2.insert(i,1,letter);
			bool itemfound=(find(suggestion.begin(),suggestion.end(),copy2)!=suggestion.end());
			if(wordExists(copy2)&&(!itemfound))
			{
				suggestion.push_back(copy2);
			}
			letter++; 
		}
	}	

	/*Deleting each character from the word*/
	for(int i=0; i<word.size();i++) 
	{
		string copy3=word; 
		copy3.erase(i,1);
		bool itemfound=(find(suggestion.begin(),suggestion.end(),copy3)!=suggestion.end());
		if(wordExists(copy3)&&(!itemfound))
		{
			suggestion.push_back(copy3); 
		}
	}	

	/*replace each character in the word with each letter from 'A' through 'Z'*/
	for(int i=0; i<word.size(); i++)
	{
		string copy4=word; 
		char letter='A';
		while(letter<='Z')
		{
			copy4[i]=letter;
			bool itemfound=(find(suggestion.begin(),suggestion.end(),copy4)!=suggestion.end());
			if(wordExists(copy4)&&(!itemfound))
			{
				suggestion.push_back(copy4);
			}
			letter++; 
		}
	}

	/*splitting the word into a pair of words by adding a space in between each adjacent pair.*/
	for(int i=1; i<word.size(); i++)
	{
		string copy5=word; 
		string subcopy1=copy5.substr(0,i);
		string subcopy2=copy5.substr(i);
		copy5=subcopy1+" "+subcopy2;
		bool itemfound=(find(suggestion.begin(),suggestion.end(),copy5)!=suggestion.end()); 
		if(wordExists(subcopy1)&&wordExists(subcopy2)&&(!itemfound))
		{
			suggestion.push_back(copy5);
		}

	}

    return suggestion; 
}

