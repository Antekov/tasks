def pascal_triangle():
    row = 0
    col = -1
    current_row = []
    prev_row = []

    while True:
        if col < row:
            col += 1
        else:
            row += 1
            prev_row = current_row
            current_row = []
            col = 0

        if row == 0:
            val = 1
        elif col == 0:
            val = prev_row[col]
        elif col == row:
            val = prev_row[col - 1]
        else:
            val = prev_row[col - 1] + prev_row[col]

        current_row.append(val)

        yield val
