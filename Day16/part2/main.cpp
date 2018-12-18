#include <iostream>
#include <fstream>
#include "../../../stringent/stringent.h"
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
vector<vector<int>> manual;

int behaviour(int opcode, int a, int b, int c, std::vector<int> regBefore, std::vector<int> regAfter)
{
  vector<bool> tmp(16,false);
  /* Addr */
  if (regAfter[c]==regBefore[a]+regBefore[b])
    tmp[0]=true;
  /* Addi */
  if (regAfter[c]==regBefore[a]+b)
    tmp[1]=true;
  /* Mulr */
  if (regAfter[c]==regBefore[a]*regBefore[b])
    tmp[2]=true;
  /* muli */
  if (regAfter[c]==regBefore[a]*b)
    tmp[3]=true;
  /* banr */
  if (regAfter[c]==(regBefore[a]&regBefore[b]))
    tmp[4]=true;
  /* bani */
  if (regAfter[c]==(regBefore[a]&b))
    tmp[5]=true;
  /* borr */
  if (regAfter[c]==(regBefore[a]|regBefore[b]))
    tmp[6]=true;
  /* bori */
  if (regAfter[c]==(regBefore[a]|b))
    tmp[7]=true;
  /* setr */
  if (regAfter[c]==regBefore[a])
    tmp[8]=true;
  /* seti */
  if (regAfter[c]==a)
    tmp[9]=true;
  /*gtir*/
  if ((regAfter[c]==1 && a>regBefore[b]) || (regAfter[c]==0 && a<=regBefore[b]))
    tmp[10]=true;
  /*gtri*/
  if ((regAfter[c]==1 && regBefore[a]>b) || (regAfter[c]==0 && regBefore[a]<=b))
    tmp[11]=true;
  /*gtrr*/
  if ((regAfter[c]==1 && regBefore[a]>regBefore[b]) || (regAfter[c]==0 && regBefore[a]<=regBefore[b]))
    tmp[12]=true;
  /*eqir*/
  if ((regAfter[c]==1 && a==regBefore[b]) || (regAfter[c]==0 && a!=regBefore[b]))
    tmp[13]=true;
  /*eqri*/
  if ((regAfter[c]==1 && regBefore[a]==b) || (regAfter[c]==0 && regBefore[a]!=b))
    tmp[14]=true;
  /*eqrr*/
  if ((regAfter[c]==1 && regBefore[a]==regBefore[b]) || (regAfter[c]==0 && regBefore[a]!=regBefore[b]))
    tmp[15]=true;

  for (int i=0; i<16; ++i)
      if (tmp[i])
            manual[opcode][i]++;

}

void applyFunction(vector<int> & registers, int opcode, int a, int b, int c)
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

int main()
{
  auto ifs=ifstream("input.txt");
  int totRes=0;
  string s;
  manual=vector<vector<int>>(16,vector<int>(16,0));
  int prog=0;
  while (getline(ifs,s))
    {
      auto regBefore=stringent::explode(s,"Before:[,] ");
      vector<int> rb;
      for (auto c: regBefore)
        if (c.size()>0)
          rb.push_back(stoi(c));

      getline(ifs,s);
      auto cmd=stringent::explode(s," ");

      int op=stoi(cmd[0]);
      int regA=stoi(cmd[1]);
      int regB=stoi(cmd[2]);
      int res=stoi(cmd[3]);

      getline(ifs,s);
      auto regAfter=stringent::explode(s,"After:[,] ");

      vector<int> ra;
      for (auto c: regAfter)
        if (c.size()>0)
          ra.push_back(stoi(c));
      behaviour(op,regA,regB,res,rb,ra);
        getline(ifs,s);
        ++prog;

    }

  map<int,int> codes;


  for (auto it=manual.begin(); it!=manual.end();)
    {
      auto m=*it;
      if (std::count_if(m.begin(), m.end(),[](int n){return n>0;})==1)
        {
          int code=distance(m.begin(),std::find_if(m.begin(),m.end(),[](int n){return n>0;}));
          codes[distance(manual.begin(),it)]=code;
          for (auto & c : manual)
            c[code]=0;
          it=manual.begin();
          
        }
      else
        ++it;
    }


  auto ifs2= ifstream("input2.txt");

  vector<int> regs(4,0);
  while (getline(ifs2,s))
    {
      auto a=stringent::explode(s," ", [](string s){return stoi(s);});
      applyFunction(regs,codes[a[0]],a[1],a[2],a[3]);

    }
  cout << regs[0];
  cout << endl;
}     

