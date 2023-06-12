for j in 0 1
do
    for i in 12 14 17
    do
        timeout 15s stdbuf -oL ./prunning${j}TopSpin${i}Token.out < ../Definitions/GoalState${i}.txt > output_${i}Prunning${j}.txt
    done
done