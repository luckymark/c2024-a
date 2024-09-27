//
// Created by Emerson on 2024/9/23.
//
#include <iostream>
#include<string>
using namespace std;

string yuanma;
string mima;
int target;

void mimahanshu(string& yuanma, int& target) {
    for (int i = 0; i < yuanma.size(); ++i) {
        mima = mima + yuanma[(i + target) % yuanma.size()];
    }
}

string jiemahanshu(string& mima, int& target,string &jiema) {
    for (int i = 0; i < mima.size(); ++i) {
        jiema = jiema + mima[(i + mima.size() - target) % mima.size()];
    }

    return jiema;
}
int main() {
    cout <<"请输入源码:";
    cin >> yuanma;
    cout <<"请输入改变位数:";
    cin >> target;
    mimahanshu(yuanma, target);
    cout <<"密码为" << mima << endl;
    string jiema;
    jiema = jiemahanshu(mima, target, jiema);
    cout << "解码为" << jiema << endl;

}