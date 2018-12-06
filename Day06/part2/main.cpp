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

int areaAtDistance(corners box, int threshold, std::vector<coords> m)
{
  int totArea=0;
  int minX=std::get<0>(box);
  int minY=std::get<1>(box);
  int maxX=std::get<2>(box);
  int maxY=std::get<3>(box);

  for (int x=minX-0; x<=maxX+0; ++x)
    for (int y=minY-0; y<=maxY+0; ++y)
      {
        int totDistance=0;
        bool close=true;
        for (auto c:m)
          {
            totDistance+=manhattanDistance(c,coords(x,y));
            if (totDistance>threshold)
              {
                close=false;
                break;
              }
          }
        if (close)
          totArea++;
      }
  return totArea;
}


int main()
{
  const int THRESH=10000;
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
  cout << areaAtDistance(box,THRESH,m) << endl;
}
