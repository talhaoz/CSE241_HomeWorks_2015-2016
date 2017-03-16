//includes for CPUProgramDyn.cpp

#include <iostream>
#include <string>
#include <fstream>

//include CPUProgramDyn.h which keeps the class information
//#include "CPUProgramDyn.h"
#include "CPUProgramDyn.h"

using namespace std;


namespace space_CPUProgramDyn
{

	//constructor gonna call readfile func
	CPUProgramDyn::CPUProgramDyn(const char *fileName)
	{
		ReadFile(fileName);
	}

	//this constructor takes a vector string and put it into private lines
	CPUProgramDyn::CPUProgramDyn(string *temp,int size_temp)
	{	
		lines=new string[size_temp];

		for(int i=0; i<size_temp; ++i)
		{
			lines[i]=temp[i];
		}

		sizeOfLines=size_temp;

	}

	//setting option
	CPUProgramDyn::CPUProgramDyn(int opt)
	{
		option=opt;
		sizeOfLines=0;
		lines=new string[0];
	}

	
	CPUProgramDyn::CPUProgramDyn()
	{
		sizeOfLines=0;
		lines=new string[0];
	}

	//readfile func gonna read the lines from file one by one
	void CPUProgramDyn::ReadFile(const char *fileName)
	{
		fstream inputStream;
		int i=0,count=0;
		string empty,temp;


		//open file
		inputStream.open(fileName);

		//find number of lines for initialize the dynamic string
		while(getline(inputStream,empty)) count++;

		inputStream.close();
	
		sizeOfLines=count; //init the size first time
		delete [] lines;
		lines=new string[size()]; //allocate memory for the coming lines

		inputStream.open(fileName);

		//get the lines into string array
		while(getline(inputStream,temp))
		{	
			lines[i]=temp;
			i++;
		}

		//close file
		inputStream.close();
	}


	//[] operator takes an index and return a line according to index
	const string CPUProgramDyn::operator [](int index) const
	{
		string empty;

		//if index smaller than 0 or bigger than size print an error
		if(index < 0 || ((index!=0) && (index > size()-1)) )
		{
			cerr << "Unexpected Index!" <<endl;
			return empty;
		}

		return lines[index];
	}


	// first + operator gonna add a new line into new obejct
	CPUProgramDyn CPUProgramDyn::operator +(const string newLine)
	{	
		string *temp; //make temp string
		int i;

		//check is the string empty
		if(newLine.empty())
		{
			cerr << "WARNING :The string that you trying to add is empty!"<<endl;
			return *this;
		}

		temp=new string[size()+1];

		//adding old object lines
		for(i=0; i< size(); ++i)
		{
			temp[i]=lines[i];
		}
		//adding new line
		temp[sizeOfLines]=newLine;
		CPUProgramDyn tempProg(temp,size()+1);

		delete [] temp;

		return CPUProgramDyn(tempProg); //its gonna call copy constructor
	}

	// += operetor gonna take a string and add a newline into given object
	CPUProgramDyn & CPUProgramDyn::operator +=(const string newLine)
	{	
		string *temp;
		int i;
		//check is the string empty
		if(newLine.empty())
		{
			cerr << "WARNING :The string that you trying to add is empty!"<<endl;
			return *this;
		}

		temp=new string[size()];

		for(i=0; i<size(); ++i)
			temp[i]=lines[i];

		delete [] lines;

		lines=new string[size()+1];

		for(i=0; i<size(); ++i)
		{
			lines[i]=temp[i];
		}

		lines[sizeOfLines]=newLine;

		sizeOfLines++; // plus with one because we add one more line

		delete [] temp;

		return *this;
	}

	// second + operator gonna take a second prog and add
	CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn &secProg)
	{
		string *temp=new string[size()+secProg.size()]; //make temp string
		int i,firstObjSize;

		//adding first objects lines into temp object
		for(i=0; i< size(); ++i)
		{	
			temp[i]=lines[i];
		}

		firstObjSize=size();
		//adding second objects lines into temp object
		for(i=0; i<secProg.size(); ++i)
		{
			temp[firstObjSize]=secProg.lines[i];
			
			firstObjSize++;
		}

		CPUProgramDyn tempProg(temp,size()+secProg.size());

		delete [] temp;

		return CPUProgramDyn(tempProg); //its gonna call copy constructor
	}


	// << operator gonna print the all lines 
	ostream & operator <<(ostream &outputStream,const CPUProgramDyn &prog)
	{	
		if(prog.size()==0)
		{
			return outputStream;
		}
		//loop for print the lines
		for(int i=0; i<prog.size(); ++i)
		{
			outputStream << prog.lines[i] << endl;
		}

		return outputStream;
	}

	// operator pre -- is gonna delete last line from given object and return object
	CPUProgramDyn & CPUProgramDyn::operator --()
	{	
		string *temp=new string[size()-1];

		for(int i=0; i<size()-1; ++i) 
			temp[i]=lines[i];

		delete [] lines;

		lines=new string[size()-1];

		for(int i=0; i<size()-1; ++i) 
			lines[i]=temp[i];

		delete [] temp;

		sizeOfLines--;

		return *this;
	}
	// operator post -- is gonna copy object into temp object than delete the last line and return temp object
	CPUProgramDyn CPUProgramDyn::operator --(int IgnoreMe)
	{
		CPUProgramDyn tempProg=*this;
		string *temp=new string[size()-1];

		for(int i=0; i<size()-1; ++i) 
			temp[i]=lines[i];

		delete [] lines;

		lines=new string[size()-1];

		for(int i=0; i<size()-1; ++i) 
			lines[i]=temp[i];

		delete [] temp;

		sizeOfLines--;

		return tempProg;
	}

	// function call operator gonna takes two edges and return new object between this edges
	const CPUProgramDyn CPUProgramDyn::operator ()(int startIndex,int endIndex)
	{
		CPUProgramDyn newProg,empty; //make new and empty objects
		int i,j=0;
		
		// if indexes re wrong return an empty obj
		if( (startIndex < 0) || (endIndex > size()-1) || (startIndex >= endIndex) )
		{
			cerr << "Unexpected Index!" <<endl;
			return empty;
		}

		newProg.lines=new string[endIndex-startIndex+1];
		cout << "A" <<endl;
		newProg.sizeOfLines=endIndex-startIndex+1;
		cout << "B" <<endl;
		//loop for add the objects
		for(i=startIndex; i<=endIndex; ++i)
		{
			newProg.lines[j]=lines[i];
			j++;
		}
		cout << "C" <<endl;
		return CPUProgramDyn(newProg);
	}

	// assignment operator
	CPUProgramDyn & CPUProgramDyn::operator =(const CPUProgramDyn &rightSide)
	{	
		//if left side same as right side
		if(this==&rightSide)
		{
			return *this;
		}
		else
		{
			option=rightSide.option;
			sizeOfLines=rightSide.size();

			delete [] lines;

			lines=new string[size()];

			for(int i=0; i< size(); ++i)
			{
				lines[i]=rightSide.lines[i];
			}
		}

		return *this;
	}



	// copy constructor can do deep copy
	CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn &rightSide):option(rightSide.option),sizeOfLines(rightSide.size())
	{
		lines=new string[size()];
		//copy all the lines
		for(int i=0; i<size(); ++i)
		{
			lines[i]=rightSide.lines[i];
		}
	}

	//destructor
	CPUProgramDyn::~CPUProgramDyn()
	{
		delete [] lines;
	} 



}

/*############################################################################*/
/* 						       END OF CPUProgramDyn.cpp                       */
/*############################################################################*/

