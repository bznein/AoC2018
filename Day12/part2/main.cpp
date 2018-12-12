#include <iostream>
#include <fstream>
#include <map>
#include "../../../stringent/stringent.h"

using namespace std;

using inState = std::vector<bool>;
using rules = map<inState,bool>;

const long long GENS =50000000000ll;

inState boolRule(string s)
{
  inState retVal(5,false);
  for (long long i=0; i<s.size() /*Should be always 5! */; ++i)
    retVal[i] = (s[i]=='#');
  return retVal;
}

bool getfromMap(const map<long long, bool>& state, long long idx )
{
  if (state.find(idx)==state.end())
    return false;
  else return state.at(idx);
}

void printState(const map<long long,bool> & s, long long lowestPlant, long long highestPlant)
{
  for (long long i=lowestPlant; i<=highestPlant; ++i)
    {
      if (s.at(i))
        cout << "#";
      else
        cout << ".";

    }
  cout << endl;
}

long long getTotVal(const map<long long, bool> &state, long long lowestPlant, long long highestPlant )
{
  long long totRes=0;
  for (long long i=lowestPlant; i<=highestPlant; ++i)
    {
      if (state.at(i))
        totRes+=i;

    }
  return totRes;
}

void advanceGen(const map<long long,bool> & state, map<long long,bool> & newState, const rules & spread, long long& lowestPlant , long long &highestPlant)
{
  long long l=lowestPlant;
  long long h=highestPlant;
  long long last_plant_found;
  for (long long i=l-5; i<=h+5; ++i)
    {
      inState v{getfromMap(state, i-2),getfromMap(state,i-1),getfromMap(state,i),getfromMap(state,i+1),getfromMap(state,i+2)};
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
  map<long long,bool> state;
  long long lowestPlant=-1, highestPlant=-1;
  for (long long i=0; i<input[2].size(); ++i)
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
    {
      /* Personal explode function, see here: https://github.com/bznein/stringent/blob/master/stringent.h */
      auto rule=stringent::explode(s," =>");
      spread[boolRule(rule[0])] = rule[1]=="#";
    }


  auto oldState=state;
  auto oldVal=getTotVal(state,lowestPlant,highestPlant);
  int oldDiff=-1;
  int repeatingDiff=0;
  const int thresh_repeating=100;
  for (long long i=1; i<=GENS; ++i)
    {
      advanceGen(oldState,state,spread,lowestPlant,highestPlant);
      oldState=state;
      auto curVal=getTotVal(state,lowestPlant,highestPlant);
      int curDiff=curVal-oldVal;
      oldVal=curVal;
      if (oldDiff==-1)
        oldDiff=curDiff;
      else
        {
          if (curDiff==oldDiff)
            {
              repeatingDiff++;
              if (repeatingDiff==thresh_repeating)
                {
                  cout << "Final res is: " << (curVal+(curDiff*(GENS-i))) << endl;
                  break;
                }
            }
          else
            repeatingDiff=0;
          oldDiff=curDiff;
        }
    }
 
  
}
