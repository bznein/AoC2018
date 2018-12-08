#include <iostream>
#include <fstream>

using namespace std;

int totalMetadata=0;


void processNode(std::ifstream& ifs)
{
	int n_children;
	int n_meta;
	int tmp;
	ifs >> n_children >> n_meta;
	for (int i=0; i<n_children; ++i)
		processNode(ifs);
	for (int i=0; i<n_meta; ++i)
	{
		ifs >> tmp;
		totalMetadata+=tmp;
	}

}


int main()
{
	auto ifs=std::ifstream("input.txt");
	processNode(ifs);
	cout << totalMetadata << endl;
}
