#include <stdio.h>
#include <stdlib.h>

typedef struct command {
	char operator_;
	int operand_;
} cmd;

cmd commandParser(char* input);

typedef struct Node {
	int value;
	int height;
	struct Node *left;
	struct Node *right;
} node;

typedef struct AVLTree {
	node *root;
} AVL;

void printNode(node* curNode) {
	printf("%d", curNode->value);
	if (curNode->left || curNode->right) {
		printf("(");
		if (curNode->left) printNode(curNode->left);
		printf(",");
		if (curNode->right) printNode(curNode->right);
		printf(")");
	}
}

void print(AVL *myAVL) {
	if (myAVL == NULL) printf("No Tree\n");
	else {
		printf("(");
		printNode(myAVL->root);
		printf(")\n");
	}
}

void create(AVL **myAVL, int value) {
	*myAVL = (AVL*)malloc(sizeof(AVL));
	node* rootNode = (node*)malloc(sizeof(node));
	rootNode->value = value;
	rootNode->height = 0;
	(*myAVL)->root = rootNode;
}

int getBalanceFactor(node *curNode) {
	int left = -1;
	int right = -1;
	if (curNode->left) left = curNode->left->height;
	if (curNode->right) right = curNode->right->height;

	return left - right;
}

node* findParentNode(AVL *myAVL, node *targetNode) {
	if (myAVL->root == targetNode) return NULL;

	node* curNode = myAVL->root;
	node* nextNode = curNode;
	while (nextNode != NULL) {
		curNode = nextNode;
		if (curNode->value > targetNode->value) {
			if (curNode->left == targetNode) return curNode;
			else nextNode = curNode->left;
		} else if (curNode->value < targetNode->value) {
			if (curNode->right == targetNode) return curNode;
			else nextNode = curNode->right;
		}
	}
	printf("ERROR: Such node doesn't exist!\n");
	return targetNode;
}

void RRotate(AVL *myAVL, node *targetNode) {
	node* parentNode = findParentNode(myAVL, targetNode);
	node* childNode = targetNode->left;

	if (parentNode == NULL) myAVL->root = childNode;
	else if (parentNode->left == targetNode) parentNode->left = childNode;
	else if (parentNode->right == targetNode) parentNode->right = childNode;

	if (childNode->right) targetNode->left = childNode->right;
	else targetNode->left = NULL;
	childNode->right = targetNode;
}

void LRotate(AVL *myAVL, node *targetNode) {
	node* parentNode = findParentNode(myAVL, targetNode);
	node* childNode = targetNode->right;

	if (parentNode == NULL) myAVL->root = childNode;
	else if (parentNode->left == targetNode) parentNode->left = childNode;
	else if (parentNode->right == targetNode) parentNode->right = childNode;

	if (childNode->left) targetNode->right = childNode->left;
	else targetNode->right = NULL;
	childNode->left = targetNode;
}

int setHeight(node *curNode) {
	if (curNode->left == NULL && curNode->right == NULL) return 0; // leaf

	int left = 0;
	int right = 0;
	if (curNode->left) left = setHeight(curNode->left);
	if (curNode->right) right = setHeight(curNode->right);

	curNode->height = 1 + ((left > right) ? left : right);
	return curNode->height;
}

void balanceTree(AVL *myAVL, node *curNode) {
	if (curNode->left) balanceTree(myAVL, curNode->left);
	if (curNode->right) balanceTree(myAVL, curNode->right);

	int BF = getBalanceFactor(curNode);
	// printf("%d\n", BF);
	if (BF < 2 && BF > -2) return;

	int leftBF = 0;
	int rightBF = 0;
	if (curNode->left) leftBF = getBalanceFactor(curNode->left);
	if (curNode->right) rightBF = getBalanceFactor(curNode->right);

	if (BF == 2 && leftBF == 1) RRotate(myAVL, curNode);
	else if (BF == 2 && leftBF == -1) {
		LRotate(myAVL, curNode->left);
		RRotate(myAVL, curNode);
	} else if (BF == -2 && rightBF == -1) LRotate(myAVL, curNode);
	else if (BF == -2 && rightBF == 1) {
		RRotate(myAVL, curNode->right);
		LRotate(myAVL, curNode);
	}

	setHeight(myAVL->root);
}

void insertNode(AVL *myAVL, int value) {
	node* curNode = myAVL->root;
	node* nextNode = curNode;
	while(nextNode != NULL) {
		curNode = nextNode;
		if (value < curNode->value) nextNode = curNode->left;
		else if (value > curNode->value) nextNode = curNode->right;
		else {
			printf("ERROR: The node already exists!\n");
			return ;
		}
	}

	node* newNode = (node*)malloc(sizeof(node));
	newNode->value = value;
	newNode->height = 0;

	if (value < curNode->value) curNode->left = newNode;
	else curNode->right = newNode;

	setHeight(myAVL->root);
	balanceTree(myAVL, myAVL->root);
}

node* search(AVL *myAVL, int value) {
	node* curNode = myAVL->root;

	while(curNode != NULL) {
		if (curNode->value == value) return curNode;
		else if (curNode->value > value) curNode = curNode->left;
		else curNode = curNode->right;
	}

	printf("ERROR: Such node doesn't exist!\n");
	return NULL;
}

void inorderTraversal(node *curNode) {
	if (curNode->left) inorderTraversal(curNode->left);
	printf("%d ", curNode->value);
	if (curNode->right) inorderTraversal(curNode->right);
}

void rightRootLeftTraversal(node *curNode) {
	if (curNode->right) inorderTraversal(curNode->right);
	printf("%d ", curNode->value);
	if (curNode->left) inorderTraversal(curNode->left);
}

int getMin(AVL *myAVL) {
	node* curNode = myAVL->root;
	while(curNode->left) curNode = curNode->left;
	return curNode->value;
}

int getMax(AVL *myAVL) {
	node* curNode = myAVL->root;
	while(curNode->right) curNode = curNode->right;
	return curNode->value;
}

void find(AVL *myAVL, int value) {
	int direction[myAVL->root->height];
	node* curNode = myAVL->root;
	int i=0;
	while(1) {
		if (curNode == NULL) {
			printf("ERROR: Such node doesn't exist!\n");
			return;
		}
		if (curNode->value > value) {
			curNode = curNode->left;
			direction[i] = 1;
		} else if (curNode->value < value) {
			curNode = curNode->right;
			direction[i] = -1;
		} else break;
		i++;
	}

	printf("Root");
	for(int j=0; j<i; j++) {
		if (direction[j] == 1) printf(" - Left");
		else if (direction[j] == -1) printf(" - Right");
	}
	printf("\n");
}

int heightTree(AVL *myAVL) {return myAVL->root->height;}

void heightNode(AVL *myAVL, int value) {
	node* targetNode = search(myAVL, value);
	if (targetNode) printf("%d\n", targetNode->height);
}

void getRightChild(AVL *myAVL, int value) {
	node* targetNode = search(myAVL, value);
	if (targetNode) {
		if (targetNode->right) printf("%d\n", targetNode->right->value);
		else printf("NULL\n");
	} 
}

void getLeftChild(AVL *myAVL, int value) {
	node* targetNode = search(myAVL, value);
	if (targetNode) {
		if (targetNode->left) printf("%d\n", targetNode->left->value);
		else printf("NULL\n");
	} 
}

int countNode(node *curNode) {
	int left, right;
	left = right = 0;
	if (curNode->left) left = countNode(curNode->left);
	if (curNode->right) right = countNode(curNode->right);
	return left + right + 1;
}

void clear(AVL** myAVL) {*myAVL = NULL;}

void deleteNode(AVL **myAVL, int value) {
	node* targetNode = search(*myAVL, value);
	if (targetNode == NULL) return;

	node* parentNode = findParentNode(*myAVL, targetNode);
	if (targetNode->left == NULL && targetNode->right == NULL) {
		if (parentNode == NULL) {
			clear(myAVL);
			return;
		}
		else if (parentNode->left == targetNode) parentNode->left = NULL;
		else parentNode->right = NULL;
	} else if (targetNode->left && targetNode->right == NULL) {
		if (parentNode == NULL) (*myAVL)->root = targetNode->left;
		else if (parentNode->left == targetNode) parentNode->left = targetNode->left;
		else parentNode->right = targetNode->left;
	} else if (targetNode->left == NULL && targetNode->right) {
		if (parentNode == NULL) (*myAVL)->root = targetNode->right;
		else if (parentNode->left == targetNode) parentNode->left = targetNode->left;
		else parentNode->right = targetNode->left;
	} else {
		char direction;
		getchar();
		printf("successor direction[l/r]: ");
		scanf("%c", &direction);

		node* successor;
		if (direction == 'l') {
			successor = targetNode->left;
			while(successor->right) successor = successor->right;
		} else {
			successor = targetNode->right;
			while(successor->left) successor = successor->left;
		}
		int newValue = successor->value;
		deleteNode(myAVL, newValue);

		node* newNode = (node*)malloc(sizeof(node));
		newNode->value = newValue;
		newNode->left = targetNode->left;
		newNode->right = targetNode->right;
		if (parentNode == NULL) (*myAVL)->root = newNode;
		else if (parentNode->left == targetNode) parentNode->left = newNode;
		else parentNode->right = newNode;
	}
	targetNode->left = targetNode->right = NULL;
	free(targetNode);

	setHeight((*myAVL)->root);
	balanceTree(*myAVL, (*myAVL)->root);
}

void preorderTraversal(node *curNode) {
	printf("%d ", curNode->value);
	if (curNode->left) preorderTraversal(curNode->left);
	if (curNode->right) preorderTraversal(curNode->right);
}

void postorderTraversal(node *curNode) {
	if (curNode->left) postorderTraversal(curNode->left);
	if (curNode->right) postorderTraversal(curNode->right);
	printf("%d ", curNode->value);
}

int getRoot(AVL *myAVL) {
	if (myAVL) return myAVL->root->value;
	else {
		printf("ERROR: No tree!\n");
		return -1;
	}
}

int main() {

	int process = 1;
	int line = 1;
	cmd command;
	char input[10];

	AVL *myAVL;

	while(process) {

		// print status
		printf("[%d] current data status: ", line);
		print(myAVL);

		scanf("%s", input);
		command = commandParser(input);

		switch(command.operator_) {
			case '+':
				if (myAVL == NULL) create(&myAVL, command.operand_);
				else insertNode(myAVL, command.operand_);
				break;
			case 'P':
				print(myAVL);
				break;
			case 'B':
				node* targetNode = search(myAVL, command.operand_);
				if (targetNode) printf("%d\n", getBalanceFactor(targetNode));
				break;
			case 'I':
				inorderTraversal(myAVL->root);
				printf("\n");
				break;
			case 'R':
				rightRootLeftTraversal(myAVL->root);
				printf("\n");
				break;
			case 'N':
				printf("%d\n", getMin(myAVL));
				break;
			case 'X':
				printf("%d\n", getMax(myAVL));
				break;
			case 'F':
				find(myAVL, command.operand_);
				break;
			case 'T':
				printf("%d\n", heightTree(myAVL));
				break;
			case 'H':
				heightNode(myAVL, command.operand_);
				break;
			case 'G':
				getRightChild(myAVL, command.operand_);
				break;
			case 'L':
				getLeftChild(myAVL, command.operand_);
				break;
			case '#':
				printf("%d\n", countNode(myAVL->root));
				break;
			case '-':
				deleteNode(&myAVL, command.operand_);
				break;
			case 'C':
				clear(&myAVL);
				break;
			case 'O':
				preorderTraversal(myAVL->root);
				printf("\n");
				break;
			case 'o':
				postorderTraversal(myAVL->root);
				printf("\n");
				break;
			case '~':
				printf("%d\n", getRoot(myAVL));
				break;
			case 'Q':
				process = 0;
				break;
		}
		line++;
	}

	return 0;
}

#define OPERATOR_COUNT 19

const char operators[] = {'+', 'P', 'B', 'I', 'R', 'N', 'X', 'F', 'T', 'H', 'G', 'L', '#', '-', 'C', 'o', 'O', '~', 'Q'};

cmd commandParser(char* input) {
	int i = 0;
	while(input[i] == ' ') i++;
	
	int flag = 1;
	cmd command;
	for (int j=0; j<OPERATOR_COUNT; j++) {
		if (input[i] == operators[j]) {
			command.operator_ = input[i];
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
		command.operand_ = 0;
		while (input[i] != '\0' && input[i] != ')') {
			command.operand_ = command.operand_ * 10 + input[i] - '0';
			i++;
		}
	}

	return command;
}
