//BigramMap.h  header file

//if there is any library included before, dont include it again
#ifndef BIGRAMMAP_H 

#define BIGRAMMAP_H



#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <map>

// using std's
using std::string;
using std::map;
using std::pair;


// derived BigramMap class from Bigram base class
template <class T>
class BigramMap : public Bigram<T>
{

public:
	BigramMap(); // no param constructor
	BigramMap(int typeOfData); 
	void readFile(const string fileName); //readfile func calculate bigrams
	int numGrams()  { return numOfBigrams; } // return the number of bigrams
	int numOfGrams(T &element1,T &element2); //return the number of bigram according to inputs
	//friend ostream &operator <<(ostream &outputStream,const BigramMap<T> &obj); // overload output operator
	pair<T,T> maxGrams(); // return the bigram that has occurred most frequently

private:
	int dataType; // keep the data type
	map <pair<T,T>,int> data; // keep the all datas in a map
	int numOfBigrams; // keep the number of the bigrams
};

#endif


/*############################################################################*/
/* 						       END OF BigramMap.h                             */
/*############################################################################*/