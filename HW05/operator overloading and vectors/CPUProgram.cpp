//includes for CPUProgram.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//include CPUProgram.h which keeps the class information
#include "CPUProgram.h"

using namespace std;



//constructor gonna call readfile func
CPUProgram::CPUProgram(const char *fileName)
{
	ReadFile(fileName);
}

//this constructor takes a vector string and put it into private lines
CPUProgram::CPUProgram(vector <string> &temp)
{
	for(int i=0; i<temp.size(); ++i)
	{
		lines.push_back(temp[i]);
	}
}

//setting option
CPUProgram::CPUProgram(int opt)
{
	option=opt;
}

//do nothing
CPUProgram::CPUProgram()
{
	int i;   //mean nothing
	i=0;
}

//readfile func gonna read the lines from file one by one
void CPUProgram::ReadFile(const char *fileName)
{
	fstream inputStream;
	string myTempLine;


	//open file
	inputStream.open(fileName);

	//get the lines into string array
	while(getline(inputStream,myTempLine))
	{
		lines.push_back(myTempLine);

	}

	//close file
	inputStream.close();
}


//[] operator takes an index and return a line according to index
const string CPUProgram::operator [](int index) const
{
	string empty;

	//if index smaller than 0 or bigger than size print an error
	if(index < 0 || index > size()-1)
	{
		cerr << "Unexpected Index!" <<endl;
		return empty;
	}

	return lines[index];
}

// first + operator gonna add a new line into new obejct
CPUProgram CPUProgram::operator +(const string newLine)
{	
	vector <string> temp; //make temp string
	int i;

	//check is the string empty
	if(newLine.empty())
	{
		cerr << "WARNING :The string that you trying to add is empty!"<<endl;
		return *this;
	}

	//adding old object lines
	for(i=0; i< size(); ++i)
	{
		temp.push_back(lines[i]);
	}
	//adding new line
	temp.push_back(newLine);

	return CPUProgram(temp);
}

// += operetor gonna take a string and add a newline into given object
CPUProgram & CPUProgram::operator +=(const string newLine)
{	
	//check is the string empty
	if(newLine.empty())
	{
		cerr << "WARNING :The string that you trying to add is empty!"<<endl;
		return *this;
	}

	lines.push_back(newLine);

	return *this;
}

// second + operator gonna take a second prog and add
CPUProgram CPUProgram::operator +(const CPUProgram &secProg)
{
	vector <string> temp; //make temp string
	int i;

	//adding first objects lines into temp object
	for(i=0; i< size(); ++i)
	{	
		temp.push_back(lines[i]);
	}
	//adding second objects lines into temp object
	for(i=0; i<secProg.size(); ++i)
	{
		temp.push_back(secProg.lines[i]);

	}

	return CPUProgram(temp);
}


// << operator gonna print the all lines 
ostream & operator <<(ostream &outputStream,const CPUProgram &prog)
{	
	//loop for print the lines
	for(int i=0; i<prog.size(); ++i)
	{
		outputStream << prog.lines[i] << endl;
	}

	return outputStream;
}

// operator pre -- is gonna delete last line from given object and return object
CPUProgram & CPUProgram::operator --()
{
	lines.pop_back();

	return *this;
}
// operator post -- is gonna copy object into temp object than delete the last line and return temp object
CPUProgram CPUProgram::operator --(int IgnoreMe)
{
	CPUProgram temp=*this;

	lines.pop_back();


	return temp;
}

// function call operator gonna takes two edges and return new object between this edges
CPUProgram CPUProgram::operator ()(int startIndex,int endIndex)
{
	CPUProgram newProg,empty; //make new and empty objects
	int i;
	
	// if indexes re wrong return an empty obj
	if( (startIndex < 0) || (endIndex > size()-1) || (startIndex >= endIndex) )
	{
		cerr << "Unexpected Index!" <<endl;
		return empty;
	}
	


	//loop for add the objects
	for(i=startIndex; i<=endIndex; ++i)
	{
		newProg.lines.push_back(lines[i]);
	}

	return newProg;
}

/*############################################################################*/
/* 						       END OF CPUProgram.cpp                          */
/*############################################################################*/





