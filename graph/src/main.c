#include "lib.h"

int main( int argc , char const *argv[] ) {
    Debug( "DEBUG ACTIVE" );
    Graph * graph = InitGraph();
    PushVertex( graph , 1 );
    PushVertex( graph , 5 );
    PushVertex( graph , 4 );
    PushVertex( graph , 3 );
    PushVertex( graph , 2 );
    PrintGraph( graph );
    printf( "-----------\n" );
    PushEdge( graph , 1 , 5 );
    PushEdge( graph , 1 , 4 );
    PushEdge( graph , 1 , 3 );
    PushEdge( graph , 1 , 2 );
    PushEdge( graph , 1 , 1 );
    PrintGraph( graph );
    Clear( &graph );
    return 0;
}
