#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <ctime>
#include "student.h"
#include "item.h"
#include "mylist.h"
using namespace std;
//---------------------прототипы функций -------------------------
//реализация пункта меню "1: Read from the file"
void ReadListFromFile(MyList* lst);
//реализация пункта меню "3: Add student"
void AddStudToList(MyList* lst);
//реализация пункта меню "4: Save to the file"
void LoadListToFile(MyList* lst);
int main()
{
cout.setf(ios::left); // выравнивание по левому краю
bool flag = true; // флаг продолжения работы
int choice; // выбор пользователя
Student student; // переменная типа Студент
MyList spisok; // переменная типа Список
while (flag)
{
system("cls"); // очисткаэкрана
cout << " MENU" << endl;
cout << "_____________________" << endl;
cout << "1: Read from the file" << endl;
cout << "2: Show list" << endl;
cout << "3: Add student" << endl;
cout << "4: Save to the file" << endl;
cout << "5: Delete last the record" << endl;
cout << "6: Search" << endl;
cout << "7: Sort" << endl;
cout << "8: Exit" << endl;
cout << "_____________________" << endl << endl;
cout << "Make your choice (1-8): ";
cin >> choice;
switch (choice)
{
case 1: ReadListFromFile( &spisok); system("PAUSE"); break;
case 2: spisok.Show(); system("PAUSE"); break;
case 3: AddStudToList( &spisok ); break;
case 4: LoadListToFile( &spisok ); break;
case 5:
case 6:
case 7: cout << "Not implemented :( " << endl; break;
case 8: flag = false; break;
default: cout << "You are wrong. " << endl;
}
}
system("PAUSE");
return 0;
}
//реализация пункта меню "1: Read from the file"
void ReadListFromFile( MyList * lst) {
if (lst == NULL) {
cout << "Wrong list!!" << endl;
return;
}
char file_name[30]; // если имя файла задается пользователем
//ifstream fin("C:\\Users\\Stud\\Desktop\\temp\\student.dat", ios::binary | ios::in);
cout << "Input file name: ";
cin >> file_name;
if (! lst->ReadFromFile(file_name) )
cout << "Wrong File\n";
else
cout << "Data is received\n";
}
//реализация пункта меню "3: Add student"
void AddStudToList(MyList* lst) {
if (lst == NULL) {
cout << "Wrong list!!" << endl;
return;
}
Student st;
system("cls"); // Очистка экрана
cin.ignore(); //Игнорируем символ
cout << "NameLast: "; cin.getline(st.NameLast, 20); //Ввод имени
cout << "Name: "; cin.getline(st.Name, 20); //Ввод фамилии
cout << "Age: "; cin >> st.Age; //Ввод возраста
cin.ignore(); //Игнорируем символ
cout << "Course: "; cin >> st.Course; //Ввод курса
cin.ignore(); //Игнорируем символ
lst->AddToTop(&st);
}
//реализация пункта меню "4: Save to the file"
void LoadListToFile(MyList* lst) {
if (lst == NULL) {
cout << "Wrong list!!" << endl;
return;
}
char file_name[30];
system("cls");
cout << "Input file name: ";
cin >> file_name;
cout << "Begin writing...\n";
if ( lst->LoadToFile( file_name ) ) //Если открытие файла прошло успешно
{
cout << "File created\n";
}
else cout << "File is not create\n";
system("pause");
}