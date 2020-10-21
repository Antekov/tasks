#include <iostream>
#include <iomanip>
#include <cstring>
#include "reader.h"

using namespace std;
int main()
{
    setlocale(0, "");
    
    freopen("readers.txt", "r", stdin);

    // ���������� �������
    // �������� readers ���� student
    struct reader readers[10];
        
    int records = 0;
    // ���������� ���������� ����������-�����
    char flag = 'y';
    cout << "���� ������ � ���������" << endl;
    // ���� ������
    do {
        cout << "�������� �" << records + 1 << endl;
        cout << "������� �������: ";
        cin >> readers[records].name;
        cout << "������� ����� ������������� ������: ";
        cin >> readers[records].id;
        cout << "������� �������� �����: ";
        cin >> readers[records].book;
        cout << "������� ���� �������� (Y-m-d): ";
        cin >> readers[records].date;
        records++;
        cout << "���������� ����? (y/n)";
        cin >> flag;
        cout << endl;
    } while (flag == 'y' && records < 10);
    
    cout << endl << "������ ���������, ������� �������������" << endl;
    cout << setw(16) << "�������" << setw(20) <<
    "����� ������" << endl;
    for (int i = 0; i < records; i++) {
        if (strcmp(readers[i].date, "2020-03-24") < 0) {
            cout << setw(16) << readers[i].name << setw(20) <<
            readers[i].id  << setw(24) << readers[i].book << endl;
        }
    }
    return 0;
}