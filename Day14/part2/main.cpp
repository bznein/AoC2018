#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N_RECIPES = 793061;
using scoreboard = vector<int>;

auto getDigits(int number)
{
  vector<int> digits;
  if (number==0)
    digits.push_back(0);
  while(number)
    {
      digits.push_back(number%10);
      number /= 10;
    }
  std::reverse(digits.begin(),digits.end());
  return digits;
}

void printScoreboard(const scoreboard & scores, const vector<int> &curPos)
{
  int idx=0;
  for (auto i: scores)
    {
      if (idx==curPos[0])
        cout << "(" << i << ") ";
      else if (idx==curPos[1])
        cout << "[" << i << "] ";
      else
        cout << i << " ";
      ++idx;
    }
  cout << endl;
}

int main()
{
  scoreboard scores(2);
  vector<int> curPos={0,1};
  scores.reserve(N_RECIPES+10);
  scores[0]=3;
  scores[1]=7;

  auto target=getDigits(N_RECIPES);

  bool first_round=true;
  int cur_match=-1;
  if (target[0]==3)
    {
    if (target[1]==7)
      cur_match=1;
    else
      cur_match=0;
    }
  while(true)
    {
      int sum=scores[curPos[0]]+scores[curPos[1]];
      auto l=getDigits(sum);
      for (auto i: l)
        {
           scores.push_back(i);
           if (i==target[cur_match+1])
             cur_match++;
           else if (i==target[0])
             cur_match=0;
           else cur_match=-1;
           if (cur_match==target.size()-1)
             {
             cout << scores.size()-target.size() << endl;
             exit(0);
             }
        }
      /* Advance elves */
      if (first_round)
        {
          first_round=false;
          continue;
        }
      curPos[0]=(1+curPos[0]+scores[curPos[0]])%scores.size();
      curPos[1]=(1+curPos[1]+scores[curPos[1]])%scores.size();

    }


}
