//CPUProgram.h  header file

//if there is any library included before, dont include it again
#ifndef CPUPROGRAM_H

#define CPUPROGRAM_H


using namespace std;

//class for read the lines from file into string array and keep it
class CPUProgram
{
	
public:
		CPUProgram(const char *fileName); //constructor gonna call readfile func
		CPUProgram();
		string getLine(int lineNum) {return lines[lineNum]; } //it returns the line according to lineNum parameter
		int size() { return sizeOfLines; } //size func return that how many lines read from file

private:
		string lines[200]; //this string array for keep the lines
		int sizeOfLines; //this is for size func, size func gonna return it
		void ReadFile(const char *fileName);// readFile func gonna read all lines 

};

#endif

/*############################################################################*/
/* 						       END OF CPUProgram.h                            */
/*############################################################################*/