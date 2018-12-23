#include <iostream>
#include <fstream>

#include <map>

using namespace std;


const int DEPTH=8112;
const int TARGETX=13;
const int TARGETY=743;

using coords=pair<int,int>;

const int Y_CONST=48271;
const int X_CONST=16807;

const int MODULO = 20183;

int main()
{
	int totRisk=0;
	map<coords, long long> geoIndex;
	map<coords, int> erosion;
	geoIndex[coords(0,0)]=geoIndex[coords(TARGETX,TARGETY)]=0;
        erosion[coords(0,0)]=erosion[coords(TARGETX,TARGETY)]=((0+DEPTH)%MODULO);
	totRisk+=erosion[coords(0,0)]%3;
	totRisk+=erosion[coords(0,0)]%3;
	for (int i=1; i<=TARGETY; ++i)
	{
		auto val=i*Y_CONST;
		geoIndex[coords(0,i)]=val;
		erosion[coords(0,i)]=((val+DEPTH)%MODULO);
		totRisk+= ((val+DEPTH)%MODULO)%3;
	}	
	for (int i=1; i<=TARGETX; ++i)
	{
		auto val=i*X_CONST;
		geoIndex[coords(i,0)]=val;
		erosion[coords(i,0)]=((val+DEPTH)%MODULO);
		totRisk+= ((val+DEPTH)%MODULO)%3;
	}
	for (int i=1; i<=TARGETY; ++i)
		for (int j=1; j<=TARGETX; ++j)
		{
			if (geoIndex.find(coords(j,i))!=geoIndex.end())
			continue;
			auto val = erosion.at(coords(j-1,i))*erosion.at(coords(j,i-1));
			geoIndex[coords(j,i)]=val;
			erosion[coords(j,i)]=((val+DEPTH)%MODULO);
			totRisk+= ((val+DEPTH)%MODULO)%3;

		}

	cout << totRisk << endl;
}

