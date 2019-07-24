#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


/* Returns true if the string s has at least one character appearing exactly o times */ 
bool exactOccurrence(const std::string& s, int o)
{
  for (auto c: s)
    {
      if (std::count(s.begin(),s.end(),c)==o) 
        return true;
    }
  return false;
}

int main()
{
  auto ifs=ifstream("input.txt");

  string s;
  int twoOccurr=0;
  int threeOccurr=0;
  while(ifs >> s)
    {
      twoOccurr+=exactOccurrence(s,2)?1:0;
      threeOccurr+=exactOccurrence(s,3)?1:0;
    }

  std::cout << twoOccurr * threeOccurr << std::endl;
}
