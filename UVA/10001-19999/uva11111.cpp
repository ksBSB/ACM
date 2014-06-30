#include<string.h>
#include<stdio.h>
#include<stack>
using namespace std;
#define N 1000010

int num[N];
int cnt;
int wa;
int ti;

struct ma{
	int value;
	int sum;
};

int main()
{
	int n;
	char c;
	memset(num, 0, sizeof(num));
	cnt = 0;

	while (scanf("%d%c", &num[cnt++], &c) != EOF)
	{
		if(c =='\n')
		{
			// Init.
			wa = 0;
			stack<ma> s;
			ti = 0;

			ma now;
			for (int i = cnt -1; i >= 0; i--)
			{
				if(num[i] > 0)
				{
					now.value = num[i];
					now.sum = 0;
					s.push(now);
				}
				else if(num[i] < 0 && !s.empty())
				{
					now = s.top();
					if (now.value == -num[i])
					{
						s.pop();

						if (s.empty())
							ti++;
						else
						{
							ma change = s.top();
							s.pop();
							change.sum += now.value;
							if (change.value <= change.sum)
							{
								wa = 1;
								break;
							}
							s.push(change);
						}
					}
					else
					{
						now.value = num[i];
						now.sum = 0;
						s.push(now);
					}
				}
				else
				{
					wa = 1;
					break;
				}
			}

			if(ti > 1)
				wa = 1;
			if (s.empty() && !wa)
				printf(":-) Matrioshka!\n");
			else
				printf(":-( Try again.\n");

			memset(num, 0, sizeof(num));
			cnt = 0;
		}
	}
	return 0;}
