
oxygen_gen_rating = ""
co2_scrub_rating = ""
count_zero = 0
count_one = 0

with open("./input.txt") as file:
    original_arr = file.readlines()

filtered_arr = original_arr

for i in range(12):
    if(len(filtered_arr) > 2):
        for line in filtered_arr:
            if (line[i] == "0"):
                count_zero += 1
            else:
                count_one += 1

        if (count_zero > count_one):
            oxygen_gen_rating += "0"
        else:
            oxygen_gen_rating += "1"

        filtered_arr = list(filter(lambda x: x.startswith(oxygen_gen_rating), filtered_arr))
        count_one = 0
        count_zero = 0
    else:
        if(filtered_arr[0][i] == "1"):
            oxygen_gen_rating = filtered_arr[0] + ""
        else:
            oxygen_gen_rating = filtered_arr[1] + ""
        break

filtered_arr = original_arr

# Too lazy to refactor right now...
for i in range(12):
    if(len(filtered_arr) > 2):
        for line in filtered_arr:
            if (line[i] == "0"):
                count_zero += 1
            else:
                count_one += 1

        if (count_zero > count_one):
            co2_scrub_rating += "1"
        else:
            co2_scrub_rating += "0"

        filtered_arr = list(filter(lambda x: x.startswith(co2_scrub_rating), filtered_arr))
        count_one = 0
        count_zero = 0
    else:
        if(filtered_arr[0][i] == "0"):
            co2_scrub_rating = filtered_arr[0] + ""
        else:
            co2_scrub_rating = filtered_arr[1] + ""
        break

print(int(oxygen_gen_rating, 2) * int(co2_scrub_rating, 2))
