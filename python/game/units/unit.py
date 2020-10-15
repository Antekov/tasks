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
