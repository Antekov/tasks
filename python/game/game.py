'''
В игре существуют две фракции с различными непересекающимися наборами боевых
единиц (юнитов).
В начале игры игрок выбирает фракцию и далее набирает армию из доступных
боевых единиц.
Каждая боевая единица имеет свою стоимость.
У игрока в начале игры есть фиксированная сумма денег, на которую он может
покупать боевые единицы.
Противником игрока выступает компьютер, который на такую же сумму денег
покупает юниты для своей армии.
Игра состоит из набора ходов. В каждый ход игрок и компьютер выбирают вид
деятельности в этот ход.
Есть два возможных вида деятельности: бой и развитие.
Если хотя бы одна из сторон выбрала бой, то происходит сражение армий.
Если обе стороны выбрали развитие, то происходит восстановление и развитие
армий.
Игра заканчивается, когда после очередного сражения в армии одной из сторон
не осталось живых боевых единиц.

Для реализации игры создается объект класса Game

При старте игры создается конкретная фабрика (в зависимости от выбранной
фракции), которая по id юнита создает требуемый объект.
Все классы юнитов - наследники абстрактного класса Unit...
'''

from units import *


class Game:
    '''
    Класс игры
    '''
    initialMoney = 200
    unitTypes = [Archer, Knight, Grunt]
    minUnitPrice = min([unitType.price for unitType in unitTypes])
    turns = 0

    def __init__(self, fraction: str):
        '''
        Конструктор игры.
        fraction - название фракции.
        В зависимости от названия фракции создаются фабрики боевых единиц для
        игрока и компьютера
        (userUnitFactory, compUnitFactory), и через них создаются армии для
        обеих сторон.
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

    def takeUserChoice(self):
        money = self.userMoney
        unitTypes = []

        while money >= Game.minUnitPrice:
            print('Money:', money)
            print('Select unit type to buy:')
            print(f'1. Archer ({Archer.price})')
            print(f'2. Knight ({Knight.price})')
            print(f'3. Grunt ({Grunt.price})')
            typeNumber = int(input())
            if typeNumber in [1, 2, 3]:
                unitType = self.unitTypes[typeNumber - 1]
                unitTypes.append(unitType)
                money -= unitType.price
            else:
                print('Wrong type')

        return unitTypes

    def createUserArmy(self):
        '''
        Создание армии игрока.
        Пока у игрока не кончатся деньги, происходит покупка боевых единиц и
        добавление их в армию
        (Пока армия генерируется случайным образом, к третьему заданию будет
        добавлена полноценная функция покупки)
        '''
        unitTypes = self.takeUserChoice()

        self.userArmy = Squad(f'User\'s Army ({self.userFraction})')

        for unitType in unitTypes:
            power, defense = unitType.generateParams()
            self.userArmy.add(unitType(100, power, defense))
            self.userMoney -= unitType.price

        print(self.userArmy)

    def createCompArmy(self):
        '''
        Создание армии компьютера.
        Пока у компьютера не кончатся деньги, происходит покупка боевых единиц
        и добавление их в армию
        '''
        unitTypes = self.takeCompChoice()

        self.compArmy = Squad(f'Computer\'s Army ({self.compFraction})')

        for unitType in unitTypes:
            power, defense = unitType.generateParams()
            self.compArmy.add(unitType(100, power, defense))
            self.compMoney -= unitType.price

        print(self.compArmy)

    def takeCompChoice(self):
        money = self.compMoney
        unitTypes = []

        while money >= Game.minUnitPrice:
            unitType = self._generate_unit_type()
            unitTypes.append(unitType)
            money -= unitType.price

        return unitTypes

    def _generate_unit_type(self):
        '''
        Генерация случайного типа боевой единицы из доступных
        '''
        index = randint(0, len(Game.unitTypes)-1)
        return Game.unitTypes[index]

    def start(self):
        pass

    def isOver(self) -> bool:
        '''
        Проверка окончания игры. True - игра закончена
        '''
        return len(self.compArmy) == 0 or len(self.userArmy) == 0

    def fight(self):
        '''
        Реализация сражения армий двух сторон
        '''
        Game.turns += 1
        self.userArmy.attack(self.compArmy)

    def recover(self):
        Game.turns += 1
        self.userArmy.recover()
        self.compArmy.recover()

    def result(self):
        if len(self.compArmy) == 0:
            print('USER WINS!')
        elif len(self.userArmy) == 0:
            print('COMPUTER WINS!')
        else:
            print('Nobody has won yet')
