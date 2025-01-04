#include <iostream>
#include <string>

// 加密函数
std::string encrypt(const std::string& text, int shift) {
    std::string result = "";

    for (char ch : text) {
        // 处理大写字母
        if (isupper(ch)) {
            result += char((ch + shift - 'A') % 26 + 'A');
        }
        // 处理小写字母
        else if (islower(ch)) {
            result += char((ch + shift - 'a') % 26 + 'a');
        }
        // 非字母字符保持不变
        else {
            result += ch;
        }
    }

    return result;
}

// 解密函数
std::string decrypt(const std::string& text, int shift) {
    // 解密是加密的逆过程，移动位数取反
    return encrypt(text, 26 - shift);
}

int main() {
    std::string input;
    int shift;

    // 输入字符串和移动位数
    std::cout << "请输入要加密的字符串: ";
    std::getline(std::cin, input);
    std::cout << "请输入移动位数（密钥）: ";
    std::cin >> shift;

    // 加密
    std::string encrypted = encrypt(input, shift);
    std::cout << "加密后的字符串: " << encrypted << std::endl;

    // 解密
    std::string decrypted = decrypt(encrypted, shift);
    std::cout << "解密后的字符串: " << decrypted << std::endl;

    return 0;
}