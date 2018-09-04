file = open('tests.txt', 'w')
for i in range(32):
    for j in range(32):
        file.write(f'{i:05b} {j:05b}\n')
