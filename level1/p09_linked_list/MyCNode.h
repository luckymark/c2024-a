#pragma once
#ifndef MYCNODE_H
#define MYCNODE_H
typedef unsigned long long size_t;
struct ListNode{
    int val;
    struct ListNode *next;
};
typedef struct ListNode ListNode;
ListNode *Initialize(int val);
ListNode *Initialize_with_next(int val, ListNode *next);
ListNode *Initialize_by_array(int *arr, size_t arrsize);
size_t size(ListNode *head);
void for_each_printf(ListNode *head);
void reverse_listnode(ListNode *head);
void free_listnode(ListNode *head);
size_t npos = -1;
size_t find_kth_target(ListNode *find, size_t kth, int target);
#endif //MYCNODE_H