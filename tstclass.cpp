#include <iostream>
#include <fstream>
#include "STLDeque.hpp"
using namespace std;
using namespace mystl;
#define cin fin
int main()
{
	ofstream fout("input.txt");
	int o;
	deque<int> mylist;
	for (int i = 0; i < 100000; i++)
	{
		mylist.push_front(i);
	}
	deque<int> :: iterator it;
	for (it = mylist.begin(); it != mylist.end(); it++)
	{
		o = *it;
		fout << o << endl;
	}
	return 0;
}