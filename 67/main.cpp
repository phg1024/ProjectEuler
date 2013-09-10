#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	const int levels = 101;
	int num[levels][levels] = {0};
	
	for(int i=1;i<levels;i++)
	{
		for(int j=1;j<=i;j++)
		{
			cin >> num[i][j];
		}
	}
	
	for(int i=2;i<levels;i++)
	{
		for(int j=1;j<=i;j++)
		{
			int a = (j==0)?0:num[i-1][j-1];
			int b = num[i-1][j];
			num[i][j] = num[i][j] + max(a, b);
		}
	}
	
	int maxVal = 0;
	for(int i=1;i<levels;i++)
	{
		if( maxVal < num[levels-1][i] )
			maxVal = num[levels-1][i];
	}
	
	cout << maxVal << endl;
	return 0;
}