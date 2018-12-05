#include <fstream>
#include <iostream>
#include <stack>
#include <cctype>
#include <sstream>
#include <limits>
using namespace std;



char swapCase(char c)
{
  if (std::islower(c))
    return std::toupper(c);
  return std::tolower(c);
}

auto removeOccurrences(const string &s, char c)
{
  auto c2=swapCase(c);
  stringstream ss;

  for (auto elem:s)
    {
      if (elem != c && elem != c2)
        ss << elem;
    }
  return ss.str();
}

auto polymerLength(const string &s)
{
  std::stack<char> sequence;
  for (auto c: s)
    {
      if (sequence.empty())
        sequence.push(c);
      else if (auto top=sequence.top(); top==swapCase(c))
        sequence.pop();
      else
        sequence.push(c);
    }
  return sequence.size();
}


int main()
{
  auto ifs=ifstream("input.txt");


  std::string val;
  ifs >> val;
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

  int minV=std::numeric_limits<int>::max();
  for (auto c: alphabet)
    {
      if (int valT=polymerLength(removeOccurrences(val,c)); valT<minV)
        {
          minV=valT;
        }
    }

  cout << minV << endl;


}
