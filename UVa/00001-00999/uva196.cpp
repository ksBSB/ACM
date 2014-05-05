#include<stdio.h>
#include<string.h>

#define N 1005*1005

int num[N], map[N][100], in[N];
int r, c;

int is_alph(char c){
	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}
int is_num(char c){
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int DFS(int k){
	int sum = 0;
	for (int i = 0; i < in[k]; i++){
		if (in[map[k][i]] && !DFS(map[k][i]))
			return 0;
		sum += num[map[k][i]];
	}
	in[k] = 0;
	num[k] = sum;
	return 1;
}

void toposort(){
	for (int i = 0; i < r * c; i++)
		if (in[i] && !DFS(i))
			return ;
	return;
}

int main(){
	int t;
	scanf("%d", &t);
	while (t--){
		// Init.
		memset(map, 0, sizeof(map));
		memset(num, 0, sizeof(num));
		memset(in, 0, sizeof(in));

		// Read.
		scanf("%d%d", &c, &r);
		for (int i = 0; i < r * c; i++){
			char str[N];
			scanf("%s", str);
			int move = 1, f = 0, t = 0;

			if (str[0] == '='){
				int len = strlen(str);
				str[len] = '+';
				str[len + 1] = '\0';
				while (str[move]){
					if (is_alph(str[move]))
						f = f * 26 + str[move] - 'A' + 1;
					else if (is_num(str[move]))
						t = t * 10 + str[move] - '0';
					else{
						map[i][in[i]++] = (t - 1) * c + f - 1;
						t = f = 0;
					}
					move++;
				}
			}
			else
				sscanf(str, "%d", &num[i]);
		}

		// Handle.
		toposort();

		// Printf.
		for (int i = 0; i < r * c; i++){
			if (i && !(i % c))
				printf("\n");
			if (i % c)
				printf(" ");
			printf("%d", num[i]);
		}
		printf("\n");
	}
	return 0;}
