make 24puzzle.a
make 15puzzle.a
# se llama el .a con la ruta al archivo .abst y .pdb o .state_map, adicionalmente se puede redireccionar el input del estado pedido
./15puzzle.a ../Definitions/15puzzleAbstraction1.abst ../Definitions/15puzzleAbstraction1.pdb < ../Definitions/initState15.txt
./24puzzle.a ../Definitions/24puzzleAbstraction1.abst ../Definitions/24puzzleAbstraction1.pdb < ../Definitions/initState24.txt
