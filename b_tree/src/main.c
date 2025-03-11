#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct Container Container;

struct Container {
    int value;
};  

struct Node {
    Container *info;
    void * left , * right; 
};

void Push( Node ** stump , int value );
void List( Node ** stump );
void PreOrdem( Node * node , int height );
Node **SearchPush( Node * node , int value );
void Pop( Node ** stump, int value );
Node ** FindPop( Node ** node , int value );
Node ** SearchReplacementPop( Node ** node );
void Clear( Node ** stump );

int main( int argc , char const *argv[] ) {
    Node *stump = NULL;
    List( &stump );
    Push( &stump , 10 );
    Push( &stump , 20 );
    Push( &stump , 15 );
    Push( &stump , 5 );
    Push( &stump , 50 );
    Push( &stump , 56 );
    Push( &stump , 27 );
    Push( &stump , 8 );
    Push( &stump , 12 );
    Push( &stump , 90 );
    Push( &stump , 1 );
    List( &stump );
    Pop( &stump , 10 );
    Pop( &stump , 20 );
    Pop( &stump , 15 );
    Pop( &stump , 5 );
    Pop( &stump , 90 );
    Pop( &stump , 1 );
    List( &stump );
    Clear( &stump );
    List( &stump );
    return 0;
}

void Clear( Node ** stump ) {
    while ( *stump != NULL ) {
        Pop( stump , ( * stump )->info->value );
    }
}

void Push( Node ** stump , int value ) {
    Node * newNode = ( Node * )malloc( sizeof( Node ) ) , ** temp = NULL ;
    Container * newContainer = ( Container * )malloc( sizeof( Container ) );
    newContainer->value = value;
    newNode->info = newContainer;
    newNode->left = NULL;
    newNode->right = NULL;
    if ( *stump == NULL ) {
        *stump = newNode;
        return;
    }
    temp = ( Node ** ) SearchPush( *stump , value );
    *temp = newNode;
}

Node **SearchPush( Node * node , int value ) {
    if( value < node->info->value ) {
        if( node->left == NULL ) {
            return ( Node ** )( &node->left );
        } else{
            return SearchPush( node->left , value );
        }
    } 
    if( value > node->info->value ) {
        if( node->right == NULL ) {
            return ( Node ** )( &node->right );
        } else{
            return SearchPush( node->right , value );
        }
    }
    if( value == node->info->value ) {
        return NULL;
    }
    return NULL;
}

void List( Node ** stump ) {
    if ( *stump == NULL ) {
        printf( "b_tree vaiza\n" );
        return;
    }
    PreOrdem( *stump , 0 );
}

void PreOrdem( Node * node  , int height ){
    for ( int i = 0; i < height ; i++ ) {
        printf( " | " );
    }
    printf( "%d\n", node->info->value );
    if( node->left != NULL ) {
        PreOrdem( node->left , height + 1 );
    }
    if( node->right != NULL ) {
        PreOrdem( node->right , height + 1 );
    }
    return;
}

void Pop( Node ** stump, int value ) {
    Node ** node = NULL , * auxP = NULL , ** auxPP = NULL ;
    if( *stump == NULL ) {
        printf( "b_tree vazia\n" );
        return;
    }
    node = FindPop( stump , value );

    if( node == NULL ) {
        printf( "não encontrado\n" );
        return;
    }

    if ( ( * node )->right != NULL && ( * node )->left != NULL ) { //pior caso
        auxPP = SearchReplacementPop( ( Node ** )( &( * node )->right ) );
        free( ( * node )->info );
        ( * node )->info = ( * auxPP )->info; 
        auxP = ( * auxPP )->right;
        free( * auxPP );
        * auxPP = auxP;
        return;
    } 

    if( ( * node )->right == NULL && ( * node )->left == NULL ) { // melhor caso
        free( ( * node )->info );
        ( * node )->info = NULL;
        auxP = * node;
        *node = NULL;
        free( auxP );
        return;
    }

    if ( ( * node )->right != NULL ) {
        auxP = ( * node )->right;
        free( ( * node )->info );
        free( * node );
        *node = auxP;
        return;
    }

    if ( ( * node )->left != NULL ) {
        auxP = ( * node )->left;
        free( ( * node )->info );
        free( * node );
        *node = auxP;
        return;
    }
}

Node ** SearchReplacementPop( Node ** node ) {
    if( ( * node )->left != NULL ) {
        return SearchReplacementPop( ( Node ** )( &( * node )->left ) );
    }
    return node;
}


Node ** FindPop( Node ** node , int value ) {
    if( ( * node )->info->value == value ) {
        return node;
    }
    if( ( * node )->info->value < value ) {
        return FindPop( ( Node ** )( &( * node )->right ) , value );
    }
    if( ( * node )->info->value > value ) {
        return FindPop( ( Node ** )( &( * node )->left ) , value );
    }
    return NULL;
}