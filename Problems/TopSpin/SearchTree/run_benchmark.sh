for i in 12 14 17
do
    timeout 10s stdbuf -oL ./TopSpin${i}Token.out < ../Definitions/GoalState${i}.txt > output_${i}.txt
done