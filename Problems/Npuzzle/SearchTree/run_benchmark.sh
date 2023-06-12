for j in 0 1
do
    for i in 15 24
    do
        timeout 15s stdbuf -oL ./prunning${j}${i}puzzle.out < ../Definitions/GoalState${i}.txt > output_${i}Prunning${j}.txt
    done
done
