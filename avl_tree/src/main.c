#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>

#define MIN 1
#define MAX 50000

typedef struct Node Node;

struct Node {
    int val , height ;
    Node * left , * right;
};

void List( Node ** root );
void PreOrder( Node ** root ,int height );
void Push( Node ** root , int val );
void Balance( Node ** node );
int CalculateFB( Node * node );
int TaCertoIsso( Node * root );
void LeftRotation( Node ** node );
void RightRotation( Node ** node );
void CalculateHeight( Node ** node );
void Pop( Node ** root , int val ); 
Node ** FindPop( Node ** root , int val );
Node ** FindReplacement( Node ** node );
void RebalanceTree( Node ** node );
void Clear( Node ** root );

int main( int argc , char const *argv[] ) {
    Node * root = NULL;
    srand( time( NULL ) );
    for ( int i = 0 ; i < 50000 ; i++ ) {
        Push( &root , rand() % MAX + MIN );
        //List( &root );
        //printf( "-------------------\n" );
    }
    
    List( &root );

    for ( int i = 0 ; i < 5000 ; i++ ) {
        Pop( &root , rand() % MAX + MIN ); 
        //List( &root );
        //printf( "-------------------\n" );
    }

    List( &root );
    
    printf( "Ta Certo %d\n" , TaCertoIsso( root ) );

    Clear( &root );
    return 0;
}

void Clear( Node ** root ) {
    for ( int i = MIN; i < MAX ; i++ ) {
        Pop( root , i );
    }
    *root = NULL;
}


Node ** FindReplacement( Node ** node ) {
    if( ( * node )->left != NULL ) {
        return FindReplacement( ( Node ** )( &( * node )->left ) );
    }
    return node;
}

void Pop( Node ** root , int val ) {
    Node ** pop = FindPop( root , val ) , ** aux = NULL , * auxP = NULL;
    if( pop == NULL ) {
        return;
    }

    if( ( *pop )->left == NULL && ( *pop )->right == NULL ) {
        aux = pop;
        free( *aux );
        *pop = NULL;
        CalculateHeight( root );
        RebalanceTree( root );
        return; 
    }

    if( ( *pop )->left != NULL && ( *pop )->right != NULL ) {
        aux = FindReplacement( ( Node ** )&( *pop )->right );
        ( *pop )->val = ( *aux )->val;
        auxP = ( *aux )->right;
        free( *aux );
        *aux = auxP;
        CalculateHeight( pop );
        RebalanceTree( pop );
        return;
    }

    if ( ( * pop )->right != NULL ) {
        auxP = ( * pop )->right;
        free( * pop );
        *pop = auxP;
        CalculateHeight( pop );
        RebalanceTree( pop );
        return;
    }

    if ( ( * pop )->left != NULL ) {
        auxP = ( * pop )->left;
        free( * pop );
        *pop = auxP;
        CalculateHeight( pop );
        RebalanceTree( pop );
        return;
    }
}

void RebalanceTree( Node ** node ) {
    if( *node == NULL ) {
        return;
    }
    Balance( node );
    RebalanceTree( ( Node ** )&( *node )->left );
    RebalanceTree( ( Node ** )&( *node )->right );
}

Node ** FindPop( Node ** root , int val ) {
    if( *root == NULL ) {
        return NULL;
    }
    if( val == ( *root )->val ) {
        return root;
    }
    if( val < ( *root )->val ) {
        return FindPop( ( Node ** )&( *root )->left , val );
    } else {
        return FindPop( ( Node ** )&( *root )->right , val );
    }
}

void List( Node ** root ) {
    if( *root == NULL ) {
        printf( "tree empty\n" );
        return;
    }
    PreOrder( root , 0 );
}

void Push( Node ** root , int val ) {
    if( *root == NULL ) {
        *root = ( Node * )malloc( sizeof( Node ) );
        ( *root )->left = NULL;
        ( *root )->right = NULL;
        ( *root )->val = val;
        ( *root )->height = 0;
        return;
    }
    if( val > ( *root )->val ) {
        Push( ( Node ** )&( *root )->right , val );
        if( ( *root )->height < ( *root )->right->height + 1 ) {
            ( *root )->height = ( *root )->right->height + 1;
        }
    } else {
        Push( ( Node ** )&( *root )->left , val );
        if( ( *root )->height < ( *root )->left->height + 1 ) {
            ( *root )->height = ( *root )->left->height + 1;
        }
    }

    Balance( root );    
     
    return;
}

void CalculateHeight( Node ** node ) {
    int heightLeft = 0 , heightRight = 0;
    if( !( ( *node )->left == NULL && ( *node )->right == NULL ) ) {
        if( ( *node )->left != NULL ) {
            CalculateHeight( ( Node ** )&( *node )->left );
            heightLeft = ( *node )->left->height;
        }
        if( ( *node )->right != NULL ) {
            CalculateHeight( ( Node ** )&( *node )->right );
            heightRight = ( *node )->right->height;
        }
    } else {
        ( *node )->height = 0;
        return;
    }

    if( heightLeft > heightRight ) {
        ( *node )->height = heightLeft + 1;
    } else {
        ( *node )->height = heightRight + 1;
    }
    return;
}

int CalculateFB( Node * node ) {
    int fb = 0 ;
    if( node->left != NULL ) {
        fb = node->left->height;
    } 
    if( node->right != NULL ) {
        fb -= node->right->height;
    }
    return fb;
}

void RightRotation( Node ** node ) {
    Node * aux = NULL;
    aux = ( *node )->left;
    ( *node )->left = aux->right;
    aux->right = *node;
    *node = aux;
}

void LeftRotation( Node ** node ) {
    Node * aux = NULL;
    aux = ( *node )->right;
    ( *node )->right = aux->left;
    aux->left = *node;
    *node = aux;
}

void Balance( Node ** node ) {
    int fb = 0 , fbLeft = 0 , fbRight = 0;

    fb = CalculateFB( *node );

    if( fb > 1 ) { 
        if( ( *node )->left != NULL ) {
            fbLeft = CalculateFB( ( *node )->left );
        } 

        if( fbLeft < 0 ) {
            LeftRotation( ( Node **)&( *node )->left );
        }
        RightRotation( node );    
        CalculateHeight( node );
        return;
    }

    if( fb < -1 ) {
        if( ( *node )->right != NULL ) {
            fbRight = CalculateFB( ( *node )->right );
        }
        if( fbRight > 0 ) {
            RightRotation( ( Node **)&( *node )->right );
        }
        LeftRotation( node );
        CalculateHeight( node );
        return;
    }

}

int TaCertoIsso( Node * root ) {
    int fb;
    if( root == NULL ) {
        return 1;
    }

    if( !TaCertoIsso( root->left ) ) {
        return 0;
    }
    if( !TaCertoIsso( root->right ) ) {
        return 0;
    }

    fb = CalculateFB( root );
    if( ( fb > 1 ) || ( fb < -1 ) ) {
        return 0;
    } else {
        return 1;
    }
}

void PreOrder( Node ** root , int height ) {
    for ( int i = 0; i < height ; i++ ) {
        printf( " | " );
    }
    printf( "%d, %d\n" , ( * root )->val , ( *root )->height );
    if( ( *root )->left != NULL ) {
        PreOrder( ( Node ** )&( *root )->left , height + 1 );
    } 
    if( ( *root )->right != NULL ) {
        PreOrder( ( Node ** )&( *root )->right , height + 1 );
    }
    return;
}