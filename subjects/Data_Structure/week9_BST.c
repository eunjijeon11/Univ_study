#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPERATOR_COUNT 17

typedef struct command {
	char operator;
	int operand;
} cmd;

typedef struct Node {
	int value;
	struct Node* left;
	struct Node* right;
} node;

typedef struct BinarySearchTree {
	node* root;
} BST;

typedef struct NodeInfo {
	node* targetNode;
	node* parentNode;
	char direction;
} nodeInfo;

const char operators[] = {'+', 'P', 'I', 'R', 'N', 'X', 'F', '-', 'H', 'G', 'L', '#', 'C', '@', '?','~', 'Q'};

cmd commandParser(char* input) {
	int i = 0;
	while(input[i] == ' ') i++;
	
	int flag = 1;
	cmd command;
	for (int j=0; j<OPERATOR_COUNT; j++) {
		if (input[i] == operators[j]) {
			command.operator = input[i];
			flag = 0;
			i++;
			break;
		}
	}
	
	if (flag) {
		printf("ERROR: Wrong operator\n");
		return command;
	}

	if (input[i] == '(') i++;

	if ('0' <= input[i] && input[i] <= '9') {
		command.operand = 0;
		while (input[i] != '\0' && input[i] != ')') {
			command.operand = command.operand * 10 + input[i] - '0';
			i++;
		}
	}

	return command;
}

void printNode(node* currentNode) {
	if (currentNode != NULL) printf("%d", currentNode->value);
	else return;

	if (currentNode->left != NULL || currentNode->right != NULL) {
		printf("(");
		printNode(currentNode->left);
		printf(",");
		printNode(currentNode->right);
		printf(")");
	}
}

void print(BST* myBST) {
	if (myBST == NULL) printf("No Tree\n");
	else {
		printf("(");
		printNode(myBST->root);
		printf(")\n");
	}
}

void create(BST** myBST, int root) {
	*myBST = (BST*)malloc(sizeof(BST));
	node* rootNode = (node*)malloc(sizeof(node));
	rootNode->value = root;
	(*myBST)->root = rootNode;
}

void insertNode(BST* myBST, int value) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->value = value;

	node* currentNode = myBST->root;
	while(1) {
		if (currentNode->value > value) {
			if (currentNode->left == NULL) {
				currentNode->left = newNode;
				break;
			}
			else currentNode = currentNode->left;
		}
		else if (currentNode->value < value) {
			if (currentNode->right == NULL) {
				currentNode->right = newNode;
				break;
			}
			else currentNode = currentNode->right;
		}
		else {
			printf("ERROR: Cannot insert duplicate value\n");
			return;
		}
	}
}

void inorderTraversal(node* curNode) {
	if (curNode->left != NULL) inorderTraversal(curNode->left);

	printf("%d ", curNode->value);

	if (curNode->right != NULL) inorderTraversal(curNode->right);
}

void rightRootLeftTraversal(node* curNode) {
	if (curNode->right != NULL) rightRootLeftTraversal(curNode->right);

	printf("%d ", curNode->value);

	if (curNode->left != NULL) rightRootLeftTraversal(curNode->left);
}

int getMin(BST* myBST) {
	node* currentNode = myBST->root;
	while(currentNode->left != NULL) currentNode = currentNode->left;
	return currentNode->value;
}

int getMax(BST* myBST) {
	node* currentNode = myBST->root;
	while(currentNode->right != NULL) currentNode = currentNode->right;
	return currentNode->value;
}

int height(node* currentNode, int curHeight) {
	int left = 0;
	int right = 0;
	if (currentNode->left != NULL) left = height(currentNode->left, curHeight+1);
	if (currentNode->right != NULL) right = height(currentNode->right, curHeight+1);

	int max = curHeight;
	if (left > max) max = left;
	if (right > max) max = right;

	return max;
}

void findNode(BST* myBST, int value) {
	int history[height(myBST->root, 0)];
	int i = 0;

	node* currentNode = myBST->root;
	while(1) {
		if (currentNode == NULL) {
			printf("ERROR: Such node doesn't exist\n");
			return;
		}

		if (value == currentNode->value) break;
		else if (value < currentNode->value) {
			currentNode = currentNode->left;
			history[i++] = 1;
		} else {  // value > currentNode->value
			currentNode = currentNode->right;
			history[i++] = 2;
		}
	}

	printf("Root");
	for (i=0; i<height(myBST->root, 0); i++) {
		if (history[i] != 1 && history[i] != 2) break;
		printf(" > %s", (history[i]==1) ? "Left" : "Right");
	}
	printf("\n");
}

nodeInfo* getNodeInfo(BST* myBST, int value) {
	nodeInfo* info = (nodeInfo*)malloc(sizeof(nodeInfo));
	if (myBST->root->value == value) {
		info->targetNode = myBST->root;
		info->direction = 'R';
		return info;
	}

	node* currentNode = myBST->root;
	node* nextNode;
	char dir;
	while(1) {
		if (currentNode->value > value) {
			nextNode = currentNode->left;
			dir = 'l';
		} else {
			nextNode = currentNode->right;
			dir = 'r';
		}

		if (nextNode == NULL) return NULL;
		else if (nextNode->value == value) break;
		else currentNode = nextNode;
	}

	info->targetNode = nextNode;
	info->parentNode = currentNode;
	info->direction = dir;

	return info;
}

void clear(BST** myBST) {*myBST = NULL;}

void deleteNode(BST** myBST, int value) {
	nodeInfo* info = getNodeInfo(*myBST, value);
	if (info == NULL) {
		printf("ERROR: Such node doesn't exist\n");
		return;
	}
	if (info->targetNode->left == NULL && info->targetNode->right == NULL) {
		if (info->direction == 'l') info->parentNode->left = NULL;
		else if (info->direction == 'r') info->parentNode->right = NULL;
		else {
			clear(myBST);
			return;
		}
	} else if (info->targetNode->left != NULL && info->targetNode->right == NULL) {
		if (info->direction == 'l') info->parentNode->left = info->targetNode->left;
		else if (info->direction == 'r') info->parentNode->right = info->targetNode->left;
		else (*myBST)->root = info->targetNode->left;
	} else if (info->targetNode->left == NULL && info->targetNode->right != NULL) {
		if (info->direction == 'l') info->parentNode->left = info->targetNode->right;
		else if (info->direction == 'r') info->parentNode->right = info->targetNode->right;
		else (*myBST)->root = info->targetNode->right;
	} else {
		char choice;
		getchar();
		printf("Select the direction of a successor[l/r]: ");
		scanf("%c", &choice);

		node* successor;
		if (choice == 'l') {
			successor = info->targetNode->left;
			while(successor->right != NULL) successor = successor->right;
		} else {
			successor = info->targetNode->right;
			while(successor->left != NULL) successor = successor->left;
		}
		
		node* newNode = (node*)malloc(sizeof(node));
		newNode->value = successor->value;
		deleteNode(myBST, successor->value);
		
		newNode->left = info->targetNode->left;
		newNode->right = info->targetNode->right;
		if (info->direction == 'l') info->parentNode->left = newNode;
		else if (info->direction == 'r') info->parentNode->right = newNode;
		else (*myBST)->root = newNode;
	}
	
	info->targetNode->left = info->targetNode->right = NULL;
	free(info->targetNode);
}

void getRightChild(BST* myBST, int value) {
	nodeInfo* info = getNodeInfo(myBST, value);
	if (info == NULL) printf("ERROR: Such node doesn't exist\n");
	else if (info->targetNode->right == NULL) printf("NULL\n");
	else printf("%d\n", info->targetNode->right->value);
}

void getLeftChild(BST* myBST, int value) {
	nodeInfo* info = getNodeInfo(myBST, value);
	if (info == NULL) printf("ERROR: Such node doesn't exist\n");
	else if (info->targetNode->left == NULL) printf("NULL\n");
	else printf("%d\n", info->targetNode->left->value);
}

int countNode(node* curNode) {
	int left = 0;
	int right = 0;

	if (curNode->left != NULL) left = countNode(curNode->left);
	if (curNode->right != NULL) right = countNode(curNode->right);

	return left + right + 1;
}

int isIn(BST* myBST, int value) {
	nodeInfo* info = getNodeInfo(myBST, value);
	if (info == NULL) return 0;
	else return 1;
}

int getRoot(BST* myBST) {
	if (myBST == NULL) {
		printf("ERROR: No tree\n");
		return -1;
	}
	return myBST->root->value;
}

int main() {

	BST* myBST;

	int process = 1;
	int line = 1;
	cmd command;

	char input[8];
	while(process) {

		printf("[%d] current data status: ", line);
		print(myBST);

		scanf("%s", input);
		command = commandParser(input);

		switch(command.operator) {
			case '+':
				if(myBST == NULL) create(&myBST, command.operand);
				else insertNode(myBST, command.operand);
				break;
			case 'P':
				print(myBST);
				break;
			case 'I':
				inorderTraversal(myBST->root);
				printf("\n");
				break;
			case 'R':
				rightRootLeftTraversal(myBST->root);
				printf("\n");
				break;
			case 'N':
				printf("%d\n", getMin(myBST));
				break;
			case 'X':
				printf("%d\n", getMax(myBST));
				break;
			case 'F':
				findNode(myBST, command.operand);
				break;
			case '-':
				deleteNode(&myBST, command.operand);
				break;
			case 'H':
				printf("%d\n", height(myBST->root, 0));
				break;
			case 'G':
				getRightChild(myBST, command.operand);
				break;
			case 'L':
				getLeftChild(myBST, command.operand);
				break;
			case '#':
				printf("%d\n", countNode(myBST->root));
				break;
			case 'C':
				clear(&myBST);
				break;
			case '@':
				nodeInfo* info = getNodeInfo(myBST, command.operand);
				if (info->parentNode) 
					printf("parent node: %d %p -> (%s) ", 
							info->parentNode->value, info->parentNode, (info->direction='l') ? "left" : "right");
				printf("targetNode: %d %p ", info->targetNode->value, info->targetNode);
				findNode(myBST, command.operand);
				break;
			case '?':
				printf("%d %s member of the tree\n", command.operand, (isIn(myBST, command.operand)) ? "is" : "is not");
				break;
			case '~':
				printf("%d\n", getRoot(myBST));
				break;
			case 'Q':
				process = 0;
				break;
			default:
				break;
		}
		line++;
	}

	return 0;
}
