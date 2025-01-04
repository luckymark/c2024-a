#include <iostream>

// 定义链表节点结构
struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

// 遍历链表并打印节点的值
void traverseList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

// 反序链表
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next; // 保存下一个节点
        current->next = prev; // 反转当前节点的指针
        prev = current;       // 移动 prev 和 current
        current = next;
    }

    return prev; // 返回新的头节点
}

// 查找第一个值为 target 的节点，返回节点序号（从0开始）
int findFirstValue(Node* head, int target) {
    Node* current = head;
    int index = 0;

    while (current != nullptr) {
        if (current->value == target) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1; // 未找到
}

// 查找下一个值为 target 的节点，返回节点序号（从0开始）
int findNextValue(Node* head, int target, int startIndex) {
    Node* current = head;
    int index = 0;

    // 移动到 startIndex 的位置
    while (current != nullptr && index < startIndex) {
        current = current->next;
        index++;
    }

    // 从 startIndex 开始查找
    while (current != nullptr) {
        if (current->value == target) {
            return index;
        }
        current = current->next;
        index++;
    }

    return -1; // 未找到
}

int main() {
    // 创建单向链表
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(5);
    head->next->next->next = new Node(3);
    head->next->next->next->next = new Node(5);

    // 遍历链表并打印节点的值
    std::cout << "链表节点值: ";
    traverseList(head);

    // 反序链表
    head = reverseList(head);
    std::cout << "反序后的链表节点值: ";
    traverseList(head);

    // 查找第一个值为 5 的节点
    int firstIndex = findFirstValue(head, 5);
    if (firstIndex != -1) {
        std::cout << "第一个值为 5 的节点序号: " << firstIndex << std::endl;
    }
    else {
        std::cout << "未找到值为 5 的节点" << std::endl;
    }

    // 查找下一个值为 5 的节点
    int nextIndex = findNextValue(head, 5, firstIndex + 1);
    if (nextIndex != -1) {
        std::cout << "下一个值为 5 的节点序号: " << nextIndex << std::endl;
    }
    else {
        std::cout << "未找到下一个值为 5 的节点" << std::endl;
    }

    // 释放链表内存
    Node* current = head;
    Node* nextNode;
    while (current != nullptr) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }

    return 0;
}