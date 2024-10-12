#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define nullptr (void*)0
struct _stackNode {
	int val;
	struct _stackNode *next;
};
typedef struct _stackNode Stack;
Stack *Init_with_val(int val) {
	Stack *s = (Stack *) malloc(sizeof(Stack));
	if(!s) {
		puts("Memory allocation failed\n");
		exit(1);
	}
	s->val = val;
	s->next = nullptr;
	return s;
}
Stack *Init_with_next(int val, Stack *next) {
	Stack *s = (Stack *) malloc(sizeof(Stack));
	if(!s) {
		puts("Memory allocation failed\n");
		exit(1);
	}
	s->val = val;
	s->next = next;
	return s;
}
Stack *Init_by_array(int *arr, int n) {
	Stack *head = nullptr;
	for(int i = n - 1; i >= 0; i--) {
		head = Init_with_next(arr[i], head);
	}
	return head;
}
void push(Stack **stk, int val) {
	Stack *temp = Init_with_next(val, *stk);
	*stk = temp;
}
int pop(Stack **stk) {
	if((*stk)->next == nullptr) {
		puts("Stack is empty\n");
		exit(1);
	}
	int val = (*stk)->val;
	Stack *temp = *stk;
	*stk = (*stk)->next;
	free(temp);
	return val;
}
int top(Stack *stk) {
	if(stk->next == nullptr) {
		puts("Stack is empty\n");
		exit(1);
	}
	return stk->val;
}
bool empty(Stack *stk) {
	return stk == nullptr;
}
int main() {
	Stack *stk = Init_by_array((int[]) { 1, 2, 3 }, 3);
	printf("%d\n", top(stk));
	push(&stk, 4);
	printf("%d\n", top(stk));
	printf("%d\n", pop(&stk));
	return 0;
}