for j in 0 1
do
    timeout 3s stdbuf -oL ./prunning${j}3x3RubikCube.out < ../Definitions/GoalState.txt > output_Prunning${j}.txt
done
