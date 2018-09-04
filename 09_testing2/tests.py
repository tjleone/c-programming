import random

def toFstr(n, base, size):
    s = toStr(n,base)
    if len(s) < size:
        s = '0' * (size - len(s)) + s
    return s

def toStr(n, base):
    n = int(n)
    convertString = "0123456789ABCDEF"
    if n < base:
        return convertString[n]
    else:
        return toStr(n/base, base) + convertString[n%base]
    
file = open('tests.txt', 'w')
file.write('12345 123456\n')
file.write('123456 12345\n')
file.write('12345 1234\n')
file.write('1234 12345\n')
file.write('12345\n')
file.write(' 12345\n')
file.write('\n')
file.write('12345\t12345\n')
file.write('\t \t\n')
file.write('12345 54321')
unprintable = ''
for i in range(5):
    unprintable += chr(i)
file.write(unprintable + ' 12345\n')
file.write(unprintable + '\n')

for i in range(27):
    for j in range(27):
        file.write(toFstr(i,3,4) + '0 ' + toFstr(j,3,4) + '0\n')
        
for i in range(32):
    for j in range(32):
        file.write(f'{i:05b} {j:05b}\n')

file.close()
