#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct vertex Vertex;
typedef struct graph Graph;

struct vertex {
    int val;
    int sizeAdjacency;
    Vertex **adjacency;
    int *weight;
};

struct graph {
    int sizeGraph;
    int allocedMem;
    Vertex *vertexs;
};

void PushVertex( Graph * graph , int val);
Vertex CreateVertex( int val);
void AllocateMemGraph( Graph * graph );
Graph *InitGraph();
void Clear( Graph ** graph );
void PrintGraph( Graph * graph );
void *MyMalloc( void * ptr , int size );
void PushEdge( Graph * graph , int vertexVal1 , int vertexVal2 );
Vertex * Search( Graph * graph , int val );
void Debug( char * msg );