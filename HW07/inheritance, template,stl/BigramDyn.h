//BigramDyn.h  header file

//if there is any library included before, dont include it again
#ifndef BIGRAMDYN_H 

#define BIGRAMDYN_H


#include <iostream>
#include <utility>
#include <fstream>

// using std
using std::pair;



// derived BigramDyn class from Bigram base class
template <class T>
class BigramDyn : public Bigram<T>
{

public:
	BigramDyn(); // no param constructor
	BigramDyn(int typeOfData); 
	void readFile(const string fileName); //readfile func calculate bigrams
	int numGrams()  { return numOfBigrams; } // return the number of bigrams
	int numOfGrams(T &element1,T &element2); //return the number of bigram according to inputs
	//friend ostream &operator <<(ostream &outputStream,const BigramDyn<T> &obj); // overload output operator
	pair<T,T> maxGrams(); // return the bigram that has occurred most frequently

	int size() {return dataSize;} // return the size of the read data

	//big three (assignment operator,copy constructor,destructor)
	BigramDyn &operator =(const BigramDyn<T> &rightSide);
	BigramDyn(const BigramDyn<T> &rightSide);
	~BigramDyn();


private:
	int dataType; // keep data type
	T *data;	// keep the all data in a template memory 
	int dataSize; // keep data size
	int numOfBigrams; // keep the number of Bigrams
};


#endif


/*############################################################################*/
/* 						       END OF BigramDyn.h                             */
/*############################################################################*/