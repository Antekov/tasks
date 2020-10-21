#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include "mylist.h"
using namespace std;
//Деструктор класса List
MyList::~MyList()
{
Clear();
}
// очистка списка (удаление всех эл.)
void MyList::Clear()
{
while (Head != NULL) //Пока по адресу есть хоть что-то
{
Item* temp = Head->next; //Сразу запом. указатель на адрес след. элемента структуры
delete Head; //Освобождаем память по месту начала списка
Head = temp; //Меняем адрес начала списка
}
Head = NULL;
}
/*функция добавления новой записи в начало списка*/
void MyList::AddToTop(Student* st)
{
Item* temp = new Item(st); //Выделение памяти под новый элемент
temp->next = Head; //Указываем, что адрес следующего элемента это старое начало списка
Head = temp; //Смена адреса начала списка
}
/*функция добавления новой записи в конец списка*/
void MyList::AddToEnd(Student* st)
{
Item* tmpNewItem = new Item(st); //Выделение памяти под новый элемент
//если список пустой, то новый эл. это голова списка
if (Head == NULL) {
Head = tmpNewItem;
return;
}
//если список не пустой, то переходим на последний эл. и добавляем в конец
Item* p = Head;
while (p->next != NULL) {
p = p->next;
}
//теперь p указывает на последний эл-т
p->next = tmpNewItem; //добавляем новый эл-т в конец
}
/*вывод списка на экран*/
void MyList::Show()
{
Item* temp = Head; //Объявляем указатель, он указывает на начало
system("cls"); // очисткаэкрана
cout << setw(20) << "NameLast" << setw(20) << "Name" <<
setw(10) << "Age" << setw(10) << "Course\n"; // выводзаголовка
cout << "_______________________________________"
<< endl << endl;
while (temp != NULL) //Пока по адресу на начало есть данные
{
//Выводим все элементы структуры
cout << setw(20) << temp->data.NameLast; //Вывод имени
cout << setw(20) << temp->data.Name; //Вывод фамилии
cout << setw(10) << temp->data.Age; //Вывод возраста
cout << setw(10) << temp->data.Course << endl; //Вывод курса
//Переходим на следующий адрес из списка
temp = temp->next;
}
cout << "________________________________________" << endl << endl;
}
// чтение из файла в тот же список
// старые элеметы удаляются
bool MyList::ReadFromFile(char * file_name)
{
//если имя файла отсутствует
if (file_name == NULL) return false;
ifstream fin;
fin.open(file_name, ios::binary | ios::in);
//Если файл не открыт
if (!fin) return false;
// когда файл открыт ------------------
Clear(); // удаляем старые элементы
//в цикле читаем из файла и добавляем в конец списка
Student tmpStud;
bool isOk;
while (!fin.eof()) {
if (fin.peek() != EOF) {
isOk = tmpStud.read(&fin);
if (!isOk) {
fin.close(); //Закрываем файл
return false;
}
AddToEnd( &tmpStud );
}
}
fin.close(); //Закрываем файл
return true;
}
bool MyList::LoadToFile(char* file_name)
{
//если имя файла отсутствует
if (file_name == NULL) return false;
ofstream fout(file_name, ios::binary | ios::out);
//Если файл не открыт
if (!fout) return false;
Item* temp = Head; //Объявляем указатель, он указывает на начало списка
while (temp != NULL) //Пока по адресу на начало есть данные
{
temp->data.write( &fout );
temp = temp->next; //переходим на следующий адрес из списка
if (!fout.good()) {
fout.close();
return false; //если ошибка записи
}
}
fout.close();
return true;
}