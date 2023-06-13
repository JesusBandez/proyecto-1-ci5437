#el .pdb debe estar en Definitions, en este caso 15puzzleAbstraction1.pdb
#./15puzzle.ida ../Definitions/15puzzleAbstraction1 < ../Definitions/initState15.txt
#./24puzzle.ida ../Definitions/24puzzleAbstraction1 < ../Definitions/initState24.txt


echo ">>>>>>>>>> 15"
time ./15puzzle.ida ../Definitions/15puzzleAbstraction1 ../Definitions/15puzzleAbstraction2 < ./Benchmark/15puzzleBench.txt
echo ""


echo ">>>>>>>>>> 24"
time ./24puzzle.ida ../Definitions/24puzzleAbstraction1 ../Definitions/24puzzleAbstraction2 ../Definitions/24puzzleAbstraction3 ../Definitions/24puzzleAbstraction4 ../Definitions/24puzzleAbstraction5 < ./Benchmark/24puzzleBench.txt
echo ""