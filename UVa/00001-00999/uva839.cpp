#include<stdio.h>
int bo;
int DFS(){
	int wl, dl, wr, dr;
	scanf("%d%d%d%d", &wl, &dl, &wr, &dr);
	if (wl == 0)
		wl = DFS();
	if (wr == 0)
		wr = DFS();
	if (wl * dl != wr * dr)
		bo = 1;
	return wr + wl;
}

int main(){
	int t;
	scanf("%d", &t);
	while (t--){
		bo = 0;
		DFS();
		if (bo)
			printf("NO\n");
		else
			printf("YES\n");
		if (t)
			printf("\n");
	}
	return 0;}
