import math

res = []
for f in dir(math):
    func = getattr(math, f)
    if callable(func):
        res.append(f)

print(res)
