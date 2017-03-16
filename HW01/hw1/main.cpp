/*----------------------------------------------------------------------------*/
/* */
/* HW01_131044003_Talha_Oz */
/* */
/*                              main.cpp                                      */
/* ---------------------------------------------------------------------------*/
/* Created on 9/10/2016 by Talha_OZ */ 
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

//these functions re help to find errors and make their job
bool MOV(string line, size_t found,int *Reg,int opt);
bool ADD(string line, size_t found,int *Reg,int opt);
bool SUB(string line, size_t found,int *Reg,int opt);
bool JMP(string line, size_t found,int *Reg,int opt,int *goline);
bool PRN(string line, size_t found,int *Reg,int opt);

//this func make the lines understandable for the computer
bool lineProcessor(string line, size_t found,int *first,int *second,int *constant);
//this func take a string and make it int 
bool stoi(string line,int foundInt,int *constant);


//main func
int main(int argc, char *argv[])
{
	
	int R[6]={0,0,0,0,0,0}; //register as int array
	int i,j,flag,goLine;
	string line,empty; //string types for read the lines inside them
	char command[6][4]={"MOV","ADD","SUB","JMP","PRN","HLT"}; //commands as strings
	fstream inputStream;
	bool res;
	size_t found; //this variable for the .find func that we re gonna use for find the strings
	int const HLT=5;
	int option=0;

	//if there is any argument missing ,give out an error
	if(argc > 3)
	{
		cerr << "Too much compile argument!" << endl;
		return 0;
	}
	else if(argc < 3)
	{
		cerr << "Compile argument is missing!" << endl;
		return 0;
	}

	//check the what opt entered
	if(argv[2][0]-'0'==1)
		option=1;
	else if(argv[2][0]-'0'==0)
		option=option;
	else
	{
		cerr << "Unexpected Compile Command!" <<endl;
		return 0;
	}

	//loop for read the lines one by one
	inputStream.open(argv[1]);
	do
	{
		
		getline(inputStream,line);
	
		line=toupper(line);
		line=commentErase(line);


		flag=-1;
		found=-1;
		//look for the command inside the line that we have read
		for(i=0; i<6 && flag==-1; i++)
		{ 
			found=line.find(command[i]);
	
			if((int)found!=-1)
				flag=i;
		}

		if((int)found==-1)
			cerr << "Command NOT FOUND!" << endl;
		else
		{	
			switch(flag)
			{
				case 0: 
						res=MOV(line,found,R,option);
						break;

				case 1: res=ADD(line,found,R,option);
						break;

				case 2: res=SUB(line,found,R,option);
						break;

				case 3: if(JMP(line,found,R,option,&goLine) && goLine!=-1)
						{
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
							return false;
						}

						break;

				case 4: res=PRN(line,found,R,option);
						break;

			}
		}

		if(!res)
			return 0;
		//we erase inside of older string
		line.erase(line.begin(),line.end());

	}while(flag!=HLT);

	inputStream.close();
	//when program reach the Halt line print all the registers and exit
	cout << "R1=" << R[1] << ",R2=" << R[2] << ",R3=" << R[3] << ",R4=" << R[4] << ",R5=" << R[5]<<endl;
		 


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

//mov func for assign the new values to the registers and assign the registers each other
bool MOV(string line, size_t found,int *Reg,int opt)
{
	int firstReg=0;
	int secReg=0;
	int value=0;
	bool res;


	//we call this func for control every character
	//if there is any other letter inside the line print an error and exit
	res=lineProcessor(line, found, &firstReg, &secReg, &value);

	if(!res)
		return false;
	//value our constant number, if exist assign it to the read register
	if(value!=0)
	{
		Reg[firstReg]=value;
	}
	else // if constant doesnt exist so there is a register
		Reg[secReg]=Reg[firstReg];

	//if option 1, we have to print all registers
	if(opt==1 && value==0)
	{
		cout << "MOV R"<< firstReg <<",R" << secReg << "-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}
	else if(opt==1 && value!=0)
	{
		cout << "MOV R"<< firstReg << "," << value << "-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}

	return true;
}

//add func gonna add reg to reg or constant to reg
bool ADD(string line, size_t found,int *Reg,int opt)
{
	int firstReg=0;
	int secReg=0;
	int value=0;
	bool res;

	//we call this func for control every character
	//if there is any other letter inside the line print an error and exit
	res=lineProcessor(line, found, &firstReg, &secReg, &value);

	if(!res)
		return false;
	//value our constant number, if exist assign it to the read register
	if(value!=0)
	{
		Reg[firstReg]+=value;
	}
	else	// if constant doesnt exist so there is a register
		Reg[firstReg]+=Reg[secReg];

	//if option 1, we have to print all registers
	if(opt==1 && value==0)
	{
		cout << "ADD R"<< firstReg <<",R" << secReg << "-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}
	else if(opt==1 && value!=0)
	{
		cout << "ADD R"<< firstReg << "," << value << "-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}

	return true;
}

//sub func gonna substract reg from reg or constant from reg
bool SUB(string line, size_t found,int *Reg,int opt)
{
	int firstReg=0;
	int secReg=0;
	int value=0;
	bool res;


	//we call this func for control every character
	//if there is any other letter inside the line print an error and exit
	res=lineProcessor(line, found, &firstReg, &secReg, &value);

	if(!res)
		return false;
	//value our constant number, if exist assign it to the read register
	if(value!=0)
	{
		Reg[firstReg]=Reg[firstReg]-value;
	}
	else
		Reg[firstReg]=Reg[secReg]-Reg[firstReg];

	//if option 1, we have to print all registers
	if(opt==1 && value==0)
	{
		cout << "SUB R"<< firstReg <<",R" << secReg << "-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}
	else if(opt==1 && value!=0)
	{
		cout << "SUB R"<< firstReg << "," << value << "-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
	}

	return true;
}

//jmp func gonna go to line that user want
bool JMP(string line, size_t found,int *Reg,int opt,int *goLine)
{

	int i,j,k,foundReg,foundComma,flag;
	int regNum,constant;
	string str("JMPR0123456789, 	");
	size_t error;

	//we re gonna look for the characters but not the characters of str
	error=line.find_first_not_of(str);

	//if there is any forbidden char print an error
	if(error!=std::string::npos)
	{
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}

	//loop for pass the spaces before command
	k=0;
	while(k<(int)found)
	{	
		if(line[k]==' ' || line[k]=='\t')
			k=k;
		
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
		++k;
	}
	//loop for pass the spaces after command
	j=found+3;
	flag=0;
	while(j<(int)line.length())
	{
		if(line[j]==',')
			++flag;
		++j;
	}

	//After the command, we re gonna pass the spaces
	i=found+3;

	while(line[i]==' ' || line[i]=='\t')
		++i;

	foundReg=i;

	//After all passed spaces we find an R char which is our first reg
	//If there is no R so there has to be a constant number
	if(line[i]=='R' && flag)
		regNum=line[i+1]-'0';
	else if(line[i]!='R' && flag)
	{		
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}
	else
	{	//so we re looking for number with stoi func
		//if opt 1 print out all the line that we have
		if(stoi(line,i,&constant) && opt==1)
		{
			*goLine=constant;
			cout << "JMP "<< constant <<"-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
			return true;
		}// if option 0 just send to the constant to the main func,so program can jump
		else if(stoi(line,i,&constant) && opt==0)
		{
			*goLine=constant;
			return true;
		}
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}

	}

	//we plus with two because we re gonna continue after the first reg position
	foundReg=foundReg+2;
	while(line[foundReg]!=',' && foundReg<(int)line.length())
		++foundReg;

	if(line[foundReg]!=',')
	{	
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}

	foundComma=foundReg+1;
	//if there is a register it has to be zero for programme jump
	if(Reg[regNum]==0)
	{
		if(stoi(line,foundComma,&constant) && opt==1)
		{
			*goLine=constant;
			cout << "JMP "<< "R" << regNum << "," << constant <<"-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
		}
		else if(stoi(line,foundComma,&constant) && opt==0)
		{
			*goLine=constant;
			return true;
		}
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
	}
	else
	{
		*goLine=-1;
	}

	return true;
}

//prn func gonna print the register or a constant number
bool PRN(string line, size_t found,int *Reg,int opt)
{
	int i,k,foundReg,reg,constant;
	string str("PRNR0123456789 	");
	size_t error;
	//we re gonna look for the characters but not the characters of str

	error=line.find_first_not_of(str);
	//if there is any forbidden char print an error
	if(error!=std::string::npos)
	{
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}

	k=0;
	//loop for pass the spaces before command
	while(k<(int)found)
	{	
		if(line[k]==' ' || line[k]=='\t')
			k=k;
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
		++k;
	}

	//After the PRN command we pass the spaces
	i=found+3;

	while(line[i]==' ' || line[i]=='\t')
		++i;

	foundReg=i;

	
	//After all passed spaces we find a register
	
	if(line[i]=='R' && opt==0)
	{
		reg=line[i+1]-'0';
		cout << Reg[reg] << endl;
	}
	else if(line[i]=='R' && opt==1)
	{
		reg=line[i+1]-'0';
		cout << Reg[reg] << endl;
		cout << "PRN R"<< reg << "-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;

	}
	else //If there is no R char , there has to be a constant number
	{		
		if(stoi(line,foundReg,&constant))
		{
			cout << constant << endl;
			cout << "PRN "<< constant <<"-"
			 << "R1=" << Reg[1] << ",R2=" << Reg[2] << ",R3=" << Reg[3] << ",R4=" << Reg[4] << ",R5=" << Reg[5]<<endl;
		}
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
	}
	

	return true;

}

//stoi func gonna make a given string integer
bool stoi(string line,int foundInt,int *constant)
{
	int i,j;
	int flag,count,count2,mult,res,digNum,indis,exitt;
	int digit[200];//this is our array for read the numbers from string

	//loop for make the array all comp -1
	for(i=0; i<200; ++i) digit[i]=-1;
		
	count=0;
	flag=0;
	digNum=0;
	j=foundInt;
	//we start to searching from found int
	//loop gonna find the number characters and make them integer
	while(j<(int)line.length())
	{
		if(line[j]=='-')
			++flag;

		if(line[j]>='0' && line[j]<='9')
		{
			digit[count]=line[j]-'0';
			++digNum;
		}
		++count;
		++j;
	}
	
	if(digNum==0)
	{	
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}

	exitt=0;
	count2=0;
	//we re gonna control that all characters in order or not
	//if its not order print our an error
	for(i=0; i<200 && exitt==0; ++i)
	{
		if(digit[i]!=-1)
		{
			for(j=i; j<i+digNum; ++j)
			{
				if(digit[j]!=-1)
					count2++;
			}

			if(digNum!=count2)
			{	
				cerr << "Unexpected Text File Format!" << endl;
				return false;
			}
			else
			{
				indis=i;
				exitt++;
			}
		}
	}
	

	i=0;
	mult=1;
	//this loop gonna power up like math library func(pow())
	while(i<digNum-1)
	{
		mult=mult*10;
		++i;
	}

	res=0;
	i=0;
	//this loop add all integers
	while(i<digNum)
	{
		res=res+digit[indis]*mult;
		mult/=10;
		++i;
		++indis;
	}

	//we use the flag before for if user enter a negative integer we have to make the integer negative
	if(flag==1)
	{
		res*=-1;
		*constant=res;
	}
	else
		*constant=res;



	return true;
}

//this func process our read lines ,search for forbidden char
bool lineProcessor(string line, size_t found,int *first,int *second,int *constant)
{
	int i,k,foundReg,foundComma,constNumb,flag2;
	string str("MOVADDSUBR0123456789,- 	");
	size_t error;
	//we re gonna look for the characters but not the characters of str
	error=line.find_first_not_of(str);

	//if there is any forbidden char print an error
	if(error!=std::string::npos)
	{
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}

	
	k=0;
	//loop for pass the spaces before command
	while(k<(int)found)
	{	
		if(line[k]==' ' || line[k]=='\t')
			k=k;
		
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
		++k;
	}

	//After the command we pass the spaces
	i=found+3;

	while(line[i]==' ' || line[i]=='\t')
		++i;

	foundReg=i;

	//After all passed spaces we find an R char which is our first reg
	//If there is no R char before the comma print out an error message
	if(line[i]=='R')
		*first=line[i+1]-'0';
	else
	{		
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}

	//we plus with two because we re gonna continue after the first reg position
	foundReg=foundReg+2;
	while(line[foundReg]!=',' && foundReg<(int)line.length())
		++foundReg;

	if(line[foundReg]!=',')
	{	
		cerr << "Unexpected Text File Format!" << endl;
		return false;
	}

	foundComma=foundReg+1;
	//we re look for second register so passing the spaces
	while(line[foundComma]!='R' && foundComma<(int)line.length())
		++foundComma;
	
	flag2=0;
	//if found char is R assign it
	if(line[foundComma]=='R' && foundComma+1<(int)line.length())
	{
		*second=line[foundComma+1]-'0';
		
		flag2++;

	}
	else
	{	// if there is no R char then it has to be constant numb
		if(stoi(line,foundReg,&constNumb))
			*constant=constNumb;
		else
		{
			cerr << "Unexpected Text File Format!" << endl;
			return false;
		}
	}



	return true;

}

/*############################################################################*/
/* 						       END OF HW1                                     */
/*############################################################################*/