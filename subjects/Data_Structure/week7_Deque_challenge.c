#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char value;
	struct Node* next;
	struct Node* prev;
} node;

typedef struct Deque {
	node* front;
	node* rear;
} deque;

void print(deque* myQue) {
	node* current = myQue->front;
	while(current != NULL) {
		printf("%c ", current->value);
		current = current->next;
	}
}

void status(deque* myQue) {
	if (myQue == NULL) printf("No deque\n");
	else if (myQue->front == NULL) printf("No data\n");
	else {
		printf("<< ");
		print(myQue);
		printf("<<\n");
	}
}

void create(deque** myQue) {
	*myQue = (deque*)malloc(sizeof(deque));
	(*myQue)->front = NULL;
	(*myQue)->rear = NULL;
}

void addFront(deque* myQue, char value) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->value = value;
	newNode->prev = NULL;
	newNode->next = myQue->front;

	if (myQue->front == NULL) myQue->rear = newNode;
	else myQue->front->prev = newNode;
	
	myQue->front = newNode;
}

char deleteFront(deque* myQue) {
	if (myQue->front == NULL) {
		printf("ERROR: Nothing to delete");
		return ' ';
	}

	node* temp = myQue->front;
	myQue->front = temp->next;
	if (myQue->front != NULL) myQue->front->prev = NULL;
	else myQue->rear = NULL;

	char value = temp->value;
	free(temp);
	return value;
}

char getFront(deque* myQue) {
	if (myQue->front == NULL) {
		printf("ERROR: Nothing to return");
		return ' ';
	} else return myQue->front->value;
}

void addRear(deque* myQue, char value) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->value = value;
	newNode->next = NULL;
	newNode->prev = myQue->rear;

	if (myQue->rear == NULL) myQue->front = newNode;
	else myQue->rear->next = newNode;
	
	myQue->rear = newNode;
}

char deleteRear(deque* myQue) {
	if (myQue->rear == NULL) {
		printf("ERROR: Nothing to delete");
		return ' ';
	}

	node* temp = myQue->rear;
	myQue->rear = temp->prev;
	if (myQue->rear != NULL) myQue->rear->next = NULL;
	else myQue->front = NULL;

	char value = temp->value;
	free(temp);
	return value;
}

char getRear(deque* myQue) {
	if (myQue->rear == NULL) {
		printf("ERROR: Nothing to return");
		return ' ';
	} else return myQue->rear->value;
}

int dataCount(deque* myQue) {
	int count = 0;
	node* current = myQue->front;

	while(current != NULL) {
		count++;
		current = current->next;
	}
	
	return count;
}

int isEmpty(deque* myQue) {return (myQue->front == NULL);}

void clear(deque* myQue) {
	int count = dataCount(myQue);
	for (int i=0; i<count; i++) deleteFront(myQue);
}

int main() {
	deque* myQue;
	int process = 1;
	int line = 1;

	while(process) {

		printf("[%2d] current data status: ", line);
		status(myQue);

		char input[6];
		scanf("%s", input);

		switch(input[0]) {
			case '*':
				create(&myQue);
				break;
			case '+':
				if (input[1] == 'f') addFront(myQue, input[2]);
				else if (input[1] == 'r') addRear(myQue, input[2]);
				break;
			case 'L':
				print(myQue);
				printf("\n");
				break;
			case '-':
				if (input[1] == 'f') printf("%c\n", deleteFront(myQue));
				else if (input[1] == 'r') printf("%c\n", deleteRear(myQue));
				break;
			case 'G':
				if (input[1] == 'f') printf("%c\n", getFront(myQue));
				else if (input[1] == 'r') printf("%c\n", getRear(myQue));
				break;
			case '#':
				printf("%d\n", dataCount(myQue));
				break;
			case 'E':
				printf("The deque %s empty.\n", (isEmpty(myQue)) ? "is" : "is not");
				break;
			case 'C':
				clear(myQue);
				break;
			case 'Q':
				process = 0;
				break;
		}

		line++;
	}

	return 0;
}
