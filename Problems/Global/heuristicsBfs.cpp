/* Implementacion del algoritmo BFS para crear las PDB

Las PDB se guardan en un archivo que contiene un "state_map" de la api PSVN.
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
    
    // Obtener el estado inicial por stdin
    std::string input;
    std::string str = "";
    while (std::getline(std::cin, input)) {
        str = str + input + "\n";
    };

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

    free(str_state);
    // Algoritmo bfs
    list<pair<state_t*, int>> stack;
    stack.push_back(make_pair(state, 0));

    // state map donde se guardan los costos para cada estado.
    state_map_t *PDB = new_state_map(); 
    state_map_add(PDB, state, 0);
    int current_deep = 0;
    while (stack.size() > 0){        
        ruleid_iterator_t iter;
        int ruleid; 
        /* Extraer el nodo a expandir*/
        pair<state_t*, int> node =  stack.front();
        stack.pop_front();



        /* Comprobar si ya no ha sido expandido*/
        const int *d = state_map_get(PDB, node.first);
        if (*d < node.second){
            free(node.first);
            continue;
        }
        if (current_deep < node.second){
            printf("%d\n", current_deep);
            current_deep = node.second;
        }

        /* Expandir el nodo */
        init_bwd_iter( &iter, node.first );
        while ( (ruleid = next_ruleid( &iter )) >= 0){
            state_t* predecesor = (state_t*) malloc(sizeof(state_t));
            apply_bwd_rule( ruleid, node.first, predecesor );

            /*Guardar la distancia de los estados generados.
            No se guardan los nodos ya encontrados*/
            const int *old_predecesor = state_map_get( PDB, predecesor );
            if (old_predecesor==NULL){
                state_map_add( PDB, predecesor, node.second +1);
                stack.push_back(make_pair(predecesor, node.second+1));
            } else {
                free(predecesor);
            }
            
        }
        
        free(node.first);
        
        
    };

    FILE *file;
    if( argc >= 2 ) {     /* write the state map to a file */
        file = fopen( argv[ 1 ], "w" );
        if( file == NULL ) {
            fprintf( stderr, "could not open %s for writing\n", argv[ 1 ] );
            exit( -1 );
        }
        write_state_map( file, PDB );
        fclose( file );
    }

    return 0;
} 
