//Memory.h  header file

//if there is any library included before, dont include it again
#ifndef MEMORY_H

#define MEMORY_H


using namespace std;

// our memory class
class Memory
{
public:
	Memory(int option); // memory constructor
	Memory(); // memory constructor
	void setMem(int index,int value); // to set the values to the memory
	unsigned int getMem(int index) { return Adr[index]; } //return memory value that required
	void printAll(); //this func gonna print all memory


private:
	unsigned int Adr[50]; // making 50 unsigned int memory
	int opt; // our option which entered from terminal


};

#endif

/*############################################################################*/
/* 						       END OF CPU.h                                   */
/*############################################################################*/