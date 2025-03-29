//只加密了大小写字母，数字和符号未加密（懒bushi）
//代码应该没什么问题，但在CLION上跑的时候第二行前莫名有一个空格，VS跑的时候就没有
//感觉和换行符有关，但没有细究
#include <iostream>
#include <string>
using namespace std;
// 加密函数
string encrypt(const string& text) {
    string encrypted;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = static_cast<char>(((c - base + 3) % 26) + base);
        }
        encrypted += c;
    }
    return encrypted;
}

// 解密函数
string decrypt(const string& text) {
    string decrypted;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = static_cast<char>(((c - base - 3 + 26) % 26) + base);
        }
        decrypted += c;
    }
    return decrypted;
}

int main() {
    cout << "Original text: ";
    string text;
    getline(cin,text);   //一次性读到换行符为止
    string encryptedText = encrypt(text);
    string decryptedText = decrypt(encryptedText);

    cout << "Encrypted text: " << encryptedText << endl;
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}