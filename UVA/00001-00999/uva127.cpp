#include<iostream>
#include<stack>
using namespace std;
#define N 5
#define M 52
struct st{
	stack<char> n;
	stack<char>	c;
	st *p;
}*head=NULL,*move=NULL;
//head一直指向头部，move用于遍历。

st* find(int n);	//该函数用于寻找当前第n个牌堆，返回牌堆。

int main()
{ 
	char str[N];
	int i;
	
	while(cin>>str,str[0]!='#')
	{
		//Init.
		head=new st;
		head->n.push(str[0]);	
		head->c.push(str[1]);
		head->p=NULL;
		move=head;

		//Read.
		for(i = 1;i < 52; i++)
		{
			cin>>str;
			move->p=new st;
			move=move->p;
			move->n.push(str[0]);
			move->c.push(str[1]);
			move->p=NULL;
		}
		
		//Make.
		move=head->p;
		int t=1;

		while(move!=NULL)					//合并。
		{
			st *f=find(t-3);				//找到左边第三张。
			st *e=find(t-1);				//找到左边第一张。

			if(f == NULL);					//没有的时候跳过。
			else if(f->n.top() == move->n.top()||f->c.top() == move->c.top())
			{
				f->n.push(move->n.top());		//转移扑克。
				f->c.push(move->c.top());

				move->n.pop();					//去除第一张。
				move->c.pop();
				
				if(move->c.empty())				//链表的删除过程。
				{	e->p=move->p;
					delete move;
				}
				move=head->p;		//进行一次移动后，从头进行考虑。		
				t=1;
				continue;
			}

			if(e == NULL);
			else if(e->n.top() == move->n.top()||e->c.top() == move->c.top())
			{
				e->n.push(move->n.top());		//转移扑克。
				e->c.push(move->c.top());

				move->n.pop();					//去除第一张。
				move->c.pop();
				
				if(move->c.empty())			//链表的删除过程。
				{	e->p=move->p;
					delete move;
				}
				move=head->p;				//进行一次移动后，从头进行考虑。
				t=1;
				continue;
			}

			move=move->p;
			t++;
		}

		move=head;
		for(i = 0;move!=NULL;i++)		//计算牌堆数。
			move=move->p;

		if(i==1)
			cout<<i<<" pile remaining:";
		else
			cout<<i<<" piles remaining:";

		for(move=head;move!=NULL;move=move->p)
			cout<<" "<<move->c.size();
		cout<<endl;
	}

return 0;}

st* find(int n)
{
	int i;
	st *f=head;
	
	if(n < 0)	return f=NULL;

	for(i = 0;i < n; i++)
		f=f->p;
		
	return f;
}
