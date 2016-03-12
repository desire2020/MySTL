#include <iostream>
#include "STLDeque.hpp"
#include <string>
using namespace std;
using namespace mystl;
deque<int> mylist;
int main()
{
	ios :: sync_with_stdio(false);

	deque<int> :: iterator it;

	for (int i = 0; i < 512; i++)
		mylist.push_back(i);
	mylist.push_back(512);
	for (int i = 0; i < 513; i++)
		cout << mylist[i] << endl;
	return 0;
}