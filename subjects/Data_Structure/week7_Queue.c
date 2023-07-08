#include <stdio.h>
#include <stdlib.h>

#define MAX_QUE_SIZE 10

// circle queue
typedef struct Queue{
	char data[MAX_QUE_SIZE];
	int front;
	int rear;
} queue;

void create(queue** myQue) {
	(*myQue) = (queue*)malloc(sizeof(queue));
	(*myQue)->front = (*myQue)->rear = 0;
}

int dataCount(queue* myQue) {
	int count = myQue->rear - myQue->front;
	if (count < 0) count += MAX_QUE_SIZE;
	return count;
}

void enqueue(queue* myQue, char value) {
	int nextIndex = (myQue->rear + 1) % MAX_QUE_SIZE;
	if (nextIndex == myQue->front) {
		printf("ERROR: The queue is full.\n");
		return;
	}

	myQue->data[nextIndex] = value;
	myQue->rear = nextIndex;
}

char peek(queue* myQue) {return myQue->data[(myQue->front+1)%MAX_QUE_SIZE];}

char dequeue(queue* myQue) {
	if (myQue->front == myQue->rear) {
		printf("ERROR: Nothing to dequeue");
		return ' ';
	}

	char value = myQue->data[(myQue->front+1)%MAX_QUE_SIZE];
	myQue->front = (myQue->front+1)%MAX_QUE_SIZE;
	myQue->data[myQue->front] = '\0';

	return value;
}

void print(queue* myQue) {
	int count = dataCount(myQue);   /* changed */
	char temp;
	for (int i=0; i<count; i++) {
		temp = dequeue(myQue);
		printf("%c ", temp);
		enqueue(myQue, temp);
	}
	printf("\n");
}

void status(queue* myQue) {
	if (myQue == NULL) printf("No queue\n");
	else if (myQue->front == myQue->rear) printf("No data\n");
	else print(myQue);
}

int isEmpty(queue* myQue) {return (myQue->front == myQue->rear);}

int isFull(queue* myQue) {return (myQue->front == (myQue->rear+1)%MAX_QUE_SIZE);}

int head(queue* myQue) {return (myQue->front + 2) % MAX_QUE_SIZE;}

int tail(queue* myQue) {return (myQue->rear + 1) % MAX_QUE_SIZE;}

int isMember(queue* myQue, char value) {
	for (int i=1; i<=dataCount(myQue); i++) if (myQue->data[myQue->front + i] == value) return 1;
	return 0;
}

void replace(queue* myQue, char value) {myQue->data[myQue->rear] = value;}

void clear(queue* myQue) {
	int count = dataCount(myQue);
	for (int i=0; i<count; i++) dequeue(myQue);
}

void addFront(queue* myQue, char value) {
	if (isFull(myQue)) {
		printf("ERROR: The queue is full.\n");
		return;
	}

	myQue->data[myQue->front % MAX_QUE_SIZE] = value;
	myQue->front = (myQue->front - 1) % MAX_QUE_SIZE;
}

char get(queue* myQue, int index) {return myQue->data[(myQue->front + index) % MAX_QUE_SIZE];}

void change(queue* myQue, int index, char value) {myQue->data[(myQue->front + index)%MAX_QUE_SIZE] = value;}

int main() {
	queue* myQue;

	char input[6];
	int process = 1;
	int line = 1;

	while(process) {
		printf("[%2d] current data status: ", line);
		status(myQue);

		scanf("%s", input);

		switch(input[0]) {
			case '*':
				create(&myQue);
				break;
			case '+':
				enqueue(myQue, input[1]);
				break;
			case 'L':
				print(myQue);
				break;
			case 'P':
				printf("%c\n", peek(myQue));
				break;
			case '-':
				printf("%c\n", dequeue(myQue));
				break;
			case 'E':
				printf("This queue %s empty.\n", (isEmpty(myQue)) ? "is" : "is not");
				break;
			case 'F':
				printf("This queue %s full.\n", (isFull(myQue)) ? "is" : "is not");
				break;
			case '#':
				printf("%d\n", dataCount(myQue));
				break;
			case 'H':
				printf("%d\n", head(myQue));
				break;
			case 'T':
				printf("%d\n", tail(myQue));
				break;
			case '?':
				printf("%c %s member of the queue.\n", input[1], (isMember(myQue, input[1])) ? "is" : "is not");
				break;
			case '=':
				replace(myQue, input[1]);
				break;
			case 'C':
				clear(myQue);
				break;
			case '<': // add value at front
				addFront(myQue, input[1]);
				break;
			case 'G': // get specific index data
				printf("%c\n", get(myQue, input[1] - '0'));
				break;
			case 'Q':
				process = 0;
				break;
			default:
				if ('1' <= input[0] && input[0] <= '9') {
					if (input[1] == '-') {
						for (int i=0; i<input[0] - '0'; i++) printf("%c ", dequeue(myQue));
						printf("\n");
					} else if (input[1] == '=') { // change specific index data
						change(myQue, input[0]-'0', input[2]);
					}
				}
		}
		line++;
	}

	return 0;
}
