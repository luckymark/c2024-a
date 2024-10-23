#include <iostream>

using namespace std;

struct node
{
    int val;
    node* next;
};


node* creat(int val)
{
    node* newnode = (node*)malloc(sizeof(node));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}


node* insert(node* head, int val)
{
    node* newnode = creat(val);
    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        node* tmp = head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = newnode;
    }
    return head;
}

void printlist(node* head)
{
    node* tmp = head;
    while (tmp != NULL)
    {
        cout << tmp->val << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

node* reverse(node* head) {
    node* prev = NULL;
    node* current = head;
    node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

void my_find(node* head, int vall)
{
    node* tmp = head;
    int num = 1;
    int flag = 1;
    while (tmp != NULL)
    {
        if (tmp->val == vall)
        {
            flag = 0;
            cout << "第 " << num << " 个是数字5" << endl;
        }
        num++;
        tmp = tmp->next;
    }
    if (flag)
    {
        cout << "-1" << endl;
    }
}

int main()
{
    node* head = NULL;
    int a[10] = { 1,2,3,6,4,5,7,5,7,9 };
    for (int i = 0; i < 10; i++)
    {
        head=insert(head, a[i]);
    }

    printlist(head);
    head=reverse(head);
    printlist(head);

    my_find(head, 5);

    return 0;
}