#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

#define N 1000005
#define M 1005 

int p[N];
int now[N];
int cnt_now;
int sex[M];

int main()
{
	int t = 1;
	int n;
	
	while(cin >> n, n) 
	{
		// Init.
		memset(p, 0, sizeof(p));
		memset(now, 0, sizeof(now));
		memset(sex, 0, sizeof(sex));
		cnt_now = 0;

		// Read.
		    for(int i = 1; i <= n; i++) { int sum;
			cin >> sum;
			for(int j = 0; j < sum; j++)
			{
				int f;
				cin >> f;
				p[f] = i;
			}
		}

		int first = 0;
		queue<int> team[M];
		char str[10];
		int num;
		int move;

		while(cin >> str)
		{
			if( strcmp( str, "STOP") == 0) 
				break; 
			else if( strcmp( str, "DEQUEUE" ) == 0) 
			{
				now[cnt_now++] = team[first].front();
				team[first].pop();

				if(team[first].empty())
				{
					sex[first] = 0;
					first++;	
				}
			}
			else
			{
				if(first >= M)
					first = first % M;

				cin >> num;
				for(move = first; ; move++)
				{
					if(move >= M )
						move = move % M;

					if(sex[move] == p[num])
						break;
					else if(sex[move] == 0)
						break;
				}	
				team[move].push(num);
				sex[move] = p[num];
			} 
		}

		cout <<"Scenario #" << t++ << endl;
		for(int i = 0; i < cnt_now; i++)
			cout << now[i] << endl;
		cout << endl;
	}
	return 0;
}
