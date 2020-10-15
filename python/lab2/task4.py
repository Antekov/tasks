password = input()

is_strong = True

if len(password) < 8:
    is_strong = False
elif len(set(password)) < 4:
    is_strong = False
elif password.lower().find('anna') != -1:
    is_strong = False
elif password == password.lower() or password == password.upper():
    is_strong = False
elif len(set(password) & set('0123456789')) == 0:
    is_strong = False

if is_strong:
    print('strong')
else:
    print('weak')
