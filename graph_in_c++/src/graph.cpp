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
    vertex[size - 1] = *( new Vertex( val , size - 1 ) );
}
void Graph::AddAdjToVertex( int vertexStartVal , int vertexEndVal , int weight ) {
    int indexStart = SearchVertex( vertexStartVal );
    int indexEnd = SearchVertex( vertexEndVal );
    if( indexEnd <= -1 && indexStart <= -1 ) {
        std::cout << "AddAdjToVertex FAILED\n";
        return;
    }
    std::shared_ptr< Vertex > ptr = std::make_shared< Vertex >( vertex[indexEnd] );
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
void Vertex::AddAdj( std::shared_ptr< Vertex > vertex , int weightVertex ) {
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

