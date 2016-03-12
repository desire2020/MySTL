#include <iostream>
#include <string>
using namespace std;

class A
{
	class B
	{
		public:
			int a;
	};
};
int main()
{
	ios :: sync_with_stdio(false);
	A :: B sa;
	sa.a = 3213;
	return 0;
}