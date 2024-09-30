#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void *nullptr = (void *) 0;
struct Queue {
	int *val;
	size_t size;
	size_t capacity;
};
typedef struct Queue Queue;
Queue *initialize() {
	Queue *q = (Queue *) malloc(sizeof(Queue));
	q->capacity = 0;
	q->size = 0;
	q->val = nullptr;
	return q;
}
Queue *Initialize_with_capacity(size_t capacity) {
	Queue *q = initialize();
	q->capacity = capacity;
	q->size = 0;
	q->val = (int *) malloc(sizeof(int) * q->capacity);
	return q;
}
Queue *Initialize_with_array(int *arr, size_t arrsize, size_t capacity) {
	Queue *q = initialize();
	q->capacity = capacity;
	q->size = arrsize;
	q->val = (int *) malloc(sizeof(int) * q->capacity);
	for(size_t i = 0; i < arrsize; i++) {
		q->val[i] = arr[i];
	}
	return q;
}
void append(Queue *q, int val) {
	if(q->size <= q->capacity) {
		q->val[q->size++] = val;
	}
}
void pop(Queue *q) {
	--q->size;
}
bool isempty(Queue *q) {
	return q->size == 0;
}
bool isfull(Queue *q) {
	return q->size == q->capacity;
}
int get(Queue *q) {
	return q->val[q->size - 1];
}
int main() {
	int val[5] = { 1,2,3,4,5 };
	Queue *q = Initialize_with_array(val, 5, 10);
	append(q, 6);
	printf("%d\n", get(q));
	pop(q);
	printf("%d\n", get(q));
	return 0;
}