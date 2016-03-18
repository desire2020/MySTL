#include <iostream>
#include "STLSet.hpp"
using namespace std;
//using namespace mystl;
naive_set<int> myset;
int main()
{
	ios :: sync_with_stdio(false);
	for (int i = 0; i < 3; i++)
	{
		int p;
		cin >> p;
		myset.insert(p);
	}
	for (int i = 0; i < 3; i++)
	{
		int p;
		cin >> p;
		if (myset.exist(p))
			cout << "YES" << endl;
		else 
			cout << "NO" << endl;
	}
	return 0;
}