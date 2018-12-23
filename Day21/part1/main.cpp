#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include "../../../stringent/stringent.h"


using namespace std;

const int REGS = 6;

map<string,int> opcodes
{
  {"addr",0},
  {"addi",1},
  {"mulr",2},
  {"muli",3},
  {"banr",4},
  {"bani",5},
  {"borr",6},
  {"bori",7},
  {"setr",8},
  {"seti",9},
  {"gtir",10},
  {"gtri",11},
  {"gtrr",12},
  {"eqir",13},
  {"eqri",14},
  {"eqrr",15},
    };

void applyFunction(vector<long long> & registers, int opcode, int a, int b, int c)
{
  switch (opcode)
    {
    case 0:
      registers[c]=registers[a]+registers[b];
      break;
    case 1:
      registers[c]=registers[a]+b;
      break;
    case 2:
      registers[c]=registers[a]*registers[b];
      break;
    case 3:
      registers[c]=registers[a]*b;
      break;
    case 4:
      registers[c]=(registers[a]&registers[b]);
      break;
    case 5:
      registers[c]=(registers[a]&b);
      break;
    case 6:
      registers[c]=(registers[a]|registers[b]);
      break;
    case 7:
      registers[c]=(registers[a]|b);
      break;
    case 8:
      registers[c]=registers[a];
      break;
    case 9:
      registers[c]=a;
      break;
    case 10:
      registers[c]=(a>registers[b]);
      break;
    case 11:
      registers[c]=(registers[a]>b);
      break;
    case 12:
      registers[c]=(registers[a]>registers[b]);
      break;
    case 13:
      registers[c]=(a==registers[b]);
      break;
    case 14:
      registers[c]=(registers[a]==b);
      break;
    case 15:
      registers[c]=(registers[a]==registers[b]);
      break;
    }
  
}

const int REGZERO_INSTRUCTION=28;


int main()
{
	int last_reg4=0;
	auto ifs = ifstream("input.txt");
	std::vector<long long> registers(REGS,0);
	int ip=0;
	int ip_address=-1;

	string s;
	getline(ifs,s);
	auto a=stringent::explode(s," ");
	ip_address=stoi(a[1]);
	vector<string> commands;
	while (getline(ifs,s))
	  commands.push_back(s);

	int n_commands=0;
	while (ip>=0 && ip<commands.size())
	{
	   registers[ip_address]=ip;
	   auto a=stringent::explode(commands[ip]," ");
	   applyFunction(registers,opcodes[a[0]],stoi(a[1]),stoi(a[2]),stoi(a[3]));
	   ip=registers[ip_address];
	   if (ip==REGZERO_INSTRUCTION)
	   {
	       cout << registers[4] << endl;
	       return 0;
	   }
	++ip;
	}
}

