/*----------------------------------------------------------------------------*/
/* */
/* HW02_131044003_Talha_Oz */
/* */
/*                              main.cpp                                      */
/* ---------------------------------------------------------------------------*/
/* Created on 16/10/2016 by Talha_OZ */ 
/*____________________________________________________________________________*/




/*############################################################################*/
/*                                 Includes                                   */
/*############################################################################*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//this func gonna erase all comments
string commentErase(string lines);
//toupper gonna make all letter upper
string toupper(string lines);
//this func take a string and make it int 
int stoi(string str);
//this func gonna parse the line to the 3 strings
void lineParser(string line,string &strCommand,string &str1,string &str2);
//printout func print the registers and memory by options
void printOut(int opt,string command,char cont1,int firstInt,char comma,char cont2,int secInt,int *Reg,unsigned int *Adr);
//this controller func gonna control the stirngs for the forbidden char
bool strController(string str);

//these functions are going to do their own jobs
bool MOV(string str1,string str2,int opt,int *Reg,unsigned int *Adr);
bool ADD(string str1,string str2,int opt,int *Reg,unsigned int *Adr);
bool SUB(string str1,string str2,int opt,int *Reg,unsigned int *Adr);
bool JMP(string str1,string str2,int opt,int *Reg,unsigned int *Adr,int &goLine);
bool JPN(string str1,string str2,int opt,int *Reg,unsigned int *Adr,int &goLine);
bool PRN(string str1,string str2,int opt,int *Reg,unsigned int *Adr);

//he program and print all registers and memory
bool HLT(int *Reg,unsigned int *Adr);


//main func
int main(int argc, char const *argv[])
{
	int const ARRAY_SIZE=50;
	int const MAX_LINE=200;
	int R[6]={0,0,0,0,0,0}; //register as int array
	unsigned int Adr[ARRAY_SIZE];
	string line,empty,command,str1,str2; //string types for read the lines inside them
	fstream inputStream;
	bool res;
	int option,i,j,goLine,numbOfLines=0;

	//if there is any argument missing ,give out an error
	if(argc > 3 || argc < 3)
	{
		cerr << "Unexpected Compile Type!" << endl;
		return 0;
	}

	//check the what opt entered
	if(argv[2][0]-'0'>=0 && argv[2][0]-'0'<=2)
		option=argv[2][0]-'0';
	else
	{
		cerr << "Unexpected Compile Option!" << endl;
		return 0;
	}

	//fill up the adress array with zero
	for(i=0; i<ARRAY_SIZE; ++i)	Adr[i]=0;

	
	inputStream.open(argv[1]);
	
	//this loop count the lines of input file
	while(getline(inputStream,empty))
		++numbOfLines;
	// if lines over the 200 , print an error and halt
	if(numbOfLines > MAX_LINE)
	{
		cerr << "Too Many Lines In Text File!" <<endl;
		return 0;
	}


	inputStream.close();
	inputStream.open(argv[1]);
	//loop for read the lines one by one
	do
	{
		getline(inputStream,line);
		
		//make all the characters upper and erase the comments
		line=toupper(line);
		line=commentErase(line);

		//parse the lines
		lineParser(line,command,str1,str2);

		//check is there any other char
		if(!strController(str1))
		{
			HLT(R,Adr);
			return 0;
		}
		
		if(!strController(str2))
		{
			HLT(R,Adr);
			return 0;
		}

		goLine=-1;
		//check which command entered and go to func
		if(command=="MOV")
			res=MOV(str1,str2,option,R,Adr);
		else if(command=="ADD")
			res=ADD(str1,str2,option,R,Adr);
		else if(command=="SUB")
			res=SUB(str1,str2,option,R,Adr);
		else if(command=="PRN")
			res=PRN(str1,str2,option,R,Adr);
		else if(command=="JMP" || command=="JPN")
		{	
			if(command=="JMP")
				res=JMP(str1,str2,option,R,Adr,goLine);
			else if(command=="JPN")
				res=JPN(str1,str2,option,R,Adr,goLine);

			if( res && goLine!=-1)
			{	
				//cout<< goLine <<endl;
				//every time we jump,close file and open again
				inputStream.close();
				inputStream.open(argv[1]);

				j=1;
				//then read some empty lines
				while(j<goLine)
				{
					getline(inputStream,empty);
					++j;
				}
			}
			else if(goLine==-1)
				goLine=-1; // mean nothing
			else
			{
				cerr << "Unexpected Text File Format!" << endl;
				HLT(R,Adr);
				return 0;
			}
			
		}
		else if(command=="HLT")
			res=true;
		else
		{	
			cerr << "Unexpected Text File Format!" << endl;
			HLT(R,Adr);
			return 0;
		}
		//we erase inside of older string
		line.erase(line.begin(),line.end());

	}while(command!="HLT" && res);

	//when program ends, halt
	HLT(R,Adr);

	inputStream.close();

	return 0;
}

//erase the comments after ';' character
string commentErase(string lines)
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
string toupper(string lines)
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
void lineParser(string line,string &strCommand,string &str1,string &str2)
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
bool strController(string str)
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
		//it can be a sharp, R or constant
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
		else if(str[found]=='#' || (str[found]>='0' && str[found]<='9'))
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

			if(str[found]=='#')
			{	
				temp=str.substr(found+digit+1);
				found2=temp.find_first_not_of(" 	");
				if((int)found2!=-1)
				{
					cerr << "Unexpected Text File Format!" << endl;
					return false;
				}
			} //if after the constant there is no character we need to stop there so we check the length either
			else if(str[found]>='0' && str[found]<='9' && found+digit+1 < str.length())
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
int stoi(string str)
{
	int i,digNum=0,mult,res,constant;
	size_t found=str.find_first_not_of("# 	");

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
void printOut(int opt,string command,char cont1,int firstInt,char comma,char cont2,int secInt,int *Reg, unsigned int *Adr)
{
	int i,k=1;
	int const ARRAY_SIZE=50;

	//if there is any comma char we have just one content
	if(comma!=',' && opt==1)
	{
		cout << command << " " << cont1 << firstInt << "-"
		     << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}
	else if(comma!=',' && opt==2)
	{
		cout << command << " " << cont1 << firstInt << "-"
		     << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;

		for(i=0; i<ARRAY_SIZE; ++i) 
		{
			cout << "#" << i << "=" << Adr[i] ;
			if(i!=ARRAY_SIZE-1)
				cout <<",";

			if(i==10*k-1)
			{
				cout <<endl;
				++k;
			}
		}	
	}
	//if we have the comma char we have two content so print out
	if(comma==',' && opt==1)
	{
		cout << command << " " << cont1 << firstInt << comma << cont2 << secInt << "-"
		     << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}
	else if(comma==',' && opt==2)
	{
		cout << command << " " << cont1 << firstInt << comma << cont2 << secInt << "-"
		     << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;

		for(i=0; i<ARRAY_SIZE; ++i) 
		{
			cout << "#" << i << "=" << Adr[i] ;
			if(i!=ARRAY_SIZE-1)
				cout <<",";

			if(i==10*k-1)
			{
				cout <<endl;
				++k;
			}
		}	
	}
}

//mov func can assign the register each other , or assign reg to adress
bool MOV(string str1,string str2,int opt,int *Reg,unsigned int *Adr)
{
	int firstReg,secReg,adress,constant;
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
		}	// reg to adress assignment
		else if(str2[found2]=='#')
		{	
			cont2='#'; //this is for print out func
			adress=secInt=stoi(str2);
			if(adress<50) // if given adress over 50 print error
				Adr[adress]=Reg[firstReg];
			else
			{
				cerr << "Unexpected Text File Format!" << endl;
				return false;
			}
			
		}
		else if((str2[found2]>='0' && str2[found2]<='9') || str2[found2]=='-')
		{	// reg to constant assignment
			constant=secInt=stoi(str2);
			Reg[firstReg]=constant;
		}
		else
		{	
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
	}
	else if(str1[found1]=='#')
	{	
		adress=firstInt=stoi(str1);
		cont1='#'; //this is for print out func
		if(adress>=50)
		{	
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}

		if(str2[found2]=='R')
		{	// adress to reg assignment
			cont2='R';
			secReg=secInt=str2[found2+1]-'0';
			Reg[secReg]=Adr[adress];
		}
		else if((str2[found2]>='0' && str2[found2]<='9') || str2[found2]=='-')
		{	// adress to const assignment
			constant=secInt=stoi(str2);
			Adr[adress]=constant;		
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
	//at last print the all contents if the opt=1 or opt=2
	printOut(opt,"MOV",cont1,firstInt,',',cont2,secInt,Reg,Adr);

	return true;
}

//this func gonna add the things(reg to reg,value of adress to reg) 
bool ADD(string str1,string str2,int opt,int *Reg,unsigned int *Adr)
{
	int firstReg,secReg,adress,constant;
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
		else if(str2[found2]=='#')
		{	
			cont2='#';
			adress=secInt=stoi(str2);
			if(adress<50)
				Reg[firstReg]+=Adr[adress];
			else
			{
				cerr << "Unexpected Text File Format!" << endl;
				return false;
			}
			
		}
		else if((str2[found2]>='0' && str2[found2]<='9') || str2[found2]=='-')
		{
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
	//at last print the all contents if the opt=1 or opt=2
	printOut(opt,"ADD",cont1,firstInt,',',cont2,secInt,Reg,Adr);

	return true;
}

bool SUB(string str1,string str2,int opt,int *Reg,unsigned int *Adr)
{
	int firstReg,secReg,adress,constant;
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
		else if(str2[found2]=='#')
		{	
			cont2='#';
			adress=secInt=stoi(str2);
			if(adress<50)
				Reg[firstReg]-=Adr[adress];
			else
			{
				cerr << "Unexpected Text File Format!" << endl;
				return false;
			}
			
		}
		else if((str2[found2]>='0' && str2[found2]<='9') || str2[found2]=='-')
		{
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
		//at last print the all contents if the opt=1 or opt=2
	printOut(opt,"SUB",cont1,firstInt,',',cont2,secInt,Reg,Adr);

	return true;
}
//jmp func gonna jmp to entered line if the register is zero
bool JMP(string str1,string str2,int opt,int *Reg,unsigned int *Adr,int &goLine)
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
	else if(str2[found2]>='0' && str2[found2]<='9')
		goLine=firstInt=stoi(str1);
	else
	{
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}
	//at last print the all contents if the opt=1 or opt=2
	printOut(opt,"JMP",cont1,firstInt,comma,cont2,secInt,Reg,Adr);

	return true;
}

//jpn func is just like the jmp func but it wors only the register is zero or smaller
bool JPN(string str1,string str2,int opt,int *Reg,unsigned int *Adr,int &goLine)
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
		{	
			constant=secInt=stoi(str2);
			
			if(Reg[firstReg]<=0)
				goLine=constant;
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

	printOut(opt,"JPN",cont1,firstInt,comma,cont2,secInt,Reg,Adr);

	return true;
}
//prn func is print the constant, register or value of an adress
bool PRN(string str1,string str2,int opt,int *Reg,unsigned int *Adr)
{
	int firstReg,constant,adress;
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
	else if(str1[found]=='#')
	{
		adress=stoi(str1);
		if(adress<50)
		{
			firstInt=Adr[adress];
			cout << Adr[adress] <<endl;
		}
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
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


	printOut(opt,"PRN",cont1,firstInt,comma,cont2,secInt,Reg,Adr);


	return true;
}

//halt func gonna finish the program and print the all things
bool HLT(int *Reg,unsigned int *Adr)
{
	int i,k=1;
	int const MEMORY_SIZE=50;
	int const REG_SIZE=6;

	for(i=1; i<REG_SIZE; ++i)
	{
		cout << "R" << i << "=" << Reg[i];
		if(i!=REG_SIZE-1)
				cout <<",";
	}

	cout <<endl;

	for(i=0; i<MEMORY_SIZE; ++i) 
		{
			cout << "#" << i << "=" << Adr[i] ;
			if(i!=MEMORY_SIZE-1)
				cout <<",";

			if(i==10*k-1)
			{
				cout <<endl;
				++k;
			}
		}

	return true;
}

/*############################################################################*/
/* 						       END OF HW1                                     */
/*############################################################################*/