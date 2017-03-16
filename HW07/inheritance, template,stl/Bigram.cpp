/*----------------------------------------------------------------------------*/
/* */
/* HW07_131044003_Talha_Oz */
/* */
/*                              main.cpp                                      */
/* ---------------------------------------------------------------------------*/
/* Created on 27/12/2016 by Talha_OZ */ 
/*____________________________________________________________________________*/


#ifndef BIGRAM
#define BIGRAM

#include <iostream>
#include <utility> // including for pair using

using namespace std;

// our base class Bigram
template <class T>
class Bigram
{
public:
	// All functions are pure virtual
	Bigram(); // no param constructor
	virtual void readFile(const string fileName) =0; //readfile func calculate bigrams
	virtual int numGrams()  =0; // return the number of bigrams
	virtual int numOfGrams(T &element1,T &element2) =0; //return the number of bigram according to inputs
	//friend ostream &operator <<(ostream &outputStream,const Bigram<T> &obj){} // overload output operator
	virtual pair<T,T> maxGrams()  =0; // return the bigram that has occurred most frequently


};

template <class T>
Bigram<T>::Bigram()
{
	// deliberately empty
}


// Dear asistant,I couldnt implement this stream operator 
/*
template <class T>
ostream &operator <<(ostream &outputStream,const Bigram<T> &obj)
{
		Bigram<T> *optr = &obj;

		if( dynamic_cast<(BigramMap<T> *)>(optr) != NULL ){
			outputStream << *((BigramMap*)optr);
		}	
}
*/

#endif


/*############################################################################*/
/* 						       END OF Bigram.cpp                              */
/*############################################################################*/