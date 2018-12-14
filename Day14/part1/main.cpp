#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

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

  bool first_round=true;;
  while(scores.size()<N_RECIPES+10)
    {
      int sum=scores[curPos[0]]+scores[curPos[1]];
      auto l=getDigits(sum);
      for (auto i: l)
        scores.push_back(i);
      /* Advance elves */
      if (first_round)
        {
          first_round=false;
          continue;
        }
      curPos[0]=(1+curPos[0]+scores[curPos[0]])%scores.size();
      curPos[1]=(1+curPos[1]+scores[curPos[1]])%scores.size();
    }

  for (int i=N_RECIPES; i<N_RECIPES+10; ++i)
    cout << scores[i];
  cout << endl;


}
