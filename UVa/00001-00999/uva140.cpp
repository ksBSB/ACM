#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 1000
#define M 30

int Min, g[M][M], bir[M], son[N];
int n, num[N], rec[N];
char str[N];

bool judge(int u, int v){
    for (int i = 0; i < son[u]; i++)
	if (v == g[u][i])
	    return false;
    return true;
}

int find(int k){
    for (int i = 0; i < n; i++)
	if (num[i] == k)
	    return i;
}

void handle(){
    char f = str[0], s;
    bir[f - 'A'] = 1;
    int len = strlen(str);
    for (int i = 1; i < len; i++){
	if (str[i] == ';')
	{
	    f = str[++i];
	    bir[f - 'A'] = 1;
	}
	else if (str[i] == ':')
	    continue;
	else{
	    s = str[i];
	    int a = f - 'A', b = s - 'A';
	    if (judge(a, b)){
		g[a][son[a]++] = b;
		g[b][son[b]++] = a;
	    }
	    bir[b] = 1;
	}
    }
}

void count(){
    int Max = 0;
    for (int i = 0; i < n; i++){
	for (int j = 0; j < son[num[i]]; j++){
	    int t = abs(find(g[num[i]][j]) - i);
	    if (Max < t)
		Max = t;
	}
    }
    if (Max < Min){
	memcpy(rec, num, sizeof(num));
	Min = Max;
    }
}

int main(){
    while (1){
	scanf("%s", str);
	if (strcmp(str, "#") == 0)
	    break;
	// Init.
	memset(g, 0, sizeof(g));
	memset(bir, 0, sizeof(bir));
	memset(num, 0, sizeof(num));
	memset(rec, 0, sizeof(rec));
	memset(son, 0, sizeof(son));
	Min = 0x7fffffff;
	n = 0;

	// Handle.
	handle();
	for (int i = 0; i < M; i++)
	    if (bir[i])	    
		num[n++] = i;

	sort(num, num + n);
	do{
	    count();
	}while (next_permutation(num, num + n));
	for (int i = 0; i < n; i++)
	    printf("%c ", 'A' + rec[i]);
	printf("-> %d\n", Min);
	sizeof(str, 0, sizeof(str));
    }
    return 0;
}
