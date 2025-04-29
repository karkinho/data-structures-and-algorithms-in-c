#include "lib.h"

void * MyMalloc( void * ptr , int size ) {
    do {
        ptr = realloc( ptr , size );
    } while ( ptr == NULL );
    return ptr;
}

void Debug( char * msg ) {
    #ifdef DEBUG
        printf( "DEBUG: %s\n", msg );
    #endif
    return;
}