import sys, random

MIN_NUM = -100000
MAX_NUM = 100000

GENERATION_FILE = "matrix.txt"
N = 1000
PERSENTAGE = 60

n = N if len(sys.argv) == 1 else int(sys.argv[1])
m = n if len(sys.argv) <= 2 else int(sys.argv[2])
persentage = PERSENTAGE if len(sys.argv) <= 3 else float(sys.argv[3])

with open(GENERATION_FILE, 'w') as file:
    zeros_m1 = 0
    file.write(f"{n} {m}\n")
    for i in range(n):
        for j in range(m):
            is_zero = random.random() * 100 > persentage
            cur = 0 if is_zero else random.randint(MIN_NUM, MAX_NUM)
            zeros_m1+= 1 if is_zero else 0
            file.write(f"{cur} ")
        file.write("\n")

    zeros_m2 = 0
    file.write(f"{n} {m}\n")
    for i in range(n):
        for j in range(m):
            is_zero = random.random() * 100 > persentage
            cur = 0 if is_zero else random.randint(MIN_NUM, MAX_NUM)
            zeros_m2 += 1 if is_zero else 0
            file.write(f"{cur} ")
        file.write("\n")
print(f"M1: nonzeros/nums = {(n*m - zeros_m1) / (n*m) * 100}")
print(f"M2: nonzeros/nums = {(n*m - zeros_m2) / (n*m) * 100}")