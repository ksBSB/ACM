#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 5005
#define M 201

struct say{
	char str[M];
};

say tem[N * M];

char strl(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return ch + 32;
	else
		return ch;
}

int cmp(const say &a, const say &b)
{
	return strcmp(a.str, b.str) < 0;
}

int main()
{
	int cnt = 0;
	memset(tem, 0, sizeof(tem));
	char ch;
	int m = 0, bo = 0;
	while ((ch = getchar()) != EOF)
	{
		ch = strl(ch);
		if (ch >= 'a' && ch <= 'z' && bo)
			tem[cnt].str[m++] = ch;	
		else if (ch >= 'a' && ch <= 'z')
		{
			bo = 1;
			cnt++;
			m = 0;
			tem[cnt].str[m++] = ch;
		}
		else
		{
			bo = 0;
			tem[cnt].str[m] = '\0';
		}
	}

	sort(tem, tem + cnt + 1, cmp);

	for (int i = 1; i <= cnt; i++)
	{
		if(strcmp(tem[i].str, tem[i - 1].str) == 0)
			continue;
		puts(tem[i].str);
	}

	return 0;
}
