#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <utility>
#include <algorithm>
#include <iomanip>

using namespace std;

using coords=pair<int,int>;

int minI, maxI, minJ, maxJ;
map<coords,char> maze;


coords N(const coords c)
{
  return coords(c.first-1,c.second);
}

coords S(const coords c)
{
  return coords(c.first+1,c.second);
}

coords W(const coords c)
{
  return coords(c.first,c.second-1);
}

coords E(const coords c)
{
  return coords(c.first,c.second+1);
}

pair<int,coords>  createRoute(const string &s, coords c, int i)
{
  coords curCords=c;
  switch (s[i])
    {
    case '$':
      return pair<int,coords>(i,curCords);
    case 'N':
      curCords=N(curCords);
      maze[curCords]='-';
      maze[E(curCords)]=maze[W(curCords)]='#';
      curCords=N(curCords);
      maze[curCords]='.';
      minI=min(minI,curCords.first);
      minJ=min(minJ,curCords.second-1);
      maxJ=max(maxJ,curCords.second+1);
      return createRoute(s,curCords,i+1);
      break;
    case 'S':
      curCords=S(curCords);
      maze[curCords]='-';
      maze[E(curCords)]=maze[W(curCords)]='#';
      curCords=S(curCords);
      maze[curCords]='.';
      maxI=max(maxI,curCords.first);
      minJ=min(minJ,curCords.second-1);
      maxJ=max(maxJ,curCords.second+1);
      return createRoute(s,curCords,i+1);
      break;
    case 'W':
      curCords=W(curCords);
      maze[curCords]='|';
      maze[N(curCords)]=maze[S(curCords)]='#';
      curCords=W(curCords);
      maze[curCords]='.';
      minJ=min(minJ,curCords.second);
      minI=min(minI,curCords.first-1);
      maxI=max(maxI,curCords.first+1);
      return createRoute(s,curCords,i+1);
      break;
    case 'E':
      curCords=E(curCords);
      maze[curCords]='|';
      maze[N(curCords)]=maze[S(curCords)]='#';
      curCords=E(curCords);
      maze[curCords]='.';
      maxJ=max(maxJ,curCords.second);
      minI=min(minI,curCords.first-1);
      maxI=max(maxI,curCords.first+1);
      return createRoute(s,curCords,i+1);
      break;
    case '|':
      return pair<int,coords>(i,curCords);
    case ')':
      return pair<int,coords>(i,curCords);
    case '(':
      vector<pair<int,coords>> v;
      auto j=createRoute(s,curCords,i+1);
      v.push_back(j);
      while (s[j.first]!=')')
        {
          j=createRoute(s,curCords,j.first+1);
          v.push_back(j);
        }
      for (auto a: v)
        return createRoute(s,a.second,j.first+1);



    }
}

void setMaze()
{
  for (int i=minI; i<=maxI; ++i)
      for (int j=minJ; j<=maxJ; ++j)
          if (maze.find(coords(i,j))==maze.end())
              maze[coords(i,j)]='#';
}
map<char,int> mm{
  {'.',-1},
    {'-',-2},
      {'|',-3},
        {'#',-4},
          };
bool isNeighborTrace(const vector<vector<int>>& m, coords from, coords to)
{

  if (to.first<minI || to.second<minJ || from.first<minI || from.second <minJ)
    return false;
  if (to.first>=maxI || to.second>=maxJ || from.first>=maxI || from.second>=maxJ )
    return false;

  if (from.first-2==to.first && from.second==to.second &&  m[to.first-minI][to.second-minJ]==mm['.'] &&  m[from.first-1-minI][from.second-minJ]==mm['-'])
    return true;
  if (from.first+2==to.first && from.second==to.second && m[to.first-minI][to.second-minJ]==mm['.'] &&  m[from.first+1-minI][from.second-minJ]==mm['-'])
    return true;
  if (from.first==to.first && from.second-2==to.second &&  m[to.first-minI][to.second-minJ]==mm['.'] && m[from.first-minI][from.second-1-minJ]==mm['|'])
    return true;
  if (from.first==to.first && from.second+2==to.second &&  m[to.first-minI][to.second-minJ]==mm['.'] &&  m[from.first-minI][from.second+1-minJ]==mm['|'])
    return true;
  return false;
}


void floodArea(int i1, int j1, vector<vector<int>>& m, int tot)
  {
    m[i1-minI][j1-minJ]=tot;
    coords current(i1,j1);
    for (int i=current.first-2; i<=current.first+2; i+=2)
      for (int j=current.second-2; j<=current.second+2; j+=2)
        {
          coords neighbor(i,j);
          if (!isNeighborTrace(m,current,neighbor))
            continue;
          floodArea(i,j,m, tot+1);
            }
  }

  int main()
  {
  auto ifs=ifstream("input.txt");
  string s;
  ifs >> s;


  maze[coords(0,0)]='.';
  minI=maxI=minJ=maxJ=0;
  createRoute(s, coords(0,0),1);
  vector<vector<coords>> c;

   vector<vector<int>> trace(maxI-minI+1,vector<int>(maxJ-minJ+1,' '));

   for (int i=minI; i<=maxI; ++i)
      for (int j=minJ; j<=maxJ; ++j)
        trace[i-minI][j-minJ]=mm[maze[coords(i,j)]];


   floodArea(0,0,trace,0);


   int tot=0;
   int best=0;
   for (int i=minI; i<=maxI; ++i)
      for (int j=minJ; j<=maxJ; ++j)
        {
          int u=trace[i-minI][j-minJ];
          if (u<0)
            continue;

          if (u>=1000)
            tot++;
          best=max(u,best);
        }
   cout <<"Part 1: " << best << "\nPart 2: " << tot << endl; 
}
