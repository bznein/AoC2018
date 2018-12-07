#include <iostream>
#include "../../../stringent/stringent.h" /* Personal library, check on: https://github.com/bznein/stringent */
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

  while(nodes>0)
    {
      for (int i=0; i<26;++i)
        {
          /* Match found */
          if (exists[i] && dependencies[i].size()==0)
            {
              cout << static_cast<char>('A'+i);
              nodes--;
              exists[i]=false;
              for (auto& a : dependencies)
                {
                  auto pos=a.find(static_cast<char>('A'+i));
                  if (pos!=a.end())
                    {
                    a.erase(pos);
                    }
                }
              i=-1;
            }
        }
    }
  cout << endl;

}
