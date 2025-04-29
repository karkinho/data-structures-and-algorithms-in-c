#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define SWAP( val1 , val2 , temp ) temp = val1; val1 = val2; val2 = temp;

void QuickSort( int * array , int start , int end );
void PrintArray( int * array , int size );
void Fill( int * array , int size );

int main( int argc , char const *argv[] ) {
    if( argc != 2 ) exit(0);
    int size = 0; 
    sscanf( argv[1] , "%d" , &size );
    srand(time(NULL));
    int *array = ( int * )malloc( sizeof( int ) *size ); 
    clock_t start , end;
    double cpuTimeUsed;
    if ( array == NULL ) exit(0);
    Fill( array , size );
    start = clock();
    QuickSort( array , 0 , size - 1 );
    end = clock();
    PrintArray( array , size );
    cpuTimeUsed = (( double ) ( end - start )) / CLOCKS_PER_SEC;
    printf( "Tempo em Segundos: %lf\n" , cpuTimeUsed );
    free( array );
    array = NULL;
    return 0;
}

void Fill( int * array , int size ) {
    for ( int i = 0 ; i < size ; i++ ) {
        array[i] = rand() % INT_MAX;
    }
}

void PrintArray( int * array , int size ) {
    for ( int i = 0 ; i < size ; i++ ) {
        printf( "%d, ", array[i] );
    }
    printf( "\n" );
}

void QuickSort( int * array , int start , int end ) {
    if( start >= end ) {
        return;
    }
    int newPivot, pivot = array[end], lowDivider = start - 1, highDivider = start , temp;

    while( highDivider < end ) {
        if( array[highDivider] <= pivot ) {
            lowDivider++;
            SWAP( array[lowDivider] , array[highDivider] , temp )   
        }
        highDivider++;
    }
    lowDivider++;
    SWAP( array[end] , array[lowDivider] , temp )
    newPivot = lowDivider;
    QuickSort( array , start , newPivot - 1 );
    QuickSort( array , newPivot + 1 , end );
}


