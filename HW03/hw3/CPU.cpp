//includes for CPU.cpp

#include <iostream>
#include <string>
#include "CPU.h"

//CPU constructor will run when program start
//its gonna initialize the value of registers,PC and ifhalted
CPU::CPU(int opt)
{
	int i;
	int REG_SIZE=6;

	for(i=1; i<REG_SIZE; ++i) { setReg(i,0);}
	
	setPC(1);
	ifhalted=0;
	option=opt;
}

//setReg func gonna init registers 
void CPU::setReg(int index,int value)
{
	R[index]=value;
}

//setReg func gonna init PC
void CPU::setPC(int lineNum)
{
	PC=lineNum;
}

//ifhalted is true, halted func gonna return true
bool CPU::halted()
{
	if(ifhalted)
		return true;

	return false;
}

//execute func going to execute lines according to instruction
bool CPU::execute(string line)
{
	string command,str1,str2; //string types for read the lines inside them
	int goLine; //this variable for Jump func, it has the number of the line for jump
	bool res; // res variable for check the functions for return true or false

	//make all the characters upper and erase the comments
	line=toupper(line);
	line=commentErase(line);

	//parse the lines
	lineParser(line,command,str1,str2);

	//check is there any other char
	if(!strController(str1))
	{
		HLT();
		ifhalted=1;
		return false;
	}
	//check is there any other char
	if(!strController(str2))
	{
		HLT();
		ifhalted=1;
		return false;
	}

	goLine=-1;
	//check which command entered and call func
	if(command=="MOV")
		res=MOV(str1,str2,R);
	else if(command=="ADD")
		res=ADD(str1,str2,R);
	else if(command=="SUB")
		res=SUB(str1,str2,R);
	else if(command=="PRN")
		res=PRN(str1,str2,R);
	else if(command=="JMP")
	{	
		res=JMP(str1,str2,R,goLine);

		//we init the goLine as -1, so if its not -1 we have to jump
		if( res && goLine!=-1)
		{	//call the setPC func for set PC
			setPC(goLine);
		}
		else if(goLine==-1)
			goLine=-1; // mean nothing
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			HLT();
			ifhalted=1;
			return false;
		}
		
	}
	else if(command=="HLT")
	{
		res=HLT();
		ifhalted=1;
	}
	else
	{	
		cerr << "Unexpected Text File Format!" << endl;
		HLT();
		return false;
	}
	//if any instruction return false halt the program
	if(!res)
	{
		HLT();
		ifhalted=1;
	}

	//if we didnt jump anywhere ,so we keep on the lines
	if(goLine==-1)
	{
		setPC(PC+1);
	}

	return res;

}


//erase the comments after ';' character
string CPU::commentErase(string lines)
{
	int i;
	//loop for the find the ; char, and erase it
	for(i=0; i<=(int)lines.length(); ++i)
		if(lines[i]==';')
		{
			lines.erase(lines.begin()+i,lines.end());
		}
	return lines;
}

//make upper all letters
string CPU::toupper(string lines)
{
	int i;
	//loop for find just the letters and change it
	for(i=0; i<=(int)lines.length(); ++i)
		if(lines[i]>='a' && lines[i]<='z')
		{
			lines[i]-='a'-'A';
		}

	return lines;
}

//these func gonna parse the line to the strings
void CPU::lineParser(string line,string &strCommand,string &str1,string &str2)
{
	int const SIZEOFCOMMAND=3;
	string temp;
	size_t pos=-1,found=line.find_first_not_of(" 	");
	//parse the command string
	strCommand=line.substr(found,SIZEOFCOMMAND);

	pos=line.find(",");
	//if there is any comma ,so we have 3 strings
	if((int)pos!=-1)
	{
		str2=line.substr(pos+1);
		str1=line.substr(found+3,pos-found-3);
	}
	else//if there is no comma just we have 2 string
		str1=line.substr(found+3);

}
//this func gonna control the stings
bool CPU::strController(string str)
{
	size_t found;
	size_t found2=-1;
	string temp;
	int constant,digit=0;

	//if string is empty do nothing
	if(!str.empty())
	{
		found=str.find_first_not_of(" 	");
		//we re looking for the allowed characters and we check the characters after their position
		//it can be a  R or constant
		if(str[found]=='R' && found+2 < str.length())
		{
			temp=str.substr(found+2);
			found2=temp.find_first_not_of(" 	");
			if((int)found2!=-1)
			{
				cerr << "Unexpected Text File Format!" << endl;
				return false;
			}
		}
		else if(str[found]>='0' && str[found]<='9')
		{	
		
			constant=stoi(str);

			//we need to find how many digit constant have because we re gonna pass it all
			if(constant==0)
				digit=1;
			else if(constant/10==0)
				digit=1;
			else
			{
				while(constant/10!=0)
				{
					++digit;
					constant/=10;
				}
			}

		
			//if after the constant there is no character we need to stop there so we check the length either
			if(found+digit+1 < str.length())
			{
				temp=str.substr(found+digit+1);
				found2=temp.find_first_not_of(" 	");
				if((int)found2!=-1)
				{
					cerr << "Unexpected Text File Format!" << endl;
					return false;
				}

			}
			
		}
	}

	return true;
}


//stoi func gonna make a given string integer
int CPU::stoi(string str)
{
	int i,digNum=0,mult,res,constant;
	size_t found=str.find_first_not_of(" 	");

	for(i=(int)found; i<(int)str.length(); ++i)
	{	
		if(str[i]>='0' && str[i]<='9')
		 ++digNum;
	}
	i=0;
	mult=1;
	//this loop gonna power up like math library func(pow())
	while(i<digNum-1)
	{
		mult=mult*10;
		++i;
	}

	if(str[found]=='-')
		i=found+1;
	else
		i=found;
	res=0;
	//this loop add all integers
	while(i<(int)(digNum+found))
	{
		res=res+(str[i]-'0')*mult;
		mult/=10;
		++i;
	}
	//if there is - character this constant is negative
	if(str[found]=='-')
		constant=res*-1;
	else
		constant=res;

	return constant;

}

//this func gonna print the registers and memory
void CPU::printOut(string command,char cont1,int firstInt,char comma,char cont2,int secInt)
{
	int opt=getOption(); //get the which option entered
	

	//if there is any comma char we have just one content
	if(comma!=',' && opt==1)
	{
		cout << command << " " << cont1 << firstInt << "-"
		     << "R1=" << getR(1) << ",R2=" << getR(2) << ",R3=" << getR(3) << ",R4=" << getR(4) << ",R5=" << getR(5);
	}
	
	//if we have the comma char we have two content so print out
	if(comma==',' && opt==1)
	{
		cout << command << " " << cont1 << firstInt << comma << cont2 << secInt << "-"
		     << "R1=" << getR(1) << ",R2=" << getR(2) << ",R3=" << getR(3) << ",R4=" << getR(4) << ",R5=" << getR(5);
	}

	if(opt==1)
	{
		cout << " PC="<< getPC() << endl;
	}
	
}

//mov func can assign the register each other , or assign reg to adress
bool CPU::MOV(string str1,string str2,int *Reg)
{
	int firstReg,secReg,constant;
	int firstInt,secInt;
	char cont1,cont2;
	size_t found1=str1.find_first_not_of("	 ");
	size_t found2=str2.find_first_not_of("	 ");
	
	//we re looking for which contents entered for assignment
	if(str1[found1]=='R')
	{	
		firstReg=firstInt=str1[found1+1]-'0';
		cont1='R'; //this is for print out func
		if(str2[found2]=='R')
		{	//reg to reg assignment
			cont2='R'; //this is for print out func
			secReg=secInt=str2[found2+1]-'0';
			Reg[secReg]=Reg[firstReg];
		}	
		else if((str2[found2]>='0' && str2[found2]<='9') || str2[found2]=='-')
		{	// reg to constant assignment
			cont2='\0';
			constant=secInt=stoi(str2);
			Reg[firstReg]=constant;
		}
		else
		{	
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
	}
	else
	{	
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}
	//at last print the all contents if the opt==1
	printOut("MOV",cont1,firstInt,',',cont2,secInt);

	return true;
}


//this func gonna add the things(reg to reg,value of adress to reg) 
bool CPU::ADD(string str1,string str2,int *Reg)
{
	int firstReg,secReg,constant;
	int firstInt,secInt;
	char cont1,cont2;
	size_t found1=str1.find_first_not_of("	 ");
	size_t found2=str2.find_first_not_of("	 ");

	//we re looking for which contents entered for assignment
	if(str1[found1]=='R')
	{	
		firstReg=firstInt=str1[found1+1]-'0';
		cont1='R';
		if(str2[found2]=='R')
		{	
			cont2='R';
			secReg=secInt=str2[found2+1]-'0';
			Reg[firstReg]+=Reg[secReg];
		}
		else if((str2[found2]>='0' && str2[found2]<='9') || str2[found2]=='-')
		{	cont2='\0';
			constant=secInt=stoi(str2);
			Reg[firstReg]+=constant;
		}
		else
		{	
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}

	}
	else
	{	
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}
	//at last print the all contents if the opt=1
	printOut("ADD",cont1,firstInt,',',cont2,secInt);

	return true;
}

bool CPU::SUB(string str1,string str2,int *Reg)
{
	int firstReg,secReg,constant;
	int firstInt,secInt;
	char cont1,cont2;
	size_t found1=str1.find_first_not_of("	 ");
	size_t found2=str2.find_first_not_of("	 ");

	//we re looking for which contents entered for assignment
	if(str1[found1]=='R')
	{	
		firstReg=firstInt=str1[found1+1]-'0';
		cont1='R';
		if(str2[found2]=='R')
		{	
			cont2='R';
			secReg=secInt=str2[found2+1]-'0';
			Reg[firstReg]-=Reg[secReg];
		}
		else if((str2[found2]>='0' && str2[found2]<='9') || str2[found2]=='-')
		{	
			cont2='\0';
			constant=secInt=stoi(str2);
			Reg[firstReg]-=constant;
		}
		else
		{	
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}

	}
	else
	{	
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}
		//at last print the all contents if the opt=1
	printOut("SUB",cont1,firstInt,',',cont2,secInt);

	return true;
}
//jmp func gonna jmp to entered line if the register is zero
bool CPU::JMP(string str1,string str2,int *Reg,int &goLine)
{
	int firstReg,constant;
	int firstInt,secInt;
	char cont1,cont2,comma;
	size_t found1=str1.find_first_not_of("	 ");
	size_t found2=str2.find_first_not_of("	 ");
	
	cont1=cont2='\0';
	if(str1[found1]=='R')
	{	
		firstReg=firstInt=str1[found1+1]-'0';
		cont1='R';
		comma=',';
		if(str2[found2]>='0' && str2[found2]<='9')
		{	//if R is zero update the goline variable
			constant=secInt=stoi(str2);
			
			if(Reg[firstReg]==0)
				goLine=constant;
		}
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}

	}//if there is just constant number update the goline
	else if(str1[found1]>='0' && str1[found1]<='9')
		goLine=firstInt=stoi(str1);
	else
	{
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}
	//at last print the all contents if the opt=1
	printOut("JMP",cont1,firstInt,comma,cont2,secInt);

	return true;
}

//prn func is print the constant, register or value of an adress
bool CPU::PRN(string str1,string str2,int *Reg)
{
	int firstReg,constant;
	int firstInt,secInt=0;
	char cont1,cont2,comma='\0';
	size_t found=str1.find_first_not_of("	 ");
	
	cont1=cont2='\0';
	if(str1[found]=='R')
	{
		firstReg=str1[found+1]-'0';
		firstInt=Reg[firstReg];
		cout << Reg[firstReg] <<endl;
	}
	else if(str1[found]>='0' && str1[found]<='9')
	{
		constant=firstInt=stoi(str1);
		cout << constant <<endl;
	}
	else
	{
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}


	printOut("PRN",cont1,firstInt,comma,cont2,secInt);


	return true;
}

//halt func gonna finish the program and print the all things
bool CPU::HLT()
{
	int i;
	int const REG_SIZE=6;

	for(i=1; i<REG_SIZE; ++i)
	{
		cout << "R" << i << "=" << getR(i);
		if(i!=REG_SIZE-1)
				cout <<",";
	}

	cout << " PC=" << getPC() <<endl;

	return true;
}

/*############################################################################*/
/* 						       END OF CPU.cpp                                 */
/*############################################################################*/