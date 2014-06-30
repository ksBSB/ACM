#include <stdio.h>
#include <string.h>

const int N = 1005;
struct Node {
	int val;
	Node* leftChild;
	Node* rightChild;
	Node (int val = 0) {
		this->val = val;
		leftChild = rightChild = NULL;
	}
};

int n, p, c, pre[N], in[N], post[N];

void init () {
	c = p = 1;
	for (int i = 1; i <= n; i++)
		scanf("%d", &pre[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &in[i]);
}

void buildTree (Node* &cur, int l, int r) {
	cur = new Node;

	if (l == r) {

		cur->val = pre[p++];
	} else {

		for (int i = l; i <= r; i++) {
			if (in[i] == pre[p]) {
				cur->val = pre[p++];
				if (i != l)
					buildTree (cur->leftChild, l, i-1);
				if (i != r)
					buildTree (cur->rightChild, i+1, r);
				break;
			}
		}
	}
}

void postOrder (Node* cur) {
	if (cur->leftChild != NULL)
		postOrder (cur->leftChild);

	if (cur->rightChild != NULL)
		postOrder (cur->rightChild);

	post[c++] = cur->val;
}

void Delete (Node* &cur) {
	if (cur->leftChild != NULL)
		Delete (cur->leftChild);

	if (cur->rightChild != NULL)
		Delete (cur->rightChild);

	delete cur;
}

int main () {
	while (scanf("%d", &n) == 1) {
		init ();

		Node* root = NULL;

		buildTree (root, 1, n);

		postOrder (root);

		printf("%d", post[1]);
		for (int i = 2; i <= n; i++)
			printf(" %d", post[i]);
		printf("\n");

		Delete (root);
	}
	return 0;
}
