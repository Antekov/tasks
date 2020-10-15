text_filename = 'input.txt'
cleaned_text_filename = 'output.txt'
words_filename = 'words.txt'
with open(text_filename, 'r', encoding="utf-8") as f:
    text = f.readlines()

words = []
with open(words_filename, 'r', encoding="utf-8") as f:
    for line in f.readlines():
        words += line.split()

import re
cleaned_text = []
pattern = re.compile(r'.*\W('+ '|'.join(words) +r')\W.*', re.IGNORECASE)

for line in text:
    res = pattern.match(line)
    if (res is not None):
        for regs in res.regs[1:]:
            line = line[:regs[0]] + '*'*(regs[1] - regs[0]) + line[regs[1]:]
    cleaned_text.append(line)

with open(cleaned_text_filename, 'w', encoding="utf-8") as f:
    f.writelines(cleaned_text)

print(*cleaned_text)