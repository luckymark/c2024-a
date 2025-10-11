#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>
using namespace std;
//#define _DBG
#ifdef _DBG
#define PRIVATE public
#else
#define PRIVATE private
#endif
template<class _Ty, class _Pr = less<_Ty>, class _Eq = equal_to<_Ty>> class skiplist {
public:
	using value_type = _Ty;
	using pointer = _Ty *;
	using const_pointer = const _Ty *;
	using reference = _Ty &;
	using const_reference = const _Ty &;
	using size_type = size_t;
PRIVATE:
	struct _Node {
		value_type _Myval;
		vector<_Node *> _Forward;
		_Node(int _Val, int _Level) : _Myval(_Val), _Forward(_Level + 1, nullptr) {}
		~_Node() = default;
	};
	struct _Gen_bool {
		_Gen_bool() {
			srand(time(0));
		}
		bool _Getbool() {
			return rand() % 2;
		}
		bool operator()() {
			return rand() % 2;
		}
	};
public:
	skiplist() : _Nodecnt(0), _Level(0), _Dummy(new _Node(0, max_level)) {}
	skiplist(const initializer_list<value_type> &_Ilist)
		: _Nodecnt(0), _Dummy(new _Node(0, max_level)) {
		for(const auto &elem : _Ilist) {
			insert(elem);
		}
	}
	skiplist(const skiplist<_Ty, _Pr, _Eq> &other) : _Nodecnt(0),
		_Dummy(new _Node(0, max_level)) {
		_Node *curr = other._Dummy->_Forward[0];
		while(curr) {
			insert(curr->_Myval);
			curr = curr->_Forward[0];
		}
	}
	~skiplist() {
		_Node *curr = _Dummy;
		while(curr) {
			_Node *tmp = curr;
			curr = curr->_Forward[0];
			delete tmp;
		}
	}
	bool search(const_reference _Val) const {
		_Node *curr = _Dummy;
		for(int i = static_cast<int>(_Level); i >= 0; --i) {
			while(curr->_Forward[i]) {
				if(_Equal(_Val, curr->_Forward[i]->_Myval)) {
					return true;
				}
				else if(_Compare(curr->_Forward[i]->_Myval, _Val)) {
					curr = curr->_Forward[i];
				}
				else {
					break;
				}
			}
		}
		return false;
	}
	void insert(const_reference _Val) {
		vector<_Node *> update(max_level + 1, nullptr);
		_Node *curr = _Dummy;
		for(int i = static_cast<int>(_Level); i >= 0; --i) {
			while(curr->_Forward[i]) {
				if(_Compare(curr->_Forward[i]->_Myval, _Val)) {
					curr = curr->_Forward[i];
				}
				else {
					break;
				}
			}
			update[i] = curr;
		}
		size_t level = _Get_random_level();
		if(level > _Level) {
			level = _Level + 1;
			update[level] = _Dummy;
			_Level = level;
		}
		_Node *newnode = new _Node(_Val, level);
		for(size_t i = 0; i <= level; ++i) {
			newnode->_Forward[i] = update[i]->_Forward[i];
			update[i]->_Forward[i] = newnode;
		}
		++_Nodecnt;
	}
	bool erase(const_reference _Val) {
		_Node *curr = _Dummy;
		for(int i = static_cast<int>(_Level); i >= 0; --i) {
			while(curr->_Forward[i]) {
				if(_Equal(_Val, curr->_Forward[i]->_Myval)) {
					_Node *to_erase = curr->_Forward[i];
					for(int j = i; j >= 0; --j) {
						while(!_Equal(curr->_Forward[j]->_Myval, _Val)) {
							curr = curr->_Forward[j];
						}
						curr->_Forward[j] = to_erase->_Forward[j];
					}
					delete to_erase;
					--_Nodecnt;
					return true;
				}
				else if(_Compare(curr->_Forward[i]->_Myval, _Val)) {
					curr = curr->_Forward[i];
				}
				else {
					break;
				}
			}
		}
		return false;
	}
	size_type size() const {
		return _Nodecnt;
	}
	size_type level() const {
		return _Level;
	}
	void display() const {
		for(int i = static_cast<int>(_Level); i >= 0; --i) {
			cout << "level " << i << ": ";
			_Node *node = _Dummy->_Forward[i];
			while(node != nullptr) {
				cout << node->_Myval << " ";
				node = node->_Forward[i];
			}
			cout << endl;
		}
		cout << endl;
	}
private:
	struct _Iterator {
		using iterator_category = std::forward_iterator_tag;
		using value_type = const _Ty;
		using difference_type = std::ptrdiff_t;
		using pointer = const _Ty *;
		using reference = const _Ty &;
		_Iterator(_Node *_Begin) : _Myptr(_Begin) {}
		reference operator*() const {
			return _Myptr->_Myval;
		}
		pointer operator->() const {
			return addressof(_Myptr->_Myval);
		}
		_Iterator &operator++() {
			_Myptr = _Myptr->_Forward[0];
			return *this;
		}
		_Iterator operator++(int) {
			_Iterator tmp = *this;
			_Myptr = _Myptr->_Forward[0];
			return tmp;
		}
		bool operator==(const _Iterator &_Right) const {
			return _Myptr == _Right._Myptr;
		}
		bool operator!=(const _Iterator &_Right) const {
			return _Myptr != _Right._Myptr;
		}
	private:
		_Node *_Myptr;
	};
public:
	using iterator = _Iterator;
	iterator begin() const {
		return iterator(_Dummy->_Forward[0]);
	}
	iterator end() const {
		return iterator(nullptr);
	}
PRIVATE:
	size_t _Get_random_level() {
		for(size_t ret = 0; ret < max_level; ++ret) {
			if(!_Controller._Getbool()) return ret;
		}
		return max_level - 1;
	}
PRIVATE:
	_Node *_Dummy;
	size_type _Level, _Nodecnt;
	_Gen_bool _Controller{};
	static constexpr inline _Pr _Compare{};
	static constexpr inline _Eq _Equal{};
public:
	static constexpr inline size_type max_level = 32ULL;
};
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	skiplist<int> lst;
	int n = 5000000;
	while(n--) {
		lst.insert(rand());
	}
	vector<int> vec(lst.begin(), lst.end());
	int k = rand();
	time_t t1 = clock();
	cout << (lst.search(k) ? "true" : "false") << endl;
	time_t t2 = clock();
	cout << ((std::find(vec.begin(), vec.end(), k) != vec.end()) ? "true" : "false") << endl;
	time_t dt1 = t2 - t1, dt2 = clock() - t2;
	cout << "dt1 = " << dt1 << "ms, dt2 = " << dt2 << "ms" << endl; // 唉，常数，dt1 = 2ms, dt2 = 1ms
	// 喜报：在g++中，dt1=0ms，dt2=15ms，可喜可贺
	return 0;
}
