#include <iostream>
#include "../../../stringent/stringent.h"  /* Personal library, check on: https://github.com/bznein/stringent */
#include <fstream>
#include <vector>
#include <set>

using namespace std;


inline int getIndex(char c)
{
  return c-'A';
}

int main()
{
  auto ifs=ifstream("input.txt");

  std::vector<std::set<char>> dependencies;
  std::vector<bool> exists (26,false);
  const int WORKERS=5;
  const int BASE_TIME=60;

  dependencies.resize(26);
  int nodes=0;

  std::string temp;
  while(getline(ifs,temp))
    {
      /* Personal explode function, see here: https://github.com/bznein/stringent/blob/master/stringent.h */
      auto l=stringent::explode(temp," ");
      if (!exists[getIndex(l[1][0])])
        nodes++;
      if (!exists[getIndex(l[7][0])])
        nodes++;
      exists[getIndex(l[1][0])]=true;
      exists[getIndex(l[7][0])]=true;
      dependencies[getIndex(l[7][0])].insert(l[1][0]);
    }

  vector<int> timeToWork(WORKERS,0);
  vector<int> workingOn(WORKERS,-1);

  int time=0;
  while(nodes>0)
    {
      /* For each worker */
      for (int i=0; i<WORKERS; ++i)
        /* If he is available */
        {
          if (timeToWork[i]==0)
            {
              /* Search for a node to work on */
              for (int k=0; k<26;++k)
                {
                  /* Match found */
                  if (exists[k] && dependencies[k].size()==0)
                    {
                      /* Put the worker on it */
                      timeToWork[i]=BASE_TIME+k+1;
                      workingOn[i]=k;
                      exists[k]=false;
                      break;
                    }
                }
            }
        }
      for (int i=0; i<WORKERS; ++i)
        {
          if (timeToWork[i]>0)
            {
              timeToWork[i]--;
              if (timeToWork[i]==0)
                {
                  nodes--;
                  /* Freeing up the tasks */
                  for (auto& a : dependencies)
                    {
                      auto pos=a.find(static_cast<char>('A'+workingOn[i]));
                      if (pos!=a.end())
                        {
                          a.erase(pos);
                        }
                    }
                }
            }
        }
      ++time;
    }
  cout << time << endl;
}
