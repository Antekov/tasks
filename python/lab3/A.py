import sys


class ExtendedList(list):
    def _first_getter(self):
        return self[0]

    def _first_setter(self, val):
        self[0] = val

    def _last_getter(self):
        return self[-1]

    def _last_setter(self, val):
        self[-1] = val

    def _size_getter(self):
        return len(self)

    def _size_setter(self, val):
        # print('Set size', val, self[:val])
        n = len(self)
        self[::] = self[:val]

        if val > n:
            self[::] = self + [None]*(val - n)

    def _reversed_getter(self):
        return self[::-1]

    first = property(_first_getter, _first_setter)
    last = property(_last_getter, _last_setter)
    size = property(_size_getter, _size_setter)
    reversed = property(_reversed_getter)

    F = first
    L = last
    S = size
    R = reversed

    def __init__(self, lst):
        super().__init__(lst)


'''
lst = ExtendedList([0, 2, None, None])
print(lst.reversed)
print(lst.first)
lst.F = 0
print(lst)
lst.append(4)
print(lst.L)
lst.size = 2
print(lst)
lst.size = 4
print(lst)
'''

exec(sys.stdin.read())
