for j in 0 1
do
    for i in 12 14 18
    do
        timeout 15s stdbuf -oL ./prunning${j}HanoiTower${i}Disk.out < ../Definitions/GoalState${i}.txt > output_${i}Prunning${j}.txt
    done
done