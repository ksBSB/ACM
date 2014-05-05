#include<stdio.h>
#include<string.h>

#define N 10005
struct rode{
	int value;
	rode *lift;
	rode *right;
	rode(){
		value = 0;
		lift = right = NULL;
	}
};
int n, num[N];

rode *build(){
	char c;
	int cnt = 0, bo = 0;
	rode *now;
	now = new rode;

	while (scanf("%c", &c)){
		if (c >= '0' && c <= '9'){
			now -> value = now -> value * 10 + c - '0';
		}
		else if (c == '(' && cnt == 0){
			now -> lift = build();
			cnt++;
		}
		else if (c == '(' && cnt == 1){
			now -> right = build();
			cnt++;
		}
		else if(c == ')')
			break;
		else if (c == '-')
			bo = 1;
	}

	if (bo)
		now -> value = - now -> value;
	if (now -> value == 0 && cnt == 0)
		return NULL;
	else
		return now;
}

void BFS(rode * now, int sum){
	if (now == NULL)
		return;
	sum += now -> value;

	if (now -> lift == NULL && now -> right == NULL)
		num[n++] = sum;
	else{
		if (now -> lift != NULL)
			BFS(now -> lift, sum);
		if (now -> right != NULL)
			BFS(now -> right, sum);
	}
}	
void delete_tree(rode * now){
	if (now == NULL)
		return ;
	if (now -> lift != NULL)
		delete_tree(now -> lift);
	if (now -> right != NULL)
		delete_tree(now -> right);
	delete now;
}
int main(){
	int sum;
	char c;
	rode *head;

	while (scanf("%d", &sum) != EOF){
		// Init.
		memset(num, 0, sizeof(num));
		head = NULL;
		n = 0;

		// Build tree;
		while (scanf("%c", &c) != EOF){
			if (c == '('){
				head = build();
				break;
			}
		}

		// BFS.
		BFS(head, 0);

		// Judge.
		int i;
		for (i = 0; i < n; i++)
			if (num[i] == sum)
				break;
		if (i == n)
			printf("no\n");
		else
			printf("yes\n");

		// Delete.
		delete_tree(head);
	}
	return 0;}
