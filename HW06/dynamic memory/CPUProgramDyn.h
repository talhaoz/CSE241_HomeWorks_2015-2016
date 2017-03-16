//CPUProgramDyn.h  header file

//if there is any library included before, dont include it again
#ifndef CPUPROGRAMDYN_H

#define CPUPROGRAMDYN_H

#include <string>

using namespace std;

namespace space_CPUProgramDyn
{
	//class for read the lines from file into string array and keep it
	class CPUProgramDyn
	{
		
	public:
			explicit CPUProgramDyn(const char *fileName); //constructor gonna call readfile func
			CPUProgramDyn(int opt);
			CPUProgramDyn(string *temp,int size_temp);
			CPUProgramDyn();
			string getLine(int lineNum) const {return lines[lineNum]; } //it returns the line according to lineNum parameter
			void ReadFile(const char *fileName);// readFile func gonna read all lines 
			int size() const { return sizeOfLines; } //size func return that how many lines read from file

			//overload functions
			const string operator [](int index) const; //it returns the line according to index
			CPUProgramDyn operator +(const string newLine);
			CPUProgramDyn &operator +=(const string newLine);
			CPUProgramDyn operator +(const CPUProgramDyn &secProg);
			bool operator ==(const CPUProgramDyn &secProg) { return (size() == secProg.size()); }
			bool operator !=(const CPUProgramDyn &secProg) { return (size() != secProg.size()); }
			bool operator <=(const CPUProgramDyn &secProg) { return (size() <= secProg.size()); }
			bool operator >=(const CPUProgramDyn &secProg) { return (size() >= secProg.size()); }
			bool operator <(const CPUProgramDyn &secProg) { return (size() < secProg.size()); }
			bool operator >(const CPUProgramDyn &secProg) { return (size() > secProg.size()); }
			friend ostream & operator <<(ostream &outputStream,const CPUProgramDyn &prog);
			CPUProgramDyn &operator --();
			CPUProgramDyn operator --(int);
			const CPUProgramDyn operator ()(int startIndex,int endIndex);

			//big three (assignment operator,copy constructor,destructor)
			CPUProgramDyn &operator =(const CPUProgramDyn &rightSide);
			CPUProgramDyn(const CPUProgramDyn &rightSide);
			~CPUProgramDyn();



	private:
			string *lines; //this string pointer for keep the lines
			int sizeOfLines; // keep the number of read lines
			int option; // entered opton
			
	};

}



#endif


/*############################################################################*/
/* 						       END OF CPUProgram.h                            */
/*############################################################################*/