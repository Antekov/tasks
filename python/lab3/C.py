import sys
import traceback


def force_load(module):
    res = dict()

    with open(module + '.py', 'r') as module_file:
        lines = module_file.readlines()

        is_error = True
        count = 0
        while is_error and count < 3:
            ldict = {}
            is_error = False
            count += 1

            try:
                exec(''.join(lines), globals(), ldict)
            except Exception as e:
                is_error = True
                traceback.TracebackException()
                print(e.args)

        for m in ldict:
            if m[0] != '_':
                res[m] = ldict[m]
        return res

    return res


m = force_load('broken')

print(m)
