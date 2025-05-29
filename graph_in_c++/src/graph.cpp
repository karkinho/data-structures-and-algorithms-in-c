#include "graph.hpp"

Graph::Graph() {
    size = 0;
    vertex.resize( 0 );
}
Graph::~Graph() {
    vertex.clear();
}
void Graph::AddVertex( int val ) {
    size++;
    vertex.resize( size );
    vertex[size - 1] = Vertex( val , size - 1 );
}
void Graph::AddAdjToVertex( int vertexStartVal , int vertexEndVal , int weight ) {
    int indexStart = SearchVertex( vertexStartVal );
    int indexEnd = SearchVertex( vertexEndVal );
    if( indexEnd <= -1 && indexStart <= -1 ) {
        std::cout << "AddAdjToVertex FAILED\n";
        return;
    }
    Vertex * ptr = &vertex[indexEnd];
    vertex[indexStart].AddAdj( ptr , weight );
}
int Graph::SearchVertex( int val ) {
    for ( int index = 0 ; index < size ; index++ ) {
        if ( vertex[index].getVal() == val ) {
            return index;
        }
    }
    std::cout << val << " VERTEX NOT FOUND\n";
    return -1;
}
void Graph::Print() {
    for ( int index = 0 ; index < size ; index++ ) {
        vertex[index].Print();
    }
}
void Graph::Dijsktra( int vertexStartVal , int vertexEndVal ) {
    std::vector< int > dist( size , INT32_MAX );
    std::priority_queue< int * > queue;
    std::vector< int > prev( size , -1 );
    int currentDist , currentIndex , *temp;
    int indexSource = SearchVertex( vertexStartVal );
    int indexEnd = SearchVertex( vertexEndVal );
    if( indexEnd <= -1 && indexSource <= -1 ) {
        std::cout << "Dijsktra FAILED\n";
        return;
    }
    dist[indexSource] = 0;
    temp = new int[2];
    temp[0] = 0;
    temp[1] = indexSource;
    queue.push( temp );
    while ( !queue.empty() ) {
        currentDist = queue.top()[0];
        currentIndex = queue.top()[1];
        queue.pop();
        for ( int index = 0 ; index < vertex[currentIndex].getAdjSize() ; index++ ) {
            temp = vertex[currentIndex].getAdj( index );
            if( dist[temp[1]] > currentDist + temp[0] ) {
                temp[0] += currentDist; 
                dist[temp[1]] = temp[0];
                queue.push( { temp } );
                prev[temp[1]] = currentIndex;
            }
        }
    }
    std::cout << "Dijsktra Results From " << vertexEndVal << ":\n";
    for ( int i = 0 ; i < size ; i++ ) {
        if( dist[i] == INT32_MAX ) {
            std::cout << vertex[i].getVal() << " - " << "Not Reachable\n";
            continue;
        }
        std::cout << vertex[i].getVal() << " - " <<  dist[i] << "\n";
    }
    std:: cout << "Shortest Path From " << vertexStartVal << " To " << vertexEndVal << ": ";
    if( dist[indexEnd] == INT16_MAX ) {
        std::cout << "Don't Exist\n";
        return;
    }
    currentIndex = indexEnd;
    std::stack< int > stack;
    stack.push( indexEnd );
    while ( currentIndex != -1 && currentIndex != indexSource ) {
        stack.push( prev[currentIndex] );
        currentIndex = prev[currentIndex];
    }
    while ( stack.top() != indexEnd ) {
        std::cout << vertex[stack.top()].getVal() << " -> ";
        stack.pop();
    }
    std::cout << vertex[stack.top()].getVal() << "\n";
    stack.pop();
}

void Graph::Kruskal() {
    int edgesSize = 0 , *adj , cost = 0 , count = 0;
    std::vector< std::vector< int > > orderedEdges;


    for ( int indexVertex = 0 ; indexVertex < size ; indexVertex++ ) {
        for ( int indexAdj = 0 ; indexAdj < vertex[indexVertex].getAdjSize() ; indexAdj++ )
        {
            adj = vertex[indexVertex].getAdj( indexAdj );
            orderedEdges.push_back( std::vector< int >{ indexVertex , vertex[adj[1]].getIndex() , adj[0] } );
            edgesSize++;
        }
    }
    std::sort( orderedEdges.begin() , orderedEdges.end() , comparator );

    DSU dsu = DSU( size );


    std::cout << orderedEdges[3][0] << " - " << orderedEdges[3][1] << '\n';
    for ( int i = 0 ; i < edgesSize ; i++ ) {
        if( dsu.find( orderedEdges[i][0] ) != dsu.find( orderedEdges[i][1] ) ) {
            dsu.unite( orderedEdges[i][0] , orderedEdges[i][1] );
            cost += orderedEdges[i][2];
            count++;
            std::cout << "\t" << vertex[orderedEdges[i][0]].getVal() << " - " << vertex[orderedEdges[i][1]].getVal() << " | " << orderedEdges[i][2] << "\n";
            if ( count + 1 == size ) {
                std::cout << "Minimum Cost: " << cost << "\n";
                break;
            }
        }
    }
}


Vertex::Vertex() {
    val = -1;
}
Vertex::Vertex( int val , int index ) {
    this->val = val;
    this->index = index;
    adjSize = 0;
}
Vertex::~Vertex() {
    weight.clear();
    adj.clear();
}
int Vertex::getVal( ) {
    return this->val;
}
void Vertex::Print() {
    std::cout << val << ": ";
    for ( int i = 0 ; i < adjSize ; i++ ) {
        std::cout << ( *adj[i] ).getVal() << "-" << weight[i] << " | ";
    }
    std::cout << "\n";
}
void Vertex::AddAdj( Vertex * vertex , int weightVertex ) {
    adjSize++;
    weight.resize( adjSize );
    adj.resize( adjSize );
    weight[adjSize - 1] = weightVertex;
    adj[adjSize - 1] = vertex;
}
int Vertex::getAdjSize() {
    return adjSize;
}
int Vertex::getIndex() {
    return index;
}
int* Vertex::getAdj( int index ) {
    int *array = new int[2];
    array[0] = weight[index];
    array[1] = ( *adj[index] ).getIndex();
    return array;
}

DSU::DSU( int size ) {
    rank.resize( size );
    parent.resize( size );
    for ( int i = 0 ; i <= size ; i++ ) {
        rank[i] = 0;
        parent[i] = i;
    }
}

DSU::~DSU() {
    rank.clear();
    parent.clear();
}

int DSU::find( int index ) {
    if ( parent[index] != index ) {
        parent[index] = find( parent[index] );
    }
    return parent[index];
}

void DSU::unite( int x , int y ) {
    x = find( x );
    y = find( y );
    if( rank[x] < rank[y] ) {
        parent[x] = y;
    } else if( rank[x] > rank[y] ) {
        parent[y] = x;
    } else {
        rank[y]++;
    }
}

bool comparator( std::vector< int > &a,std::vector<int> &b ){
    if(a[2]<b[2])return true;
    return false;
}