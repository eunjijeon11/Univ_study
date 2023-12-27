#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *left;
	struct Node *right;
} node;

void preorder(node *current) {
	printf("%d ", current->value);
	if (current->left) preorder(current->left);
	if (current->right) preorder(current->right);
}

void inorder(node *current) {
	if (current->left) inorder(current->left);
	printf("%d ", current->value);
	if (current->right) inorder(current->right);
}

void postorder(node *current) {
	if (current->left) postorder(current->left);
	if (current->right) postorder(current->right);
	printf("%d ", current->value);
}

void insert(node *head, int value) {
	node *current = head;
	node *next = current;
	while(next) {
		current = next;
		if (value < current->value) next = current->left;
		else next = current->right;
	}
	node *newNode = malloc(sizeof(node));
	newNode->value = value;
	if (current->value > value) current->left = newNode;
	else current->right = newNode;
}

int main() {

	int arr[] = {41, 74, 16, 53, 65, 25, 46, 55, 63, 70, 42, 62, 64};
	node tree;
	tree.value = 60;

	for (int i=0; i<13; i++) insert(&tree, arr[i]);

	printf("preorder: ");
	preorder(&tree);

	printf("\ninorder: ");
	inorder(&tree);

	printf("\npostorder: ");
	postorder(&tree);
	printf("\n");

	return 0;
}
