#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <time.h>
//
using namespace std;
struct SkiplistNode
{
    int _val;
    vector<SkiplistNode*> _nextV;
    SkiplistNode(int val, int level)
            :_val(val)
            , _nextV(level, nullptr)
    {}
};
class Skiplist {
    typedef SkiplistNode Node;
public:
    Skiplist() {
        srand(time(nullptr));

        _head = new SkiplistNode(-1, 1);
    }

    bool search(int target) {
        Node* cur = _head;
        int level = _head->_nextV.size() - 1;

        while (level >= 0)
        {

            if (cur->_nextV[level] && cur->_nextV[level]->_val < target)
            {
                cur = cur->_nextV[level];
            }

            else if (cur->_nextV[level] == nullptr || cur->_nextV[level]->_val > target)
            {
                level--;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    vector<Node*> FindPrevNode(int num)
    {
        Node* cur = _head;
        int level = _head->_nextV.size() - 1;

        vector<Node*> prevV(level + 1, _head);

        while (level >= 0)
        {
            if (cur->_nextV[level] && cur->_nextV[level]->_val < num)
            {
                cur = cur->_nextV[level];
            }
            else if (cur->_nextV[level] == nullptr || cur->_nextV[level]->_val >= num)
            {
                prevV[level] = cur;

                level--;
            }
        }
        return prevV;
    }

    void add(int num)
    {
        vector<Node*> prevV = FindPrevNode(num);

        int n = RandomLevel();
        Node* newnode = new Node(num, n);
        if (n > _head->_nextV.size())
        {
            _head->_nextV.resize(n, nullptr);
            prevV.resize(n, _head);
        }

        for (int i = 0; i < n; i++)
        {
            newnode->_nextV[i] = prevV[i]->_nextV[i];
            prevV[i]->_nextV[i] = newnode;
        }
    }

    bool erase(int num)
    {
        vector<Node*> prevV = FindPrevNode(num);
        if (prevV[0]->_nextV[0] == nullptr || prevV[0]->_nextV[0]->_val != num)
        {
            return false;
        }
        else
        {
            Node* del = prevV[0]->_nextV[0];
            for (size_t i = 0; i < del->_nextV.size(); i++)
            {
                prevV[i]->_nextV[i] = del->_nextV[i];
            }
            delete del;

            int i = _head->_nextV.size() - 1;
            while (i > 0)
            {
                if (_head->_nextV[i] == nullptr)
                {
                    --i;
                }
                else
                {
                    break;
                }
            }
            _head->_nextV.resize(i + 1);

            return true;
        }
    }

    int RandomLevel()
    {
        size_t level = 1;
        while (rand() < RAND_MAX * _p && level < _maxLevel)
        {
            ++level;
        }
        return level;
    }



    void Print()
    {

        Node* cur = _head;
        while (cur)
        {
            for (auto e : cur->_nextV)
            {
                printf("%2d", cur->_val);
            }
            cout << endl;

            for (auto e : cur->_nextV)
            {
                printf("%2s", "↓");
            }
            printf("\n");

            cur = cur->_nextV[0];
        }



    }
private:
    Node* _head;
    size_t _maxLevel = 32;
    double _p = 0.5;
};

int main()
{
    Skiplist sl;
    sl.Print();
    cout << "-------------------" << endl;

    int a[] = { 5,2,3,8,9,6 };
    for (auto e : a)
    {
        sl.add(e);
        sl.Print();
        cout << "-------------------" << endl;
    }
    for (auto e : a)
    {
        sl.erase(e);
        sl.Print();
        cout << "-------------------" << endl;
    }

    return 0;
}




