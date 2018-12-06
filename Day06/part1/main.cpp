#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <map>
#include <tuple>
using namespace std;
using coords=pair<int,int>;
using corners=tuple<int,int,int,int>;

int manhattanDistance(coords c1, coords c2)
{
  return std::abs(c1.first-c2.first)+std::abs(c1.second-c2.second);
}

/* Given a coordinate and a set of coordinates, returns the
   number of integer coords closest to c than to any other point */
int getClosestArea(coords c, std::vector<coords> m, corners t, int border)
{
  int area=0;

  /* Loop the box */
  for (int x=std::get<0>(t)-border; x<=std::get<2>(t)+border; x++)
    for (int y=std::get<1>(t)-border; y<=std::get<3>(t)+border; ++y)
      {
        int candidateDistance=manhattanDistance(c,coords(x,y));
        bool closest=true;
        for (auto p:m)
          {
            if (p!=c && manhattanDistance(p,coords(x,y))<=candidateDistance)
              {
                closest=false;
                break;
              }
          }
        if (closest)
          area++;
      }
  return area;

}

int main()
{
  std::vector<coords> m;
  corners box;
  auto ifs=ifstream("input.txt");
  int minX=std::numeric_limits<int>::max(), maxX=-1;
  int minY=std::numeric_limits<int>::max(), maxY=-1;
  std::string line;
  while (getline(ifs,line))
    {
      int a=std::stoi(line.substr(0,line.find(',')));
      int b=std::stoi(line.substr(line.find(' ')+1));
      minX=std::min(minX,a);
      minY=std::min(minY,b);
      maxX=std::max(maxX,a);
      maxY=std::max(maxY,b);

      m.emplace_back(coords(a,b));
    }
  box=corners(minX,minY,maxX,maxY);
  int largestFiniteArea=0;
  for (auto c : m)
    {
      int tmpArea=getClosestArea(c,m,box,0);
      if (tmpArea==getClosestArea(c,m,box,1))
        largestFiniteArea=std::max(largestFiniteArea,tmpArea);
    }
  cout << largestFiniteArea << endl;
}
