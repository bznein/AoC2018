#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "../../../stringent/stringent.h"

using namespace std;

using nanobot=std::vector<int>;
using nanobotState=vector<nanobot>;



inline int manhattanDistance(const nanobot &n1, const nanobot &n2)
{
	return std::abs(n1[0]-n2[0])+
		std::abs(n1[1]-n2[1])+
		std::abs(n1[2]-n2[2]);
}

int main()
{
	auto ifs = ifstream("input.txt");
	string s;
	nanobotState state;
	while (getline(ifs,s))
	{
		auto a=stringent::explode(s,"posr=<,> ", [](const string &s){return stoi(s);});
		state.push_back(nanobot{a[0],a[1],a[2],a[3]});
	}

	std::sort(state.begin(), state.end(), [](const nanobot & n1, const nanobot & n2) {return n1[3]>n2[3];});

	
	int signal=state.front()[3];

	int tot=0;
	for (auto i: state)
		if (manhattanDistance(state.front(),i)<=signal)
			tot++;


	cout << tot << endl;
}
