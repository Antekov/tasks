'''
В игре существуют две фракции с различными непересекающимися наборами
боевая единица (юнитов). В начале игры игрок выбирает фракцию, и далее набирает армию
из доступных боевых единиц. Каждая боевая единица имеет свою стоимость.
У игрока в начале игры есть фиксированная сумма денег, на которую он может покупать
боевые единицы.
Противником игрока выступает копмпьютер, который на такую же сумму денег покупает 
юниты для своей армии.
Игра состоит из набора ходов. В каждый ход игрок и компьютер выбирают вид деятельности 
в этот ход. 
Есть два возможных вида деятельности: бой и развитие.
Если хотя бы одина из сторон выбрала бой, то происходит сражение армий.
Если обе стороны выбрали развитие, то происходит восстановление и развитие армий.
Игра заканчивается, когда после очередного сражения в армии одной из сторон не осталось
живых боевых единиц.

Для реализации игры создается объект класса Game

При старте игры создается конкретная фабрика (в зависимости от выбранной
фракции), которая по id юнита создает требуемый объект.
Все классы юнитов - наследники абстрактного класса Unit...
'''


from abc import ABCMeta, abstractmethod, abstractproperty
from random import randint

class Unit:
    def __init__(self, health, power, defense):
        self.health = health
        self.power = power
        self.defense = defense

    def __str__(self):
        return f'health: {self.health}, power: {self.power}, ' + \
               f'defense: {self.defense}'

    def recover(self):
        if self.health < 100:
            self.health += 2

        if self.health > 100:
            self.health = 100

    def attack(self, enemy):
        damage = max(0, self.power - self.defense)
        print(f'{self.name} ({self.health}) -> {enemy.name} ({enemy.health})'
              f' : {damage} ({enemy.health - damage})')

        enemy.health -= damage
        if enemy.health < 0:
            enemy.health = 0


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


class EnglishArcher(Archer):
    pass


class FrenchArcher(Archer):
    pass


class EnglishKnight(Knight):
    pass


class FrenchKnight(Knight):
    pass


class EnglishGrunt(Grunt):
    pass


class FrenchGrunt(Grunt):
    pass


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


class Squad:
    '''Армия (отряд) боевых единиц.
    Реализует паттерн "Структура": каждый отряд может состоять из
    боевых единиц и/или из других отрядов
    '''
    def __init__(self, name=''):
        self.units = []
        self.name = name

    def add(self, unit):
        self.units.append(unit)

    def remove(self, unit):
        self.units.remove(unit)

    def all(self):
        '''Получение списка всех боевых единиц, входящих в данный отряд и его
        дочерние отряды'''
        units = []
        for unit in self.units:
            if isinstance(unit, Squad):
                units += unit.all()
            else:
                units.append(unit)
        return units

    def attack(self, enemy):
        '''Метод сражения двух армии с другой армией.
        Вначале каждый юнит первой армии случайно выбирает себе одного
        противника из другой армии и атакует его.
        Затем каждый юнит другой армии случайно выбирает себе одного
        противника из первой армии и атакует его.

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
        'Метод удаления погибших юнитов (у которых здоровье <= 0)'
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
        '''Метод восстановления армии.
        Для каждого юнита вызывается метод восстановления
        '''
        for unit in self.units:
            unit.recover()


class Game:
    '''Класс игры'''
    initialMoney = 200
    unitTypes = [Archer, Knight, Grunt]
    turns = 0

    def __init__(self, fraction: str):
        '''Конструктор игры.
        fraction - название фракции.
        В зависимости от названия фракции создаются фабрики боевых единиц 
        для игрока и компьютера (userUnitFactory, compUnitFactory) и через них 
        создаются армии для обоих сторон.
        '''
        self.userMoney = Game.initialMoney
        self.compMoney = Game.initialMoney

        if fraction == 'English':
            self.userFraction = fraction
            self.compFraction = 'French'
            self.userUnitFactory = EnglishUnitFactory()
            self.compUnitFactory = FrenchUnitFactory()
        else:
            self.userFraction = 'French'
            self.compFraction = 'English'
            self.userUnitFactory = FrenchUnitFactory()
            self.compUnitFactory = EnglishUnitFactory()

        self.createUserArmy()
        self.createCompArmy()
        pass

    def createUserArmy(self):
        '''
        Создание армии игрока.
        Пока у игрока не кончатся деньги, происходит покупка боевых единиц и 
        добавление их в армию
        '''
        self.userArmy = Squad(f'User\'s Army ({self.userFraction})')
        while self.userMoney > 10:
            # print('Money:', self.userMoney)
            unitType = self._generate_unit_type()
            # print(f'Buy {unitType} ({unitType.price})')
            power, defense = unitType.generateParams()
            self.userArmy.add(unitType(100, power, defense))
            self.userMoney -= unitType.price

        print(self.userArmy)
        pass

    def createCompArmy(self):
        '''
        Создание армии игрока.
        Пока у игрока не кончатся деньги, происходит покупка боевых единиц и 
        добавление их в армию
        '''
        self.compArmy = Squad(f'Computer\'s Army ({self.compFraction})')

        while self.compMoney > 10:
            # print('Money:', self.compMoney)
            unitType = self._generate_unit_type()
            # print(f'Buy {unitType} ({unitType.price})')
            power, defense = unitType.generateParams()
            self.compArmy.add(unitType(100, power, defense))
            self.compMoney -= unitType.price

        print(self.compArmy)

    def _generate_unit_type(self):
        'Генерация случайного типа боевой единицы из доступных'
        index = randint(0, len(Game.unitTypes)-1)
        return Game.unitTypes[index]

    def start(self):
        pass

    def isOver(self) -> bool:
        'Проверка окончания игры. True - игра закончена'
        return len(self.compArmy) == 0 or len(self.userArmy) == 0

    def fight(self):
        'Реализация сражения армий двух сторон'
        Game.turns += 1
        self.userArmy.attack(self.compArmy)

    def recover(self):
        Game.turns += 1
        self.userArmy.recover()
        self.compArmy.recover()

    def result(self):
        if len(self.compArmy) == 0:
            print('USER WIN!')
        elif len(self.userArmy) == 0:
            print('COMP WIN!')
        else:
            print('No wins yet')


game = Game('English')

while not game.isOver():
    action = int(input('Action (1 - Attack, 2 - Marsh): '))

    if action == 1:
        game.fight()
    elif action == 2:
        compAction = randint(1, 2)
        if compAction == 1:
            game.fight()
        else:
            game.recover()

game.result()
