/* if HAVE_FWD_MOVE_PRUNING is defined then does move pruning. If not, it does parent pruning. */

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>
#include <list>


#define myMAX(x,y) (((x)>(y))?(x):(y))
#define myMIN(x,y) (((x)<(y))?(x):(y))

typedef struct {
    abstraction_t* abst;
    state_map_t* map;
} abstraction_data_t;

/* GLOBAL VARIABLES */
int64_t nodes_expanded_for_bound ;    // number of nodes expanded for a given cost bound
int64_t nodes_generated_for_bound ;   // number of nodes generated for a given cost bound
int64_t nodes_expanded_for_startstate ;   // number of nodes expanded until solution found for a given start state
int64_t nodes_generated_for_startstate ;  // number of nodes generated until solution found for a given start state
int best_soln_sofar = INT_MAX;


abstraction_data_t* read_abstraction_data(char* prefix)
{
    abstraction_data_t* data;
    data = (abstraction_data_t*) malloc (sizeof(abstraction_data_t));

    /* get the abstraction filename by adding the extension ".abst" to the prefix */
    char filename[2048];
    strcpy(filename, prefix);
    strcat(filename, ".abst");

    data->abst = read_abstraction_from_file( filename );
    if( data->abst == NULL ) {
        fprintf( stderr, "could not read the abstraction file %s\n", filename );
        return NULL;
    }
    /* get the pattern database filename by adding the extension ".state_map" to the prefix */
    char map_filename[2048];
    strcpy(map_filename, prefix);
    strcat(map_filename, ".pdb");
    
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

void destroy_abstraction_data(abstraction_data_t** data, int argc)
{
    for (int i=0; i<argc-1; i++){
        destroy_abstraction(data[i]->abst);
        destroy_state_map(data[i]->map);
        free(data[i]);
    };

}

int abstraction_data_lookup(const abstraction_data_t** absts, 
                            const state_t* state,
                            int argc)
{
    int foo = 0;
    int* current_best_h = &foo;
    for (int i=1; i<argc; i++){
        state_t abst_state;
        abstract_state( absts[i-1]->abst, state, &abst_state );
        int *h;
        h = state_map_get( absts[i-1]->map, &abst_state );
        if (h != NULL and *h > *current_best_h) {
            current_best_h = h;
        };
    };

    if (*current_best_h == 0){
        return INT_MAX;
    } else {
        return *current_best_h;
    }    
}

int dfs_heur( const abstraction_data_t **absts,
              state_t *state,
#ifdef HAVE_FWD_MOVE_PRUNING
              const int history,           // for move pruning
#else
              const state_t *parent_state, // for parent pruning
#endif
              const int bound, int *next_bound, int current_g, int argc )
{
    int ruleid;
#ifdef HAVE_FWD_MOVE_PRUNING
    int c_history;
#endif
    ruleid_iterator_t iter;
    state_t child;

    nodes_expanded_for_bound++;

    init_fwd_iter( &iter, state );
    while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {

#ifdef HAVE_FWD_MOVE_PRUNING
        if( !fwd_rule_valid_for_history( history, ruleid ) )
            continue;
        c_history = next_fwd_history( history, ruleid );
#endif

        apply_fwd_rule( ruleid, state, &child );
        nodes_generated_for_bound++;

#ifndef HAVE_FWD_MOVE_PRUNING
        if( compare_states( &child, parent_state ) == 0 )   // parent pruning
            continue;
#endif

        const int move_cost = get_fwd_rule_cost( ruleid );
                
        if (is_goal(&child)) {
            best_soln_sofar = myMIN(best_soln_sofar, current_g + move_cost);
            if (best_soln_sofar <= bound) {
               return 1;
            } else {
               continue;
            }
        } else {
            int child_h = abstraction_data_lookup( absts, &child, argc );
            if (current_g + move_cost + child_h > bound) {
               *next_bound = myMIN( *next_bound, current_g + move_cost + child_h );
            } else {
               if( dfs_heur( absts, &child,
        #ifdef HAVE_FWD_MOVE_PRUNING
                             c_history,  // move pruning
        #else
                             state,      // parent pruning
        #endif
                             bound, next_bound, current_g + move_cost, argc ) ) 
               {
                   return 1;
                }
            }
        }
    }
    assert( *next_bound > bound );
    return 0;
}



int idastar( const abstraction_data_t **absts, state_t *state, int argc )
{
    int next_bound, bound, done;

    nodes_expanded_for_startstate  = 0;
    nodes_generated_for_startstate = 0;

    if (is_goal(state)) { return 0; }

    best_soln_sofar = INT_MAX;
    bound = abstraction_data_lookup( absts, state, argc ); // initial bound = h(start)
    while (1) {
        next_bound = INT_MAX;
        nodes_expanded_for_bound  = 0;
        nodes_generated_for_bound = 0;
        done = dfs_heur( absts, state,
#ifdef HAVE_FWD_MOVE_PRUNING
                             init_history,  // move pruning
#else
                             state,         // parent pruning
#endif
                             bound, &next_bound, 0, argc );
        printf( "bound: %d, expanded: %" PRId64 ", generated: %" PRId64 "\n", bound, nodes_expanded_for_bound, nodes_generated_for_bound );
        nodes_expanded_for_startstate  += nodes_expanded_for_bound;
        nodes_generated_for_startstate += nodes_generated_for_bound;
        if( done ) {
            break;
        }
        assert( next_bound > bound );
        bound = next_bound;
        if ( best_soln_sofar <= bound ) { // will always be true if bound == INT_MAX
            break;
        }
    }
        
    return best_soln_sofar;
}



int main( int argc, char **argv )
{
    state_t state;
    int64_t total_expanded;  // the total number of nodes expanded over all the start states
    int64_t total_generated; // the total number of nodes generated over all the start states
    int trials, d, total_d;
    const abstraction_data_t* absts[argc-1];

    char line[ 8192 ];
    struct timeval start, end, total;
    total.tv_sec = 0;
    total.tv_usec = 0;

    
    if( argc < 2 ) {
        printf("There must 1 command line argument, the prefix of the abstraction and pattern database to use.\n");
        return EXIT_FAILURE;
    } else {
        /* read the abstraction and pattern database (state_map) */
        for (int i=1; i<argc; i++){
            absts[i-1] = read_abstraction_data( argv[i] );
            if (absts[i-1] == NULL) {
                return EXIT_FAILURE;
            }
        }

    }

    total_d = 0;
    total_expanded = 0;
    total_generated = 0;
    printf("Enter a start state (empty input line to quit): ");
    for( trials = 0;
         fgets( line, 8192, stdin ) != NULL
             && read_state( line, &state ) > 0;
         ++trials ) {
        
        
        print_state( stdout, &state );
        printf( "\n" );
        gettimeofday( &start, NULL );

        d = idastar( absts, &state, argc );
                
        gettimeofday( &end, NULL );
        end.tv_sec -= start.tv_sec;
        end.tv_usec -= start.tv_usec;
        if( end.tv_usec < 0 ) {
            end.tv_usec += 1000000;
            --end.tv_sec;
        }
                
        if (end.tv_usec + total.tv_usec >= 1000000) {
            total.tv_usec = end.tv_usec + total.tv_usec - 1000000;
            total.tv_sec = total.tv_sec + 1;                
        } else {
            total.tv_usec = end.tv_usec + total.tv_usec;
        }
        total.tv_sec = total.tv_sec + end.tv_sec;

        if ( d == INT_MAX ) {
            printf( "no solution found. expanded nodes: %" PRId64 ", generated nodes: %" PRId64 "\n",
		      nodes_expanded_for_startstate, nodes_generated_for_startstate );
        } else {
            printf( "solved. solution cost: %d, expanded nodes: %" PRId64 ", generated nodes: %" PRId64 "\n",
		      d, nodes_expanded_for_startstate, nodes_generated_for_startstate );
        } 
        total_d += d;
        total_expanded  += nodes_expanded_for_startstate;
        total_generated += nodes_generated_for_startstate;

        
    }

    
    printf( "\ntotal: depth: %d, expansion: %" PRId64 ", generation: %" PRId64 ", %zd.%06zd seconds\n",
            total_d, total_expanded, total_generated, total.tv_sec, total.tv_usec );

    
    return EXIT_SUCCESS;
}
