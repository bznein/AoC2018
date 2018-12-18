#include <iostream>
#include <fstream>
#include <limits>
#include <list>
#include <vector>
#include "../../stringent/stringent.h"


using namespace std;
const int WATERX=500;
const int WATERY=0;
int minX, maxX, minY, maxY;
int totWater=1;

using coords=pair<int,int>;
bool isWater(const vector<vector<char>>& cave, int i, int j)
{
  return cave[i][j]=='|' || cave[i][j]=='~';
}
bool isWater(const vector<vector<char>>& cave,coords c)
{
  return isWater(cave,c.first,c.second);
}



bool isStill(const vector<vector<char>>& cave, int i, int j)
{
  return cave[i][j]=='~';
}
bool isStill(const vector<vector<char>>& cave,coords c)
{
  return isStill(cave,c.first,c.second);
}

bool isRunning(const vector<vector<char>> &cave, int i, int j)
{
  return cave[i][j]=='|';
}
bool isRunning(const vector<vector<char>>& cave,coords c)
{
  return isRunning(cave,c.first,c.second);
}

bool isWall(const vector<vector<char>> cave, int i, int j)
{
  return cave[i][j]=='#';
}
bool isWall(const vector<vector<char>>& cave,coords c)
{
  return isWall(cave,c.first,c.second);
}

bool isBounded(const vector<vector<char>>& cave,int i, int j)
{
  /* Left Bounded */
  int k=j;
  do
    {
      k--;
      if (cave[i+1][k]=='.' || j<minX)
        return false;

    } while (cave[i][k]!='#');
  /* Right Bounded */
  k=j;
  do
    {
      k++;
      if (cave[i+1][k]=='.' || j>maxX)
        return false;

    } while (cave[i][k]!='#');
  return true;
}



int countFlood(const vector<vector<char>> & cave, bool still=false)
{
  int tot=0;
   for (int i=minY; i<=maxY; ++i)
    for (int j=minX-1; j<=maxX+1; ++j)
      if (still && isStill(cave,i,j) && isBounded(cave,i,j))
          tot++;
      else if (!still && isWater(cave,i,j))
        tot++;
   return tot;
}
void printCave(const vector<vector<char>> & cave, coords el=coords(-1000,-1000))
{
  for (int i=minY-1; i<=maxY+1; ++i)
    {
    for (int j=minX-1; j<=maxX+1; ++j)
      if (i==WATERY && j==WATERX)
        cout << "+";
      else
        if(i==el.first && j==el.second)
          cout << "C";
    else
      cout << cave[i][j];
    cout << endl;
      }
  cout << endl << endl<< endl << endl << endl << endl;
}


bool hasFlooded(const vector<vector<char>> & cave, int i, int j)
{
  for (int k=j; k>minX; k--)
    {
    if (cave[i][k]=='#')
             return false;
    if (cave[j][k]=='|')
      break;

    }
  for (int k=j; k<maxX; k++)
    {
    if (cave[i][k]=='#')
             return false;
    if (cave[j][k]=='|')
      break;

    }
  return true;
}
int nn=0;
void flood(vector<vector<char>> &cave, int i, int j, char c)
{
  if (cave[i][j]=='#' || cave[i][j]=='~' || i>maxY)
    return;
  if (!isWater(cave,i,j) && (c=='~' || c=='|'))
    totWater++;
  cave[i][j]=c;


  if (cave[i+1][j]=='.')
    {
      cave[i][j]='|';
    return flood(cave,i+1,j,'|');
    }
  if (cave[i][j]=='|' && cave[i+1][j]=='~' && !isBounded(cave,i+1,j))
    return;
  cave[i][j]='~';
  flood(cave,i,j+1,'~');
  flood(cave,i,j-1,'~');
  if (isBounded(cave,i,j) && isRunning(cave,i-1,j))
    flood(cave,i-1,j,'|');
}



int main()
{
  auto ifs = ifstream("input.txt");

  minX=minY=numeric_limits<int>::max();
  maxX=maxY=-minX;
  vector<vector<char>> cave(3000,vector<char>(3000,'.'));
  string s;
  while (getline(ifs,s))
    {
      if (s[0]=='x')
        {
          /* Vertical slice */
          auto a=stringent::explode(stringent::explode(s,"y")[1],"=.");
          int x=stoi(stringent::explode(s,"x=,")[0]);
          minX=min(x,minX);
          maxX=max(x,maxX);
          int y1=stoi(a[0]),y2=stoi(a[1]);
          minY=min(y1,minY);
          maxY=max(y2,maxY);
          for (int i=y1; i<=y2; ++i)
            {
              cave[i][x]='#';
            }
        }
      if (s[0]=='y')
        {
          /* Horizontal slice */
          auto a=stringent::explode(stringent::explode(s,"x")[1],"=.");
          int x=stoi(stringent::explode(s,"y=,")[0]);
          minY=min(x,minY);
          maxY=max(x,maxY);
          int y1=stoi(a[0]),y2=stoi(a[1]);
          minX=min(y1,minX);
          maxX=max(y2,maxX);
          for (int i=y1; i<=y2; ++i)
            {
              cave[x][i]='#';
            }

        }
    }
  cave[WATERY+1][WATERX]='|';

  bool keep=true;
  flood(cave,WATERY+1, WATERX, '|');
  cout << "TOTAL WATER: " << countFlood(cave) << endl;
  cout << "STILL WATER: " << countFlood(cave, true) << endl;

}
