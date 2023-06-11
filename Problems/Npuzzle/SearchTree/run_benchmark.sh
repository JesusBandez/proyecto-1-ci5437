for i in 15 24
do
    timeout 10s stdbuf -oL ./${i}puzzle.out < ../Definitions/GoalState${i}.txt > output_${i}.txt
done
