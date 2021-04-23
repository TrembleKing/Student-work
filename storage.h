#include <iostream>

typedef struct LNode{
    int data;
    struct LNode *pNext;
}Lnode,*node;

void Head_Initsert_node(node *,node *,int val);   //ignore
void printf_Lnode(node);
void reverse_Lnode(node *,node *);                //ignore
void First_insert_node(node *,node *,int vals);   
void Second_insert_node(node *,node *,int vals);
void Result_node(node *,node *,node *,node *);
node Return_list_node(node);    //ignore