//
// Created by Emerson on 2024/9/24.
//
#include <iostream>


using namespace std;

struct ListNode {
    int data;
    ListNode* next;
    ListNode(int x):data(x),next(NULL){}
};

class LinkedList {
public:
    ListNode* head;
    int size;
    LinkedList() :head(NULL), size(0) {}
    void insert(int i, int value);
    int find(ListNode *head,int value);
    int nextfind(ListNode* head, int value);
    void print(ListNode* head);
    ListNode* reverseList(ListNode* head);
};

void LinkedList::insert(int i, int value) {
    ListNode* newNode = new ListNode(value);
    if (i == 0) {
        newNode->next = head;
        head = newNode;
    }
    else {
        ListNode* curr = head;
        for (int j = 0; j < i - 1; ++j) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    size++;
}
void LinkedList::print(ListNode *head) {
    ListNode* curr = head;
    while (curr != NULL) {
        cout << curr->data<< " ";
        curr = curr->next;
    }
    cout << endl;
}

int LinkedList::find(ListNode *head,int value) {
    int index = 0;
    ListNode* curr = head;
    while (curr != NULL) {
        if (curr->data == value) {
            return index;
        }
        curr = curr->next;
        index++;
    }
    return -1;
}
int LinkedList::nextfind(ListNode* head, int value) {
    int FirstIndex = find(head, value);
    if (FirstIndex == -1) {
        return -1;
    }
    int index = FirstIndex + 1;
    ListNode* curr = head;
    for (int i = 0; i < FirstIndex + 1; ++i) {
        curr = curr->next;
    }
    while (curr != NULL) {
        if (curr->data == value) {
            return index;
        }
        curr = curr->next;
        ++index;
    }
    return -1;
}
ListNode* LinkedList::reverseList(ListNode* head) {
    ListNode* pre = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    return pre;
}



int main() {
    LinkedList list;
    list.insert(0, 1);
    list.insert(1, 5);
    list.insert(2, 2);
    list.insert(3, 3);
    list.insert(4, 4);
    list.insert(5, 5);
    list.insert(6, 5);

    list.print(list.head);
    ListNode* newhead = list.reverseList(list.head);
    list.print(newhead);
    cout << "第一个值为5的节点的序号" << list.find(newhead,5) << endl;
    cout << "第二个值为5的节点的序号" << list.nextfind(newhead,5) << endl;

}