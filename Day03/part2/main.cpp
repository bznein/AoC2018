#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

using coords = pair<int,int>;

int main()
{
  auto ifs = ifstream("input.txt");

  int overlap=0;
  std::map<coords,int> m;
  std::map<int,bool> claims;
  std::string temp;
  int i,j,a,b;
  int index=1;
  while (ifs >> temp)
    {
      ifs >> temp >> temp;
       i=std::stoi(temp.substr(0,temp.find(",")));
       j=std::stoi(temp.substr(temp.find(",")+1,temp.find(":")));
       ifs >> temp;
       int a=std::stoi(temp.substr(0,temp.find("x")));
       int b=std::stoi(temp.substr(temp.find("x")+1));

       for (int k=0; k<a; ++k)
         for (int l=0; l<b; ++l)
           if(m.find(coords(i+k,j+l))==m.end())
               m[coords(i+k,j+l)]=(index);
           else
             claims[index]=claims[m[coords(i+k,j+l)]]=true;

      ++index;
 
    }
  for (int i=1; i<index; ++i)
    if (claims.find(i)==claims.end())
      cout << i << endl;

}
