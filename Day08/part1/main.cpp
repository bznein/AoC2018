#include <iostream>
#include <fstream>

using namespace std;

int processNode(std::ifstream& ifs)
{
	int n_children,n_meta,tmp,retVal=0;
	ifs >> n_children >> n_meta;
	for (int i=0; i<n_children; ++i)
		retVal+=processNode(ifs);
	for (int i=0; i<n_meta; ++i)
	{
		ifs >> tmp;
		retVal+=tmp;
	}
	return retVal;

}


int main()
{
	auto ifs=std::ifstream("input.txt");
	cout << processNode(ifs) << endl;
}
