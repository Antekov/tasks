class pascal_triangle():
    def __init__(self):
        self.row = 0
        self.col = -1
        self.d = {(0, 0): 1}

    def __next__(self):
        if self.col < self.row:
            self.col += 1
        else:
            self.row += 1
            self.col = 0
            dr = self.row - 2
            if dr >= 0:
                for c in range(0, dr + 1):
                    del(self.d[(dr, c)])
                    pass

        if self.row == 0:
            val = 1
        elif self.col == 0:
            val = self.d[(self.row - 1, self.col)]
        elif self.col == self.row:
            val = self.d[(self.row - 1, self.col - 1)]
        else:
            val = self.d[(self.row - 1, self.col - 1)] \
                 + self.d[(self.row - 1, self.col)]

        self.d[(self.row, self.col)] = val

        return val
