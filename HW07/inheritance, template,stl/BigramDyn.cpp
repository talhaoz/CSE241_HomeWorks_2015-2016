// Derived class BigramDyn

////// include //////

#include "BigramDyn.h"

using namespace std;

// no param constructor
template <class T>
BigramDyn<T>::BigramDyn()
{	
	//allocate a memory for data
	data=new T[0];
	dataSize=0;
	numOfBigrams=0;
}

// constructor takes the type of the datas and allocate mem for them
template <class T>
BigramDyn<T>::BigramDyn(int typeOfData)
{
	dataType=typeOfData;
	data=new T[0];
	dataSize=0;
	numOfBigrams=0;
}


// readfile func gonna read the data from file and calculate the bigrams then keep them in a dynamic memory
template <class T>
void BigramDyn<T>::readFile(const string fileName)
{

	T tempData,empty;
	pair<T,T> myPair;
	char empty2;
	int i;

	ifstream inputStream(fileName);
	
	// file open error
	if(!inputStream.is_open())
	{
		throw exception();
	}

	
	inputStream >> empty2;
	// empty txt file error
	if(inputStream.eof())
	{
		throw exception();
	}

	// returning to beginning of the file
	inputStream.clear();
	inputStream.seekg(0,ios::beg);

	// calculate how much memory we need
	while(inputStream >> empty)
	{
		dataSize++;
	}

	// allocate the memory
	delete [] data;
	data=new T[size()];

	// returning to beginning of the file
	inputStream.clear();
	inputStream.seekg(0,ios::beg);

	// read all the data in dynamic template memory
	i=0;
	while(inputStream >> tempData)
	{
		data[i]=tempData;
		++i;
	}

	// if there is any unexpected data(like waiting for int but data is double) throw exception
	if(!inputStream.eof())
	{
		throw exception();
	}

	// we will always have number of bigrams that size miles one
	numOfBigrams=size()-1;

}

// numOfGrams gonna return the number of bigram which wanted in the parameters
template <class T>
int BigramDyn<T>::numOfGrams(T &element1,T &element2) 
{
	int count=0;

	// loop for check the data one by one 
	for(int i=0; i< size()-1; ++i)
	{	
		// if first element is same then check the sec element
		if(element1==data[i])
		{	
			if(element2==data[i+1])
				count++;
		}
	}

	return count;

}

// maxGram gonna return a pair that has occurred most frequently
template <class T>
pair<T,T> BigramDyn<T>::maxGrams() 
{
	int max=0,temp=0;
	// making a pair for return
	pair<T,T> myPair;

	for(int i=0; i<size()-1; ++i)
	{	
		// call the numOfGrams for check the given data how many exist in the file
		temp=numOfGrams(data[i],data[i+1]);

		// if this data is exist more than the max then change it as max data
		if(temp > max)
		{
			max=temp;
			myPair.first=data[i];
			myPair.second=data[i+1];
		}
	}

	// return the found max Gram
	return pair<T,T>(myPair.first,myPair.second);
}


// assignment operator
template <class T>
BigramDyn<T> & BigramDyn<T>::operator =(const BigramDyn<T> &rightSide)
{	
	//if left side same as right side
	if(this==&rightSide)
	{
		return *this;
	}
	else
	{	
		// assignmets
		dataType=rightSide.dataType;
		numOfBigrams=rightSide.numOfBigrams;

		dataSize=rightSide.size();
		//delete the old allocated memory
		delete [] data;
		// allocate new memory with new size
		data=new T[size()];

		// assign the whole data
		for(int i=0; i< size(); ++i)
		{
			data[i]=rightSide.data[i];
		}
	}

	return *this;
}


// copy constructor can do deep copy
template <class T>
BigramDyn<T>::BigramDyn(const BigramDyn<T> &rightSide):dataType(rightSide.dataType),numOfBigrams(rightSide.numOfBigrams)
{	
	dataSize=rightSide.size();

	data=new T[size()];
	//copy all the lines
	for(int i=0; i<size(); ++i)
	{
		data[i]=rightSide.data[i];
	}
}

// destructor for delete the used memory
template <class T>
BigramDyn<T>::~BigramDyn()
{
	delete [] data;
} 

/*############################################################################*/
/* 						       END OF BigramDyn.cpp                           */
/*############################################################################*/