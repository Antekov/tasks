from abc import ABCMeta, abstractmethod, abstractproperty
from random import randint

from . import Unit


class Knight(Unit):
    count = 0

    minPower = 15
    maxPower = 25

    minDefense = 10
    maxDefense = 18

    price = 40

    @staticmethod
    def generateParams():
        power = randint(Knight.minPower, Knight.maxPower)
        defense = randint(Knight.minDefense, Knight.maxDefense)

        return power, defense

    def __init__(self, health, power, defense, name=None):
        super().__init__(health, power, defense)
        self.type = 'Knight'

        Knight.count += 1

        if name is None:
            self.name = self.type + ' ' + str(Knight.count)
        else:
            self.name = name

    def __str__(self):
        return f'{self.type} {self.name} | ' + super().__str__()


class EnglishKnight(Knight):
    pass


class FrenchKnight(Knight):
    pass
