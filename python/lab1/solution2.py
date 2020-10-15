def pascal_triangle():
    row = 0
    col = -1
    d = {(0, 0): 1}

    while True:
        if col < row:
            col += 1
        else:
            row += 1
            col = 0
            dr = row - 2
            if dr >= 0:
                for c in range(0, dr + 1):
                    del(d[(dr, c)])
                    pass

        if row == 0:
            val = 1
        elif col == 0:
            val = d[(row - 1, col)]
        elif col == row:
            val = d[(row - 1, col - 1)]
        else:
            val = d[(row - 1, col - 1)] \
                    + d[(row - 1, col)]

        d[(row, col)] = val

        yield val
