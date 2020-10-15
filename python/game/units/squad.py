from abc import ABCMeta, abstractmethod, abstractproperty
from random import randint


class Squad:
    '''
    Армия (отряд) боевых единиц. Каждый отряд может состоять из боевых единиц
    и/или из других отрядов
    '''
    def __init__(self, name=''):
        self.units = []
        self.name = name

    def add(self, unit):
        self.units.append(unit)

    def remove(self, unit):
        self.units.remove(unit)

    def all(self):
        '''
        Получение списка всех боевых единиц, входящих в данный отряд и его
        дочерние отряды
        '''
        units = []
        for unit in self.units:
            if isinstance(unit, Squad):
                units += unit.all()
            else:
                units.append(unit)
        return units

    def attack(self, enemy):
        '''
        Метод сражения двух армий.
        Каждый юнит первой армии случайно выбирает себе одного противника из
        другой армии и атакует его.
        Затем каждый юнит другой армии случайно выбирает себе одного противника
        из первой армии и атакует его.
        После боя каждая армия хоронит погибших юнитов.
        '''
        units1 = self.all()
        units2 = enemy.all()

        print(f'{self.name} -> {enemy.name}')
        for unit in units1:
            index = randint(0, len(units2)-1)
            unit.attack(units2[index])

        print(f'\n{enemy.name} -> {self.name}')
        for unit in units2:
            index = randint(0, len(units1)-1)
            unit.attack(units1[index])

        self.clean()
        enemy.clean()
        print()

    def clean(self):
        '''
        Метод удаления погибших юнитов (юнитов, у которых здоровье <= 0)
        '''
        aliveUnits = []
        for i in range(len(self.units)):
            if isinstance(self.units[i], Squad):
                self.units[i].clean()
                if len(self.units[i]) > 0:
                    aliveUnits.append(self.units[i])
            else:
                if self.units[i].health > 0:
                    aliveUnits.append(self.units[i])

        self.units = aliveUnits

    def __str__(self):
        s = [self.name]
        for unit in self.units:
            s.append(str(unit))

        return '\n'.join(s) + '\n'

    def __len__(self):
        res = 0

        for unit in self.units:
            if isinstance(unit, Squad):
                res += len(unit)
            else:
                res += 1

        return res

    def recover(self):
        '''
        Метод восстановления армии.
        Для каждого юнита вызывается метод восстановления
        '''
        for unit in self.units:
            unit.recover()
