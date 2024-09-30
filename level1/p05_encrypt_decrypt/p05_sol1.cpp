//
// Created by Emerson on 2024/9/23.
//
#include <iostream>
#include<string>

//思路：将 yuanma 前 target 个字符按原顺序移动至字符串末尾
using namespace std;

string yuanma;
string mima;
string jiema;
int target;

string mimahanshu(string& yuanma, int& target) {
    // for (int i = 0; i < yuanma.size(); ++i) {
    //     mima = mima + yuanma[(i + target) % yuanma.size()];
    // }
    //优化如下
    return yuanma.substr(target) + yuanma.substr(0,target);
}

string jiemahanshu(string& mima, int& target) {
    // for (int i = 0; i < mima.size(); ++i) {
    //     jiema = jiema + mima[(i + mima.size() - target) % mima.size()];
    // }
    //优化如下
    return mima.substr(mima.size()-target) + mima.substr(0,mima.size()-target);
}
int main() {
    cout <<"请输入源码:";
    cin >> yuanma;
    cout <<"请输入改变位数:";
    cin >> target;
    mima = mimahanshu(yuanma, target);
    cout <<"密码为" << mima << endl;
    jiema = jiemahanshu(mima, target);
    cout << "解码为" << jiema << endl;

}