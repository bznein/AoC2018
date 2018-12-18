
#include <iostream>
#include <fstream>
#include <map>

#include <vector>

std::map<int,bool> freq;
int totFrequency=0;

bool parseInput(const std::vector<int> &v)
{

  for (auto tmp: v)
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
  auto ifs = std::ifstream("input.txt");
  std::vector<int> v;
  v.reserve(5000);
  int tmp;
  while(ifs >> tmp)
    v.push_back(tmp);
  for(;!parseInput(v););

}
