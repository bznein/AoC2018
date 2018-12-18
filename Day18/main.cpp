#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

const int AREA_SIDE=50;
const int MINUTES_P1=10;
const int MINUTES_P2=1000000000;

using state=vector<vector<char>>;

void printState(const state & area)
{
  for (auto s : area)
    {
      for (auto i : s)
        cout << i;
      cout << endl;
    }
  cout << endl << endl;
}

inline bool isOpen(const state & area, int i, int j)
{
  return area[i][j]=='.';
}
inline bool isLumberyard(const state & area, int i, int j)
{
  return area[i][j]=='#';
}

inline bool isTree(const state & area, int i, int j)
{
  return area[i][j]=='|';
}

int getAdjacentByType(const state & area, int i, int j, char type)
{
  int tot=0;
  for (int k=i-1; k<=i+1; k++)
    for (int l=j-1; l<=j+1; ++l)
      if (k>=0 && k<area.size() && l>=0 && l<area[k].size() && !(k==i && j==l) && area[k][l]==type)
        ++tot;
  return tot;
}

void evolve(state & area)
{
  auto oldArea=area;
  for (int i=0; i<oldArea.size(); ++i)
    {
      for (int j=0; j<oldArea[i].size(); ++j)
        {
          switch (oldArea[i][j])
            {
            case '.':
              if (getAdjacentByType(oldArea,i,j,'|')>=3)
                area[i][j]='|';
              break;
            case  '|':
              if (getAdjacentByType(oldArea,i,j,'#')>=3)
                area[i][j]='#';
              break;
            case '#':
              if (getAdjacentByType(oldArea,i,j,'#')<1 || getAdjacentByType(oldArea,i,j,'|')<1)
                area[i][j]='.';
              break;
            }
        }
    }
}


int getCollectionValue(const state & area)
{
  int totL=0;
  int totT=0;
  for (auto s: area)
    for (auto i: s)
      if (i=='#')
        totL++;
      else if (i=='|')
        totT++;
  return totT*totL;
}



int main()
{
  auto ifs=ifstream("input.txt");
  string s;

  state area(AREA_SIDE,vector<char>(AREA_SIDE,' '));

  int i=0;
  while (ifs >> s)
    {
      for (int j=0; j<s.size(); ++j)
        area[i][j]=s[j];
      ++i;
    }


  map<int,int> loopD;
  int loopThresh=1000;
  int curLoop=0;
  int identifiedLoop=-1;
  for (i=0; i<MINUTES_P2; ++i)
    {
      if (i==MINUTES_P1)
        cout << "Wood after " << MINUTES_P1 << " minutes: " << getCollectionValue(area) << endl;
      evolve(area);
      if (identifiedLoop==-1)
        {
          int c= getCollectionValue(area);
          if (loopD.find(c)!=loopD.end())
            {
              curLoop++;
              if (curLoop>loopThresh)
                  identifiedLoop=i-loopD[c];
            }
          loopD[c]=i;
        }
      else if ((MINUTES_P2-i-1)%identifiedLoop==0)
        break;
    }
  cout << "Wood after " << MINUTES_P2 << " minutes: " << getCollectionValue(area) << endl;

}
