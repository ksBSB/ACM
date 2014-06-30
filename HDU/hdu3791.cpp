#include <stdio.h>
#include <string.h>

struct Node{
    int val;
    Node* left;
    Node* right;
    Node(){
        val = 0;
        left = right = NULL;
    }
};

void Insert(Node* &root,int a){
    if(root == NULL){
        root = new Node;
        root->val = a;
    } else if(root->val > a)
        Insert(root->left, a);
    else
        Insert(root->right, a);
}

bool equal_tree(Node* root, Node* root1){

	if(root == NULL && root1 == NULL)
		return true;

	if (root != NULL && root1 != NULL) {
		if (root->val != root1->val) return false;

		if(equal_tree(root->left,root1->left)&&equal_tree(root->right,root1->right))
			return true;
		else 
			return false;
	}
	return false;
}

void Delete(Node* &root){
	if(root->left != NULL)
		Delete(root->left);
	if(root->right != NULL)
		Delete(root->right);
	delete root;
}

const int N = 105;
char node[N];

int main(){
	int n,a,flag,i,len,n1;

	while(scanf("%d", &n) == 1 && n){
		Node* root = NULL;
		scanf("%s",node);
		len=strlen(node);
		for(i = 0; i < len; i++){
			a = node[i]-'0';
			Insert(root,a);
		}
		while(n--){
			Node* root1 = NULL;
			scanf("%s", node);
			for(i = 0; i < len; i++){
				a=node[i]-'0';
				Insert(root1,a);
			}

			flag=equal_tree(root,root1);

			if(flag==1)
				printf("YES\n");
			else
				printf("NO\n");
			Delete(root1);
		}
		Delete(root);
	}
	return 0;
}
