#include <iostream>
#include <iomanip>
#include <cstring>
#include "reader.h"

using namespace std;
int main()
{
    setlocale(0, "");
    
    freopen("readers.txt", "r", stdin);

    // Объявление массива
    // структур readers типа student
    struct reader readers[10];
        
    int records = 0;
    // Объявление символьной переменной-флага
    char flag = 'y';
    cout << "Ввод данных о читателях" << endl;
    // Ввод данных
    do {
        cout << "Читатель №" << records + 1 << endl;
        cout << "Введите фамилию: ";
        cin >> readers[records].name;
        cout << "Введите номер читательского билета: ";
        cin >> readers[records].id;
        cout << "Введите название книги: ";
        cin >> readers[records].book;
        cout << "Введите дату возврата (Y-m-d): ";
        cin >> readers[records].date;
        records++;
        cout << "Продолжить ввод? (y/n)";
        cin >> flag;
        cout << endl;
    } while (flag == 'y' && records < 10);
    
    cout << endl << "Список читателей, имеющих задолженности" << endl;
    cout << setw(16) << "Фамилия" << setw(20) <<
    "Номер билета" << endl;
    for (int i = 0; i < records; i++) {
        if (strcmp(readers[i].date, "2020-03-24") < 0) {
            cout << setw(16) << readers[i].name << setw(20) <<
            readers[i].id  << setw(24) << readers[i].book << endl;
        }
    }
    return 0;
}