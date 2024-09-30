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

// ��ȡ�������
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

// ����������
void saveInventory(const string& filename, const vector<InventoryItem>& inventory) {
    ofstream file(filename);
    for (const auto& item : inventory) {
        file << item.model << " " << item.quantity << "\n";
    }
    file.close();
}

// ��ʾ����б�
void displayInventory(const vector<InventoryItem>& inventory) {
    cout << "����б�:" << endl;
    for (const auto& item : inventory) {
        cout << "�ͺ�: " << item.model << ", ����: " << item.quantity << endl;
    }
}

// ���
void addInventory(vector<InventoryItem>& inventory) {
    string model;
    int quantity;
    cout << "�����ͺ�: ";
    cin >> model;
    cout << "��������: ";
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

// ����
void removeInventory(vector<InventoryItem>& inventory) {
    string model;
    int quantity;
    cout << "�����ͺ�: ";
    cin >> model;
    cout << "��������: ";
    cin >> quantity;

    bool found = false;
    for (auto& item : inventory) {
        if (item.model == model) {
            if (item.quantity >= quantity) {
                item.quantity -= quantity;
                found = true;
            } else {
                cout << "��治�㣬�޷�����ָ��������" << endl;
                return;
            }
            break;
        }
    }

    if (!found) {
        cout << "δ�ҵ�ָ���ͺŵĿ�档" << endl;
    }
}

int main() {
    using namespace std;
    const string filename = "inventory.txt";
    vector<InventoryItem> inventory = readInventory(filename);

    int choice;
    do {
        cout << "1. ��ʾ����б�\n";
        cout << "2. ���\n";
        cout << "3. ����\n";
        cout << "4. ���沢�˳�����\n";
        cout << "��ѡ�����: ";
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
                cout << "�������˳���" << endl;
                break;
            default:
                cout << "��Чѡ�����������롣" << endl;
        }
    } while (choice != 4);

    return 0;
}