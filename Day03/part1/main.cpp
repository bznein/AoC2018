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
  std::string temp;
  int i,j,a,b;
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
           m[coords(i+k,j+l)]++;
 
    }


  for (auto const & [key,val] : m)
    {
      if (val>1)
        overlap++;
    }

  cout << overlap << endl;
}
