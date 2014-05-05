#include <stdio.h>
#include <string.h>

const int N = 1e5+5;
struct Node {
	int val;
	Node* leftChild;
	Node* rightChild;
	Node () {
		leftChild = rightChild = NULL;
	}
	Node (int val) {
		this->val = val;
		leftChild = rightChild = NULL;
	}
};

int n, c, ans[N];

void Insert (Node* &cur, int v) {
	if (cur == NULL) {
		cur = new Node(v);
	} else if (cur->val > v) {
		Insert(cur->leftChild, v);
	} else {
		Insert(cur->rightChild, v);
	}
}

void PreOrder (Node* cur) {
	ans[c++] = cur->val;
	if (cur->leftChild != NULL) PreOrder(cur->leftChild);
	if (cur->rightChild != NULL) PreOrder(cur->rightChild);
}

void Delete (Node* cur) {
	if (cur->leftChild != NULL) Delete(cur->leftChild);
	if (cur->rightChild != NULL) Delete(cur->rightChild);
	delete cur;
}

int main () {
	int a;
	while (scanf("%d", &n) == 1) {
		c = 0;
		Node* root = NULL;

		for (int i = 0; i < n; i++) {
			scanf("%d", &a);
			Insert(root, a);
		}
		PreOrder(root);
		printf("%d", ans[0]);
		for (int i = 1; i < n; i++) 
			printf(" %d", ans[i]);
		printf("\n");
		Delete(root);
	}	
	return 0;
}
