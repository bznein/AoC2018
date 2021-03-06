#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <limits>


using namespace std;
using coords=pair<int,int>;

const int GRID_SERIAL_NUMBER=5177;
const int SQUARE_SIZE=3;
const int GRID_SIZE=300;


int getRackId(coords c)
{
  return c.first+10;
}

int getPowerLevel(coords c)
{
  int base=getRackId(c);
  int level=base;
  level*=c.second;
  level+=GRID_SERIAL_NUMBER;
  level*=base;

  int hundred_number=level/100%10;
  return hundred_number-5;

}

int main()
{


  auto powers=vector<vector<int>>(GRID_SIZE,vector<int>(GRID_SIZE,0));
  int largestTotalPower=-std::numeric_limits<int>::max();

  int tempLowest;
  coords maxCoords;
  for (int i=1; i<=GRID_SIZE; ++i)
    for (int j=1; j<=GRID_SIZE; ++j)
      powers[i-1][j-1]=getPowerLevel(coords(i,j));

  for (int i=1; i<=GRID_SIZE-SQUARE_SIZE; ++i)
    for (int j=1; j<=GRID_SIZE-SQUARE_SIZE; ++j )
      {
        tempLowest=0;
        for (int k=0; k<SQUARE_SIZE; ++k)
          {
            for (int l=0; l<SQUARE_SIZE; ++l)
              {
                tempLowest+=powers[i+k-1][j+l-1];
              }
          }
        if (tempLowest>largestTotalPower)
          {
            largestTotalPower=tempLowest;
            maxCoords=coords(i,j);
          }
      }
  cout << maxCoords.first << "," << maxCoords.second << "\t " << largestTotalPower << endl;
}
