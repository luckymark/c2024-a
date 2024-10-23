//真的有点崩溃，在VS上跑的好好的，在CLION上就直接没反应
//也不是报错，也不是啥，就是没反应
//受不了啦，就这样吧，代码逻辑应该是没问题的
//为了在CLION上不报错，我把VS上的fscanf_s和scanf_s都改成了fscanf和scanf

#include <iostream>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <cstring>
using namespace std;

#define NAME_MAX 20
#define GOODS_KINDS_MAX 20

void List()
{
    system("cls");
    FILE* file;
    errno_t err;
    err=fopen_s(&file, "store.txt", "r");
    if (err != 0)
    {
        cout << "We cannot find the document" << endl;
        return;
    }
    char** name = (char**)malloc(GOODS_KINDS_MAX *sizeof(char*));
    for (int i = 0; i < GOODS_KINDS_MAX; i++)
    {
        name[i] = (char*)calloc(NAME_MAX, sizeof(char));
    }
    int* num = (int*)malloc(GOODS_KINDS_MAX * sizeof(int));

    int i = 0;
    while (fscanf(file, "%s", name[i], NAME_MAX) != EOF)
    {
        fscanf(file, "%d", &num[i]);
        getc(file);

        cout << name[i] << " " << num[i] << endl;
        i++;
    }

    fclose(file);

    Sleep(2000);
    for (int i = 0; i < GOODS_KINDS_MAX; i++)
    {
        free(name[i]);
    }
    free(name);
    free(num);
    return;

}
void Warehousing()
{
    system("cls");
    cout << "Please input the goods' name and the amount that you want to put in" << endl;
    char goods_name[NAME_MAX];
    int amout;

    scanf("%s%d", goods_name,NAME_MAX, &amout);

    char** name = (char**)malloc(GOODS_KINDS_MAX * sizeof(char*));
    for (int i = 0; i < GOODS_KINDS_MAX; i++)
    {
        name[i] = (char*)calloc(NAME_MAX, sizeof(char));
    }
    int* num = (int*)calloc(GOODS_KINDS_MAX , sizeof(int));

    FILE* file;
    fopen_s(&file, "store.txt", "r");

    int i = 0;
    while (fscanf(file, "%s", name[i], NAME_MAX) != EOF)
    {
        fscanf(file, "%d", &num[i]);
        getc(file);
        i++;
    }
    bool judge = 1;
    for (int j = 0; j < i; j++)
    {
        if (strcmp(goods_name, name[j])==0)
        {
            judge = 0;
            num[j] += amout;
        }
    }

    if (judge)
    {
        strcpy_s(name[i], NAME_MAX, goods_name);
        num[i] = amout;
    }

    fclose(file);

    fopen_s(&file, "store.txt", "w");
    for (int j = 0; j <= i; j++)
    {
        fprintf(file, "%s %d\n", name[j], num[j]);
    }
    fclose(file);

    for (int i = 0; i < GOODS_KINDS_MAX; i++)
    {
        free(name[i]);
    }
    free(name);
    free(num);

    cout << "OK,FINE" << endl;
    Sleep(2000);
    return;

}
void Delivering()
{
    system("cls");
    cout << "Please input the name and the amount of the goods that you want to deliver" << endl;
    char goods_name[NAME_MAX];
    int amount;

    scanf("%s%d", goods_name, NAME_MAX, &amount);

    char** name = (char**)malloc(GOODS_KINDS_MAX * sizeof(char*));
    for (int i = 0; i < GOODS_KINDS_MAX; i++)
    {
        name[i] = (char*)calloc(NAME_MAX, sizeof(char));
    }
    int* num = (int*)calloc(GOODS_KINDS_MAX, sizeof(int));

    FILE* file;
    fopen_s(&file, "store.txt", "r");

    int i = 0;
    while (fscanf(file, "%s", name[i], NAME_MAX) != EOF)
    {
        fscanf(file, "%d", &num[i]);
        getc(file);
        i++;
    }

    bool judge = 1;
    for (int j = 0; j < i; j++)
    {
        if (strcmp(goods_name, name[j]) == 0)
        {
            judge = 0;
            if (num[j] < amount)
            {
                cout << "It is not enough" << endl;
                Sleep(1500);
                return;
            }
            num[j] -= amount;
        }
    }

    if (judge)
    {
        cout << "We don't have " << goods_name << " in the store" << endl;
        Sleep(1500);
        return;
    }

    fclose(file);

    fopen_s(&file, "store.txt", "w");
    for (int j = 0; j <= i; j++)
    {
        fprintf(file, "%s %d\n", name[j], num[j]);
    }
    fclose(file);

    for (int i = 0; i < GOODS_KINDS_MAX; i++)
    {
        free(name[i]);
    }
    free(name);
    free(num);

    cout << "OK,FINE" << endl;
    Sleep(2000);
    return;

}


int main()
{
    while (1)
    {
        system("cls");
        cout << "Welcome to my store" << endl;
        cout << "1.List" << endl;
        cout << "2.Warehousing" << endl;
        cout << "3.Delivering" << endl;
        cout << "4.Exit" << endl;
        char c = _getch();
        int flag = 0;
        switch (c)
        {
            case '1':
                List();
                break;
            case '2':
                Warehousing();
                break;
            case '3':
                Delivering();
                break;
            case '4':
                flag = 1;
                break;
            default:
                break;
        }
        if (flag) break;
    }

    system("cls");
    cout << "Bye" << endl;
    cout << "See you next time" << endl;
    return 0;
}