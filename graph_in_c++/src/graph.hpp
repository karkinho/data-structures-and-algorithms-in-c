#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

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
        void Kruskal();
};

class Vertex {
    private:
        int val;
        int index;
        int adjSize;
        std::vector< int > weight;
        std::vector< Vertex * > adj;
    public:
        Vertex();
        Vertex( int val , int index );
        ~Vertex();
        void Print();
        int getVal();
        int getIndex();
        int getAdjSize();
        void AddAdj( Vertex * vertex , int weightVertex );
        int* getAdj( int index );
};

class DSU {
    public:
        DSU( int size );
        ~DSU();
        int find( int index );
        void unite( int x , int y  );

    private:
        std::vector< int > rank , parent;
};

bool comparator( std::vector< int > &a,std::vector<int> &b );
