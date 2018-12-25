#include <iostream>
#include <fstream>
#include "../../../stringent/stringent.h"
#include <vector>

using namespace std;

using star=vector<int>;

const int DISTANCE=3;

int manhattanDistance(const star & s1, const star & s2)
{
	int tot=0;
	for (int i=0; i<s1.size(); ++i)
	{
		tot+=std::abs(s1[i]-s2[i]);
	}
	return tot;
}

int main()
{
	auto ifs = ifstream("input.txt");
	string s;
	vector<star> stars;
	vector<vector<star>> constellations;
	int inConstellation=0;
	map<int,bool> isInConstellation;
	while (ifs >> s)
	{
		auto a = stringent::explode(s,", ", [](const string & s){return stoi(s);});
		stars.push_back(star{a[0],a[1],a[2],a[3]});
	}

	isInConstellation[0]=true;
	inConstellation=1;
	constellations.push_back(vector<star>{stars[0]});

	while (inConstellation<stars.size())
	{
		for (int i=0; i<constellations.size(); ++i)
		{
			for (int k=0; k<constellations[i].size(); ++k)
			{
				bool expanded=false;
				/* We try to add stars to this constellation */
				for (int j=0; j<stars.size(); ++j)
				{
					/* If it is already inside a constellation we skip */
					if (isInConstellation[j])
						continue;
					if (manhattanDistance(stars[j], constellations[i][k])<=DISTANCE)
					{
						constellations[i].push_back(stars[j]);
						isInConstellation[j]=true;
						inConstellation++;
						expanded=true;
					}

				}
				/* If we expanded the constellation we start back */
				if (expanded)
					k--;
			}
		}
		/* We add the first that is not in a constellation to a new onw */
		for (int i=0; i<stars.size(); ++i)
		{
			if (isInConstellation[i])
				continue;
			constellations.push_back(vector<star>{stars[i]});
			inConstellation++;
			isInConstellation[i]=true;
			break;
		}
	}
	cout << constellations.size() << endl;
}
