# from app import VeryImportantClass, decorator


class VeryImportantClass:
    def __init__(self):
        self.a = 10
        self.b = 20
        self.s = {1, 2, 3}

    def f1(self, n):
        return self.a + n

    def f2(self, lst=[]):
        return self.s | lst


def decorator(func):
    def wrapped(self, *args, **kwargs):
        print(f'Called {func.__name__}')
        print(self, args)
        res = func(self, *args, **kwargs)
        print(f'{func.__name__} done')
        return res

    return wrapped


class HackedClass(VeryImportantClass):
    def set_hc_value(self, name, value):
        exec(f'self._hc_{name} = value')

    def __init__(self):
        super().__init__()
        methods = [name for name in dir(self) if name[0] != '_']
        # print(methods)
        for method in methods:
            if method == 'set_hc_value':
                continue

            is_function = eval(f'callable(self.{method})')
            if is_function:
                exec(f'self.{method} = decorator(self.{method})')
            else:
                is_container = eval(f'hasattr(self.{method}, ' +
                                    '\'__contains__\')')
                # print(method, is_container)
                if is_container:
                    method_type = eval(f'str(type(self.{method}))' +
                                       '.split("\'")[1]')
                    exec(f'self._hc_{method} = self.{method}')
                    exec(f'HackedClass.{method} = property(lambda self: ' +
                         f'{method_type}(), lambda self, x: ' +
                         f'self.set_hc_value(\'{method}\', x))')
                else:
                    is_number = eval(f'hasattr(self.{method}, ' +
                                     '\'__mul__\')')
                    if is_number:
                        exec(f'self._hc_{method} = self.{method}')
                        exec(f'HackedClass.{method} = property(lambda self: ' +
                             f'self._hc_{method}*2, lambda self, x: ' +
                             f'self.set_hc_value(\'{method}\', x))')



v = HackedClass()

print(v.f1(10))

print(v.f2({9, 8, 7}))

print(dir(v))

print(v._hc_s)

v.s |= {4, 5}

print(v._hc_s, v.s)

print(v._hc_a, v.a)
v.a = 100
print(v._hc_a, v.a)
