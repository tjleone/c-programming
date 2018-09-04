import random

file = open('tests.txt', 'w')
file.write('12345 123456\n')
file.write('123456 12345\n')
file.write('12345 1234\n')
file.write('1234 12345\n')
for i in range(32):
    for j in range(32):
        file.write(f'{i:05b} {j:05b}\n')

file.close()
