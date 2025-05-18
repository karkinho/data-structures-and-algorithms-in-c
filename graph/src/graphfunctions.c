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
    SortAfterPushVertex( graph );
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

Vertex * SearchVertexBinary( Graph * graph , int val ) {
    int left = 0 , right = graph->sizeGraph - 1 , half = ( left + right ) / 2;
    while ( left <= half && half <= right ) {
        if( graph->vertexs[half].val == val ) return &graph->vertexs[half];
        if( graph->vertexs[half].val > val ) {
            right = half - 1;
        } else {
            left = half + 1;
        }
        half = ( left + right ) / 2;
    }
    
    Debug( "Vertex not found" );
    return NULL;
}

void SortAfterPushVertex( Graph * graph ) {
    Vertex temp;
    int index = graph->sizeGraph - 1;
    while ( index > 0 ) {
        if( graph->vertexs[index - 1].val > graph->vertexs[index].val ) {
            SWAP( graph->vertexs[index - 1] , graph->vertexs[index] , temp );
            index--;
        } else {
            return;
        }
    }
    return;
}

void PushEdge( Graph * graph , int vertexStartVal , int vertexEndVal ) {
    Vertex * vertexStart = SearchVertexBinary( graph , vertexStartVal );
    Vertex * vertexEnd = SearchVertexBinary( graph , vertexEndVal );
    if( vertexEnd == NULL || vertexStart == NULL ) return;
    vertexStart->sizeAdjacency += 1;
    vertexStart->adjacency = ( Vertex ** )MyMalloc( vertexStart->adjacency , sizeof( Vertex * ) * vertexStart->sizeAdjacency );
    vertexStart->adjacency[vertexStart->sizeAdjacency - 1] = vertexEnd;
    SortAfterPushEdge( vertexStart );
}

void Clear( Graph ** graph ) {
    for ( int i = 0 ; i < ( *graph )->sizeGraph ; i++) {
        free( ( *graph )->vertexs[i].adjacency );
    }
    free( ( *graph )->vertexs );
    free( *graph );
    *graph = NULL;
}

void SortAfterPushEdge( Vertex * vertex ) {
    Vertex * temp;
    int index = vertex->sizeAdjacency - 1;
    while ( index > 0 ) {
        if( vertex->adjacency[index - 1]->val > vertex->adjacency[index]->val ) {
            SWAP( vertex->adjacency[index - 1] , vertex->adjacency[index] , temp );
            index--;
        } else {
            return;
        }
    }
    return;
}