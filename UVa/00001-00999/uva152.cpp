#include<stdio.h>
#include<string.h>
#include<math.h>

#define N 10
#define MAX 5005

struct rode{
	int x;
	int y;
	int z;
};
rode tree[MAX];
int vis[N];

int dis(rode a, rode b){
	return (int)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

int main(){
	// Init.
   	int cnt = 0;
	memset(vis, 0, sizeof(vis));

	// Read.
	while (scanf("%d%d%d", &tree[cnt].x, &tree[cnt].y,&tree[cnt].z), tree[cnt].x || tree[cnt].y || tree[cnt].z){
	   cnt++;
	}	   

	// Count. 
	for (int i = 0; i < cnt; i++){
		int min = 200000000, len;
		for (int j = 0; j < cnt; j++){
			if (i == j)
				continue;
			len = dis(tree[i], tree[j]);
			if (min > len)
				min = len;
		}

		if (min < 10)
			vis[min]++;
	}
			
	// Printf.
	for (int i = 0; i < N; i++)
		printf("%4d", vis[i]);
	printf("\n");

	return 0;
}
