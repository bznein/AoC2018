#include <iostream>
#include <fstream>
#include <queue>
#include <limits>

#include <map>

using namespace std;



const int DEPTH=8112;
const int TARGETY=13;
const int TARGETX=743;

const int MAX_SIZE=1000;

using coords=pair<int,int>;

const int Y_CONST=48271;
const int X_CONST=16807;

const int MODULO = 20183;

 
class state
{
public:
	int x, y;
	int type; /* The tye of regione in which is not valid */
	int dist;
};

vector<int> switchX{-1, 0, 1, 0};
vector<int> switchY{0, 1, 0, -1};

auto dijkstra(vector<vector<int>> cave)
{
	
	auto cmp = [](const state& s1, const state &s2){return s1.dist>s2.dist;};
	vector<vector<vector<int>>> best(MAX_SIZE,vector<vector<int>>(MAX_SIZE,vector<int>(3,0)));
	vector<vector<vector<bool>>> stateSeen(MAX_SIZE,vector<vector<bool>>(MAX_SIZE,vector<bool>(3,false)));
	
	auto Q=priority_queue<state,vector<state>,decltype(cmp)>(cmp);

	state start;
	start.x=start.y=0;
	start.dist=0;
	start.type=1;
	Q.push(start);
	
	while (!Q.empty() && !stateSeen[TARGETX][TARGETY][1])
	{
		auto cur = Q.top();
		Q.pop();
		if (stateSeen[cur.x][cur.y][cur.type])
			continue;
		stateSeen[cur.x][cur.y][cur.type]=true;
		best[cur.x][cur.y][cur.type] = cur.dist;
		for (int i=cur.x-1; i<=cur.x+1; ++i)
			for (int i=0; i<4; ++i)
			{
				state tmp;
				tmp.x=cur.x+switchX[i];
				tmp.y=cur.y+switchY[i];
				tmp.type=cur.type;
				tmp.dist=cur.dist+1;
				if (tmp.x>=0 && tmp.y>=0 && tmp.x<MAX_SIZE && tmp.y<MAX_SIZE && cave[tmp.x][tmp.y] != tmp.type && !stateSeen[tmp.x][tmp.y][tmp.type])
					Q.push(tmp);
			}
		for (int i = 0; i < 3; i++){
			state tmp;
			tmp.x = cur.x;
			tmp.y = cur.y;
			tmp.type = i;
			tmp.dist = cur.dist + 7;

			if (cave[tmp.x][tmp.y] != tmp.type && !stateSeen[tmp.x][tmp.y][tmp.type])
				Q.push(tmp);
			


		}
	}
	cout << best[TARGETX][TARGETY][1] << endl;
}


int main()
{
	vector<vector<int>> cave(MAX_SIZE,vector<int>(MAX_SIZE,0));
	for (int i=0; i<MAX_SIZE; ++i)
		for (int j=0; j<MAX_SIZE; ++j)
		{
			if (i == 0 && j == 0)
				cave[i][j] = 0;
		      	else if (i == TARGETX && j == TARGETY)
				cave[i][j] = 0;
		      	else if (i == 0)
				cave[i][j] = (j * X_CONST) % MODULO;
		      	else if (j == 0)
				cave[i][j] = (i * Y_CONST) % MODULO;
		      	else
				cave[i][j] = (cave[i - 1][j] * cave[i][j - 1]) % MODULO;
		      
		      	cave[i][j] = (cave[i][j] + DEPTH) % MODULO;
		}

	for (int i=0; i<MAX_SIZE; ++i)
		for (int j=0; j<MAX_SIZE; ++j)
     			cave[i][j] %= 3;
   
	dijkstra(cave);

}

