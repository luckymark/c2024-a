#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// 定义货物结构
struct Product {
    std::string model; // 货物型号
    int quantity;      // 货物数量
};

// 全局变量：库存列表
std::vector<Product> inventory;

// 显示存货列表
void displayInventory() {
    if (inventory.empty()) {
        std::cout << "库存为空！" << std::endl;
        return;
    }

    std::cout << "存货列表：" << std::endl;
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << "型号: " << inventory[i].model << ", 数量: " << inventory[i].quantity << std::endl;
    }
}

// 入库
void addStock() {
    std::string model;
    int quantity;

    std::cout << "请输入货物型号: ";
    std::cin >> model;
    std::cout << "请输入入库数量: ";
    std::cin >> quantity;

    // 查找是否已存在该型号
    for (auto& product : inventory) {
        if (product.model == model) {
            product.quantity += quantity;
            std::cout << "入库成功！" << std::endl;
            return;
        }
    }

    // 如果不存在，添加新货物
    inventory.push_back({ model, quantity });
    std::cout << "新货物入库成功！" << std::endl;
}

// 出库
void removeStock() {
    std::string model;
    int quantity;

    std::cout << "请输入货物型号: ";
    std::cin >> model;
    std::cout << "请输入出库数量: ";
    std::cin >> quantity;

    // 查找货物
    for (auto& product : inventory) {
        if (product.model == model) {
            if (product.quantity >= quantity) {
                product.quantity -= quantity;
                std::cout << "出库成功！" << std::endl;
            }
            else {
                std::cout << "库存不足，无法出库！" << std::endl;
            }
            return;
        }
    }

    std::cout << "未找到该货物！" << std::endl;
}

// 从文件加载库存数据
void loadInventory() {
    std::ifstream file("inventory.txt");
    if (!file.is_open()) {
        std::cout << "未找到库存文件，将创建新文件。" << std::endl;
        return;
    }

    inventory.clear();
    std::string model;
    int quantity;
    while (file >> model >> quantity) {
        inventory.push_back({ model, quantity });
    }

    file.close();
    std::cout << "库存数据加载成功！" << std::endl;
}

// 保存库存数据到文件
void saveInventory() {
    std::ofstream file("inventory.txt");
    if (!file.is_open()) {
        std::cerr << "无法保存库存数据！" << std::endl;
        return;
    }

    for (const auto& product : inventory) {
        file << product.model << " " << product.quantity << std::endl;
    }

    file.close();
    std::cout << "库存数据保存成功！" << std::endl;
}

// 显示菜单
void showMenu() {
    std::cout << "===== 进销存管理系统 =====" << std::endl;
    std::cout << "1. 显示存货列表" << std::endl;
    std::cout << "2. 入库" << std::endl;
    std::cout << "3. 出库" << std::endl;
    std::cout << "4. 退出程序" << std::endl;
    std::cout << "请选择功能: ";
}

int main() {
    // 启动时加载库存数据
    loadInventory();

    int choice;
    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayInventory();
            break;
        case 2:
            addStock();
            break;
        case 3:
            removeStock();
            break;
        case 4:
            // 退出时保存库存数据
            saveInventory();
            std::cout << "程序已退出。" << std::endl;
            return 0;
        default:
            std::cout << "无效选择，请重新输入！" << std::endl;
            break;
        }
    }

    return 0;
}