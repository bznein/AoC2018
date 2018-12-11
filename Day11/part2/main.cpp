#include <utility>
#include <vector>
#include <iostream>
#include <map>
#include <limits>


using namespace std;
using coords=pair<int,int>;

const int GRID_SERIAL_NUMBER=5177;
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

int getPowerLevel(int i, int j)
{
  return getPowerLevel(coords(i,j));
}


std::tuple<coords,int> getMaxPower(const vector<vector<int>>& powers, int square_size, vector<vector<int>>& totSquarePowers)
{
  int largestTotalPower=-std::numeric_limits<int>::max();

  coords maxCoords;
  for (int i=1; i<=GRID_SIZE-square_size; ++i)
    for (int j=1; j<=GRID_SIZE-square_size; ++j )
      {
        coords c(i,j);
        /* If square_size is 1, we have to populate totSquarePowers
         with the base powers */
        if (square_size==1)
          totSquarePowers[i-1][j-1]=powers[i-1][j-1];
        else
          {
            /* Otherwise we just have to increase its totSquarePowers with the
               other two sides of the square */
            int tempSum=0;
            for (int k=0; k<square_size-1; ++k)
              {
                tempSum+=powers[i-1+square_size-1][j+k-1];
                tempSum+=powers[i-1+k][j+square_size-1-1];
              }
            tempSum+=powers[i+square_size-1-1][j+square_size-1-1];
            totSquarePowers[i-1][j-1]+=tempSum;
            if (totSquarePowers[i-1][j-1]>largestTotalPower)
              {
                largestTotalPower=totSquarePowers[i-1][j-1];
                maxCoords=c;
              }
          }
      }
  return std::tuple(maxCoords,largestTotalPower);
}

int main()
{
  auto powers=vector<vector<int>>(GRID_SIZE,vector<int>(GRID_SIZE,0));
  auto totSquarePowers=vector<vector<int>>(GRID_SIZE,vector<int>(GRID_SIZE,0));
  for (int i=1; i<=GRID_SIZE; ++i)
    for (int j=1; j<=GRID_SIZE; ++j)
        powers[i-1][j-1]=getPowerLevel(coords(i,j));
  int max_power=-std::numeric_limits<int>::max();
  int best_size;
  coords maxC;
  for (int i=1; i<=GRID_SIZE; ++i)
    {
      if (auto [c,power]=getMaxPower(powers, i, totSquarePowers); power>max_power)
        {
          maxC=c;
          max_power=power;
          best_size=i;
        }
    }

  cout << maxC.first << "," << maxC.second << ","  << best_size << endl;
}
