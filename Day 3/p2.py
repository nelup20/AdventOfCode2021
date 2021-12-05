
import enum

class Type(enum.Enum):
    Oxygen = 0
    Co2 = 1

with open("./input.txt") as file:
    original_arr = file.readlines()

def findResultForType(inputArr, type):
    result = ""
    count_zero = 0
    count_one = 0

    for i in range(12):
        if (len(inputArr) > 2):
            for line in inputArr:
                if (line[i] == "0"):
                    count_zero += 1
                else:
                    count_one += 1

            if (count_zero > count_one):
                result += "0" if type == Type.Oxygen else "1"
            else:
                result += "1" if type == Type.Oxygen else "0"

            inputArr = list(filter(lambda x: x.startswith(result), inputArr))
            count_one = 0
            count_zero = 0
        else:
            if(type == Type.Oxygen):
                result = inputArr[0] if inputArr[0][i] == "1" else inputArr[1]
            else:
                result = inputArr[0] if inputArr[0][i] == "0" else inputArr[1]
            break

    return result

print(int(findResultForType(original_arr, Type.Oxygen), 2) * int(findResultForType(original_arr, Type.Co2), 2))