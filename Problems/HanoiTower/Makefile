CC = gcc
CXX = g++
OPT = -g -Wall -O3 -Wno-unused-function -Wno-unused-variable -lstdc++
PSVNOPT = --no_state_map --no_abstraction --no_backwards_moves --history_len=0
PSVN = ../../PSVN
IMPLEMENTATION = ../Global

psvn2c_core.c:
	cp ${PSVN}/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ${PSVN}/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ${PSVN}/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn  psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	${PSVN}/psvn2c  $(PSVNOPT) --name=$(*F)  < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ${IMPLEMENTATION}/succ.cpp
	$(CXX) $(OPT) ${IMPLEMENTATION}/succ.cpp -include $< -o $@

.PHONY : clean
clean:
	rm -f *.succ *.o sliding_tile1x3.c psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
