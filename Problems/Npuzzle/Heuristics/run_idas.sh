make 24puzzle.ida
make 15puzzle.ida
#el .pdb debe estar en Definitions, en este caso 15puzzleAbstraction1.pdb
./15puzzle.ida ../Definitions/15puzzleAbstraction1 < ../Definitions/initState15.txt
./24puzzle.ida ../Definitions/24puzzleAbstraction1 < ../Definitions/initState24.txt

