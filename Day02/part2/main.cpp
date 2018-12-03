#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


bool differByOne(std::string s1, std::string s2)
{
  short totDiff=0;
  for (int i=0; i<s1.size(); ++i)
    {
      if (s1[i]!=s2[i])
        {
           totDiff+=1;
           if (totDiff==2)
             return false;
        }
    }
  return totDiff==1;
}

void printCommonLetters(std::string s1, std::string s2)
{
  for (int i=0; i<s1.size(); ++i)
    {
      if (s1[i]==s2[i])
        {
          cout << s1[i];
        }
    }
  cout << endl;
}

int main()
{
  auto ifs=ifstream("input.txt");

  string s;
  std::vector<string> ss;
  while(ifs >> s)
      ss.emplace_back(s);

  for (int i=0; i<ss.size(); ++i)
    for (int j=0; j<ss.size(); ++j)
      if (i!=j && differByOne(ss[i],ss[j]))
        {
        printCommonLetters(ss[i],ss[j]);
        break;
        }
}

