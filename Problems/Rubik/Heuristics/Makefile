CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -lstdc++
PSVNOPT = --state_map --abstraction --backwards_moves --history_len=0
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

%.ida: %.c ${IMPLEMENTATION}/ida.c
	$(CC) $(OPT) ${IMPLEMENTATION}/ida.c -include $< -o $@

.PRECIOUS: %.c

%.out: %.c ${IMPLEMENTATION}/heuristicsBfs.cpp
	$(CXX) $(OPT) ${IMPLEMENTATION}/heuristicsBfs.cpp -include $< -o $@

.PHONY : clean
clean:
	rm -f  *.o 3x3Rubik*.c psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c 15puzzleAbstraction*.c 24puzzleAbstraction*.c 
