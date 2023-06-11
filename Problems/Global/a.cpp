#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

#include "priority_queue.hpp"


/* GLOBAL VARIABLES */
long nodos_expandidos ;   
long nodos_generados ;
long profundidad = INT64_MAX;

typedef struct {
    abstraction_t* abst;
    state_map_t* map;
} abstraction_data_t;

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
int buscar_valor_en_pdb(const abstraction_data_t* abst, const state_t* state)
{
    state_t abst_state;
    abstract_state( abst->abst, state, &abst_state );
    int *h;
    h = state_map_get( abst->map, &abst_state );
    if (h == NULL) {
        return INT_MAX;
    }
    return *h;
}

int heuristica(){
  return 0;
}

// best_first_search con heuristica admisible (A*)
int a_star(const abstraction_data_t *abst, state_t *state) {

  state_t child;
  ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
  int ruleid, childCount;

  nodos_expandidos = 0;
  nodos_generados = 0;

  // estado objetivo
  if (is_goal(state)) { return 0; }

  //int PriorityQueue<T>::Add(int f, int g, const T& data)
  // f valor heuristica
  // g costo del camino o distancia
  // data estado
  PriorityQueue<state_t> q; // ordered by f-value
  //set_color(init(), Gray);
  //set_distance(init(), 0);

  // se agrega el estado a la cola de prioridad
  q.Add(buscar_valor_en_pdb(abst, state), 0, *state);  
  while (!q.Empty()) {

    state_t ns = q.Top();
    q.Pop();

    state_t n = q.Top();
    if (q.CurrentPriority() < buscar_valor_en_pdb(abst,ns)) {
      
      q.Modify(buscar_valor_en_pdb(abst,ns), q.CurrentPriority(), ns);
      solucion = buscar_valor_en_pdb(abst,ns);
      nodos_expandidos  += 1;
      if (is_goal(q.Top())) {
        return ns;
      }

      // se agregan todos los hijos del estado a la cola de prioridad
      init_fwd_iter(&iter, &ns);  // initialize the child iterator 
      while( (ruleid = next_ruleid(&iter)) >= 0 ) {
        apply_fwd_rule(ruleid, &ns, &child);
        ++childCount;
        
        //printf("child %d. ",childCount);
        
        print_state(stdout, &child);

        if (is_goal(&child)) {
          return buscar_valor_en_pdb(abst, &child);
        }
        q.Add(buscar_valor_en_pdb(abst, &child), q.CurrentPriority(), child);
        //printf("  %s (cost %d), goal=%d\n", get_fwd_rule_label(ruleid), get_fwd_rule_cost(ruleid), is_goal(&child));
        nodos_generados += 1;
      }
      if (childCount == 0) {
        printf("no children\n");
      }

    }
    profundidad = q.CurrentPriority();
  }
  return profundidad;
}

int main(int argc, char **argv)
{
  state_t state;
  int cont, depth, total_depth;
  abstraction_data_t* abst;
  char line[ 4096 ];

  if( argc != 3 ) {
    printf("Deben haber 2 argumentos: la ruta al archivo.abst y la ruta al archivo .pdb (state_map).\n");
    return EXIT_FAILURE;
  } else {
    // leer los datos de la abstraccion y la PDB
    abst = leer_abstraccion( argv[1], argv[2] );
    if (abst == NULL) {
      printf("No se pudo leer la abstraccion y la PDB.\n");
      return EXIT_FAILURE;
    }
  }

  printf("Introduzca el estado inicial del problema o enter para salir: ");
  for( cont = 0; fgets( line, 4096, stdin ) != NULL && read_state( line, &state ) > 0; ++cont ) {
      
    printf( "problem %d: ", cont + 1 );
    print_state( stdout, &state );
    printf( "\n" );
    
    depth = a_star( abst, &state );

    if ( profundidad == INT64_MAX ) {
      printf( "no se encontro solucion. nodos expandidos: %ld , nodos generados: %ld \n",
            nodos_expandidos, nodos_generados );
    } else {
      printf( "se encontro una solucion. nodos expandidos: %ld , nodos generados: %ld \n",
            nodos_expandidos, nodos_generados );
    } 
    printf("Introduzca el estado inicial del problema o enter para salir: ");
  }

  destruir_abstraccion(abst);
  return 0;
}
