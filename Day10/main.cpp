#include "../../stringent/stringent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

using coords=pair<int,int>;
long long manhattanDistance(coords c1, coords c2)
{
  return std::abs(c1.first-c2.first)+std::abs(c1.second-c2.second);
}

class Point
{
public:

  Point(int a, int b, int c, int d): x(a), y(b), velX(c), velY(d){};
  int x,y;
  int velX,velY;
};

void advanceGrid(vector<Point> & grid, int n=1)
{
  for (auto& i: grid)
    {
      i.x+=i.velX*n;
      i.y+=i.velY*n;
    }
}

long long dispersion(const vector<Point> & grid)
{

  long long totDispersion=0;
  for (const auto & i: grid)
    {
      for (const auto & j: grid)
        totDispersion+=manhattanDistance(coords(i.x,i.y),coords(j.x,j.y));
    }
  return totDispersion;
}


void printGrid(const vector<Point> & grid)
{
  /* We get the corners */
  auto minmax_coordsX=std::minmax_element(grid.begin(), grid.end(), [](const Point &p1, const Point&p2){return p1.x<p2.x;});
  auto minmax_coordsY=std::minmax_element(grid.begin(), grid.end(), [](const Point &p1, const Point&p2){return p1.y<p2.y;});
  for (int j=minmax_coordsY.first->y; j<=minmax_coordsY.second->y; ++j)
    {
      for (int i=minmax_coordsX.first->x; i<=minmax_coordsX.second->x; ++i)
      {
        if (std::find_if(grid.begin(),grid.end(),[i,j](const Point &p){return p.x==i && p.y==j;})!=grid.end())
          cout << "#";
        else
          cout << ".";
      }
    cout << endl;
    }
}

void tempMinimum(std::vector<Point>& grid, int steps, int& seconds)
{

  long long disp, oldDispersion;
  
  disp=dispersion(grid);
  do
    {
      oldDispersion=disp;
      advanceGrid(grid,steps);
      disp=dispersion(grid);
      seconds+=steps;
    } while(disp<oldDispersion);
  advanceGrid(grid,-steps);
  seconds-=steps;
}

int main()
{
  auto ifs=ifstream("input.txt");
  vector<Point> grid;


  std::string temp;
  while(getline(ifs,temp))
    {
      /* Personal explode function, see here: https://github.com/bznein/stringent/blob/master/stringent.h */
      auto l=stringent::explode(temp,"<,>");
      grid.push_back(Point(stoi(l[1]),stoi(l[2]),stoi(l[4]),stoi(l[5])));
    }

  int seconds=0;
  int step=10000;
  while (step!=0)
    {
      tempMinimum(grid,step,seconds);
      step/=10;
    }
  printGrid(grid);
  cout << "------------------------------------------------\n";
  cout << seconds << endl;

  cout << "------------------------------------------------\n";
  cout << "If you don't see letters in the print above\nTry lowering the value of step by a factor of 10\n";
  cout << "------------------------------------------------\n";

 
}
