#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	char value;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
} node;

typedef struct Tree {
	int isBinary;
	node* root;
} tree;

void print(tree* myTree) {
	printf("%c", myTree->root->value);
	if (myTree->root->left != NULL) {
		printf("(");
		tree newTree;
		newTree.root = myTree->root->left;
		newTree.isBinary = myTree->isBinary;
		print(&newTree);
		printf(")");
	}

	if (myTree->root->right != NULL) {
		printf(",");
		tree newTree;
		newTree.root = myTree->root->right;
		newTree.isBinary = myTree->isBinary;
		print(&newTree);
	}
}

void status(tree* myTree) {
	if (myTree == NULL) printf("No tree\n");
	else if (myTree->root == NULL) printf("No data\n");
	else {
		print(myTree);
		printf("\n");
	}
}

void create(tree** myTree, char root) {
	(*myTree) = (tree*)malloc(sizeof(tree));

	node* rootNode = (node*)malloc(sizeof(node));
	rootNode->value = root;
	rootNode->left = rootNode->right = rootNode->parent = NULL;

	(*myTree)->root = rootNode;
	char isBinary;
	printf("Is this tree binary?[y/n] : ");
	getchar();
	scanf("%c", &isBinary);
	(*myTree)->isBinary = (isBinary == 'y');
}

int isIn(tree* myTree, char value) {
	if (myTree->root->value == value) return 1;
	else {
		int left = 0;
		int right = 0;

		if (myTree->root->left != NULL) {
			tree leftTree;
			leftTree.root = myTree->root->left;
			left = isIn(&leftTree, value);
		}
		if (myTree->root->right != NULL) {
			tree rightTree;
			rightTree.root = myTree->root->right;
			right = isIn(&rightTree, value);
		}

		if (left == 1 || right == 1) return 1;
		else return 0;
	}
}

node* find(tree* myTree, char value) {
	if (myTree->root->value == value) return myTree->root;
	else {
		node* left = NULL;
		node* right = NULL;

		if (myTree->root->left != NULL) {
			tree leftTree;
			leftTree.root = myTree->root->left;
			left = find(&leftTree, value);
		}
		if (myTree->root->right != NULL) {
			tree rightTree;
			rightTree.root = myTree->root->right;
			right = find(&rightTree, value);
		}

		if (left != NULL) return left;
		else if (right != NULL) return right;
		else return NULL;
	}
}

int countSibling(tree* myTree, char target) {
	node* targetNode = find(myTree, target);

	while(targetNode->parent != NULL && targetNode->parent->right == targetNode) targetNode = targetNode->parent;
	int count = -1;
	while(targetNode != NULL) {
		count++;
		targetNode = targetNode->right;
	}
	return count;
}

void getSibling(tree* myTree, char target) {
	if (countSibling(myTree, target) == 0) {
		printf("No sibling\n");
		return;
	}

	node* targetNode = find(myTree, target);

	while(targetNode->parent != NULL && targetNode->parent->right == targetNode) targetNode = targetNode->parent;
	
	printf("{");
	int first = 0;
	while(targetNode != NULL) {
		if (targetNode->value != target) {
			if (first) printf(", ");
			printf("%c", targetNode->value);
			first = 1;
		}
		targetNode = targetNode->right;
	}
	printf("}\n");
}

void insertNode(tree* myTree, char parent, char* list) {
	if (myTree == NULL) {
		printf("ERROR: No tree\n");
		return;
	}
	else if (myTree->root == NULL) {
		printf("ERROR: No root\n");
		return;
	}

	node* parentNode = find(myTree, parent);

	if (parentNode == NULL) {
		printf("ERROR: Parent node does not exist\n");
		return;
	}
	
	node* newNode = (node*)malloc(sizeof(node));
	newNode->value = list[0];
	newNode->left = newNode->right = NULL;
	if (parentNode->left == NULL) {
		if (myTree->isBinary && strlen(list) > 2) {
			printf("ERROR: Too many children for binary tree\n");
			return;
		}
		newNode->parent = parentNode;
		parentNode->left = newNode;
	}
	else {
		node* current = parentNode->left;
		if (myTree->isBinary && countSibling(myTree, current->value) + strlen(list) >= 2) {
			printf("ERROR: Too many children for binary tree\n");
			return;
		}

		while(current->right != NULL) current = current->right;
		newNode->parent = current;
		current->right = newNode;
	}
	
	for(int i=1; i<strlen(list); i++) {
		node* tempNode = (node*)malloc(sizeof(node));
		tempNode->value = list[i];
		newNode->right = tempNode;
		tempNode->parent = newNode;
		tempNode->left = tempNode->right = NULL;

		newNode = tempNode;
	}
}

char* split(char* input) {
	char* output = (char*)malloc(sizeof(char) * strlen(input));
	int i=0;
	while(input[i] != '(') i++;
	i++;
	while(input[i] != ')') {
		if (input[i] != ',') output[strlen(output)] = input[i];
		i++;
	}
	return output;
}

char getParent(tree* myTree, char target) {
	node* targetNode = find(myTree, target);
	if (targetNode == NULL) {
		printf("ERROR: Such node doesn't exist");
		return ' ';
	}

	if (targetNode == myTree->root) return '\0';
	else {
		while(targetNode->parent->right == targetNode) targetNode = targetNode->parent;
		return targetNode->parent->value;
	}
}

void getChild(tree* myTree, char target) {
	node* targetNode = find(myTree, target);
	if (targetNode == NULL) {
		printf("ERROR: Such node doesn't exist\n");
		return;
	}

	node* current = targetNode->left;
	if (current == NULL) printf("No child\n");
	else {
		printf("{");
		printf("%c", current->value);
		current = current->right;
		while(current != NULL) {
			printf(", %c", current->value);
			current = current->right;
		}
		printf("}\n");
	}
}

int levelOfNode(tree* myTree, char target, int level) {
	if (myTree->root->value == target) return level;
	else {
		int left = -1;
		int right = -1;
		if (myTree->root->left != NULL) {
			tree newTree;
			newTree.root = myTree->root->left;
			left = levelOfNode(&newTree, target, level+1);
		}
		if (myTree->root->right != NULL) {
			tree newTree;
			newTree.root = myTree->root->right;
			right = levelOfNode(&newTree, target, level);
		}
		
		return (left > right) ? left : right;
	}
}

int levelOfTree(tree* myTree, int level) {
	int left = level;
	int right = level;
	if (myTree->root->left != NULL) {
		tree newTree;
		newTree.root = myTree->root->left;
		left = levelOfTree(&newTree, level+1);
	}
	if (myTree->root->right != NULL) {
		tree newTree;
		newTree.root = myTree->root->right;
		right = levelOfTree(&newTree, level);
	}

	return (left > right) ? left : right;
}

void delete(tree* myTree, char target) {
	node* targetNode = find(myTree, target);
	if (targetNode == NULL) {
		printf("ERROR: Such node doesn't exist\n");
		return;
	} else if (targetNode->left != NULL) {
		printf("ERROR: Only empty node can be deleted\n");
		return;
	} else if (targetNode->parent == NULL) {
		myTree->root = NULL;
		return;
	}

	if (targetNode->parent->left == targetNode) targetNode->parent->left = targetNode->right;
	else if (targetNode->parent->right == targetNode) targetNode->parent->right = targetNode->right;

	if (targetNode->right != NULL) targetNode->right->parent = targetNode->parent;

	free(targetNode);
}

void getAncestors(tree* myTree, char target) {
	node* targetNode = find(myTree, target);
	if (targetNode == NULL) {
		printf("ERROR: Such node doesn't exist\n");
		return;
	}

	while(targetNode->parent->right == targetNode) targetNode = targetNode->parent;
	targetNode = targetNode->parent;
	while(targetNode != NULL) {
		printf("%c ", targetNode->value);
		targetNode = targetNode->parent;
	}
	printf("\n");
}

void getElements(node* current) {
	printf("%c ", current->value);

	if (current->left != NULL) getElements(current->left);
	if (current->right != NULL) getElements(current->right);
}

void getDescendants(tree* myTree, char target) {
	node* targetNode = find(myTree, target);
	if (targetNode == NULL) {
		printf("ERROR: Such node doesn't exist\n");
		return;
	} else if (targetNode->left == NULL) {
		printf("No Descendants\n");
		return;
	}
	
	getElements(targetNode->left);
	printf("\n");
}

void degreeOfNode(tree* myTree, char target) {
	node* targetNode = find(myTree, target);
	if (targetNode == NULL) printf("ERROR: Such node doesn't exist\n");
	else if (targetNode->left == NULL) printf("0\n");
	else {
		int count = 0;
		targetNode = targetNode->left;
		while(targetNode != NULL) {
			count++;
			targetNode = targetNode->right;
		}
		printf("%d\n", count);
	}
}

int degreeOfTree(tree* myTree) {
	int left = 0;
	int right = 0;
	if (myTree->root->left != NULL) {
		tree newTree;
		newTree.root = myTree->root->left;
		left = degreeOfTree(&newTree);
	}
	if (myTree->root->right != NULL) {
		node* current = myTree->root->right;
		while(current != NULL) {
			if (current->left != NULL) {
				tree newTree;
				newTree.root = current->left;
				int temp = degreeOfTree(&newTree);
				if (right < temp) right = temp;
			}
			current = current->right;
		}
	}
	
	int currentDegree = countSibling(myTree, myTree->root->value) + 1;
	
	int max = left;
	if (max < right) max = right;
	if (max < currentDegree) max = currentDegree;

	return max;
}

int countNode(tree* myTree) {
	if (myTree == NULL || myTree->root == NULL) return 0;
	
	int left = 0;
	int right = 0;
	if (myTree->root->left != NULL) {
		tree newTree;
		newTree.root = myTree->root->left;
		left = countNode(&newTree);
	}
	if (myTree->root->right != NULL) {
		tree newTree;
		newTree.root = myTree->root->right;
		right = countNode(&newTree);
	}
	
	return left + right + 1;
}

void insertSibling(tree* myTree, char target, char* list) {
	if (myTree == NULL) {
		printf("ERROR: No tree\n");
		return;
	} else if (myTree->root == NULL) {
		printf("ERROR: No root\n");
		return;
	}

	node* targetNode = find(myTree, target);

	if (targetNode == NULL) {
		printf("ERROR: Such node doesn't exist\n");
		return;
	}
	
	if (myTree->isBinary && countSibling(myTree, target) + 1 + strlen(list) > 2) {
		printf("ERROR: Too many siblings for binary tree\n");
		return;
	}
	
	while(targetNode->right != NULL) targetNode = targetNode->right;

	for (int i=0; i<strlen(list); i++) {
		node* newNode = (node*)malloc(sizeof(node));
		newNode->value = list[i];
		newNode->parent = targetNode;
		targetNode->right = newNode;
		targetNode = newNode;
	}
}

tree* joinTrees(char root, tree* tree1, tree* tree2) {
	if (tree1 == NULL || tree2 == NULL) {
		printf("ERROR: Cannot merge NULL tree\n");
		return tree1;
	}

	tree* newTree = (tree*)malloc(sizeof(tree));
	newTree->root = (node*)malloc(sizeof(node));
	newTree->root->value = root;
	newTree->root->left = tree1->root;
	newTree->root->left->right = tree2->root;
	if (tree1->root) tree1->root->parent = newTree->root;
	if (tree2->root) tree2->root->parent = tree1->root;

	if (tree1->isBinary && tree2->isBinary) newTree->isBinary = 1;
	else newTree->isBinary = 0;

	return newTree;
}

void clear(tree** myTree) {*myTree = NULL;}

int main() {
	tree* tree1;
	tree* tree2;
	tree* myTree;
	
	char input[20];
	
	int line = 1;
	int process = 1;
	int treeNum = 1;
	
	while(process) {
		printf("[%2d] tree%d data status: ", line, treeNum);
		status(myTree);
		
		scanf("%s", input);

		switch(input[0]) {
			case '+':
				if (input[1] == '^') {
					if (myTree == NULL || myTree->root == NULL) {
						create(&myTree, input[2]);
						if (treeNum == 1) tree1 = myTree;
						else tree2 = myTree;
					}
					else printf("ERROR: Root already exists\n");
				}
				else insertNode(myTree, input[1], split(input));
				break;
			case 'S':
				getSibling(myTree, input[2]);
				break;
			case 'T':
				print(myTree);
				printf("\n");
				break;
			case 'P':
				printf("%c\n", getParent(myTree, input[2]));
				break;
			case 'C':
				getChild(myTree, input[2]);
				break;
			case 'L':
				if (input[1] == '(') printf("%d\n", levelOfNode(myTree, input[2], 0));
				else printf("%d\n", levelOfTree(myTree, 0));
				break;
			case '-':
				delete(myTree, input[1]);
				break;
			case 'A':
				getAncestors(myTree, input[2]);
				break;
			case 'D':
				getDescendants(myTree, input[2]);
				break;
			case 'G':
				if (input[1] == '(') degreeOfNode(myTree, input[2]);
				else printf("%d\n", degreeOfTree(myTree));
				break;
			case '#':
				printf("%d\n", countNode(myTree));
				break;
			case '=':
				insertSibling(myTree, input[2], split(input));
				break;
			case '@':
				// Change Working Tree
				if (input[1] == '1') myTree = tree1;
				else if (input[1] == '2') myTree = tree2;
				treeNum = input[1] - '0';
				break;
			case 'J':
				if (treeNum == input[6] - '0') printf("ERROR: Cannot merge one same tree\n");
				else myTree = joinTrees(input[2], myTree, (input[6] == '1') ? tree1 : tree2);
				break;
			case 'K':
				clear(&myTree);
				if (treeNum == 1) tree1 = NULL;
				else tree2 = NULL;
				break;
			case 'Q':
				process = 0;
				break;
		}
		line++;
	}

	return 0;
}
