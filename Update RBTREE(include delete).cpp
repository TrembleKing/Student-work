#include "RBTREE(include delete).h" 
//I consulted the introduction to Algorithms(Third Edition)
int main(){
    Type array[] = {16,3,7,11,9,26,18,14,15};    
    Type i,ilen = sizeof(array)/sizeof(int);
    for (i = 0; i < ilen; ++i)  
        printf("%d ",array[i]);
    printf("\n-----------------------------\n");    

    RBroot *root = NULL;
    root = Create_RBroot();

    for (i = 0; i < ilen; ++i){
        Insert_RBtree(root,array[i]);
#if CHECK_INSERT
        printf("The node value: %d\n",array[i]);
        printf("The information of node: \n");
        print_RBtree(root);
        printf("\n");        
#endif
    }

    printf("\nBeginning to delete\n");

    for (i = ilen-1; i >= 0 ; --i){
        Delete_Rbtree(root,array[i]);
        printf("Delete node value: %d\n",array[i]);
        printf("The information of node: \n");
        print_RBtree(root);
        printf("\n");
    }

    system("pause");
}

void print_RBtree(RBroot *root){
    print_head_RBtree(root->node);
    //printf("\n-------------------------\n");
    //print_mid_RBtree(root->node);
    //printf("\n-------------------------\n");
    //print_back_RBtree(root->node);
}

void print_head_RBtree(NODE *node){
    if (node){
        if (rb_parent(node) != NULL)
            std::cout << node->key <<"<"<<(rb_is_black(node) ? 'B':'R')<<">\t"<<rb_parent(node)->key<<"'s\t"<<((rb_parent(node)->left == node) ? "left":"right")<<" child."<<std::endl;
        print_head_RBtree(node->left);
        print_head_RBtree(node->right);
    }
}

void print_mid_RBtree(NODE *node){     //same as print_head_RBtree
    if (node){                       
        print_mid_RBtree(node->left);  //amend this line as head_printf
        if (rb_parent(node) != NULL)
            std::cout << node->key <<"<"<<(rb_is_black(node) ? 'B':'R')<<">\t"<<rb_parent(node)->key<<"'s\t"<<((rb_parent(node)->left == node) ? "left":"right")<<" child."<<std::endl;
        print_mid_RBtree(node->right);
    }
}

void print_back_RBtree(NODE *node){    //same
     if (node){
        print_back_RBtree(node->left);
        print_back_RBtree(node->right);
        if (rb_parent(node) != NULL)
            std::cout << node->key <<"<"<<(rb_is_black(node) ? 'B':'R')<<">\t"<<rb_parent(node)->key<<"'s\t"<<((rb_parent(node)->left == node) ? "left":"right")<<" child."<<std::endl;
    }
}

RBroot *Create_RBroot(){
    RBroot *root = new RBroot;
    root->node = NULL;
    return root;
}

Type Insert_RBtree(RBroot *root,Type key){
    NODE *node;
    if (search(root->node,key) != NULL)
        return -1;
    if ((node = Create_insert_node(key,NULL,NULL,NULL)) == NULL)
        return -1;

    RBtree_Insert_node(root,node);
    return 0;
}

NODE *search(NODE *node,Type key){
    if (node == NULL || node->key == key){
        return node;
    }
    if (node->key < key){
        return search(node->right,key);
    }else{
        return search(node->left,key);
    }
}

static NODE *Create_insert_node(Type key,NODE *right,NODE *left,NODE *parent){
    NODE *p = NULL;
    p = new NODE;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK;
    return p;
}

static void RBtree_Insert_node(RBroot *root,NODE *node){
    NODE *y = NULL;
    NODE *x = root->node;
    while (x != NULL){
        y = x;
        if (node->key < x->key){
            x = x->left;
        }else {
            x = x->right;
        }
    }
    rb_parent(node) = y;
    if (y != NULL){
        if (node->key < y->key){
            y->left = node;
        }else {
            y->right = node;
        }
    }else {
        root->node = node;
    }
    node->color = RED;
    RBtree_fixup(root,node);
}

void RBtree_fixup(RBroot *root,NODE *node){
    NODE *parent,*gparent,*uncle;
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);
        if (parent == gparent->left){
            uncle = gparent->right;
            if (uncle && rb_is_red(uncle)){
                rb_set_black(parent);
                rb_set_black(uncle);
                rb_set_red(gparent);
                node = gparent;
            }else {
                if (node == parent->right){
                    node = parent;
                    LEFT_ROTATE(root,node);
                }
                rb_set_black(rb_parent(node));
                rb_set_red(gparent);
                RIGHT_ROTATE(root,gparent);    
            }
        }else{
            uncle = gparent->left;
            if (uncle && rb_is_red(uncle)){
                rb_set_black(parent);
                rb_set_black(uncle);
                rb_set_red(gparent);
                node = gparent;
            }else {
                if (node == parent->left){
                    node = parent;
                    RIGHT_ROTATE(root,node);
                }
                rb_set_black(rb_parent(node));
                rb_set_red(gparent);
                LEFT_ROTATE(root,gparent);
            }
        }
    }
    rb_set_black(root->node);
    rb_parent(root->node) = NULL;
}

void RIGHT_ROTATE(RBroot *root,NODE *node){
    NODE *x = node;
    NODE *y = node->left;
    x->left = y->right;
    if (y->right != NULL){
        rb_parent(y->right) = x;
    }
    rb_parent(y) = rb_parent(x);
    if (rb_parent(x) == NULL){
        root->node = y;
    }else{
        if (x == rb_parent(x)->right){
            rb_parent(x)->right = y;
        }else {
            rb_parent(x)->left = y;
        }
    }
    y->right = x;
    x->parent = y;
}

void LEFT_ROTATE(RBroot *root,NODE *node){
    NODE *x = node;
    NODE *y = node->right;
    x->right = y->left;
    if (y->left != NULL){
        rb_parent(y->left) = x;
    }
    rb_parent(y) = rb_parent(x);
    if (rb_parent(x) == NULL){
        root->node = y;
    }else{
        if (x == rb_parent(x)->left){
            rb_parent(x)->left = y;
        }else{
            rb_parent(x)->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}

void Delete_Rbtree(RBroot *root,Type key){
    NODE *z;
    z = Search_node(root->node,key); //to found the node of the value 
    
    RBTREE_DELETE(root,z);  //begin to delete
}

NODE *Search_node(NODE *node,Type key){
    if (node->key == key){
        return node;
    }
    if (node->key < key){
        return Search_node(node->right,key);
    }else {
        return Search_node(node->left,key);
    }
    if (node == NULL){
        printf("Not search the key.");
    }
}

//Not add the nil(对应哨兵),so must to judge the condition of NULL
void RBTREE_DELETE(RBroot *root,NODE *z){
    NODE *x,*y;
    y = z;
    unsigned char y_color = y->color;
    if (z->left == NULL){
        x = z->right;
        RB_TRANSPLANT(root,z,z->right);
    }else if (z->right == NULL){
        x = z->left;
        RB_TRANSPLANT(root,z,z->left);
    }else{
        y = TREE_RIGHT_MIN(z->right);   
        y_color = y->color;
        x = y->right;
        if (rb_parent(y) == z && x!=NULL){
            rb_parent(x) = y;
        }else if(x!=NULL){
            RB_TRANSPLANT(root,y,y->right);
            y->right = z->right;
            rb_parent(y->right) = y;
        }
        RB_TRANSPLANT(root,z,y);
        y->left = z->left;
        rb_parent(y->left) = y;
        y->color = z->color;
    }
    delete z;
    z = NULL;
    if (y_color == BLACK && x!=NULL){   //delete z is black will destroy the characteristic of red black tree,so fix it.
        RB_DELETE_FIXUP(root,x);
    }   //Well if x is NULL means z not have left child and right child,meanwhile z is black
        //I think x is a nil.Actually,it is null. 
        //Uh......I don't know whether the answer is right. 
}

NODE *TREE_RIGHT_MIN(NODE *R_min_node){ //Use the minimum of right to instead of location of delete_node
    if (R_min_node->left != NULL){
        return TREE_RIGHT_MIN(R_min_node->left);
    }else{
        return R_min_node;
    }
}

void RB_TRANSPLANT(RBroot *root,NODE *node,NODE*child){
    if (rb_parent(node) == NULL){
        root->node = child; 
    }else if (rb_parent(node)->left == node){
        rb_parent(node)->left = child;
    }else{
        rb_parent(node)->right = child;
    }
    if (child != NULL){
        rb_parent(child) = rb_parent(node);
    }   
}

void RB_DELETE_FIXUP(RBroot *root,NODE *x){
    NODE *w;
    while (x != root->node && rb_is_black(x)){
        if (x == rb_parent(x)->left){
            w = rb_parent(x)->right;
            if (rb_is_red(w)){
                rb_set_black(x);
                rb_set_red(rb_parent(x));
                LEFT_ROTATE(root,rb_parent(x));  //case1
                w = rb_parent(x)->right;
            }
            if (rb_is_black(w->left) && rb_is_black(w->right)){
                rb_set_red(w);
                x = rb_parent(x);
            }else if (rb_is_black(w->right)){
                rb_is_black(w->left);
                rb_set_red(w);
                RIGHT_ROTATE(root,w);
                w = rb_parent(x)->right;
            }
            w->color = rb_parent(x)->color;
            rb_set_black(rb_parent(x));
            rb_set_black(w->right);
            LEFT_ROTATE(root,rb_parent(x));
            x = root->node;
        }else{
            w = rb_parent(x)->left;
            if (rb_is_red(w)){
                rb_set_black(x);
                rb_set_red(rb_parent(x));
                RIGHT_ROTATE(root,rb_parent(x));
                w = rb_parent(x)->left;
            }
            if (rb_is_black(w->left) && rb_is_black(w->right)){
                rb_set_red(w);
                x = rb_parent(x);
            }else if (rb_is_black(w->left)){
                rb_is_black(w->right);
                rb_set_red(w);
                LEFT_ROTATE(root,w);
                w = rb_parent(x)->left;
            }
            w->color = rb_parent(x)->color;
            rb_set_black(rb_parent(x));
            rb_set_black(w->left);
            RIGHT_ROTATE(root,rb_parent(x));
            x = root->node;
        }
    }
    rb_set_black(x);
}
