#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

#define N 1005
#define M 305

struct T{
	char name[M];
	int ti, vic, draw, fail, get, lose;
	T(){
		memset(name, 0, sizeof(name));
		ti = vic = draw = fail = get = lose = 0;
	}
};
void change_down(char str[]){
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
}

int handle(char str[], T team[], int n){
	char tem[3][M];
	int len = strlen(str), cnt = 0, sex = 0;
	int num[3] = {0};
	for (int i = 0; i < len; i++){
		if (str[i] != '#' && sex == 0)
			tem[0][cnt++] = str[i];
		else if(str[i] == '#' && sex == 0){
			tem[0][cnt] = '\0';
			sex++;
			cnt = 0;
		}
		else if(str[i] != '@' && sex == 1)
			num[0] = num[0] * 10 + str[i] - '0';
		else if(str[i] == '@' && sex == 1)
			sex++;
		else if(str[i] != '#' && sex == 2)
			num[1] = num[1] * 10 + str[i] - '0';
		else if(str[i] == '#' && sex == 2)
			sex++;
		else
			tem[1][cnt++] = str[i];
	}
	tem[1][cnt] = '\0';
	len = cnt = -1;
	
	for (int i = 0; i < n; i++){
        if (len >= 0 && cnt >= 0)
            break;
		if (strcmp(team[i].name, tem[0]) == 0)
            len = i;
        if (strcmp(team[i].name, tem[1]) == 0)
			cnt = i;
	}
    
	if (num[0] > num[1]){
		team[len].vic++;
		team[cnt].fail++;
	}
	else if(num[0] < num[1]){
		team[len].fail++;
		team[cnt].vic++;
	}
	else{
		team[len].draw++;
		team[cnt].draw++;
	}
    
	team[len].get += num[0];
	team[len].lose += num[1];
	team[cnt].get += num[1];
	team[cnt].lose += num[0];
	team[len].ti++;
	team[cnt].ti++;
}

int cmp(const T &a, const T &b){
	if (a.vic * 3 + a.draw > b.vic * 3 + b.draw)
		return 1;
	else if (a.vic * 3 + a.draw < b.vic * 3 + b.draw)
		return 0;
	else if(a.vic > b.vic)
		return 1;
	else if(a.vic < b.vic)
		return 0;
	else if(a.get - a.lose > b.get - b.lose)
		return 1;
	else if(a.get - a.lose < b.get - b.lose)
		return 0;
	else if(a.get > b.get)
		return 1;
	else if(a.get < b.get)
		return 0;
	else if(a.ti < b.ti)
		return 1;
	else if(a.ti > b.ti)
		return 0;
	else{
		char str1[M], str2[M];
		strcpy(str1, a.name);
		strcpy(str2, b.name);
		change_down(str1);
		change_down(str2);
		return strcmp(str1, str2) < 0;
	}
}
int main(){
	int t, n, m;
	char game_name[N], game_data[N];
	scanf("%d%*c", &t);
	while (t--){
        
		// Init.
		memset(game_name, 0, sizeof(game_name));
		T team[M];
        
		// Read.
		gets(game_name);
		scanf("%d%*c", &n);
		for (int i = 0; i < n; i++)
			gets(team[i].name);
		scanf("%d%*c", &m);
		for (int i = 0; i < m; i++){
			memset(game_data, 0, sizeof(game_data));
			gets(game_data);
			handle(game_data, team, n);
		}
        
		sort(team, team + n, cmp);
        
		// Printf.
		puts(game_name);
		for (int i = 0; i < n; i++)
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n", i + 1, team[i].name, team[i].vic * 3 + team[i].draw, team[i].ti, team[i].vic, team[i].draw, team[i].fail, team[i].get - team[i].lose, team[i].get, team[i].lose);
		if(t)
			printf("\n");
	}
	return 0;}
