
#include <iostream>
#include <fstream>
#include <map>


std::map<int,bool> freq;
int totFrequency=0;

bool parseInput()
{
  auto ifS = std::ifstream("input.txt");
 int tmp;


  while(ifS >> tmp)
    {
     
      totFrequency+=tmp;
      if (freq.find(totFrequency) != freq.end())
        {
          std::cout << totFrequency << std::endl;
          return true;
        }
      freq[totFrequency]=true;
    }
  return false;

}


int main()
{
  freq[0]=true;
  for(;!parseInput(););

}
