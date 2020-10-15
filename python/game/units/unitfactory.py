from abc import ABCMeta, abstractmethod, abstractproperty
from . import *


class UnitFactory():
    __metaclass__ = ABCMeta

    @abstractmethod
    def createArcher(self, health, power, defense, name=None):
        '''Создать лучника'''

    @abstractmethod
    def createKnight(self, health, power, defense, name=None):
        '''Создать рыцаря'''

    @abstractmethod
    def createGrunt(self, health, power, defense, name=None):
        '''Создать пехотинца'''


class EnglishUnitFactory(UnitFactory):
    def createArcher(self, health, power, defense, name=None):
        '''Создать английского лучника'''
        return EnglishArcher(health, power, defense, name)

    def createKnight(self, health, power, defense, name=None):
        '''Создать английского рыцаря'''
        return EnglishKnight(health, power, defense, name)

    def createGrunt(self, health, power, defense, name=None):
        '''Создать английского пехотинца'''
        return EnglishGrunt(health, power, defense, name)


class FrenchUnitFactory(UnitFactory):
    def createArcher(self, health, power, defense, name=None):
        '''Создать английского лучника'''
        return FrenchArcher(health, power, defense, name)

    def createKnight(self, health, power, defense, name=None):
        '''Создать английского рыцаря'''
        return FrenchKnight(health, power, defense, name)

    def createGrunt(self, health, power, defense, name=None):
        '''Создать английского пехотинца'''
        return FrenchGrunt(health, power, defense, name)
