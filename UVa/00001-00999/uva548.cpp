#include<stdio.h>
#include<string.h>

#define N 100005
struct node{
	node(int a)
	{
		sum=0;
		num=a;
		lift=NULL;
		right=NULL;
	}
	int sum;
	int num;
	node *lift;
	node *right;
};

int p[N];
int q[N];
int min,cnt;
int move;

int find(int k)
{	int i;
	for(i = 0;;i++)
		if(p[i]==k)
			return i;
}

node* grow(int a,int b);
void print(node *f);

int main()
{
	char c;
	int i;

	//Init.
	memset(p,0,sizeof(p));
	memset(q,0,sizeof(q));
	

	while(scanf("%d%c",&p[0],&c)==2)
	{
		min=1000000;
		//Read.
		for(i = 1;c != '\n'; i++)
			scanf("%d%c",&p[i],&c);
		
		int k;
		c='\0';
		for(k = 0;c != '\n'; k++)
			scanf("%d%c",&q[k],&c);

		move=k-1;
		int t=find(q[move]);
		node *head;
		head=new node(q[move--]);
		head->right=grow(t,k);
		head->lift=grow(-1,t);

		head->sum=head->num;
		print(head);
		printf("%d\n",cnt);
	}
	return 0;}

node *grow(int a,int b)
{
	if(a == b-1)	return NULL;
	else
	{
		int t=find(q[move]);
		node *f;
		f=new node(q[move--]);
		f->right=grow(t,b);
		f->lift=grow(a,t);
	
		return f;
	}
}
void print(node *f)
{
	if(f->lift==NULL&&f->right==NULL)
	{	if(min > f->sum)
		{	min=f->sum;
			cnt=f->num;
		}
		else if(min == f->sum&& cnt > f->num)
			cnt=f->num;

	}
	else
	{
		if(f->lift!=NULL)
		{
			f->lift->sum=f->lift->num+f->sum;
			print(f->lift);
		}

		if(f->right!=NULL)
		{	f->right->sum=f->right->num+f->sum;
			print(f->right);
		}
	}
	delete f;
}
