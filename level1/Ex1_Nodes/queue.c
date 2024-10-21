#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define nullptr (void*)0
struct _queueNode {
	int val;
	struct _queueNode *next;
};
typedef struct _queueNode Queue;
Queue *Init_with_val(int val) {
	Queue *q = (Queue *) malloc(sizeof(Queue));
	if(!q) {
		puts("Memory allocation failed\n");
		exit(1);
	}
	q->val = val;
	q->next = nullptr;
	return q;
}
Queue *Init_with_next(int val, Queue *next) {
	Queue *q = (Queue *) malloc(sizeof(Queue));
	if(!q) {
		puts("Memory allocation failed\n");
		exit(1);
	}
	q->val = val;
	q->next = next;
	return q;
}
Queue *Init_by_array(int *arr, int n) {
	Queue *head = nullptr;
	for(int i = n - 1; i >= 0; i--) {
		head = Init_with_next(arr[i], head);
	}
	return head;
}
void Add_to_end(Queue *head1, Queue *head2) {
	if(head1 == nullptr) return;
	Queue *temp = head1;
	while(temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = head2;
}
void push(Queue *head, int val) { // 给我气炸了，push传一维指针可以，pop非要传二维指针
	Queue *temp = head;
	while(temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = Init_with_val(val);
}
int pop(Queue **head) {
	if((*head)->next == nullptr) {
		puts("Queue is empty\n");
		exit(1);
	}
	int val = (*head)->val;
	Queue *temp = *head;
	*head = (*head)->next;
	free(temp);
	return val;
}
int top(Queue *head) {
	if(head == nullptr) {
		puts("Queue is empty\n");
		exit(1);
	}
	return head->val;
}
int main() {
	int arr[] = { 1, 2, 3, 4, 5 };
	Queue *q1 = Init_by_array(arr, 5);
	printf("%d", top(q1));
	push(q1, 6);
	printf("\n%d", top(q1));
	pop(&q1);
	printf("\n%d", top(q1));
	pop(&q1);
	printf("\n%d", top(q1));
	pop(&q1);
	printf("\n%d", top(q1));
	pop(&q1);
	printf("\n%d", top(q1));
	pop(&q1);
	printf("\n%d", top(q1));
	return 0;
}