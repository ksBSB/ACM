#include<iostream>
#include<cstring>
using namespace std;

struct coordinate{
	int x;
	int y;
	int color;
	int dre;
};

int	 drg[4][2]={{-1,0},{0,1},{0,-1},{1,0}};
char map[25][25];
int  m,n;
coordinate en;
char co[4][5][25][25];
int  t;

void buile_map();
int DFS(coordinate *head,coordinate *end);

int main()
{
	int re=1,bo;
	while(cin>>m>>n,m||n)
	{
		if(re!=1)
			cout<<endl;
		cout<<"Case #"<<re<<endl;
		
		buile_map();

		coordinate pace[15000];

		pace[0].x=en.x,pace[0].y=en.y;
		t=0,pace[0].color=0,pace[0].dre=0;		//统计成员初始化；

		memset(co,'0',sizeof(co));

		bo=DFS(pace,pace+1);
		
		if(bo)
			cout<<"minimum time = "<<t<<" sec"<<endl;	
		else
			cout<<"destination not reachable"<<endl;

		re++;
	}

return 0;}	

void buile_map()
{
	memset(map,0,sizeof(map));

	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
		{
			cin>>map[i][j];
			
			if(map[i][j]=='S')
				en.x=i,en.y=j;
		}
}

int DFS(coordinate *head,coordinate *end)
{
	if(head==end)
		return 0;
	else 
	{	
		t++;

		coordinate *move=end;
		
		for(;head!=end;head++)
		{
			for(int i=0;i<4;i++)
			{
				if(head->dre==3-i)	continue;
				else if(head->dre==i)
				{	int p,q;	
					p=head->x+drg[i][0];
					q=head->y+drg[i][1];
					
					if(p<0||p>=m)		continue;
					if(q<0||q>=n)		continue;
					if(map[p][q]=='#')	continue;

					move->color=(head->color+1)%5;
					move->x=p,move->y=q;
					move->dre=i;
				}
				else
				{	move->color=head->color;
					move->x=head->x,move->y=head->y;
					move->dre=i;
				}	
				
				if(co[move->dre][move->color][move->x][move->y]=='1')		continue;		//判断该位置是否重复路过；
		
				co[i][move->color][move->x][move->y]='1';
				
				if(map[move->x][move->y]=='T'&&move->color==0)	return 1;
				
				move++;
			}
		}
		if(DFS(end,move))	return 1;
		else				return 0;		
	}
	return 0;}
