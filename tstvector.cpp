#include <vector>
#include <iostream>
using namespace std;
int day_of_week(int year, int month, int day)
		{
			int yea(year);
			static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
			yea -= month < 3;
			int ans = (yea + yea / 4 - yea / 100 + yea / 400 + t[month - 1] + day) % 7;
			if (ans == 0) ans = 7;
			return ans;
		}
int main()
{
	ios :: sync_with_stdio(false);
	cout << day_of_week(2016, 2, 22) << endl;
	return 0;
}