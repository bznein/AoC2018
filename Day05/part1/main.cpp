#include <fstream>
#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

char swapCase(char c)
{
  if (std::islower(c))
    return std::toupper(c);
  return std::tolower(c);
}

int main()
{
  auto ifs=ifstream("input.txt");


  std::string val;
  ifs >> val;

  std::stack<char> sequence;
  for (auto c: val)
    {
      if (sequence.empty())
        sequence.push(c);
      else if (auto top=sequence.top(); top==swapCase(c))
        sequence.pop();
      else
        sequence.push(c);
    }

  cout << sequence.size() << endl;
}
