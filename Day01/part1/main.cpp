
#include <iostream>
#include <fstream>


int main()
{
  auto ifS = std::ifstream("input.txt");
  int totFrequency=0, tmp;


  while(ifS >> tmp)
    totFrequency+=tmp;

  std::cout << totFrequency << std::endl;
}
