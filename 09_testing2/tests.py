import random

file = open('tests.txt', 'w')
for i in range(32):
    for j in range(32):
        file.write(f'{i:05b} {j:05b}\n')

for i in range(64):
    hand1, hand2 = '', ''
    for j in range(5):
        hand1 += chr(random.randrange(256))
        hand2 += chr(random.randrange(256))
    file.write(hand1 + ' ' + hand2 + '\n')

file.close()
