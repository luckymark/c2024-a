#include<iostream>
#include<fstream>
#include <utility>
#include<vector>
#include<algorithm>
using namespace std;
class goods {
public:
	size_t id;
	string name;
	size_t number;
	goods(size_t i, string  n, size_t nu) :id(i), name(move(n)), number(nu) {}
	void display() {
		cout << "id:" << id << ", name:" << name << ", number:" << number << endl;
	}
	void stock_removal(size_t num) {
		if(num > number) throw runtime_error("stocking removal more than original number");
		number -= num;
	}
};
vector<goods> vgoods;
void load() {
	fstream file;
	file.open("我不知道在哪/goods.txt", ios::in);
	if(file.is_open()) {
		size_t i, nu;
		string n;
		while(file >> i >> n >> nu) {
			goods g(i, n, nu);
			vgoods.push_back(g);
		}
		file.close();
	}
	else {
		throw runtime_error("Can't open file");
	}
}
void save() {
	fstream file;
	file.open("D:\\Homework\\level1\\p10_warehouse\\goods.txt", ios::out);
	if(file.is_open()) {
		for(size_t i = 0; i < vgoods.size(); i++) {
			file << vgoods[i].id << endl;
			file << vgoods[i].name << endl;
			file << vgoods[i].number << endl;
		}
		file.close();
	}
	else {
		throw runtime_error("Can't open file");
	}
}
constexpr size_t npos = static_cast<size_t>(-1);
size_t get_good_index_by_id(size_t id) {
	for(size_t i = 0; i < vgoods.size(); i++) {
		if(vgoods[i].id == id) {
			return i;
		}
	}
	return npos;
}
void showcase_all() {
	for(goods &vgood : vgoods) {
		vgood.display();
	}
}
int main() noexcept {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	try {
		load();
	}
	catch(exception &e) {
		cout << e.what() << "\n";
		return -1;
	}
	while(true) {
		try {
			cout << "Welcome to Warehouse Management System!\nPress 1 to stock goods into warehouse, press 2 to stock removal from warehouse,\n press 3 to showcase all goods in warehouse, ans press 0 to exit\n";
			int choice;
			cin >> choice;
			switch(choice) {
				case 0:
					return 0;
				case 1: {
					cout << "Please enter the id of the good you want to stock\n";
					int id;
					cin >> id;
					size_t _index = get_good_index_by_id(id);
					if(_index == npos) {
						cout << "Not finding the id you entered. A new one?(y/n)\n";
						char ch;
						cin >> ch;
						if(ch == 'n') break;
						if(ch == 'N') break;
						cout << "Please enter the name of the good\n";
						string n;
						cin >> n;
						cout << "Please enter the number of the good\n";
						int nu;
						cin >> nu;
						goods g(id, n, nu);
						vgoods.push_back(g);
						cout << "Stocking success!\n";
						save();
					}
					else {
						cout << "The id is already in the warehouse. The details of it are as fellow:\n";
						vgoods[_index].display();
						cout << "Continue?(y/n)\n";
						char ch;
						cin >> ch;
						if(ch == 'n') break;
						if(ch == 'N') break;
						cout << "Please enter the number of the good you want to stock\n";
						int nu;
						cin >> nu;
						vgoods[_index].number += nu;
						cout << "Stocking success!\n";
						save();
					}
				}
					  system("pause");
					  system("cls");
					  break;
				case 2: {
					if(vgoods.empty()) {
						cout << "The warehouse is empty! Please enter a good first\n";
						break;
					}
					showcase_all();
					cout << "Please enter the id of the good you want to stock removal\n";
					int i;
					cin >> i;
					size_t _index = get_good_index_by_id(i);
					if(_index == npos) {
						throw runtime_error("Not finding the id you entered.");
					}
					cout << "Please enter the number of the good you want to stock removal\n";
					int nu;
					cin >> nu;
					vgoods[_index].stock_removal(nu);
					cout << "Removal stocking success!\n";
					save();
				}
					  system("pause");
					  system("cls");
					  break;
				case 3: {
					showcase_all();
				}
					  system("pause");
					  system("cls");
					  break;
				default:
					cerr << "Invalid choice\n";
					system("pause");
					system("cls");
					break;
			}
		}
		catch(exception &e) {
			cerr << e.what() << "\n";
			//return -1;
		}
		catch(int i) {
			cerr << i << "\n";
			//return -2;
		}
		catch(...) {
			cerr << "Unknown exception\n";
		}
	}
	return 0;
}