/* Implementacion del algoritmo BFS

Usado para iniciar en el estado objetivo de un problema y avanzar infinitamente
generando todos los nodos que pueda. No importa si estan repetidos.

Cada vez que logra llegar a una nueva profundidad, la imprime.
*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <cstring>
#include <list>
#include <utility>

using namespace std;


int main( int argc, char **argv ){
    // Leer la string de la entrada estandar
    std::string input;
    std::string str = "";
    while (std::getline(std::cin, input)) {
        str = str + input + "\n";
    };

    // Convertir la string en el estado inicial
    char* str_state = new char[str.length()];
    strcpy(str_state, str.c_str());    

    state_t* state = (state_t*) malloc(sizeof(state_t));


    if (read_state( str_state, state ) <= 0) {
	    printf("Error: invalid state entered.\n");
	    return 0; 
    };
    printf("The state you entered is: ");
    print_state( stdout, state );
    printf("\n");

    

    // Algoritmo BFS.    
    list<pair<state_t*, int>> stack;
    stack.push_back(make_pair(state, 0));
    int current_deep = 0;
    unsigned long long int expanded_nodes = 0;
    //Poda de padres
    int hist, child_hist; 
    list<int> hist_stack;
    hist_stack.push_back(init_history);
    ////////////////

    while (stack.size() > 0){        
        ruleid_iterator_t iter; 
        int ruleid; 

        pair<state_t*, int> node = stack.front();

        //Poda de padres
        hist = hist_stack.front();
        ////////////////
        
        if (current_deep < node.second){  
            current_deep = node.second;
            printf(" deep: %d. Expanded nodes: %llu\n", current_deep, expanded_nodes);
        }
        
        init_fwd_iter( &iter, node.first );
        while ( (ruleid = next_ruleid( &iter )) >= 0){
            
            //Poda de padres
            if( fwd_rule_valid_for_history(hist, ruleid) == 0 ) continue;
            ////////////////

            state_t* child = (state_t*) malloc(sizeof(state_t));
            apply_fwd_rule( ruleid, node.first, child );            
            stack.push_back(make_pair(child, node.second+1));

            //Poda de padres
            child_hist = next_fwd_history(hist, ruleid);
            hist_stack.push_back(child_hist);
            ////////////////
        }
        
        stack.pop_front();
        free(node.first);

        //Poda de padres
        hist_stack.pop_front();
        ////////////////

        expanded_nodes++;
    };

    return 0;
} 
