/* This program reads a state from stdin and prints out its successors.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
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
    
    std::string input;
    std::string str = "";
    while (std::getline(std::cin, input)) {
        str = str + input + "\n";
    };

    char* str_state = new char[str.length()];
    strcpy(str_state, str.c_str());
    

    state_t* state = (state_t*) malloc(sizeof(state_t));

// CONVERT THE STRING TO A STATE    
    if (read_state( str_state, state ) <= 0) {
	    printf("Error: invalid state entered.\n");
	    return 0; 
    };
    printf("The state you entered is: ");
    print_state( stdout, state );
    printf("\n");

    list<pair<state_t*, int>> stack;
    stack.push_back(make_pair(state, 0));
    
    while (stack.size() > 0){        
        ruleid_iterator_t iter; 
        int ruleid; 
        pair<state_t*, int> node =  stack.front();
        
        print_state( stdout, node.first );
        printf(" deep: %d\n", node.second);
        
        init_fwd_iter( &iter, node.first );
        while ( (ruleid = next_ruleid( &iter )) >= 0){
            state_t* child = (state_t*) malloc(sizeof(state_t));
            apply_fwd_rule( ruleid, node.first, child );
            stack.push_back(make_pair(child, node.second+1));
        }
        
        stack.pop_front();
        free(node.first);
    };

    return 0;
} 
