#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 101
#define M 50

struct T{
	char str[M];
};

int cmp(const T &a, const T &b)
{
	return strlen(a.str) < strlen(b.str);
}

int main()
{
	T tem[N];
	int cnt = 0;
	int t = 1;
	int bo = 0;
	while(cin >> tem[cnt].str)
	{
		if (strcmp(tem[cnt++].str, "9"))
			continue;

		sort(tem, tem + cnt, cmp);

		for (int i = 0; i < cnt; i++)
		{
			int k = strlen(tem[i].str);
			for (int j = i + 1; j < cnt; j++)
			{
				if (strncmp(tem[i].str, tem[j].str, k) == 0)
				{
					bo = 1;
					break;
				}
			}

			if (bo)
				break;
		}
			
		if (bo)
			cout << "Set " << t++ << " is not immediately decodable" << endl;	
		else
			cout << "Set " << t++ << " is immediately decodable" << endl;
		
		// Init.
		memset(tem, 0, sizeof(tem));
		bo = 0;
		cnt = 0;
	}
	return 0;}
