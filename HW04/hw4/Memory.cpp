//includes for Memory.cpp
#include <iostream>
#include "Memory.h"

using namespace std;


//Memory constructor will run when program start
//its gonna initialize the value of memories and the option
Memory::Memory(int option)
{
	int i;
	const int MEMORY_SIZE=50;

	for(i=0; i<MEMORY_SIZE; ++i)
		setMem(i,0);
	opt=option;
}

//default constructor to can create new objects
Memory::Memory()
{
	int i;   //mean nothing
	i=0;
}

// set the value in memory
void Memory::setMem(int index,int value)
{
	Adr[index]=value;
}

//this func for print the memory values
void Memory::printAll()
{
	int i,k=1;
	int const MEMORY_SIZE=50;

	
	cout << "Memory Values:" <<endl;

	//print all memory values one by one 
	//after every ten memory values jump newline , so our printout will more readable
	for(i=0; i<MEMORY_SIZE; ++i) 
	{
		cout << "[" << i << "]" <<"->"<< getMem(i) ;
			if(i!=MEMORY_SIZE-1)
				cout <<" , ";

			if(i==10*k-1)
			{
				cout <<endl;
				++k;
			}
	}
}

/*############################################################################*/
/* 						       END OF Memory.cpp                              */
/*############################################################################*/