//CPU.h  header file

//if there is any library included before, dont include it again
#ifndef CPU_H

#define CPU_H

#include "Memory.h"

using namespace std;



//CPU class it takes the lines and execute the instructions
class CPU
{
public:
		CPU(int opt); //constructor for CPU
		CPU();
		void setReg(int index,int value); //setter registers func
		void setPC(int lineNum); //setter PC func
		int getPC() { return PC;} //getter for PC
		int getR(int index) { return R[index];} //getter for Reg
		int getOption() { return option; } //getter for option
		bool halted(); //halted return true when program halt
		bool execute(string line,Memory &myMemory); //execute func gonna execute all instructions

		void print(); //This func will print the registers 
	

private:
		int R[6]; //registers as int array
		int PC;	//PC keeps the current program line
		int ifhalted; //ifhalted will always 0,but its gonna be 1 when program halt
		int option; //option is variable that how user want to execute the program

		//this func gonna erase all comments
		string commentErase(string lines);
		//toupper gonna make all letter upper
		string toupper(string lines);
		//this func take a string and make it int 
		int stoi(string str);
		//this func gonna parse the line to the 3 strings
		void lineParser(string line,string &strCommand,string &str1,string &str2);
		//printout func print the registers by options
		void printOut(string command,char cont1,int firstInt,char comma,char cont2,int secInt,Memory &myMemory);
		//this controller func gonna control the stirngs for the forbidden char
		bool strController(string str);

		//these functions are going to do their own jobs
		bool MOV(string str1,string str2,int *Reg,Memory &myMemory);
		bool ADD(string str1,string str2,int *Reg,Memory &myMemory);
		bool SUB(string str1,string str2,int *Reg,Memory &myMemory);
		bool JMP(string str1,string str2,int *Reg,int &goLine,Memory &myMemory);
		bool JPN(string str1,string str2,int *Reg,int &goLine,Memory &myMemory);
		bool PRN(string str1,string str2,int *Reg,Memory &myMemory);

		//hlt program and print all registers
		bool HLT(Memory &myMemory);


};

#endif

/*############################################################################*/
/* 						       END OF CPU.h                                   */
/*############################################################################*/