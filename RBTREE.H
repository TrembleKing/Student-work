#include<iostream>
#define BLACK 1
#define RED 0
#define rb_set_black(r) do{(r)->color = BLACK;}while(0)
#define rb_set_red(r) do{(r)->color = RED;}while(0)
#define rb_is_black(r) ((r)->color == BLACK)
#define rb_is_red(r) ((r)->color == RED)
#define CHECK_INSERT 1
#define rb_parent(r) ((r)->parent)
#define LENGTH(a) (sizeof(a)/sizeof(a[0]))

typedef int Type;
typedef struct treenode{
    unsigned char color;
    Type key;
    treenode *right;
    treenode *left;
    treenode *parent;
}NODE, *pTreenode;

typedef struct{
    NODE *node;
}RBroot;

char color(NODE *);         //Only to print the color
const char *parent_child(NODE *);  //Only to print the node child 
RBroot *Create_RBroot();    //malloc for root
Type Insert_RBtree(RBroot *,Type);  //Insert root and key
NODE *search(NODE *,Type);  //Search the same value and exit
static NODE *Create_insert_node(Type,NODE *,NODE *,NODE *);//Insert node
static void RBtree_Insert_node(RBroot *,NODE *);
void print_RBtree(RBroot *);
void print_head_RBtree(NODE *);     
void print_mid_RBtree(NODE *);
void print_back_RBtree(NODE *);
void RBtree_fixup(RBroot *,NODE *); //fixup,include right rotate and left rotate
void LEFT_ROTATE(RBroot *,NODE *);  
void RIGHT_ROTATE(RBroot *,NODE *);
