#pragma once
/*структура студент*/
#include <fstream>
struct Student
{
char NameLast[20]; // Фамилия
char Name[20]; // Имя
int Age; //Возраст
int Course; // Курс
//метод записи данных в файл
//поток должен быть уже открыт
bool write( std::ofstream *fout );
//метод чтения данных из файла
//поток должен быть уже открыт
bool read(std::ifstream *fin );
};