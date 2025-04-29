#include "lib.h" 

Graph * InitGraph() {
    Graph * graph = NULL;
    do {
        graph = ( Graph * )malloc( sizeof( Graph ) );
    } while ( graph == NULL );
    graph->allocedMem = 0;
    graph->sizeGraph = 0;
    graph->vertexs = NULL;
    return graph;
}

void AllocateMemGraph( Graph * graph ) {
    if( graph->allocedMem <= ( graph->sizeGraph + 1 ) * sizeof( Vertex ) ) {
        graph->vertexs = ( Vertex * )MyMalloc( graph->vertexs , ( graph->sizeGraph + 500 ) * sizeof( Vertex ) );
        graph->allocedMem = ( graph->sizeGraph + 500 ) * sizeof( Vertex );
    }
}

Vertex CreateVertex( int val ) {
    Vertex new;
    new.val = val;
    new.adjacency = NULL;
    new.weight = NULL;
    new.sizeAdjacency = 0;
    return new;
}

void PushVertex( Graph * graph , int val ) {
    Vertex new = CreateVertex( val );
    AllocateMemGraph( graph );
    graph->sizeGraph += 1;
    graph->vertexs = ( Vertex * )MyMalloc( graph->vertexs , graph->sizeGraph * sizeof( Vertex ) ); 
    graph->vertexs[graph->sizeGraph - 1] = new;
}

void PrintGraph( Graph * graph ) {
    for ( int i = 0 ; i < graph->sizeGraph ; i++ ) {
        printf( "%d->", graph->vertexs[i].val );
        for ( int x = 0 ; x < graph->vertexs[i].sizeAdjacency ; x++ ) {
            printf( " %d ;", graph->vertexs[i].adjacency[x]->val );
        }
        printf( "\n" );
    }   
}

Vertex * Search( Graph * graph , int val ) {
    for ( int i = 0 ; i < graph->sizeGraph ; i++ ) {
        if( graph->vertexs[i].val == val ) {
            return &graph->vertexs[i];
        }
    }
    Debug( "Vertex not found" );
    return NULL;
}

void PushEdge( Graph * graph , int vertexStartVal , int vertexEndVal ) {
    Vertex * vertexStart = Search( graph , vertexStartVal );
    Vertex * vertexEnd = Search( graph , vertexEndVal );
    vertexStart->sizeAdjacency += 1;
    vertexStart->adjacency = ( Vertex ** )MyMalloc( vertexStart->adjacency , sizeof( Vertex * ) * vertexStart->sizeAdjacency );
    vertexStart->adjacency[vertexStart->sizeAdjacency - 1] = vertexEnd;
}

void Clear( Graph ** graph ) {
    for ( int i = 0 ; i < ( *graph )->sizeGraph ; i++) {
        free( ( *graph )->vertexs[i].adjacency );
    }
    free( ( *graph )->vertexs );
    free( *graph );
    *graph = NULL;
}