
INPUT="./input.txt"
result=0
previous_sum=0
nums=()

sumArr () {
  echo $((nums[0] + nums[1] + nums[2]))
}

while IFS= read -r line
do
  line=$(echo "$line" | sed "s/^M//g")

  if (( ${#nums[@]} < 3 ))
  then
    nums+=("$line")
  else
    previous_sum=$(sumArr)

    nums=("${nums[@]:1}")
    nums+=("$line")

    if (( $(sumArr) > previous_sum ))
    then
      (( result+=1 ))
    fi
  fi
done < $INPUT

echo "$result"
