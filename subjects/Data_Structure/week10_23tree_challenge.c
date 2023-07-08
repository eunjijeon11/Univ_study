#include <stdio.h>
#include <stdlib.h>

typedef struct command {
	char operator_;
	int operand_;
} cmd;

cmd commandParser(char* input);

typedef struct Node {
	int S;
	int M;
	int L;
	struct Node *left;
	struct Node *middle;
	struct Node *right;
	struct Node *parent;
	char childType;
} node;

typedef struct TwoThreeTree {
	node *root;
} ttt;

void printNode(node *curNode) {
	printf("(");
	if (curNode->S) {
		if (curNode->left) printf("(%d,%d)", curNode->S, curNode->L);
		else printf("%d,%d", curNode->S, curNode->L);
	} else if (curNode->M) {
		printf("%d", curNode->M);
	}

	if (curNode->left) {
		printf("(");
		printNode(curNode->left);
		printNode(curNode->middle);
		printNode(curNode->right);
		printf(")");
	}
	printf(")");
}

void print(ttt *myTtt) {
	if (myTtt == NULL) printf("No tree\n");
	else {
		printNode(myTtt->root);
		printf("\n");
	}
}

void create(ttt **myTtt, int value) {
	if (value == 0) {
		printf("ERROR: Cannot insert 0\n");
		return;
	}
	(*myTtt) = (ttt*)malloc(sizeof(ttt));
	node *newNode = (node*)malloc(sizeof(node));
	newNode->M = value;
	newNode->childType = '~';
	(*myTtt)->root = newNode;
}

void toParent(node *curNode, int value) {
	int mValue;
	if (curNode->S > value) {
		mValue = curNode->S;

	} else if (curNode->S < value && curNode->L > value) {
		mValue 
	} else if (curNode->L < value) {
		
	}

	
}

void insertNode(ttt *myTtt, int value) {
	if (value == 0) {
		printf("ERROR: Cannot insert 0!\n");
		return;
	}

	// move to leaf node
	node *curNode = myTtt->root;
	node *nextNode = curNode;
	while(nextNode) {
		curNode = nextNode;
		if (curNode->M) {
			if (curNode->M > value) nextNode = curNode->left;
			else if (curNode->M < value) nextNode = curNode->right;
			else {
				printf("ERROR: Such node already exists!\n");
				return;
			}
		} else {
			if (curNode->S > value) nextNode = curNode->left;
			else if (curNode->S < value && curNode->L > value) nextNode = curNode->middle;
			else if (curNode->L < value) nextNode = curNode->right;
			else {
				printf("ERROR: Such node already exists!\n");
				return;
			}
		}
	}

	// insert
	if (curNode->M) {
		if (value > curNode->M) {
			curNode->S = curNode->M;
			curNode->M = 0;
			curNode->L = value;
		} else {
			curNode->L = curNode->S;
			curNode->M = 0;
			curNode->S = value;
		}
	} else {
		// to parent
	}
}

int main() {
	ttt *myTtt;

	int process, line;
	process = line = 1;

	char input[10];
	cmd command;

	while(process) {

		//print
		printf("[%d] current data status: ", line);
		print(myTtt);
		scanf("%s", input);
		command = commandParser(input);

		switch(command.operator_) {
			case '+':
				if (myTtt) insertNode(myTtt, command.operand_);
				else create(&myTtt, command.operand_);
				break; 
			case 'Q':
				process = 0;
				break;
		}

		line++;
	}

	return 0;
}

#define OPERATOR_COUNT 15

const char operators[] = {'+', 'P', 'I', 'R', 'N', 'X', 'F', 'H', 'G', 'L', '#', 'D', 'M', 'C', 'Q'};

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