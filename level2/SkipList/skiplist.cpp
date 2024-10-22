//
// Created by Emerson on 2024/10/22.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int MAX_LEVEL = 16;  // 最大层数

// 节点结构
struct Node {
    int value;                // 节点值
    vector<Node*> forward;    // 指向每一层的下一个节点的指针

    // 构造函数，初始化节点值和每层的指针
    Node(int val, int level) : value(val), forward(level, nullptr) {}
};

// 跳表类
class SkipList {
public:
    SkipList();  // 构造函数
    ~SkipList(); // 析构函数

    bool search(int value) const;  // 查找函数
    void insert(int value);         // 插入函数
    void remove(int value);         // 删除函数

private:
    int randomLevel();              // 随机生成节点的层级
    Node* createNode(int value, int level);  // 创建新节点

    Node* header;  // 跳表的头节点
    int level;     // 当前的最大层数
};

// 构造函数
SkipList::SkipList() {
    level = 1;  // 初始层数为1
    // 创建头节点，使用负无穷大作为最小值
    header = new Node(std::numeric_limits<int>::min(), MAX_LEVEL);
    srand(static_cast<unsigned>(time(0)));  // 设置随机数种子
}

// 析构函数，释放跳表的内存
SkipList::~SkipList() {
    Node* current = header;  // 从头节点开始
    while (current) {
        Node* next = current->forward[0];  // 记录下一个节点
        delete current;                     // 删除当前节点
        current = next;                     // 移动到下一个节点
    }
}

// 随机生成节点的层级
int SkipList::randomLevel() {
    int lvl = 1;  // 初始层数为1
    while (lvl < MAX_LEVEL && rand() % 2 == 1) {  // 每次有50%的概率增加层数
        ++lvl;
    }
    return lvl;  // 返回生成的层数
}

// 创建一个新节点
Node* SkipList::createNode(int value, int level) {
    return new Node(value, level);  // 返回新节点
}

// 查找元素
bool SkipList::search(int value) const {
    Node* current = header;  // 从头节点开始
    // 从最高层向下查找
    for (int i = level - 1; i >= 0; --i) {
        // 遍历当前层，找到小于目标值的节点
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];  // 移动到下一层的节点
    return current && current->value == value;  // 检查是否找到目标值
}

// 插入元素
void SkipList::insert(int value) {
    vector<Node*> update(MAX_LEVEL, nullptr);  // 记录需要更新的节点
    Node* current = header;

    // 从最高层向下查找插入位置
    for (int i = level - 1; i >= 0; --i) {
        // 遍历当前层，找到插入位置
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;  // 记录需要更新的前驱节点
    }

    current = current->forward[0];  // 移动到下一层的节点

    // 如果节点不存在，则进行插入
    if (!current || current->value != value) {
        int newLevel = randomLevel();  // 随机生成新的层数
        if (newLevel > level) {  // 如果新层数大于当前层数
            for (int i = level; i < newLevel; ++i) {
                update[i] = header;  // 更新前驱节点为头节点
            }
            level = newLevel;  // 更新最大层数
        }

        Node* newNode = createNode(value, newLevel);  // 创建新节点

        // 插入新节点，更新前驱节点的 forward 指针
        for (int i = 0; i < newLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];  // 设置新节点的 forward 指针
            update[i]->forward[i] = newNode;               // 更新前驱节点的 forward 指针
        }
    }
}

// 删除元素
void SkipList::remove(int value) {
    vector<Node*> update(MAX_LEVEL, nullptr);  // 记录需要更新的节点
    Node* current = header;

    // 查找需要删除的节点
    for (int i = level - 1; i >= 0; --i) {
        while (current->forward[i] && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;  // 记录需要更新的前驱节点
    }

    current = current->forward[0];  // 移动到下一层的节点

    // 如果找到了要删除的节点
    if (current && current->value == value) {
        // 更新 forward 指针，删除节点
        for (int i = 0; i < level; ++i) {
            if (update[i]->forward[i] != current) break;  // 如果前驱节点的 forward 不指向当前节点，跳出
            update[i]->forward[i] = current->forward[i];   // 跳过当前节点
        }
        delete current;  // 删除当前节点

        // 如果最高层为空，降低层级
        while (level > 1 && !header->forward[level - 1]) {
            --level;  // 降低层数
        }
    }
}

// 主函数
int main() {
    SkipList skiplist;  // 创建跳表实例

    // 插入一些值
    skiplist.insert(3);
    skiplist.insert(6);
    skiplist.insert(7);
    skiplist.insert(9);
    skiplist.insert(12);
    skiplist.insert(19);
    skiplist.insert(17);
    skiplist.insert(26);
    skiplist.insert(21);
    skiplist.insert(25);

    // 查找值
    cout << "Search 19: " << (skiplist.search(19) ? "Found" : "Not Found") << endl;
    cout << "Search 15: " << (skiplist.search(15) ? "Found" : "Not Found") << endl;

    // 删除值
    skiplist.remove(19);
    cout << "Search 19 after deletion: " << (skiplist.search(19) ? "Found" : "Not Found") << endl;

    return 0;  // 程序结束
}
