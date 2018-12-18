#include <iostream>
#include <fstream>
#include "../../../stringent/stringent.h"
#include <vector>
using namespace std;


map<int, string> codes;

int behaviour(int opcode, int a, int b, int c, std::vector<int> regBefore, std::vector<int> regAfter)
{

  int tot=0;

  /* Test each case */

  /* Addr */
  if (regAfter[c]==regBefore[a]+regBefore[b])
    ++tot;
  /* Addi */
  if (regAfter[c]==regBefore[a]+b)
  ++tot;
  /* Mulr */
  if (regAfter[c]==regBefore[a]*regBefore[b])
    ++tot;
  /* muli */
  if (regAfter[c]==regBefore[a]*b)
  ++tot;
  /* banr */
  if (regAfter[c]==(regBefore[a]&regBefore[b]))
    ++tot;
  /* bani */
  if (regAfter[c]==(regBefore[a]&b))
  ++tot;
  /* borr */
  if (regAfter[c]==(regBefore[a]|regBefore[b]))
    ++tot;
  /* bori */
  if (regAfter[c]==(regBefore[a]|b))
  ++tot;
  /* setr */
  if (regAfter[c]==regBefore[a])
    ++tot;
  /* seti */
  if (regAfter[c]==a)
  ++tot;

  /*gtir*/
  if ((regAfter[c]==1 && a>regBefore[b]) || (regAfter[c]==0 && a<=regBefore[b]))
    ++tot;
  /*gtri*/
  if ((regAfter[c]==1 && regBefore[a]>b) || (regAfter[c]==0 && regBefore[a]<=b))
    ++tot;

  /*gtrr*/
  if ((regAfter[c]==1 && regBefore[a]>regBefore[b]) || (regAfter[c]==0 && regBefore[a]<=regBefore[b]))
    ++tot;


  /*eqir*/
  if ((regAfter[c]==1 && a==regBefore[b]) || (regAfter[c]==0 && a!=regBefore[b]))
    ++tot;
  /*eqri*/
  if ((regAfter[c]==1 && regBefore[a]==b) || (regAfter[c]==0 && regBefore[a]!=b))
    ++tot;
  /*eqrr*/
  if ((regAfter[c]==1 && regBefore[a]==regBefore[b]) || (regAfter[c]==0 && regBefore[a]!=regBefore[b]))
    ++tot;






  return tot;

}

int main()
{
  auto ifs=ifstream("input.txt");
  int totRes=0;

  string s;
  while (getline(ifs,s))
    {
      auto regBefore=stringent::explode(s,"Before:[,] ");
      vector<int> rb;
      for (auto c: regBefore)
        if (c.size()>0)
        rb.push_back(stoi(c));

      getline(ifs,s);
      auto cmd=stringent::explode(s," ");

      int regA=stoi(cmd[1]);
      int regB=stoi(cmd[2]);
      int res=stoi(cmd[3]);

      getline(ifs,s);
      auto regAfter=stringent::explode(s,"After:[,] ");

      vector<int> ra;
      for (auto c: regAfter)
        if (c.size()>0)
        ra.push_back(stoi(c));

      if (behaviour(stoi(cmd[0]),regA,regB,res,rb,ra)>=3)
        totRes++;
      getline(ifs,s);

    }

  cout << totRes << endl;
}

