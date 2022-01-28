
zeroes = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
ones = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
gamma_rate = ""
epsilon_rate = ""

with open("./input.txt") as file:
    for line in file:
        for i in range(len(zeroes)):
            if(line[i] == "0"):
                zeroes[i] += 1
            else:
                ones[i] += 1

for i in range(len(zeroes)):
    if(zeroes[i] > ones[i]):
        gamma_rate += "0"
        epsilon_rate += "1"
    else:
        gamma_rate += "1"
        epsilon_rate += "0"

print(int(gamma_rate, 2) * int(epsilon_rate, 2))