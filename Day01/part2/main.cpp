
#include <iostream>
#include <fstream>
#include <map>

#include <vector>

std::map<int,bool> freq; /* Maps whether we already found this particular frequency */
int totFrequency=0;

bool parseInput(const std::vector<int> &v) /* Called every time we have to start the loop from scratch */
{

  for (auto tmp: v)
    {
        totFrequency+=tmp; /* Compute the frequency */
        if (freq.find(totFrequency) != freq.end()) /* If we already found this frequency one, output it and terminate */
          {
            std::cout << totFrequency << std::endl;
            return true;
          }
        freq[totFrequency]=true; /* Otherwise mark this frequency as found */
      }
  return false;

}


int main()
{
  freq[0]=true;
  auto ifs = std::ifstream("input.txt");
  std::vector<int> v;
  int tmp;
  while(ifs >> tmp)
    v.push_back(tmp);
  for(;!parseInput(v););

}
