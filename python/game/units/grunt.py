from abc import ABCMeta, abstractmethod, abstractproperty
from random import randint

from . import Unit


class Grunt(Unit):
    count = 0

    minPower = 12
    maxPower = 20

    minDefense = 6
    maxDefense = 10

    price = 15

    @staticmethod
    def generateParams():
        power = randint(Grunt.minPower, Grunt.maxPower)
        defense = randint(Grunt.minDefense, Grunt.maxDefense)

        return power, defense

    def __init__(self, health, power, defense, name=None):
        super().__init__(health, power, defense)
        self.type = 'Grunt'

        Grunt.count += 1

        if name is None:
            self.name = self.type + ' ' + str(Grunt.count)
        else:
            self.name = name

    def __str__(self):
        return f'{self.type} {self.name} | ' + super().__str__()


class EnglishGrunt(Grunt):
    pass


class FrenchGrunt(Grunt):
    pass
