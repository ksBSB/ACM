#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;
#define N 10005

int tree[N];	//树.
int dep=0;		//记录深度.
int num[N];

int sq(int n)	//计算本行的头下标。
{
	int sum=0;
	int i;
	for(i = 1;i <= n; i++)
		sum+=i;
	return sum+1;
}

void grow(int k,int n)		//生成树。
{
	if(n>dep)	dep=n;
	int t;		cin>>t;
	if(t!=-1)
	{	tree[k]+=t;
	
		int	p=sq(n),q=sq(n+1); 
		grow(k-p+q,n+1);
		grow(k-p+q+1,n+1);
	}
}

int find(int m,int h)			//寻找隔层同方向。
{
	if(h<=1)	return tree[m];		
	int f=m;
	int i;
	for(i=0;i<2;i++)			//换行公式。（跳行需换行两次）
	{
		f=f-sq(h)+sq(h-1);
		h--;
	}

	f--;
	if(f<sq(h+1)&&f>=sq(h))		//判断跳行后下标是否满足。
		return tree[m]+find(f,h);
	else
		return tree[m];

}

int main()
{
	//Init.
	memset(tree,0,sizeof(tree));
	memset(num,0,sizeof(num));
	int t=1;			//计数器。
	int i;
	int k=0;			//记录落叶堆数

	while(cin>>tree[1],tree[1]!=-1)
	{
		grow(2,1);				//生成树。
		grow(3,1);	

		int h=--dep;
		int g=sq(dep+1);
		for(i = sq(dep);i < g; i++)
		{
			int o;				//辅助输出。
			int m=i-sq(h)+sq(h-1);	
			
			if(o=find(i,h))		//遍历n行。
			num[k++]=o;
			
			if(i==g-1)	break;
			
			if(o=find(m,h-1))	//遍历n-1行。
			num[k++]=o;
		}

		cout<<"Case "<<t++<<":"<<endl;	//输出。

		for(i = 0;i < k-1; i++)	
			cout<<num[i]<<" ";
		cout<<num[i]<<endl<<endl;
		
		//Init.
		memset(tree,0,sizeof(tree));
		memset(num,0,sizeof(num));
		dep=0;
		k=0;
	}
return 0;}
