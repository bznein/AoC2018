#include <iostream>
#include <fstream>
#include <map>
#include "../../../stringent/stringent.h"

using namespace std;

using inState = std::vector<bool>;
using rules = map<inState,bool>;

const int GENS = 20;

inState boolRule(string s)
{
  inState retVal(5,false);
  for (int i=0; i<s.size() /*Should be always 5! */; ++i)
    retVal[i] = (s[i]=='#');
  return retVal;
}

inline bool getfromMap(const map<int, bool>& state, int idx )
{
  if (state.find(idx)==state.end())
    return false;
  else return state.at(idx);
}

void printState(const map<int,bool> & s, int lowestPlant, int highestPlant)
{
  for (int i=lowestPlant; i<=highestPlant; ++i)
    {
      if (s.at(i))
        cout << "#";
      else
        cout << ".";

    }
  cout << endl;
}

int getTotVal(const map<int, bool> &state, int lowestPlant, int highestPlant )
{
  int totRes=0;
  for (int i=lowestPlant; i<=highestPlant; ++i)
    {
      if (state.at(i))
        totRes+=i;

    }
  return totRes;
}

void advanceGen(const map<int,bool> & state, map<int,bool> & newState, const rules & spread, int& lowestPlant , int &highestPlant)
{
  int l=lowestPlant;
  int h=highestPlant;
  int last_plant_found;
  for (int i=l-5; i<=h+5; ++i)
    {
      inState v{getfromMap(state, i-2),getfromMap(state,i-1),getfromMap(state,i),getfromMap(state, i+1), getfromMap(state, i+2)};
      if (spread.find(v)!=spread.end())
        {
          last_plant_found=i;
          newState[i]=spread.at(v);
          if (i<lowestPlant || lowestPlant == -1)
            lowestPlant=i;
          if (i>highestPlant)
            highestPlant=i;
        }
      else
        {
          newState[i]=false;
          if (i==lowestPlant)
            lowestPlant=-1;
          if (i==highestPlant)
            highestPlant=last_plant_found;
        }
    }
}

int main()
{
  auto ifs=ifstream("input.txt");
  string s;
  getline(ifs,s);
  rules spread;
  auto input=stringent::explode(s," ");
  map<int,bool> state;
  int lowestPlant=-1, highestPlant=-1;
  for (int i=0; i<input[2].size(); ++i)
    {
      state[i]=(input[2][i]=='#'?true:false);
      if (state[i])
        {
          if (lowestPlant==-1)
            lowestPlant=i;
          highestPlant=i;
        }
    }
  getline(ifs,s);

  while (getline(ifs,s))
    { /* Personal explode function, see here: https://github.com/bznein/stringent/blob/master/stringent.h */
      auto rule=stringent::explode(s," =>");
      spread[boolRule(rule[0])] = rule[1]=="#";
    }


  auto oldState=state;
  for (int i=1; i<=GENS; ++i)
    {
      advanceGen(oldState,state,spread,lowestPlant,highestPlant);
      oldState=state;
    }

  cout << getTotVal(state,lowestPlant,highestPlant) << endl;
  
}
