//
// Created by Emerson on 2024/9/27.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct InventoryItem {
    string model;
    int quantity;
};

// 读取库存数据
vector<InventoryItem> readInventory(const string& filename) {
    vector<InventoryItem> inventory;
    ifstream file(filename);
    string model;
    int quantity;

    while (file >> model >> quantity) {
        inventory.push_back({model, quantity});
    }

    file.close();
    return inventory;
}

// 保存库存数据
void saveInventory(const string& filename, const vector<InventoryItem>& inventory) {
    ofstream file(filename);
    for (const auto& item : inventory) {
        file << item.model << " " << item.quantity << "\n";
    }
    file.close();
}

// 显示存货列表
void displayInventory(const vector<InventoryItem>& inventory) {
    cout << "存货列表:" << endl;
    for (const auto& item : inventory) {
        cout << "型号: " << item.model << ", 数量: " << item.quantity << endl;
    }
}

// 入库
void addInventory(vector<InventoryItem>& inventory) {
    string model;
    int quantity;
    cout << "输入型号: ";
    cin >> model;
    cout << "输入数量: ";
    cin >> quantity;

    bool found = false;
    for (auto& item : inventory) {
        if (item.model == model) {
            item.quantity += quantity;
            found = true;
            break;
        }
    }

    if (!found) {
        inventory.push_back({model, quantity});
    }
}

// 出库
void removeInventory(vector<InventoryItem>& inventory) {
    string model;
    int quantity;
    cout << "输入型号: ";
    cin >> model;
    cout << "输入数量: ";
    cin >> quantity;

    bool found = false;
    for (auto& item : inventory) {
        if (item.model == model) {
            if (item.quantity >= quantity) {
                item.quantity -= quantity;
                found = true;
            } else {
                cout << "库存不足，无法出库指定数量。" << endl;
                return;
            }
            break;
        }
    }

    if (!found) {
        cout << "未找到指定型号的库存。" << endl;
    }
}

int main() {
    using namespace std;
    const string filename = "inventory.txt";
    vector<InventoryItem> inventory = readInventory(filename);

    int choice;
    do {
        cout << "1. 显示存货列表\n";
        cout << "2. 入库\n";
        cout << "3. 出库\n";
        cout << "4. 保存并退出程序\n";
        cout << "请选择操作: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayInventory(inventory);
                break;
            case 2:
                addInventory(inventory);
                break;
            case 3:
                removeInventory(inventory);
                break;
            case 4:
                saveInventory(filename, inventory);
                cout << "程序已退出。" << endl;
                break;
            default:
                cout << "无效选择，请重新输入。" << endl;
        }
    } while (choice != 4);

    return 0;
}