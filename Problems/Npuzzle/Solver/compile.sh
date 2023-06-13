cd ../Heuristics

./compile.sh
make 24puzzle.ida
mv ./24puzzle.ida ../Solver

make 15puzzle.ida
mv ./15puzzle.ida ../Solver

make 24puzzle.a
mv ./24puzzle.a ../Solver

make 15puzzle.a
mv ./15puzzle.a ../Solver