def check_right(s):
    n = len(s)
    count = 0

    while count < n:
        if (n + count) % 2 == 1:
            pos = (n + count) // 2
            i = 1
            is_palindrom = True
            while pos + i < n:
                if s[pos-i] != s[pos+i]:
                    is_palindrom = False
                    break
                i += 1
            if is_palindrom:
                break
        else:
            pos = (n + count) // 2 - 1
            i = 1
            is_palindrom = True
            while pos + i < n:
                if s[pos-(i-1)] != s[pos+i]:
                    is_palindrom = False
                    break
                i += 1
            if is_palindrom:
                break

        count += 1
    return count


s = input()

print(min(check_right(s), check_right(s[::-1])))
