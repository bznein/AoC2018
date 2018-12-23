#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "../../../stringent/stringent.h"
#include <limits>

using namespace std;

using nanobot=vector<int>;
using nanobotState=vector<nanobot>;



inline int manhattanDistance(const nanobot &n1, int i, int j, int l)
{
	
	return std::abs(n1[0]-i)+
		std::abs(n1[1]-j)+
		std::abs(n1[2]-l);
}

using coords=vector<int>;

int main()
{
	auto ifs = ifstream("input.txt");
	string s;
	nanobotState state;
	int minX, maxX,minY,maxY,minZ,maxZ;
	minX=minY=minZ=std::numeric_limits<int>::max();
	maxX=maxY=maxZ=-std::numeric_limits<int>::max();
	while (getline(ifs,s))
	{
		auto a=stringent::explode(s,"posr=<,> ", [](const string &s){return stoi(s);});
		state.push_back(nanobot{a[0],a[1],a[2],a[3]});
		minX=min(minX,a[0]);
		maxX=max(maxX,a[0]);
		minY=min(minY,a[1]);
		maxY=max(maxY,a[1]);
		minZ=min(minZ,a[2]);
		maxZ=max(maxZ,a[2]);
	}



	/* Binary search */
	int dist =1;
	while (dist<maxZ-minZ) 
		dist*=2;
	int best_val;
	coords best_c;
	while (dist>=1)
	{
		int bCount=0;
		for (int i=minX; i<=maxX; i+=dist)
			for (int j=minY; j<=maxY; j+=dist)
				for (int l=minZ; l<=maxZ; l+=dist)
				{
					int count = 0;
					for (const auto &n: state)
					{
						auto m=manhattanDistance(n,i,j,l);
						if ((m-n[3])<dist)
							++count;
						if (count>bCount ||(count==bCount && abs(i)+abs(j)+abs(l) < best_val))
						{
							bCount=count;
							best_c=coords{i,j,l};
							best_val=abs(i)+abs(j)+abs(l);
						}
					}
				}
		minX=best_c[0]-dist;
		maxX=best_c[0]+dist;
		minY=best_c[1]-dist;
		maxY=best_c[1]+dist;
		minZ=best_c[2]-dist;
		maxZ=best_c[2]+dist;
		dist/=2;
	}

	cout << best_val << endl;

	
}
