#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <stack>

class Graph;
class Vertex;

class Graph {
    private:
        int size;
        std::vector< Vertex > vertex;
    public:
        Graph();
        ~Graph();
        void AddVertex( int val );
        void AddAdjToVertex( int vertexStartVal , int vertexEndVal , int weight );
        int SearchVertex( int val );
        void Print();
        void Dijsktra( int vertexStartVal , int vertexEndVal );
};

class Vertex {
    private:
        int val;
        int index;
        int adjSize;
        std::vector< int > weight;
        std::vector< std::shared_ptr< Vertex >> adj;
    public:
        Vertex();
        Vertex( int val , int index );
        ~Vertex();
        void Print();
        int getVal();
        int getIndex();
        int getAdjSize();
        void AddAdj( std::shared_ptr< Vertex > vertex , int weightVertex );
        int* getAdj( int index );
};


