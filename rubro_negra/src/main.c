#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MIN 1
#define MAX 50000

typedef struct Node Node;

struct Node {
    int val;
    bool color; // false black true red
    Node *left , *right , *parent;
};

 
void InOrder( Node * root , int height );
void Push( Node ** node , int val );
void CaseRoot( Node * node );  
Node * Uncle( Node * node );
Node * GrandFather( Node * node );
void Insert( Node ** node , int val );
void CaseRoot( Node * node );
void Case1( Node * node );
void Case2( Node * node );
void RotateRight( Node * node );
void RotateLeft( Node * node );
bool IsValid( Node * node );
bool RootValid( Node * node );
bool RedSonsValid( Node * node );
int BlackPathsValid( Node * node );
void Pop( Node ** node , int val );
Node * Search( Node * node , int val );
void Transplant( Node * source , Node * destiny );
Node * Replacement( Node * delete );

Node * root = NULL;

int main() {
    srand( time( NULL ) );
    for ( int i = 0 ; i < 50000 ; i++ ) {
        //Push( &root , rand() % MAX + MIN );
        //InOrder( root , 0 );
        //printf( "-------------------\n" );
    }
    /*Push( &root , 50 );
    Push( &root , 25 );
    Push( &root , 30 );
    Push( &root , 40 );
    Push( &root , 90 );
    Push( &root , 87 );
    Push( &root , 68 );
    Push( &root , 20 ); */
    InOrder( root , 0 );
    //Pop( &root , 25 );
    printf( "Valid: %d\n", IsValid( root ) );
    return 0;
}

void Pop( Node ** node , int val ) {
    Node * delete = Search( *node , val );
    Node * replacement = NULL;
    Node * nil = ( Node * )malloc( sizeof( Node ) );

    if( delete->right == NULL ) {
        replacement = delete->left;
    } else {
        replacement = Replacement( delete->right );
    }
    printf( "%d\n", replacement->val );




}

Node * Replacement( Node * delete ) {
    if( delete->left == NULL ) {
        return delete;
    } 
    return Replacement( delete->left );
}

void Transplant( Node * source , Node * destiny ) {
    if( destiny->parent == NULL ) {
    }

    source->parent = destiny->parent;
    destiny->parent = NULL;
}

Node * Search( Node * node , int val ) {
    if( node == NULL ) {
        return NULL;
    }
    if( node->val == val ) {
        return node;
    }
    if( node->val > val ) {
        return Search( node->left , val );
    } else {
        return Search( node->right , val );
    }
}


bool IsValid( Node * node ) {
    if( BlackPathsValid( node ) > 0 ) {
        return RootValid( node ) && RedSonsValid( node ) ;
    } else {
        return false;
    }
}

bool RootValid( Node * node ) {
    if( node->color == false ) {
        return true;
    } else {
        return false;
    }
}

bool RedSonsValid( Node * node ) {
    if( node == NULL ) {
        return true;
    }
    if( node->color == true ) {
        if( node->left != NULL ) {
            if( node->left->color == true ) {
                return false;
            }
        }
        if( node->right != NULL ) {
            if( node->right->color == true ) {
                return false;
            }
        }
    }
    return RedSonsValid( node->left ) && RedSonsValid( node->right );
}

int BlackPathsValid( Node * node ) {
    if( node == NULL ) {
        return 1;
    }
    int left = BlackPathsValid( node->left );
    int right = BlackPathsValid( node->right );

    if( left == -1 || right == -1 ) {
        return -1;
    }

    int current = ( node->color == false ) ? 1 : 0;

    if( left == right ) {
        return left + current;
    } else {
        return -1;
    }
}

void Insert( Node ** node , int val ) {
    *node = ( Node * )malloc( sizeof( Node ) );
    ( *node )->left = NULL;
    ( *node )->right = NULL;
    ( *node )->parent = NULL;
    ( *node )->color = true;
    ( *node )->val = val;
}

Node * Uncle( Node * node ) {
    Node * g = GrandFather( node );
    
    if( g == NULL ) return NULL;

    if( g->left == node->parent ) {
        return g->right;
    } else { 
        return g->left;
    }
}

Node * GrandFather( Node * node ) {
    if( node != NULL && node->parent != NULL ) {
        return node->parent->parent;
    } else {
        return NULL;
    }
}

void Push( Node ** node , int val ) {
    if ( *node == NULL ) {
        Insert( node , val );
        CaseRoot( *node ); 
    } else if( ( *node )->val > val ) {
        if( ( *node )->left == NULL ) {
            Insert( ( Node ** )&( *node )->left , val );
            ( *node )->left->parent = ( *node );
            CaseRoot( ( *node )->left );
        } else {
            Push( ( Node ** )&( *node )->left , val );
        }
    } else {
        if( ( *node )->right == NULL ) {
            Insert( ( Node ** )&( *node )->right , val );
            ( *node )->right->parent = ( *node );
            CaseRoot( ( *node )->right );
        } else {
            Push( ( Node ** )&( *node )->right , val );
        }
    }
} 

void CaseRoot( Node * node ) {
    if( node->parent == NULL ) {
        node->color = false;
    } else {
        if( node->parent->color == true ) {
            Case1( node );
        }
    } 
}

void Case1( Node * node ) {
    Node * uncle = Uncle( node );
    Node * g = GrandFather( node );

    if( uncle != NULL && uncle->color == true ) {
        uncle->color = false;
        node->parent->color = false;
        g->color = true;
        CaseRoot( g );
    } else {
        Case2( node );
    }
}

void Case2( Node * node ) {
    Node * g = GrandFather( node );
    if( g == NULL ) return; 

    if( g->right == node->parent ) {
        if( node->parent->left == node ) {
            RotateRight( node->parent );
        }
        RotateLeft( g );
    } else {
        if( node->parent->right == node ) {
            RotateLeft( node->parent );
        }
        RotateRight( g );
        
    }
    g->color = true;
    g->parent->color = false;
    CaseRoot( g );
}

void RotateLeft( Node * node ) {
    Node * aux = node->right;
    node->right = aux->left;
    if( aux->left != NULL ) {
        aux->left->parent = node;
    }
    aux->parent = node->parent;
    if( node->parent == NULL ) {
        root = aux;
        aux->left = node;
        node->parent = aux;
        return;
    }
    if( node->parent->left == node ) {
        node->parent->left = aux;
    } else {
        node->parent->right = aux;
    }
    aux->left = node;
    node->parent = aux;
}

void RotateRight( Node * node ){
    Node * aux = node->left;
    node->left = aux->right;
    
    if( aux->right != NULL ) {
        aux->right->parent = node;
    }
    aux->parent = node->parent; 
    if( node->parent == NULL ) {
        root = aux;
        aux->right = node;
        node->parent = aux;
        return;
    }
    if( node->parent->left == node ) {    
        node->parent->left = aux;
    } else {
        node->parent->right = aux;
    }
    aux->right = node;
    node->parent = aux;
}


void InOrder( Node * node , int height ) {
    if( node == NULL ) return;

    for ( int i = 0 ; i < height ; i++ ) {
        printf( " | " );
    }
    
    printf( "%d ; %d" , node->val , node->color );
    if( node->parent != NULL ) {
        printf( " , %d\n", node->parent->val );
    } else {
        printf( "\n" );
    }

    InOrder( node->left , height + 1 );
    InOrder( node->right , height + 1 );
    return;
}