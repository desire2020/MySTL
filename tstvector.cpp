#include <iostream>
#include <string>
#include "STLDeque.hpp"
using namespace std;
using namespace mystl;
int main()
{
	ios :: sync_with_stdio(false);
	deque<int> d;
	int len = 1000;
	for (int i = 0; i < len; i++) {
		d.push_front(i);
	} 
	deque<int> :: iterator it;
	for (it = d.begin(); it != d.end(); it++)
	{
		cout << *it << endl;
	}
	return 0;
}