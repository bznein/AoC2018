#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



int getNodeVal(std::ifstream& ifs)
{
	int val=0;
	int n_children;
	std::vector<int> vals;
	int n_meta;
	int tmp;
	ifs >> n_children >> n_meta;
	for (int i=0; i<n_children; ++i)
	{
		vals.push_back(getNodeVal(ifs));
	}
	for (int i=0; i<n_meta; ++i)
	{
		ifs >> tmp;
		if (n_children==0)
			val+=tmp;
		else if (tmp<=vals.size() && tmp>0)
		{
			val+=vals[tmp-1];
		}
	}

	return val;
}


int main()
{
	auto ifs=std::ifstream("input.txt");
	cout << getNodeVal(ifs) << endl;
}
