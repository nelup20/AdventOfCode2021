
INPUT="./input1.txt"
previous=""
result=0

while IFS= read -r line
do
  line=$(echo "$line" | sed "s/^M//g")

  if [[ "$previous" == "" ]]
  then
    previous=$line
  else
    if (( line > previous ))
    then
      ((result+=1))
    fi
    previous=$line
  fi
done < $INPUT

echo "$result"
