#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char value;
	struct Node* next;
} node;

typedef struct Stack {
	node* top;
	node* bottom;
} stack;

void create(stack** myStack) {
	*myStack = (stack*)malloc(sizeof(stack));
	(*myStack)->top = NULL;
	(*myStack)->bottom = NULL;
}

char pop(stack* myStack) {
	if (myStack->top == NULL) {
		printf("Error: Nothing to pop");
		return ' ';
	}

	char value = myStack->top->value;
	node* top = myStack->top;
	myStack->top = top->next;
	free(top);
	return value;
}

void push(stack* myStack, char value) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->value = value;
	newNode->next = myStack->top;
	
	if (myStack->top == NULL) myStack->bottom = newNode;
	
	myStack->top = newNode;
}

char peek(stack* myStack) {return myStack->top->value;}

int elementCount(stack* myStack) {
	node* current = myStack->top;
	int count = 0;
	while(current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

void top(stack* myStack) {printf("( %d, %c )\n", elementCount(myStack), peek(myStack));}

int isMember(stack* myStack, char value) {
	stack* tempStack;
	create(&tempStack);

	int count = elementCount(myStack);
	int isIn = 0;

	for (int i=0; i<count; i++) {
		char temp = pop(myStack);
		push(tempStack, temp);
		if (temp == value) {
			isIn = 1;
			break;
		}
	}

	count = elementCount(tempStack);

	for (int i=0; i<count; i++) push(myStack, pop(tempStack));
	
	return isIn;
}

void print(stack* myStack) {
	stack* tempStack;
	create(&tempStack);
	int count = elementCount(myStack);

	for (int i=0; i<count; i++) push(tempStack, pop(myStack));
	for (int i=0; i<count; i++) {
		char temp = pop(tempStack);
		printf("%c ", temp);
		push(myStack, temp);
	}
	printf("\n");
}

void status(stack* myStack) {
	if (myStack == NULL) printf("No Stack\n");
	else if (myStack->top == NULL) printf("No data\n");
	else {
		print(myStack);
		printf("                          ");
		for (int i=0; i<elementCount(myStack) - 1; i++) printf("  ");
		printf("^\n");
	}
}

void replace(stack* myStack, char newValue) {myStack->top->value = newValue;}

void clear(stack* myStack) {
	int count = elementCount(myStack);
	for (int i=0; i<count; i++) pop(myStack);
}

int isEmpty(stack* myStack) {return myStack->top == NULL;}

void visual(stack* myStack) {
	stack* tempStack;
	create(&tempStack);

	int count = elementCount(myStack);

	for (int i=0; i<count; i++) push(tempStack, pop(myStack));

	for (int i=0; i<count; i++) {
		char temp = pop(tempStack);
		printf("| %c |\n=====\n", temp);
		push(myStack, temp);
	}
}

void opposite(stack* myStack) {
	stack* temp1;
	stack* temp2;
	create(&temp1);
	create(&temp2);
	
	int count = elementCount(myStack);
	for (int i=0; i<count; i++) push(temp1, pop(myStack));
	for (int i=0; i<count; i++) push(temp2, pop(temp1));
	for (int i=0; i<count; i++) push(myStack, pop(temp2));
}

char bottom(stack* myStack) {return myStack->bottom->value;}

int main() {
	stack* myStack;
	int line = 1;
	int process = 1;

	while(process) {
		printf("[%2d] current data status: ", line);
		status(myStack);

		char input[5];
		scanf("%s", input);

		switch(input[0]) {
			case '*':
				create(&myStack);
				break;
			case '+':
				push(myStack, input[1]);
				break;
			case 'L':
				print(myStack);
				break;
			case 'P':
				printf("%c\n", peek(myStack));
				break;
			case '-':
				printf("%c\n", pop(myStack));
				break;
			case '#':
				printf("%d\n", elementCount(myStack));
				break;
			case 'T':
				top(myStack);
				break;
			case '?':
				printf("%c %s member of stack.\n", input[1], (isMember(myStack, input[1])) ? "is" : "is not");
				break;
			case '=':
				replace(myStack, input[1]);
				break;
			case 'C':
				clear(myStack);
				break;
			case 'E':
				printf("The stack %s empty.\n", (isEmpty(myStack)) ? "is" : "is not");
				break;
			case 'V':
				visual(myStack);
				break;
			case 'O':
				opposite(myStack);
				break;
			case 'B':
				printf("%c\n", bottom(myStack));
				break;
			case 'Q':
				process = 0;
				break;
			default:
				if ('1' <= input[0] && input[0] <= '9' && input[1] == '-') {
					for (int i=0; i<input[0] - '0'; i++) printf("%c ", pop(myStack));
				}
				printf("\n");
				break;
		}
		line++;
	}

	return 0;
}
