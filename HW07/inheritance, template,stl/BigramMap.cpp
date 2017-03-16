// Derived class BigramMap

////// include //////
#include "BigramMap.h"

using namespace std;


// no parameter constructor
template <class T>
BigramMap<T>::BigramMap()
{
	// deliberately empty
}

// constructor getting the dataTYpe as parameter
template <class T>
BigramMap<T>::BigramMap(int typeOfData)
{
	dataType=typeOfData;
}

// readfile func gonna read the data from file and calculate the bigrams then keep them in a map 
template <class T>
void BigramMap<T>::readFile(const string fileName)
{

	T tempData;
	vector <T> dataTemp;
	pair<T,T> myPair;
	char empty;


	ifstream inputStream(fileName);
	
	// file open error
	if(!inputStream.is_open())
	{
		throw exception();
	}

	// empty txt file error
	inputStream >> empty;
	
	if(inputStream.eof())
	{
		throw exception();
	}

	// go to beginning of the file because we read one char
	inputStream.clear();
	inputStream.seekg(0,ios::beg);

	// get the data and put them in a vector temporarily
	while(inputStream >> tempData)
	{
		dataTemp.push_back(tempData);
	}

	// if there is any unexpected data(like waiting for int but data is double) throw exception
	if(!inputStream.eof())
	{
		throw exception();
	}


	// we will always have number of bigrams that size miles one
	numOfBigrams=dataTemp.size()-1;

	// calculating the bigrams and putting them in a map
	for(int i=0; i<(int)dataTemp.size()-1; ++i)
	{
		myPair=make_pair(dataTemp[i],dataTemp[i+1]);

		if(data.find(myPair)==data.end())
		{
			data[myPair]=1;
		}
		// if the data is already in the map then plus one its number
		else if(data.find(myPair)!=data.end())
			data[myPair]++;

	}



}

// numOfGrams gonna return the number of bigram which wanted in the parameters
template <class T>
int BigramMap<T>::numOfGrams(T &element1,T &element2) 
{
	int found=0;

	pair<T,T> myPair=make_pair(element1,element2);

	if(data.find(myPair)!=data.end())
	{
		found=data[myPair];
	}

	return found;
}

// maxGram gonna return a pair that has occurred most frequently
template <class T>
pair<T,T> BigramMap<T>::maxGrams() 
{
	int max=0;

	pair<T,T> myPair;

	// making an iterator for check the map datas one by one
	typename map<pair<T,T>,int>::iterator iter;

	for(iter=data.begin(); iter!=data.end(); ++iter)
	{
		if(iter->second > max)
		{
			max=iter->second;
			myPair=iter->first;
		}
	}

	return pair<T,T>(myPair.first,myPair.second);
}


////////////////////
// it s a pretty nice stream operator but its not working for both (as friend and virtual), i couldnt solve this problem
///////////////////////77
/*
template <class T>
ostream &operator <<(ostream &outputStream,const BigramMap<T> &obj)
{
	pair <T,T> maxBigram= obj.maxGrams();
	int max=obj.data[maxBigram];

	typename map<pair<T,T>,int>::const_iterator iter;

	for(int i=0; i<obj.data.size(); ++i)
	{
		for(iter=obj.data.begin(); iter!=obj.data.end(); ++iter)
		{
			if(iter->second == max)
			{
				outputStream << iter->first << " -> " << iter->second <<endl;
			}
		}

		max--;
	}

	return outputStream;
}

*/


/*############################################################################*/
/* 						       END OF BigramMap.cpp                           */
/*############################################################################*/