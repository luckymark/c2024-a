//
// Created by Emerson on 2024/9/24.
//
#include <iostream>
using namespace std;

void hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        cout <<"�ƶ�����" << n << " " <<from_rod << " -> " << to_rod << endl;
        return;
    }
    hanoi(n - 1, from_rod, aux_rod, to_rod);//��n-1�����ӵ���һ�����壬��A�Ƶ�B������C
    cout << "�ƶ�����" << n << " "<<from_rod << " -> " << to_rod << endl;
    hanoi(n - 1, aux_rod, to_rod, from_rod);//����B��A��λ�ã���A���ɸ������ӣ�B�����������
}

int main() {
    int n = 64;
    char from_rod = 'A';
    char to_rod = 'C';
    char aux_rod = 'B';

    cout << "��ŵ���Ľ������:\n";
    hanoi(n, from_rod, to_rod, aux_rod);
    return 0;
}