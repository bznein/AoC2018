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


std::tuple<coords,int> getMaxPower(const map<coords,int>& powers, int square_size, map<coords,int>& totSquarePowers)
{
  int largestTotalPower=-std::numeric_limits<int>::max();

  coords maxCoords;
  for (int i=1; i<=GRID_SIZE-square_size+1; ++i)
    for (int j=1; j<=GRID_SIZE-square_size+1; ++j )
      {
        coords c(i,j);
        /* If square_size is 1, we have to populate totSquarePowers
         with the base powers */
        if (square_size==1)
          totSquarePowers[c]=powers.at(c);
        else
          {
            /* Otherwise we just have to increase its totSquarePowers with the
               other two sides of the square */
            int tempSum=0;
            for (int k=0; k<square_size-1; ++k)
              {
                tempSum+=powers.at(coords(i+square_size-1,j+k));
                tempSum+=powers.at(coords(i+k,j+square_size-1));
              }
            tempSum+=powers.at(coords(i+square_size-1,j+square_size-1));
            totSquarePowers[c]+=tempSum;
            if (totSquarePowers[c]>largestTotalPower)
              {
                largestTotalPower=totSquarePowers[c];
                maxCoords=c;
              }
          }
      }
  return std::tuple(maxCoords,largestTotalPower);
}

int main()
{
  map<coords,int> powers;
  map<coords,int> totSquarePowers;
  for (int i=1; i<=GRID_SIZE; ++i)
    for (int j=1; j<=GRID_SIZE; ++j)
      {
        powers[coords(i,j)]=getPowerLevel(coords(i,j));
      }
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
      if (!(i%10))
      cout << "Computed for square of size: " << i << endl;
    }

  cout << maxC.first << "," << maxC.second << ","  << best_size << endl;
}
