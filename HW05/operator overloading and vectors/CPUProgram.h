//CPUProgram.h  header file

//if there is any library included before, dont include it again
#ifndef CPUPROGRAM_H

#define CPUPROGRAM_H

#include <vector>

using namespace std;

//class for read the lines from file into string array and keep it
class CPUProgram
{
	
public:
		explicit CPUProgram(const char *fileName); //constructor gonna call readfile func
		CPUProgram(int opt);
		CPUProgram(vector <string> &temp);
		CPUProgram();
		string getLine(int lineNum) const {return lines[lineNum]; } //it returns the line according to lineNum parameter
		void ReadFile(const char *fileName);// readFile func gonna read all lines 
		int size() const { return lines.size(); } //size func return that how many lines read from file

		//overload functions
		const string operator [](int index) const; //it returns the line according to index
		CPUProgram operator +(const string newLine);
		CPUProgram &operator +=(const string newLine);
		CPUProgram operator +(const CPUProgram &secProg);
		bool operator ==(const CPUProgram &secProg) { return (size()==secProg.size()); }
		bool operator !=(const CPUProgram &secProg) { return (size()!=secProg.size()); }
		bool operator <=(const CPUProgram &secProg) { return (size()<=secProg.size()); }
		bool operator >=(const CPUProgram &secProg) { return (size()>=secProg.size()); }
		bool operator <(const CPUProgram &secProg) { return (size()<secProg.size()); }
		bool operator >(const CPUProgram &secProg) { return (size()>secProg.size()); }
		friend ostream & operator <<(ostream &outputStream,const CPUProgram &prog);
		CPUProgram &operator --();
		CPUProgram operator --(int);
		CPUProgram operator ()(int startIndex,int endIndex);


private:
		vector <string> lines; //this vector string for keep the lines
		int option;
		

};



#endif


/*############################################################################*/
/* 						       END OF CPUProgram.h                            */
/*############################################################################*/