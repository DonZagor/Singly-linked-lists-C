#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
}Node;

Node* getNode(int data); //returns an allocated node
Node* formList(); //creates a list
void printList(Node* head); //prints the list
Node* freeList(Node* head); //deallocates a list and returns a NULL pointer
int listLength(Node* head); //returns the lenght of the list
Node* rotateList(Node* head); //rotates the elements of a list
void sortList(Node* head); //sorts the list in ascending order
Node* removeElement(Node* head, int data); //removes all occurrences of an element
Node* insertFirst(Node* head, int data); //inserts an element at the start
Node* insertLast(Node* head, int data); //inserts an element at the end
Node* insertSorted(Node* head, int data); //inserts an element into a sorted list
Node* insertUnsorted(Node* head, int pos, int data); //inserts an element on a position
void removeDuplicates(Node* head); //removes all duplicate elements
Node* sortedFusion(Node* h1, Node* h2); //sorts two lists in a sorted way
Node* getMiddle(Node* head); //returns the middle element
Node* getNthFromEnd(Node* head, int n); //returns the nth element from the end
int loopExists(Node* head); //checks if there is a loop
void removeLoop(Node* head); //removes the loop
Node* searchFirst(Node* head, int data); //returns the first occurrence of an element
Node* searchLast(Node* head, int data); //returns the last occurrence of an element

int main()
{
	//FEEL FREE TO TRY ALL OF THE FUNCTIONS HERE
	Node* head = NULL;
	head = formList();
	printList(head);
	head = freeList(head);
	return 0;
}

Node* getNode(int data)
{
	Node* node = (Node*)malloc(sizeof(Node)); //allocate the memory
	if (!node) exit(1); //check if the memory is allocated
	node->data = data; //set data
	node->next = NULL; //next element is NULL
	return node;
}

Node* formList()
{
	Node* head = NULL, *tail = NULL;
	int data;
	//loads the elements until a non-integer value is entered
	while (scanf("%d", &data) == 1) {
		Node* node = getNode(data);
		if (!head) head = node;
		else tail->next = node;
		tail = node;
	}
	return head;
}

void printList(Node* head)
{
	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}
}

Node* freeList(Node* head)
{
	Node* temp = head, * p = NULL;
	while (temp) {
		p = temp;
		temp = temp->next;
		free(p);
	}
	return NULL;
}

int listLength(Node* head)
{
	int n = 0;
	while (head) {
		n++;
		head = head->next;
	}
	return n;
}

Node* rotateList(Node* head)
{
	Node* temp = head, *prev = NULL, *next = NULL;
	while (temp) {
		next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	return prev;
}

void sortList(Node* head)
{
	Node* i, *j;
	for (i = head; i; i = i->next) {
		for (j = i->next; j; j = j->next) {
			if (i->data > j->data) {
				int t = i->data;
				i->data = j->data;
				j->data = t;
			}
		}
	}
}

Node* removeElement(Node* head, int data)
{
	Node* temp = head, *prev = NULL, *p = NULL;
	while (temp) {
		if (temp->data != data) {
			prev = temp;
			temp = temp->next;
		}
		else {
			p = temp;
			temp = temp->next;
			if (!prev) head = temp;
			else prev->next = temp;
			free(p);
		}
	}
	return head;
}

Node* insertFirst(Node* head, int data)
{
	Node* node = getNode(data);
	node->next = head;
	head = node;
	return head;
}

Node* insertLast(Node* head, int data)
{
	Node* node = getNode(data);
	if(!head) return node;
	else {
		Node* temp = head;
		while (temp->next) temp = temp->next;
		temp->next = node;
		return head;
	}
	return NULL;
}

Node* insertSorted(Node* head, int data)
{
	Node* temp = head, *prev = NULL;
	while (temp && temp->data < data) {
		prev = temp;
		temp = temp->next;
	}
	Node* node = getNode(data);
	node->next = temp;
	if (!prev) head = node;
	else prev->next = node;
	return head;
}


Node* insertUnsorted(Node* head, int pos, int data)
{
	Node* node = getNode(data);
	Node* p = NULL;
	int i;
	if (pos == 0) {
		node->next = head;
		head = node;
	}
	else {
		p = head;
		i = 1;
		while (i < pos) {
			i++;
			p = p->next;
		}
		node->next = p->next;
		p->next = node;
	}
	return head;
}

void removeDuplicates(Node* head)
{
	Node* start = head;
	while (start) {
		Node* prev = start;
		Node* temp = start->next;
		while (temp && temp->data == start->data) {
			prev = temp;
			temp = temp->next;
		}
		prev->next = NULL;
		free(start->next);
		start->next = temp;
		start = temp;
	}
}


Node* sortedFusion(Node* h1, Node* h2)
{
	Node* head = NULL, *tail = NULL, *temp;
	while (h1 && h2) {
		if (h1->data < h2->data) {
			temp = h1;
			h1 = h1->next;
		}
		else {
			temp = h2;
			h2 = h2->next;
		}
		temp->next = NULL;
		if (!head) head = temp;
		else tail->next = temp;
		tail = temp;
	}
	if (h1) {
		if (!head) head = h1;
		else tail->next = h1;
	}
	else {
		if (!head) head = h2;
		else tail->next = h2;
	}
	return head;
}

Node* getMiddle(Node* head)
{
	Node* fast = head, *slow = head;
	while (fast) {
		fast = fast->next;
		if (fast) {
			fast = fast->next;
			slow = slow->next;
		}
	}
	return slow;
}


Node* getNthFromEnd(Node* head, int n)
{
	Node* fast = head, *slow = head;
	for (int i=0; i<n && fast != NULL; ++i, fast = fast->next);
	for (; fast != NULL; fast = fast->next, slow = slow->next);
	return slow;
}

int loopExists(Node* head) //returns 1 if there is, and 0 if there is no loop
{
	Node* fast = head, *slow = head;
	while (fast) {
		slow = slow->next;
		fast = fast->next;
		if (fast) fast = fast->next;
	}
	if (fast == slow) return 1;
	else return 0;
}


void removeLoop(Node* head)
{
	int exists = loopExists(head);
	if (exists) {
		Node* fast = head, *slow = head;
		while (fast) {
			slow = slow->next;
			fast = fast->next;
			if (fast) fast = fast->next;
			if (fast == slow) break;
		}
		if (fast == head) while (fast->next) fast = fast->next;
		else {
			slow = head;
			while (fast->next != slow->next) {
				slow = slow->next;
				fast = fast->next;
			}
		}
		fast->next = NULL;
	}
}

Node* searchFirst(Node* head, int data)
{
	Node* temp = head;
	while (temp) {
		if (temp->data == data) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


Node* searchLast(Node* head, int data)
{
	Node* temp = head, * last = NULL;
	while (temp) {
		if (temp->data == data){
			last = temp;
		}
		temp = temp->next;
	}
	return last;
}