#pragma once
#include "student.h"
//Элемент односвязного списка
struct Item {
Student data;
Item* next;
//конструктор
Item(Student* st) {
//копируем поля из параметра st в поле data
strcpy_s(data.NameLast, st->NameLast);
strcpy_s(data.Name, st->Name);
data.Age = st->Age;
data.Course = st->Course;
next = NULL;
}
};