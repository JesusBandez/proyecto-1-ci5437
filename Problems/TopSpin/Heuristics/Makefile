CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -lstdc++
PSVNOPT = --state_map --backwards_moves --history_len=0
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
	$(CXX) $(OPT) ${IMPLEMENTATION}/ida.cpp -include $< -o $@

%.a: %.c ${IMPLEMENTATION}/priority_queue.hpp ${IMPLEMENTATION}/a.cpp
	$(CXX) $(OPT) ${IMPLEMENTATION}/priority_queue.hpp ${IMPLEMENTATION}/a.cpp -include $< -o $@

.PRECIOUS: %.c

%.out: %.c ${IMPLEMENTATION}/heuristicsBfs.cpp
	$(CXX) $(OPT) ${IMPLEMENTATION}/heuristicsBfs.cpp -include $< -o $@

.PHONY : clean
clean:
	rm -f  *.o psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c TopSpin*.c priority_queue.hpp
