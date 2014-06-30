#include<iostream>
#include<string.h>
using namespace std;

struct tree{
	char name;
	tree *right;
	tree *lift;
};

#define N 10010
char str[N];
int tg;
int k;

tree *build_Node(int deep)
{
	tree *now = new tree;
	now->name = str[k--];
	if(deep > tg)
		tg = deep;
	if(now->name >= 'A' && now->name <= 'Z')
	{
		now->lift = build_Node(deep + 1);
		now->right = build_Node(deep + 1);
		return now;
	}
	else
	{
		now->lift = NULL;
		now->right = NULL;
	}	
	return now;
}

tree* print(tree *now, int order, int deep)
{
	if(now->lift == NULL && now-> right == NULL && order == deep)
	{
		cout << now->name;
		delete now;
		now = NULL;
	}
	else
	{
		if(now->lift != NULL)
			now->lift = print(now->lift, order, deep + 1);
		if(now->right != NULL)
			now->right = print(now->right, order, deep + 1);
	}
	return now;
}	

int main()
{
	int n;

	cin >> n;

	while(n--)
	{
		// Init.
		memset(str, 0, sizeof(str));
		tg = 0;

		// read.
		cin >> str;
		int m = strlen(str);
		k = m - 1;

		// count.
		tree *top = NULL;
		top = build_Node(1);

		// printf.
		for(int i = tg; i > 0; i--)
		{
			top = print(top, i, 1);
		}
		cout << endl;
	}
	return 0;
}
