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
    
    return 0;
} 
