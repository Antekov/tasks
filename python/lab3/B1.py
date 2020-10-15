from app import VeryImportantClass, decorator


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
