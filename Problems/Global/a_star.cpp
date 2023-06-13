#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <iostream>
#include <queue>
#include <tuple>

using namespace std;
// struct que guarda la informacion de la abstraccion y la PDB
typedef struct {
    abstraction_t* abst;
    state_map_t* map;
} abstraction_data_t;

abstraction_data_t* abstraccion;
long nodos_expandidos;
long nodos_generados;

abstraction_data_t* leer_abstraccion(char* abs_filename, char* map_filename)
{
    abstraction_data_t* data;
    data = (abstraction_data_t*) malloc (sizeof(abstraction_data_t));

    /* get the abstraction filename by adding the extension ".abst" to the prefix */
    //char filename[1024];
    //strcpy(filename, prefix);
    //strcat(filename, ".abst");

    data->abst = read_abstraction_from_file( abs_filename );
    if( data->abst == NULL ) {
      fprintf( stderr, "no se pudo leer la abstraccion del archivo %s\n", abs_filename );
      return NULL;
    }
    /* get the pattern database filename by adding the extension ".state_map" to the prefix */
    //char map_filename[1024];
    //strcpy(map_filename, prefix);
    //strcat(map_filename, ".state_map");
    
    /* read the pattern database (state_map) */
    FILE* file = fopen( map_filename, "r" );
    if( file == NULL ) {
        fprintf( stderr, "could not open the pattern database file %s\n", map_filename);
        destroy_abstraction( data->abst );
        free( data );
        return NULL;
    }
    data->map = read_state_map( file );
    fclose( file );
    if( data->map == NULL ) {
        fprintf( stderr, "could not read the pattern database (state_map) %s\n", map_filename);
        destroy_abstraction( data->abst );
        free( data );
        return NULL;
    }
    return data;
}

void destruir_abstraccion(abstraction_data_t* data)
{
    destroy_abstraction(data->abst);
    destroy_state_map(data->map);
    free(data);
}

// retorna el valor del estado actual buscando en el mapa de estados, es decir, en la PDB
int buscar_valor_en_pdb(abstraction_data_t* abst, state_t* state)
{
    //printf("buscando valor en pdb \n");
    state_t abst_state;
    abstract_state( abst->abst, state, &abst_state );
    int *h;
    h = state_map_get( abst->map, &abst_state );
    //printf("valor encontrado en mapa de estados \n");
    //printf("valor encontrado: %d \n", *h);
    if (h == NULL) {
        return INT_MAX;
    }
    
    return *h;
}

struct CompareTuple {
    bool operator()(const pair<state_t*, int>& t1, const pair<state_t*, int>& t2) {
        return t1.second < t2.second;
    }
};

// best_first_search con heuristica admisible (A*)
int a_star(abstraction_data_t *abst, state_t state) {

  if (is_goal(&state)) { return 0; }
  ruleid_iterator_t iter; 
  int ruleid, current_depth;

  nodos_expandidos = 0;
  nodos_generados = 0;

  priority_queue<pair<state_t*, int>, vector<pair<state_t*, int>>, CompareTuple> pq;

  pq.push(make_pair(&state,0));
  current_depth = 0;
  while (!pq.empty()){

    
    pair<state_t*, int> node =  pq.top();
    pq.pop();
    
    state_t* ns = node.first;

    if (node.second < buscar_valor_en_pdb(abst, ns)) {
      
      current_depth = node.second;

      if (is_goal(ns)) {return current_depth;}

      init_fwd_iter(&iter, ns);
      while( (ruleid = next_ruleid(&iter)) >= 0 ) {
        state_t* successor = (state_t*) malloc(sizeof(state_t));
        apply_fwd_rule(ruleid, ns, successor);
          
        print_state(stdout, successor);
        printf("\n");
        pq.push(make_pair(successor,node.second+buscar_valor_en_pdb(abst, successor)));
        
        printf("cantidad de estados en cola de prioridad: %ld \n", pq.size());
        nodos_generados += 1;
      }
      nodos_expandidos += 1;
    }           
  }
  return current_depth;
}

int main(int argc, char **argv)
{
  state_t state;
  int cont, depth, total_depth;
  char line[ 4096 ];

  if( argc != 3 ) {
    printf("Deben haber 2 argumentos: la ruta al archivo.abst y la ruta al archivo .pdb (state_map).\n");
    return EXIT_FAILURE;
  } else {
    // leer los datos de la abstraccion y la PDB
    abstraccion = leer_abstraccion( argv[1], argv[2] );
    if (abstraccion == NULL) {
      printf("No se pudo leer la abstraccion y la PDB.\n");
      return EXIT_FAILURE;
    }
  }

  printf("\nIntroduzca el estado inicial del problema o enter para salir: ");
  if (fgets( line, 4096, stdin ) != NULL && read_state( line, &state ) > 0) {
      
    printf("\nestado inicial: ");
    print_state( stdout, &state );
    printf( "\n\n" );
    
    if (is_goal(&state)) {
      printf("El estado inicial es un estado objetivo.\n");
      return 0;
    }
    
    depth = a_star( abstraccion, state );

    if ( depth == 0 ) {
      printf("\nno se encontro solucion. nodos expandidos: %ld , nodos generados: %ld \n",
            nodos_expandidos, nodos_generados );
    } else {
      printf("\nse encontro una solucion. nodos expandidos: %ld , nodos generados: %ld , profundidad: %d \n",
            nodos_expandidos, nodos_generados , depth );
    } 
  }

  destruir_abstraccion(abstraccion);
  return 0;
}
