#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* command handling */

typedef struct command {
	char operator_;
	char operand1_;
	char operand2_;
} cmd;

cmd commandParser(char *input);

/* Structure */

typedef struct Node {
	char value;
	struct Node *next;
	struct Node *adjacentList;
} node;

typedef struct Graph {
	node *start;
} graph;

/* ADT */

void create(graph **myGraph) {
	(*myGraph) = (graph*)malloc(sizeof(graph));
}

void print(graph *myGraph) {
	if (myGraph == NULL) printf("No graph\n");
	else if (myGraph->start == NULL) printf("()\n");
	else {
		node *curNode = myGraph->start;
		while(curNode) {
			printf("%c%c", (curNode == myGraph->start) ? '(' : ',', curNode->value);
			if (curNode->adjacentList) {
				node *adjacent = curNode->adjacentList;
				while(adjacent) {
					printf("%c%c", (adjacent == curNode->adjacentList) ? '(' : ',', adjacent->value);
					adjacent = adjacent->next;
				}
				printf(")");
			}
			curNode = curNode->next;
		}
		printf(")\n");
	}
}

void insertVertex(graph *myGraph, char value) {
	if (myGraph == NULL) {
		printf("ERROR: No graph\n");
		return ;
	}
	
	node *curNode = myGraph->start;
	while(curNode && curNode->next) {
		if (curNode->value == value) {
			printf("ERROR: The vertex already exists!\n");
			return ;
		}
		curNode = curNode->next;
	}

	node *newNode = (node*)malloc(sizeof(node));
	newNode->value = value;
	if (curNode) curNode->next = newNode;
	else myGraph->start = newNode;
}

node* find(node *curNode, char value) {
	while (curNode) {
		if (curNode->value == value) return curNode;
		curNode = curNode->next;
	}
	return NULL;
}

void addEdge(graph *myGraph, char val1, char val2) {
	node *vertex1 = find(myGraph->start, val1);
	node *vertex2 = find(myGraph->start, val2);

	if (vertex1 == NULL || vertex2 == NULL) {
		printf("ERROR: Vertex doesn't exist!\n");
		return ;
	}

	node *curNode = vertex1->adjacentList;
	if (curNode && curNode->value == val2) {
		printf("ERROR: Edge already exists!\n");
		return;
	}
	while (curNode && curNode->next) {
		if (curNode->value == val2) {
			printf("ERROR: Edge already exists!\n");
			return;
		}
		curNode = curNode->next;
	}

	node *newEdge1 = (node*)malloc(sizeof(node));
	newEdge1->value = val2;
	if (curNode) curNode->next = newEdge1;
	else vertex1->adjacentList = newEdge1;

	curNode = vertex2->adjacentList;
	while (curNode && curNode->next) curNode = curNode->next;

	node *newEdge2 = (node*)malloc(sizeof(node));
	newEdge2->value = val1;
	if (curNode) curNode->next = newEdge2;
	else vertex2->adjacentList = newEdge2;
}

int degreeOfVertex(graph *myGraph, char value) {
	node *targetNode = find(myGraph->start, value);
	if (targetNode == NULL) {
		printf("ERROR: Vertex doesn't exist!\n");
		return -1;
	}

	int degree = 0;
	node *curNode = targetNode->adjacentList;
	while(curNode) {
		degree++;
		curNode = curNode->next;
	}
	return degree;
}

int isConnected(graph *myGraph) {
	node *curNode = myGraph->start;
	while (curNode) {
		if (curNode->adjacentList == NULL) return 0;
		else curNode = curNode->next;
	}
	return 1;
}

int isEmpty(graph *myGraph) {
	if (myGraph && myGraph->start) return 0;
	else return 1;
}

void adjacent(graph *myGraph, char value) {
	node *vertex = find(myGraph->start, value);
	if (vertex == NULL) {
		printf("ERROR: The vertex doesn't exist!\n");
		return ;
	}
	node *curNode = vertex->adjacentList;
	printf("{");
	while (curNode) {
		printf("%c%c", (curNode == vertex->adjacentList) ? '\0' : ',', curNode->value);
		curNode = curNode->next;
	}
	printf("}\n");
}

node* findPrev(node* curNode, char target) {
	if (curNode->value == target) return NULL;
	while(curNode->next) {
		if (curNode->next->value) return curNode;
		else curNode = curNode->next;
	}
}

int isExist(node* curNode, char target) {
	while(curNode){
		if (curNode->value == target) return 1;
		else curNode = curNode->next;
	}
	return 0;
}

void deleteEdge(graph *myGraph, char val1, char val2) {
	node *vertex1 = find(myGraph->start, val1);
	node *vertex2 = find(myGraph->start, val2);

	node *target = find(vertex1->adjacentList, val2);
	if (target == NULL) {
		printf("ERROR: The edge doesn't exist!\n");
		return ;
	}
	node *prev = findPrev(vertex1->adjacentList, val2);
	if (prev == NULL) vertex1->adjacentList = target->next;
	else prev->next = target->next;

	target = find(vertex2->adjacentList, val1);
	if (target == NULL) {
		printf("ERROR: The edge doesn't exist!\n");
		return ;
	}
	prev = findPrev(vertex2->adjacentList, val1);
	if (prev == NULL) vertex2->adjacentList = target->next;
	else prev->next = target->next;
}

void deleteVertex(graph *myGraph, char value) {
	if (isExist(myGraph->start, value) == 0) {
		printf("ERROR: The vertex doesn't exist!\n");
		return ;
	}

	node *target = find(myGraph->start, value);
	node *curNode = target->adjacentList;
	while(curNode) {
		char edge = curNode->value;
		curNode = curNode->next;
		deleteEdge(myGraph, value, edge);
	}

	node *prev = findPrev(myGraph->start, value);
	if (prev == NULL) {
		myGraph->start = target->next;
	} else prev->next = target->next;
	target->next = NULL;
	free(target);
}

int numOfVertex(graph *myGraph) {
	node *curNode = myGraph->start;
	int count = 0;
	while(curNode) {
		count++;
		curNode = curNode->next;
	}
	return count;
}

int edgeExist(graph *myGraph, node *curNode, char target, char before, int recursionCount) {
	if (isExist(curNode->adjacentList, target)) return 1;
	if (recursionCount == numOfVertex(myGraph)) return 0;

	char current = curNode->value;
	curNode = curNode->adjacentList;
	while(curNode) {
		if (curNode->value != before) {
			node *vertex = find(myGraph->start, curNode->value);
			if (edgeExist(myGraph, vertex, target, current, recursionCount+1)==1) return 1;
		}
		curNode = curNode->next;
	}
	return 0;
}

int pathExist(graph *myGraph, char val1, char val2) {
	if (isExist(myGraph->start, val1) && isExist(myGraph->start, val2)) {
		node *curNode = find(myGraph->start, val1);
		return edgeExist(myGraph, curNode, val2, '\0', 1);
	} else {
		printf("ERROR: The vertex doesn't exist!\n");
		return 0;
	}
}

int numOfEdge(graph *myGraph) {
	int count = 0;
	node *curNode = myGraph->start;
	while(curNode) {
		count += degreeOfVertex(myGraph, curNode->value);
		curNode = curNode->next;
	}
	return count / 2;
}

void renameVertex(graph *myGraph, char curValue, char newValue) {
	node *targetNode = find(myGraph->start, curValue);
	if (targetNode == NULL) {
		printf("ERROR: The vertex doesn't exist!\n");
		return ;
	}
	targetNode->value = newValue;

	node *curNode = targetNode->adjacentList;
	node *edgeVertex, *edge;
	while (curNode) {
		edgeVertex = find(myGraph->start, curNode->value);
		edge = find(edgeVertex->adjacentList, curValue);
		edge->value = newValue;
		curNode = curNode->next;
	}
}

void clear(graph **myGraph) {(*myGraph) = NULL;}

int makePath(graph *myGraph, node *curNode, char target, char before, int recursionCount) {
	if (isExist(curNode->adjacentList, target)) {
		printf("%c", target);
		return 1;
	}
	if (recursionCount == numOfVertex(myGraph)) return 0;

	char current = curNode->value;
	curNode = curNode->adjacentList;
	while(curNode) {
		if (curNode->value != before) {
			node *vertex = find(myGraph->start, curNode->value);
			if (makePath(myGraph, vertex, target, current, recursionCount+1)==1) {
				printf("-%c", curNode->value);
				return 1;
			}
		}
		curNode = curNode->next;
	}
	return 0;
}

void showPath(graph *myGraph, char val1, char val2) {
	if (isExist(myGraph->start, val1) && isExist(myGraph->start, val2)) {
		node *curNode = find(myGraph->start, val2);
		char path[numOfVertex(myGraph) + 1];
		if (makePath(myGraph, curNode, val1, '\0', 1)) printf("-%c\n", val2);
	} else printf("ERROR: The vertex doesn't exist!\n");
}

void cutEdge(graph *myGraph) {
	node *curVertex = myGraph->start;
	while(curVertex) {
		node *curEdge = curVertex->adjacentList;
		curVertex->adjacentList = NULL;
		node *nextEdge = curEdge;
		while(nextEdge) {
			curEdge = nextEdge;
			nextEdge = curEdge->next;
			free(curEdge);
		}
		curVertex = curVertex->next;
	}
}

int main() {

	graph *myGraph;

	int process, line;
	process = line = 1;

	char input[10];
	cmd command;

	while(process) {

		printf("[%d] current data status: ", line);
		print(myGraph);

		scanf("%s", input);
		command = commandParser(input);

		switch(command.operator_) {
			case 'G':
				create(&myGraph);
				break;
			case '+':
				insertVertex(myGraph, command.operand1_);
				break;
			case 'E':
				addEdge(myGraph, command.operand1_, command.operand2_);
				break;
			case 'L':
				print(myGraph);
				break;
			case 'V':
				printf("%d\n", degreeOfVertex(myGraph, command.operand1_));
				break;
			case 'C':
				printf("The graph %s connected.\n", (isConnected(myGraph)) ? "is": "is not");
				break;
			case 'N':
				printf("The graph %s empty.\n", (isEmpty(myGraph)) ? "is" : "is not");
				break;
			case 'A':
				adjacent(myGraph, command.operand1_);
				break;
			case '-':
				deleteVertex(myGraph, command.operand1_);
				break;
			case 'P':
				printf("The path %s exist.\n", (pathExist(myGraph, command.operand1_, command.operand2_)) ? "does" : "doesn't");
				break;
			case 'X':
				printf("%d\n", numOfVertex(myGraph));
				break;
			case 'H':
				printf("%d\n", numOfEdge(myGraph));
				break;
			case 'D':
				deleteEdge(myGraph, command.operand1_, command.operand2_);
				break;
			case 'R':
				renameVertex(myGraph, command.operand1_, command.operand2_);
				break;
			case 'K':
				clear(&myGraph);
				break;
			case '?':
				printf("The vertex %s in the graph.\n", (isExist(myGraph->start, command.operand1_)) ? "is" : "is not");
				break;
			case 'S':
				showPath(myGraph, command.operand1_, command.operand2_);
				break;
			case 'T':
				cutEdge(myGraph);
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

const char operators[] = {'G', '+', 'E', 'L', 'V', 'C', 'N', 'A', '-', 'P', 'X', 'H', 'D', 'R', 'K', 'S', 'T', '?', 'Q'};

cmd commandParser(char *input) {
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

	if (('A' <= input[i] && input[i] <= 'Z') || ('a' <= input[i] && input[i] <= 'z')) {
		command.operand1_ = input[i];
	} else if (input[i] == '(') {
		i++;

		if (('A' <= input[i] && input[i] <= 'Z') || ('a' <= input[i] && input[i] <= 'z')) {
			command.operand1_ = input[i];
			i++;
		} else {
			printf("ERROR: Wrong operand\n");
			cmd dummyCommand;
			return dummyCommand;
		}

		if (input[i] == ',') {
			i++;
			if (('A' <= input[i] && input[i] <= 'Z') || ('a' <= input[i] && input[i] <= 'z')) {
				command.operand2_ = input[i];
				i++;
			} else {
				printf("ERROR: Wrong operand\n");
				cmd dummyCommand;
				return dummyCommand;
			}
		}
	}

	return command;
}