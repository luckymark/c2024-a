//
// Created by Emerson on 2024/9/23.
//
#include <iostream>
#include<string>

//˼·���� yuanma ǰ target ���ַ���ԭ˳���ƶ����ַ���ĩβ
using namespace std;

string yuanma;
string mima;
string jiema;
int target;

string mimahanshu(string& yuanma, int& target) {
    // for (int i = 0; i < yuanma.size(); ++i) {
    //     mima = mima + yuanma[(i + target) % yuanma.size()];
    // }
    //�Ż�����
    return yuanma.substr(target) + yuanma.substr(0,target);
}

string jiemahanshu(string& mima, int& target) {
    // for (int i = 0; i < mima.size(); ++i) {
    //     jiema = jiema + mima[(i + mima.size() - target) % mima.size()];
    // }
    //�Ż�����
    return mima.substr(mima.size()-target) + mima.substr(0,mima.size()-target);
}
int main() {
    cout <<"������Դ��:";
    cin >> yuanma;
    cout <<"������ı�λ��:";
    cin >> target;
    mima = mimahanshu(yuanma, target);
    cout <<"����Ϊ" << mima << endl;
    jiema = jiemahanshu(mima, target);
    cout << "����Ϊ" << jiema << endl;

}