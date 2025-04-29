#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define PARENT( index ) ( index / 2 )
#define RIGHT( index ) ( 2 * index + 1 )
#define LEFT( index ) ( 2 * index )

void * myMalloc( int size );

typedef struct heap Heap;

struct heap {
    int * heap;
    int lenght;
    int size;
};

int main( ) {
    Heap * heap = ( Heap * )myMalloc( sizeof( Heap ) );
    heap->lenght = 0;
    heap->size = 100000;
    heap->heap = ( int * )myMalloc( sizeof( int ) * heap->size );
    
    
    
    return 0;
} 

void * myMalloc( int size ) {
    void * ptr = NULL;
    while ( ptr == NULL ) {
        ptr = malloc( size );
    }
    return ptr;
}
