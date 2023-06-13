CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -lstdc++
PSVNOPT = --fwd_history_len=0 --bwd_history_len=0  --backwards_moves --state_map
PSVN = ../../../PSVN
IMPLEMENTATION = ../../Global

psvn2c_core.c:
	cp ${PSVN}/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ${PSVN}/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ${PSVN}/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: ../Definitions/%.psvn  psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	${PSVN}/psvn2c  $(PSVNOPT) --name=$(*F)  < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

%.c: %.psvn
	${PSVN}/psvn2c $(PSVNOPT) --name=$(*F)  < $< > $@

%.ida: %.c ${IMPLEMENTATION}/ida.cpp
	$(CC) $(OPT) ${IMPLEMENTATION}/ida.cpp -include $< -o $@

%.a: %.c ${IMPLEMENTATION}/a_star.cpp
	$(CXX) $(OPT) ${IMPLEMENTATION}/a_star.cpp -include $< -o $@
	
.PRECIOUS: %.c

%.out: %.c ${IMPLEMENTATION}/heuristicsBfs.cpp
	$(CXX) $(OPT) ${IMPLEMENTATION}/heuristicsBfs.cpp -include $< -o $@

.PHONY : clean
clean:
	rm -f  *.o psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c 15puzzleAbstraction*.c 24puzzleAbstraction*.c 
