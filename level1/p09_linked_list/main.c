//#include"MyCNode.h"
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:6011)
#pragma warning(disable:4267)
#define nullptr (void*)0 //写太多c++导致的
struct ListNode {
	int val;
	struct ListNode *next;
};
typedef struct ListNode ListNode;
ListNode *Initialize(int val) {
	ListNode *res = (ListNode *) malloc(sizeof(ListNode));
	res->val = val;
	res->next = nullptr;
	return res;
}

ListNode *Initialize_with_next(int val, ListNode *next) {
	ListNode *res = (ListNode *) malloc(sizeof(ListNode));
	res->val = val;
	res->next = next;
	return res;
}
//你知道的，C语言是啥*，传一个数组进去还tm要传大小
ListNode *Initialize_by_array(int *arr, size_t arrsize) {
	if(arrsize == 0) return nullptr;
	ListNode *head = (ListNode *) malloc(sizeof(ListNode));
	head->val = arr[0];
	head->next = nullptr;
	ListNode *current = head;
	for(size_t i = 1; i < arrsize; ++i) {
		ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
		newNode->val = arr[i];
		newNode->next = nullptr;
		current->next = newNode;
		current = newNode;
	}
	return head;
}

size_t size(ListNode *head) {
	if(head == nullptr) return 0;
	int cnt = 0;
	for(ListNode *ln = head; ln != nullptr; ln = ln->next) {
		++cnt;
	}
	return cnt;
}

void for_each_printf(ListNode *head) {
	for(ListNode *ln = head; ln != nullptr; ln = ln->next) {
		printf("%d  ", ln->val);
	}
	printf("\n");
}
//我不想学c，我想学cpp，这玩意放cpp里一个引用做完了我搁这侠集霸写（又哭又闹
void reverse_listnode(ListNode *head) {
	size_t n = size(head);
	int *nums = (int *) malloc(sizeof(int) * n);
	size_t cnt = 0;
	for(ListNode *ln = head; ln != nullptr; ln = ln->next) {
		nums[cnt++] = ln->val;
	}
	for(ListNode *ln = head; ln != nullptr; ln = ln->next) {
		ln->val = nums[--cnt];
	}
	free(nums);
}

void free_listnode(ListNode *head) {
	ListNode *This = head, *Next = This->next;
	while(Next->next != nullptr) {
		free(This);
		This = Next;
		Next = Next->next;
	}
	free(Next);
}
size_t npos = -1;
size_t find_kth_target(ListNode *find, size_t kth, int target) {
	size_t cnt = 0, res = 0;
	ListNode *ln = find;
	while(ln != nullptr) {
		if(ln->val == target) ++cnt;
		if(cnt == kth) return res;
		++res;
		ln = ln->next;
	}
	return npos;
}
int main() {
	int a[5] = { 5,2,3,1,4 };
	ListNode *ln = Initialize_by_array(a, 5);
	for_each_printf(ln);
	reverse_listnode(ln);
	for_each_printf(ln);
	//reverse_listnode(ln);
	int b = find_kth_target(ln, 1, 5);
	printf("%d\n", b);
	b = find_kth_target(ln, 2, 5);
	printf("%d\n", b);
	free_listnode(ln);
	return 0;
}
