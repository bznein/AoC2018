#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <queue>
#include <functional>
#include <map>
#include <set>
using namespace std;

using maze = std::vector<std::vector<char>>;
using coords=pair<int,int>;

using qType=pair<coords,int>;
class Unit;

int totG=0;
int totE=0;
long long full_rounds=0;
bool deadElf=false;

int manhattanDistance(coords c1, coords c2)
{
  return std::abs(c1.first-c2.first)+std::abs(c1.second-c2.second);
}


auto reconstructPath(map<coords,coords> cameFrom, coords current)
{
  std::vector<coords> path{current};
  while (cameFrom.find(current)!=cameFrom.end())
    {
      current=cameFrom[current];
      path.push_back(current);
    }
  return path;
}
vector<coords> shortestPath(const maze &m ,coords from, coords to)
{
  set<coords> closedSet;
  set<coords> openSet;
  map<coords,coords> cameFrom;
  map<coords,int> gScore;
  map<coords,int> fScore;
  
  openSet.insert(from);



  gScore[from]=0;
  fScore[from]=manhattanDistance(from,to);

  while (!openSet.empty())
    {
      auto current=*(std::min_element(openSet.begin(),openSet.end(),[fScore](const coords &c1, const coords & c2){return fScore.at(c1)<fScore.at(c2);}));
      if (current == to)
        return reconstructPath(cameFrom, current);
      openSet.erase(current);
      closedSet.insert(current);

      for (int i=current.first-1; i<=current.first+1; ++i)
        for (int j=current.second-1; j<=current.second+1; ++j)
          {
            if (i==current.first-1 && j==current.second-1)
              continue;
            if (i==current.first+1 && j==current.second-1)
              continue;
            if (i==current.first+1 && j==current.second+1)
              continue;
            if (i==current.first-1 && j==current.second+1)
              continue;
            if (m[i][j]!='.')
              continue;

            coords neighbor(i,j);
            if (neighbor==current)
              continue;
            if (closedSet.find(neighbor)!=closedSet.end())
                continue;
            int tentative_gScore;
            if (gScore.find(current)!=gScore.end())
               tentative_gScore=gScore[current]+1;
            else
              tentative_gScore=numeric_limits<int>::max();

            if (openSet.find(neighbor)==openSet.end())
              openSet.insert(neighbor);
            else if (gScore.find(neighbor)!=gScore.end() && tentative_gScore>=gScore[neighbor])
              continue;

            cameFrom[neighbor]=current;
            gScore[neighbor] = tentative_gScore;
            fScore[neighbor] = gScore[neighbor] + manhattanDistance(neighbor,to);
          }
    }
  return vector<coords>();
}


class Unit
{
public:
  char type;
  int ap=3;
  int hp=200;
  coords position;

  bool hasMoved=false;

  Unit(char t, int i, int j)
  {
    type=t;
    position.first=i;
    position.second=j;
  }


};




void printMaze(const maze & m)
{
  for (int i=0; i<m.size(); ++i, cout << endl)
    for (int j=0; j<m[i].size(); ++j)
      {
          cout << m[i][j];
      }
  cout << endl << endl << endl;
}
bool isThereATroop(const maze & m, int i, int j)
{
  if (i<0 || i>=m.size() || j<0 || j>=m[i].size())
    return false;
  return (m[i][j]=='E' || m[i][j]=='G');
}

bool isThereATroop(const maze & m, int i, int j, char c)
{
  return (isThereATroop(m,i,j) && m[i][j]!=c);
}



bool isThereATroop(const maze & m, coords c)
{
  return isThereATroop(m,c.first,c.second);
}
Unit * nextToMove(vector<Unit> & units)
{
  Unit* cand=nullptr;
  for (auto & u : units)
    {
      if (u.hasMoved || u.hp<=0)
        continue;
      if (cand==nullptr)
        cand=&(u);
      else if (u.position.first < cand ->position.first ||(u.position.first==cand->position.first && u.position.second<cand->position.second))
        cand=&(u);
    }

  return cand;
}

void resetMoveFlags(vector<Unit> & units)
{
  for (auto & u : units)
    {
      u.hasMoved=false;
    }
}

vector<Unit *> getMoveSequence(vector<Unit> &units)
{
  vector<Unit *> v;
  Unit * cand=nextToMove(units);
  while (cand!=nullptr)
    {
      v.push_back(cand);
      cand->hasMoved=true;
      cand=nextToMove(units);
    }

  resetMoveFlags(units);
  return v;
}


 bool isInRange(coords c1, coords c2)
 {
   /* Return true if c1 is in the square of c2!! */

   if (c1.first==c2.first && c1.second==c2.second+1)
     return true;
   if (c1.first==c2.first && c1.second==c2.second-1)
     return true;
   if (c1.first==c2.first-1 && c1.second==c2.second)
     return true;
   if (c1.first==c2.first+1 && c1.second==c2.second)
     return true;
   return false;
 }

void printUnitStatus(const vector<Unit> & units)
{
  for (auto u: units)
    {
      cout << u.type << "(" << u.hp<< ")" << endl;
    }
}

 Unit* enemyToAttack(vector<Unit> & units, Unit* player)
 {
   Unit * cand=nullptr;
   for (auto & u: units)
     {
       if (u.hp<=0 || u.type==player->type)
         continue;
       if (isInRange(u.position, player->position))
         {
           if (cand==nullptr)
             cand=&(u);
           else if (u.hp<cand->hp)
             cand=&(u);
           else if (u.hp==cand->hp && u.position.first<cand->position.first)
             cand=&(u);
           else if (u.hp==cand->hp && u.position.first==cand->position.first && u.position.second<cand->position.second)
             cand=&(u);
         }
     }
   return cand;

 }

 void attack(Unit * player, maze & m, vector<Unit>& units)
 {
   Unit * target=enemyToAttack(units,player);
   if (target==nullptr)
     return;
   else
     {
     target->hp-=player->ap;
     if (target->hp<=0)
       {
       m[target->position.first][target->position.second]='.';
       if (target->type=='G')
         {
         totG--;
         
         }
       else if (target->type=='E')
         {
         deadElf=true;
         }

       }



     }
 }

auto getTargets(Unit * player, const vector<Unit> & units)
{
  auto res=vector<Unit>();
  for (auto u : units)
    {
      if (u.type!=player->type && u.hp>0)
        res.push_back(u);
    }
  return res;
}

auto getInRange(vector<Unit> targets, const maze &m, Unit * player)
{
  set<coords> res;
  for (auto t: targets)
    {
      coords c=t.position;
      if (isInRange(c,player->position))
        return set<coords>();
      int i=c.first;
      int j=c.second;
      if (m[i+1][j]=='.')
        res.insert(coords(i+1,j));
      if (m[i-1][j]=='.')
        res.insert(coords(i-1,j));
      if (m[i][j+1]=='.')
        res.insert(coords(i,j+1));
      if (m[i][j-1]=='.')
        res.insert(coords(i,j-1));
    }
  return res;
}

coords checkShortestPath(const maze& m,vector<coords> & path)
{
  coords c1 =path[0];
  coords c2 = path[1];

  coords ct;
  ct=coords(c1.first-1,c1.second);
  if (ct==c2)
    return ct;
  else if (m[ct.first][ct.second]=='.')
    {
      auto b=shortestPath(m,ct,path.back());
      if (b.size()==path.size()-1)
        return ct;
    }
  ct=coords(c1.first,c1.second-1);
  if (ct==c2)
    return ct;
  else if (m[ct.first][ct.second]=='.')
    {
      auto b=shortestPath(m,ct,path.back());
      if (b.size()==path.size()-1)
        return ct;
    }
  ct=coords(c1.first,c1.second+1);
  if (ct==c2)
    return ct;
  else if (m[ct.first][ct.second]=='.')
    {
      auto b=shortestPath(m,ct,path.back());
      if (b.size()==path.size()-1)
        return ct;
    }
  ct=coords(c1.first+1,c1.second);
  if (ct==c2)
    return ct;
  else if (m[ct.first][ct.second]=='.')
    {
      auto b=shortestPath(m,ct,path.back());
      if (b.size()==path.size()-1)
        return ct;
    }
}

 void move(Unit * player, maze & m, vector<Unit>& units)
 {

   auto targets=getTargets(player,units);
   auto inRange=getInRange(targets,m, player);
   coords chosenSquare;
   chosenSquare.first=chosenSquare.second=numeric_limits<int>::max();
   int bestDistance=numeric_limits<int>::max();
   for (auto c: inRange)
     {
       auto v=shortestPath(m,player->position,c);
       if (v.size()!=0 && v.size()-2<bestDistance)
         {
           bestDistance=v.size()-2;
           chosenSquare=c;
         }
       else if (v.size()!=0 && v.size()-2==bestDistance && c.first<chosenSquare.first)
         {
           bestDistance=v.size()-2;
           chosenSquare=c;
         }
       else if (v.size()!=0 && v.size()-2==bestDistance  && c.first==chosenSquare.first && c.second<chosenSquare.second)
         {
           bestDistance=v.size()-2;
           chosenSquare=c;
         }
     }




   if (bestDistance==numeric_limits<int>::max())
     return;
   auto best=shortestPath(m,player->position,chosenSquare);
   std::reverse(best.begin(),best.end());
   coords mv=checkShortestPath(m,best);
   coords c1=player->position;
   m[c1.first][c1.second]='.';
   m[mv.first][mv.second]=player->type;
   player->position=mv;

 }




bool playMove(maze & m, vector<Unit> & units)
{
  auto v=getMoveSequence(units);
  auto playerIt=v.begin();
  while (playerIt!=v.end())
    {
      
      auto player=*playerIt;
      if (player->hp<=0)
        {
          ++playerIt;
          continue;
        }
      if (totG==0)
        {
          long long tot=0;
          for (auto u: units)
            {
              if (u.hp>0)
                tot+=u.hp;
            }
          cout << full_rounds*tot << endl;

          //printMaze(m);
          exit(0);
        }
      int i= player->position.first;
      int j= player->position.second;

        move(player, m, units);
        attack(player, m, units);
      ++playerIt;
    }
  full_rounds++;
  // printMaze(m);
  return !deadElf;
}
int main(int argc, char** argv)
{
  maze cave;
  vector<Unit> units;
  ifstream ifs;
  if (argc<2)
    ifs=ifstream("input.txt");
  else
    ifs=ifstream((argv[1]));
  string s;
  int i=0;
  while (ifs >> s)
    {
      cave.push_back(vector<char>(s.size(),' '));
      int j=0;
      for (auto c: s)
        {
          if (c=='G' || c == 'E')
            {
              units.push_back(Unit(c,i,j));
              if (c=='G')
                totG++;
              if (c=='E')
                totE++;
              cave[i][j]=c;
            }
          else
            cave[i][j] = c;
          ++j;
        }
      ++i;
    }

  auto baseCave=cave;
  auto baseUnits=units;
  int basetotG=totG;

  int ap=4;
  for (auto & u: units)
    if (u.type=='E')
      u.ap=ap;
  while (true)
    {
      deadElf=false;
      full_rounds=0;
      cave=baseCave;
      totG=basetotG;
      units=baseUnits;
      for (auto & u: units)
        if (u.type=='E')
          u.ap=ap;
      //printMaze(cave);
      while(playMove(cave,units));
      ap++;

    }


}
