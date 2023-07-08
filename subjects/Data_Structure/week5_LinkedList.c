#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	char data;
	struct Node* next;
} node;

typedef struct LinkedList{
	node* head;
	node* tail;
	node* current;
} linkedList;

void create(linkedList** myList) {
	*myList = (linkedList*)malloc(sizeof(linkedList));
	(*myList)->head = NULL;
	(*myList)->tail = NULL;
	(*myList)->current = NULL;
}

void print(linkedList* myList) {
	node* current = myList->head;
	while(current != NULL) {
		printf("%c ", current->data);
		current = current->next;
	}
	printf("\n");
}

void status(linkedList* myList) {
	if (myList == NULL) {
		printf("No Linked List\n");
		return;
	}

	if (myList->head == NULL) printf("No Data\n");
	else {
		print(myList);
		printf("                          ");

		node* current = myList->head;
        	while(current != NULL) {
                	printf("%c ", (current == myList->current) ? '^' : ' ');
                	current = current->next;
        	}
        	printf("\n");
	}
}

void addTail(linkedList* myList, char data) {
	node* newNode = malloc(sizeof(node));
	newNode->data = data;
	newNode->next = NULL;
	
	if (myList->head == NULL) {
		myList->head = newNode;
	} else myList->tail->next = newNode;
	myList->tail = newNode;
	myList->current = newNode;
}

char getData(linkedList* myList) {return myList->current->data;}

int next(linkedList* myList) {
	if (myList->current->next) myList->current = myList->current->next;
	else {
		printf("ERROR: This is the end of the list!\n");
		return 0;
	}
	return 1;
}
int prev(linkedList* myList) {
	if (myList->current == myList->head) return 0;
	node* temp = myList->head;
	while (temp->next != myList->current) temp = temp->next;
	myList->current = temp;
	return 1;
}

int traverseFront(linkedList* myList, int count) {
	myList->current = myList->head;
	for (int i=0; i<count; i++) {
		if (next(myList) == 0) return 0;
	}
	return 1;
}
int traverseRear(linkedList* myList, int count) {
	myList->current = myList->tail;
	for (int i=0; i<count; i++) {
		if(prev(myList) == 0) return 0;
	}
	return 1;
}

void delete(linkedList* myList) {
	if (myList->head == myList->tail) {
		free(myList->head);
		myList->head = myList->tail = NULL;
		myList->current = NULL;
	}
	else if (myList->current == myList->head) {
		myList->head = myList->head->next;
		free(myList->current);
		myList->current = myList->head;
	}
	else if (myList->current == myList->tail) {
		prev(myList);
		free(myList->tail);
		myList->tail = myList->current;
		myList->tail->next = NULL;
		traverseFront(myList, 0);
	}
	else {
		prev(myList);
		node* temp = myList->current->next;
		myList->current->next = myList->current->next->next;
		free(temp);
		next(myList);
	}
}

void add(linkedList* myList, char data, int next) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->data = data;
	if (next) {
		newNode->next = myList->current->next;
		myList->current->next = newNode;
		myList->current = newNode;
	}
	else {
		if (myList->current == myList->head) {
			newNode->next = myList->current;
			myList->head = newNode;
			myList->current = newNode;
		}
		else {
			prev(myList);
			newNode->next = myList->current->next;
                	myList->current->next = newNode;
                	myList->current = newNode;
		}
	}
}

void replace(linkedList* myList, char data) {
	if (myList->current) myList->current->data = data;
	else printf("ERROR: No data to replace!\n");
}

int isMember(linkedList* myList, char data) {
	node* temp = myList->head;
	while(temp != NULL) {
		if (data == temp->data) return 1;
		temp = temp->next;
	}
	return 0;
}

int count(linkedList* myList) {
	if (myList->head == NULL) return 0;
	
	node* temp = myList->head;
	int num = 1;
	while(temp->next != NULL) {
		num++;
		temp = temp->next;
	}
	return num;
}

void empty(linkedList* myList) {
	int len = count(myList);
	for (int i=0; i<len; i++) delete(myList);
}

int isEmpty(linkedList* myList) {return myList->head == NULL;}

void printAll(linkedList* myList) {
	printf("| data |    current     |       next     |\n");
	node* temp = myList->head;
	while(temp != NULL) {
		printf("|  %c %c | %14p | %14p |\n", temp->data, (temp == myList->current) ? '<' : ' ', temp, temp->next);
		temp = temp->next;
	}
}

void toUpperCase(linkedList* myList) { myList->current->data += 'A' - 'a';}
void toLowerCase(linkedList* myList) { myList->current->data += 'a' - 'A';}

int main() {
	
	linkedList* myList;
	int line = 1;
	int flag = 0;
	int again = 1;

	while(again) {
		printf("[%2d] current data status: ", line);
                status(myList);

                char input;
		scanf("%c", &input);
		while(input == '\n' || input == ' ') scanf("%c", &input);
		
		char data;
		
                switch(input) {
		case '*':
			create(&myList);
			break;
		case '+':
			scanf("%c", &data);
                        if (myList->current == myList->tail) {
				addTail(myList, data);
			}
                        else add(myList, data, 1);
                        break;
		case 'L':
			print(myList);
			break;
		case 'G':
			printf("%c\n", getData(myList));
			break;
		case '<':
			while(1) {
				char temp;
				scanf("%c", &temp);
				if (temp == '+') {
					scanf("%c", &data);
					add(myList, data, 0);
					break;
				} else if (temp == '\n') {
					traverseFront(myList, 0);
					break;
				} else if (temp == 'N') {
					traverseFront(myList, 1);
					break;
				}
			}
			break;
		case '>':
			traverseRear(myList, 0);
			break;
		case 'N':
			next(myList);
			break;
		case 'P':
			prev(myList);
			break;
		case '-':
			delete(myList);
			break;
		case '=':
			scanf("%c", &data);
			replace(myList, data);
			break;
		case '?':
			scanf("%c", &data);
			printf("%c %s member of the list.\n", data, (isMember(myList, data)) ? "is" : "is not");
			break;
		case '#':
			printf("%d\n", count(myList));
			break;
		case 'C':
			empty(myList);
			break;
		case 'E':
			printf("The list %s empty.\n", (isEmpty(myList)) ? "is" : "is not");
			break;
		case 'D':
			// delete list
			myList = NULL;
			break;
		case 'A':
			// print verbose
			printAll(myList);
			break;
		case 'T':
			// change current to upper / lower case
			scanf("%c", &data);
			if (data == 'U') toUpperCase(myList);
			else if (data == 'l') toLowerCase(myList);
			break;
		case 'Q':
			again = 0;
			break;
		default:
			if ('1' <= input && input <= '9') {
				if (traverseFront(myList, input - '0' - 1) == 0) {
					while(getchar() != '\n');
					break;
				}
				scanf("%c", &data);
				if (data == 'G') printf("%c\n", getData(myList));
				else if (data == '=') {
					scanf("%c", &data);
					replace(myList, data);
				}
			} else {
				printf("Wrong command!\n");
				while(getchar() != '\n');
			}
		}
		line++;
	}	

	return 0;
}
