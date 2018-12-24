#include <iostream>
#include <fstream>
#include "../../../stringent/stringent.h"
#include <vector>
#include <optional>
#include <cmath>

using namespace std;

int totImmune=0;
int totInfection=0;
map<int,bool> invalid;

class Group
{
public:
	Group(int n, int h, int d, string a, int i, vector<string> w, vector<string> im, string t): n_units(n), hp(h), damage(d), attack_type(a), initiative(i), weaknesses(w), immunities(im), type(t){};
	Group(){};
	int n_units;
	int hp;
	int damage;
	string attack_type;
	int initiative;
	vector<string> weaknesses;
	vector<string> immunities;
	string type;
	bool hasChosen=false;
	bool hasAttacked=false;
	bool beenAttacked=false;

	bool operator==(const Group & rhs)
	{
		return n_units == rhs.n_units && hp == rhs.hp && damage == rhs.damage && attack_type == rhs.attack_type && weaknesses == rhs.weaknesses && immunities == rhs.immunities && type == rhs.type;
	}

	int getEffectivePower() const
	{
		return n_units*damage;
	}

};

void parseInput(std::vector<Group> & battle)
{
	auto ifs=ifstream("input.txt");
	string s;
	getline(ifs,s);

	vector<string> weaknesses, immunities;

	int units, hp, damage, initiative;
	string attack_type;
	while(getline(ifs,s) && s!="Infection:" && s!="")
	{
		weaknesses.clear();
		immunities.clear();
		bool hasSpecial=find(s.begin(),s.end(),'(')!=s.end();
		auto a = stringent::explode(s," ");
		units=stoi(a[0]);
		hp=stoi(a[4]);
		if (!hasSpecial)
		{
			damage = stoi(a[12]);
			attack_type = a[13];
			initiative = stoi(a[17]);
		}
		else
		{
			auto b=stringent::explode(s,"()");
			auto c=stringent::explode(b[2]," ");
			damage=stoi(c[5]);
			attack_type=c[6];
			initiative = stoi(c[10]);
			auto d=stringent::explode(b[1],";");
			for (auto e : d)
			{
				auto f=stringent::explode(e," ,");
				for (auto g : f)
				{
					if (g=="weak" || g=="immune" || g=="to")
						continue;
					if (f[0]=="weak")
						weaknesses.push_back(g);
					if (f[0]=="immune")
						immunities.push_back(g);
				}
			}

		}
		totImmune++;
		battle.push_back(Group(units,hp,damage,attack_type,initiative,weaknesses,immunities,"ImmuneSystem"));
	}

	getline(ifs,s);
	while(getline(ifs,s))
	{
		weaknesses.clear();
		immunities.clear();
		bool hasSpecial=find(s.begin(),s.end(),'(')!=s.end();
		auto a = stringent::explode(s," ");
		units=stoi(a[0]);
		hp=stoi(a[4]);
		if (!hasSpecial)
		{
			damage = stoi(a[12]);
			attack_type = a[13];
			initiative = stoi(a[17]);
		}
		else
		{
			auto b=stringent::explode(s,"()");
			auto c=stringent::explode(b[2]," ");
			damage=stoi(c[5]);
			attack_type=c[6];
			initiative = stoi(c[10]);
			auto d=stringent::explode(b[1],";");
			for (auto e : d)
			{
				auto f=stringent::explode(e," ,");
				for (auto g : f)
				{
					if (g=="weak" || g=="immune" || g=="to")
						continue;
					if (f[0]=="weak")
						weaknesses.push_back(g);
					if (f[0]=="immune")
						immunities.push_back(g);
				}
			}

		}

		battle.push_back(Group(units,hp,damage,attack_type,initiative,weaknesses,immunities,"Infection"));
		totInfection++;
	}
}


int nextToChoose(vector<Group>& battle)
{
	int candidate=-1;
	int bestVal=-1;
	for (int i=0; i<battle.size(); ++i)
	{
		if (invalid[i] || battle[i].hasChosen) 
			continue;
		int val=battle[i].getEffectivePower();
		if (val>bestVal || (val==bestVal && battle[i].initiative>battle[candidate].initiative))
		{
			bestVal=val;
			candidate=i;
		}
	}
	return candidate;
}

int nextToAttack(vector<Group>& battle)
{
	int candidate=-1;
	int bestVal=-1;
	for (int i=0; i<battle.size(); ++i)
	{
		if (invalid[i])
			continue;
		int val=battle[i].initiative;
		if (!battle[i].hasAttacked && val>bestVal)
		{
			bestVal=val;
			candidate=i;
		}
	}
	if (candidate!=-1)
		battle[candidate].hasAttacked=true;
	return candidate;
}


int getTarget(vector<Group>& battle, int player)
{
	int candidate=-1;
	int max_dmg=-1;
	for (int i=0; i<battle.size(); ++i)
	{
		if (invalid[i])
			continue;
		if (battle[i].type==battle[player].type || battle[i].beenAttacked)
			continue;
		int damage=battle[player].getEffectivePower();
		if (find(battle[i].weaknesses.begin(), battle[i].weaknesses.end(), battle[player].attack_type)!=battle[i].weaknesses.end())
			damage*=2;
		if (find(battle[i].immunities.begin(), battle[i].immunities.end(), battle[player].attack_type)!=battle[i].immunities.end())
			continue;
		if ((damage > max_dmg) || (damage==max_dmg && battle[i].getEffectivePower()>battle[candidate].getEffectivePower()) || (damage==max_dmg && battle[i].getEffectivePower()==battle[candidate].getEffectivePower() && battle[i].initiative>battle[candidate].initiative) )
		{
			max_dmg=damage;
			candidate=i;
		}

	}
	if (candidate!=-1)
		battle[candidate].beenAttacked=true;
	return candidate;
}


void resetAllFlags(vector<Group> & battle)
{
	for (int i=0; i<battle.size(); ++i)
		battle[i].hasAttacked=battle[i].hasChosen=battle[i].beenAttacked=false;
}

int turns;
bool fight(std::vector<Group>& battle)
{
	turns=0;
	invalid.clear();

	while (true)
	{
		map<int,int> attack;
		int player=nextToChoose(battle);
		while (player!=-1)
		{
			battle[player].hasChosen=true;
			int target=getTarget(battle,player);
			attack[player]=target;	
			player=nextToChoose(battle);
		}

		player=nextToAttack(battle);
		while (player!=-1)
		{
			int target=attack[player];
			if (target==-1)
			{
				player=nextToAttack(battle);
				continue;
			}
			if (invalid[target]==false)
			{
				int dmg=battle[player].getEffectivePower();
				if (find(battle[target].weaknesses.begin(), battle[target].weaknesses.end(), battle[player].attack_type)!=battle[target].weaknesses.end())
					dmg*=2;
				int killed_units=ceil(dmg/battle[target].hp);
				battle[target].n_units-=killed_units;
				if (battle[target].n_units<=0)
				{
					invalid[target]=true;
					if (battle[target].type=="ImmuneSystem")
						totImmune--;
					else
						totInfection--;
					if (totImmune==0)
						return false;
					if (totInfection==0)
						return true;
				}
			}
			player=nextToAttack(battle);
		}
		++turns;
		resetAllFlags(battle);

	}
}

int main(int argc, char * argv[])
{

	vector<Group> battle;
	parseInput(battle);

	auto oldBattle=battle;
	int oldImmune=totImmune;
	int oldInfection=totInfection;

	for (int i=1;;++i)
	{
		battle=oldBattle;
		totImmune=oldImmune;
		totInfection=oldInfection;
		for (auto &b: battle)
			if (b.type=="ImmuneSystem")
				b.damage+=i;
		cout << "Starting with " << i << endl;
		if (fight(battle))
		{
			int tot=0;
			for (auto b:battle)
				if (b.n_units>0)
					tot+=b.n_units;
			cout << tot <<endl;
			break;
		}
	}


}
