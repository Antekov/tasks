from abc import ABCMeta, abstractmethod, abstractproperty
from random import randint

from . import Unit


class Archer(Unit):
    count = 0
    minPower = 8
    maxPower = 15

    minDefense = 2
    maxDefense = 4

    price = 10

    @staticmethod
    def generateParams():
        power = randint(Archer.minPower, Archer.maxPower)
        defense = randint(Archer.minDefense, Archer.maxDefense)

        return power, defense

    def __init__(self, health, power, defense, name=None):
        super().__init__(health, power, defense)
        self.type = 'Archer'

        Archer.count += 1

        if name is None:
            self.name = self.type + ' ' + str(Archer.count)
        else:
            self.name = name

    def __str__(self):
        return f'{self.type} {self.name} | ' + super().__str__()


class EnglishArcher(Archer):
    pass


class FrenchArcher(Archer):
    pass
