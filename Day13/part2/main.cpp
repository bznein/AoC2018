#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;


using position = pair<int,int>;
using trackPiece = char;
using track = std::vector<std::vector<trackPiece>>;
bool stop=false;

/* Maps the turns created by curves*/
using curve=pair<char,char>;
map<curve,char> turns
{
  {curve('>','/'), '^'},
  {curve('>','\\'), 'v'},
  {curve('v','/'), '<'},
  {curve('v','\\'), '>'},
  {curve('<','/'), 'v'},
  {curve('<','\\'), '^'},
  {curve('^','/'), '>'},
  {curve('^','\\'), '<'},
    };


using inters=pair<char,int>;
map<inters,char> changeDir
{
  {inters('>',0),'^'},
  {inters('>',1),'>'},
  {inters('>',2),'v'},
  {inters('v',0),'>'},
  {inters('v',1),'v'},
  {inters('v',2),'<'},
  {inters('<',0),'v'},
  {inters('<',1),'<'},
  {inters('<',2),'^'},
  {inters('^',0),'<'},
  {inters('^',1),'^'},
    {inters('^',2),'>'},

      };

class Cart;

bool crash(const vector<Cart> & carts, int i, int j);
void eraseCarts(vector<Cart> & carts, int i, int j);
void checkCrashes(vector<Cart> & carts);

class Cart
{
public:

  Cart(char c, position pp, int turns=0, bool moved=false): direction(c), p(pp), n_turns(turns), hasMoved(moved){};

  position p;
  char direction;
  int n_turns;
  bool hasMoved;

  void move(track& t, vector<Cart>& c2)
  {
    /* Compute next position */
    int i=p.first,j=p.second;
    switch (direction)
      {
      case '^':
        --i;
        break;
      case '<':
        --j;
        break;
      case 'v':
        ++i;
        break;
      case '>':
        ++j;
        break;
      }

    /* Compute in what kind of piece we are now */
    switch (t[i][j])
      {
      case '-':
      case '|':
        break; /*Nothing to do here*/
      case '/':
      case '\\':
        direction=turns[curve(direction,t[i][j])]; /* Change direction */
        break;
      case '+': /* Intersection */
        direction=changeDir[inters(direction,n_turns)];
        n_turns=(n_turns+1)%3;
        break;
       
      }
    p.first=i;
    p.second=j;
    hasMoved=true;

    checkCrashes(c2);
  }

  void resetMove()
  {
    hasMoved=false;
  }

};


void eraseCarts(vector<Cart> & carts, int i, int j)
{
  for (auto it = carts.begin(); it!=carts.end();)
    {
      auto c=*it;
      if (c.p.first==i && c.p.second==j)
        {
          it=carts.erase(it);
        }
      else
        ++it;
    }
}

bool crash(const vector<Cart> & carts, int i, int j)
{
  int occ=0;
  for (auto c:carts)
    {
      if (c.p.first==i && c.p.second==j)
        {
          occ++;
          if (occ==2)
            return true;
        }
    }
  return false;
}

const Cart* isOccupied(const vector<Cart> & carts, int i, int j)
{
  for (const auto& c : carts)
    if (c.p.first==i && c.p.second==j)
      return &(c);
  return nullptr;
}

void checkCrashes(vector<Cart> & carts)
{

  for (auto it=carts.begin(); it!=carts.end(); ++it)
  {
    auto c2=*it;
    int i=c2.p.first;
    int j=c2.p.second;
  /* Crash check */
  if (crash(carts,i,j))
    {
      eraseCarts(carts,i,j);
      it=carts.begin();
      if (carts.size()==1)
        {
          stop=true;
          return;
        }
    }
  }
}

void printV(const track& t, const vector<Cart> & carts, int w, int h)
{ 
  for (int i=0; i<h; ++i)
    {
      for (int j=0; j<w; ++j)
        if (auto p=isOccupied(carts,i,j); p!=nullptr)
          cout << p->direction;
      else
        cout << t[i][j];
      cout << endl;
    }
}


Cart* nextToMove(vector<Cart> & carts)
{
  /* p.second dominates over p.first */
  Cart * candidate=nullptr;
  for (auto & c : carts)
    {
      if (c.hasMoved==false)
        {
          if (candidate==nullptr)
            candidate=&(c);
          else if (c.p.second < candidate->p.second)
            candidate=&(c);
          else if (c.p.second==candidate->p.second && c.p.first<candidate->p.first)
            candidate=&(c);

        }
    }
  return candidate;
}

void resetMoveFlags(vector<Cart> &c)
{
  for (auto & cc : c)
    cc.resetMove();
}

int main()
{
  auto ifs = ifstream("input.txt");
  string s;
  int h=0, w=0;
  while (getline(ifs,s))
  {
    h++;
    w=max(w,static_cast<int>(s.size()));
  }

  auto t=track(h,std::vector<trackPiece>(w,' '));
  ifs = ifstream("input.txt");
  int j=0;

  vector<Cart> carts;
  while (getline(ifs,s))
    {
      for (int i=0; i<w; ++i)
        {
          if (i<s.size())
            {

            switch (s[i])
              {
              case '^':
              case 'v':
                carts.push_back(Cart(s[i],position(j,i)));
                t[j][i]='|';
                break;
              case '<':
              case '>':
                carts.push_back(Cart(s[i],position(j,i)));
                t[j][i]='-';
                break;
              default:
                 t[j][i]=s[i];
              }

            }
          else
            t[i][j]=' ';
        }
      ++j;
    }

  //printV(t,carts,w,h);
  while(true)
    {
      auto c = nextToMove(carts);
      while (c!=nullptr)
        {
          c->move(t,carts);
          c=nextToMove(carts);
        }
      //   printV(t,carts,w,h);
      if (stop)
        {
          cout << carts[0].p.second<<","<<carts[0].p.first<<endl;
          exit(0);
        }
      resetMoveFlags(carts);
    }
}



