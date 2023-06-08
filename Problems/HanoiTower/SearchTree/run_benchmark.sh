for i in 12 14 18
do
    timeout 10s stdbuf -oL ./HanoiTower${i}Disk.out < ../Definitions/GoalState${i}.txt > output_${i}.txt
done