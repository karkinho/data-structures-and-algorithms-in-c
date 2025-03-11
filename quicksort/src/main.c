#include "lib.h"

int * CreateUnsortedArray( int size );
void Quicksort( int * array , int left , int right );

int main( ) {
    int size = 20000;
    int * array = CreateUnsortedArray( size );

    for ( int i = 0 ; i < size ; i++ ) {
        printf( "%d, " , array[i] );
    }
    printf( "\n" );

    Quicksort( array , 0 , size - 1 );

    for ( int i = 0 ; i < size ; i++ ) {
        printf( "%d, " , array[i] );
    }
    printf( "\n" );

    return 0;
}

void Quicksort( int * array , int left , int right ) {
    int pivot = ( left + right ) / 2 , temp = 0;
    int l = left , r = right;
    do {
        while ( array[pivot] > array[l] ) {
            l++;
        }
        while ( array[pivot] < array[r] ) {
            r--;
        }
        if( l <= r ) {
            temp = array[l];
            array[l] = array[r];
            array[r] = temp;
            l++;
            r--;
        }
    } while ( l <= r );
    if( left < r ) {
        Quicksort( array , left , r );
    }
    if( l < right ) {
        Quicksort( array , l , right );
    }

}
int * CreateUnsortedArray( int size ) {
    int * array = ( int * )malloc( sizeof( int ) * size );
    for ( int i = 0 ; i < size ; i++ ) {
        array[i] = rand() % MAX + MIN;
    }
    return array;
}