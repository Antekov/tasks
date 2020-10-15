import os
import os.path
import shutil

commands = ['ls', 'pwd', 'cd', 'cp', 'mv', 'rm', 'rmdir',
            'mkdir', 'run', 'exit']


def run_command(cmd):
    cmd_parts = cmd.split()
    command = cmd_parts[0]

    if command not in commands:
        print('Unknown command')
        return

    if command == 'ls':
        # Если текущий каталог - не корневой, то выводим каталоги '.' и '..'
        cur_dir = os.getcwd()
        if cur_dir.count('\\') > 1 or cur_dir.count('/') > 1:
            print('. <dir>  \t', end='')
            print('.. <dir> \t', end='')

        for name in os.listdir():
            print('{0} {1:<7}'.format(name, '<dir>'
                                      if os.path.isdir(name) else ''), end='')
        print()
    elif command == 'pwd':
        print(os.getcwd())
    elif command == 'cd':
        if len(cmd_parts) > 1:
            try:
                os.chdir(cmd_parts[1])
            except FileNotFoundError as e:
                print(e)
        else:
            print('Directory name is missing')
    elif command == 'cp':
        if len(cmd_parts) > 2:
            try:
                shutil.copy2(cmd_parts[1], cmd_parts[2])
            except FileNotFoundError as e:
                print(e)
        else:
            print('Source or destination name is missing')
    elif command == 'mv':
        if len(cmd_parts) > 2:
            try:
                shutil.copy2(cmd_parts[1], cmd_parts[2])
                os.remove(cmd_parts[1])
            except FileNotFoundError as e:
                print(e)
        else:
            print('Source or destination name is missing')
    elif command == 'rm':
        if len(cmd_parts) > 1:
            try:
                os.remove(cmd_parts[1])
            except FileNotFoundError as e:
                print(e)
        else:
            print('Directory name is missing')
    elif command == 'rmdir':
        if len(cmd_parts) > 1:
            try:
                os.rmdir(cmd_parts[1])
            except FileNotFoundError as e:
                print(e)
        else:
            print('Directory name is missing')
    elif command == 'mkdir':
        if len(cmd_parts) > 1:
            try:
                os.mkdir(cmd_parts[1])
            except FileNotFoundError as e:
                print(e)
        else:
            print('Directory name is missing')
    elif command == 'run':
        if len(cmd_parts) > 1:
            try:
                os.system(' '.join(cmd_parts[1:]))
            except FileNotFoundError as e:
                print(e)
        else:
            print('Command is missing')


while True:
    cmd = input('$ ')

    if cmd == 'exit':
        break

    if cmd.strip() == '':
        continue

    try:
        run_command(cmd)
    except Exception as e:
        print(e)
