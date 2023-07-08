#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 10

typedef struct Array{
	char* data;     // char array
	int current;    // current index
	int len;        // length
} array;

array* create(array* myArray) {
	myArray = (array*)malloc(sizeof(array));
	char newArray[MAX_LEN];
	myArray->data = (char*)malloc(sizeof(char));
	myArray->len = 0;
	myArray->current = -1;

	return myArray;
}

void print(array* myArray) {
	for (int i=0; i<myArray->len; i++) {
	        printf("%c ", (myArray->data)[i]);
        }
	printf("\n");
}


void status(array* myArray) {
	if (!myArray) {
		printf("No array\n");
		return;
	}

	if (myArray->len) {
		print(myArray);
		printf("                          ");
		for (int i=0; i<myArray->len; i++) {
      printf("%c ", (i==myArray->current)?'^':' ');
    }
    printf("\n");
	} else printf("No data\n");
}

void insert(array* myArray, char data) {
	if (myArray->len == myArray->current + 1) {
		(myArray->data)[myArray->len] = data;
	} else {
		for (int i=myArray->len; i>myArray->current; i--) myArray->data[i] = myArray->data[i-1];
		myArray->data[myArray->current+1] = data;	
	}
	myArray->current++;
	myArray->len++;
}

int traverseFront(array* myArray, int count) {
	if (count < myArray->len) myArray->current = count;
	else {
		printf("ERROR: Index out of range\n");
		return 0;
	}
	return 1;
}

void traverseRear(array* myArray, int count) {
	if (myArray->len - count - 1 >= 0) myArray->current = myArray->len - count - 1;
	else printf("ERROR: Index out of range\n");
}

void next(array* myArray) {
	if (myArray->current < myArray->len - 1) myArray->current++;
	else printf("ERROR: Index out of range\n");
}

void previous(array* myArray) {
	if (myArray->current > 0) myArray->current--;
	else printf("ERROR: Index out of range\n");
}

void delete(array* myArray) {
	if (myArray->len == 0) {
		printf("ERROR: Nothing to delete\n");
		return;
	}
	for (int i=myArray->current; i<myArray->len; i++) myArray->data[i] = myArray->data[i+1];
	if (myArray->current == myArray->len - 1) myArray->current = 0;
	if (myArray->len == 1) myArray->current = -1;
	myArray->len--;
	myArray->data[myArray->len] = '\0';
}

char getData(array* myArray) {
	return myArray->data[myArray->current];
}

void replace(array* myArray, char newData) {
	myArray->data[myArray->current] = newData;
}

void empty(array* myArray) {
	int len = myArray->len;
	for (int i=0; i<len; i++) {delete(myArray);}
}

int dataCount(array* myArray) {return myArray->len;}

void move(array* myArray, char* dest) {
	int destIndex = 0;
	if (dest[1] >= '0' && dest[1] <= '9') {
		int i = 1;
		while(dest[i] != '\0') {
			destIndex = destIndex * 10 + dest[i] - '0';
			i++;
		}

		if (destIndex > myArray->len - 1) {
			printf("ERROR: Index out of range\n");
			return;
		}
	} else if (dest[1] == 'P') {
		if (myArray->current == 0) {
			printf("ERROR: Index out of range\n");
			return;
		}
		destIndex = myArray->current - 1;
	} else if (dest[1] == 'N') {
		if (myArray->current == myArray->len - 1) {
			printf("ERROR: Index out of range\n");
			return;
		}
		destIndex = myArray->current + 1;
	} else if (dest[1] == 'n') {
		destIndex = myArray->len - 1;
	}

	char curValue = myArray->data[myArray->current];
	delete(myArray);
	traverseFront(myArray, destIndex-1);
	insert(myArray, curValue);
}

array* deleteArray(array* myArray) {
	myArray = NULL;
	return myArray;
}

int isEmpty(array* myArray) {return (myArray->len == 0);}

int isFull(array* myArray) {return (myArray->len == MAX_LEN);}

int current(array* myArray) {return myArray->current;}

int main() {

	array* myArray;
	int line = 0;
	int process = 1;
	
	while(process) {

		printf("[%2d] current data status: ", line);
		status(myArray);

		char input[15];
		scanf("%s", input);

		switch(input[0]) {
			case '*':
				myArray = create(myArray);
				break;
			case '+':
				insert(myArray, input[1]);
				break;
			case '<':
				traverseFront(myArray, 0);
				break;
			case '>':
				traverseRear(myArray, 0);
				break;
			case 'N':
				next(myArray);
				break;
			case 'P':
				previous(myArray);
				break;
			case '-':
				delete(myArray);
				break;
			case '@':
				printf("%c\n", getData(myArray));
				break;
			case '=':
				replace(myArray, input[1]);
				break;
			case 'E':
				empty(myArray);
				break;
			case 'M':
				move(myArray, input);
				break;
			case 'L':
				print(myArray);
				break;
			case 'D':
				myArray = deleteArray(myArray);
				break;
			case '?':
				if (input[1] == 'E') printf("The array %s empty.\n", isEmpty(myArray) ? "is" : "is not");
				else if (input[1] == 'F') printf("The array %s full.\n", isFull(myArray) ? "is" : "is not");
				break;
			case '~':
				printf("%d\n", dataCount(myArray));
				break;
			case '^':
				printf("%d\n", current(myArray));
				break;
			case 'Q':
				process = 0;
				break;
			default:
				if ('0' <= input[0] && input[0] <= '9') {
					int res = traverseFront(myArray, input[0]);
					if (res && input[1] == 'G') printf("%c\n", getData(myArray));
					else if (res && input[1] == '=') replace(myArray, input[2]);
					else printf("Unable to execute command.\n");
				}
				continue;
		}

		line++;
	}
		 	

	return 0;
}
