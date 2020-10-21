#include "student.h"
using namespace std;
//методы структуры Student -------------------------
bool Student::write(ofstream* fout) {
//Если файл не открыт
if (!fout) return false;
//записываем
fout->write((char*)this, sizeof(Student));
if (fout->good())
return true;
//else
return false;
}
//метод чтения данных из файла
//поток должен быть уже открыт
bool Student::read(ifstream* fin) {
//Если файл не открыт
if (!fin) return false;
if (fin->peek() == EOF) return false;
fin->read((char*)this, sizeof(Student));
if (fin->good())
return true;
//else
return false;
}