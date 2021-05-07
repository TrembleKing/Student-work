#include "RBTREE.H" //This redblack tree only Insert and fixed up,not show how to delect.

int main(){
    int array[] = {16,3,7,11,9,26,18,14,15};    
    int i,ilen = LENGTH(array);
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
    system("pause");
}

void print_RBtree(RBroot *root){
    print_head_RBtree(root->node);
    // printf("\n-------------------------\n");
    // print_mid_RBtree(root->node);
    // printf("\n-------------------------\n");
    // print_back_RBtree(root->node);
}

char color(NODE *node){
    char p;
    p = rb_is_black(node) ? 'B':'R';
    return p;
}

const char *parent_child(NODE *node){
    const char *p = (rb_parent(node)->left == node) ? "left":"right";
    return p;
}

void print_head_RBtree(NODE *node){
    if (node){
        if (rb_parent(node) != NULL)
            std::cout << node->key <<"<"<<color(node)<<">\t"<<rb_parent(node)->key<<"'s\t"<<parent_child(node)<<" child."<<std::endl;
        print_head_RBtree(node->left);
        print_head_RBtree(node->right);
    }
}

// void print_mid_RBtree(NODE *node){     //same as print_head_RBtree
//     if (node){                       
//         print_mid_RBtree(node->left);  //amend this line as head_printf
//         printf("%d ",node->key);
//         print_mid_RBtree(node->right);
//     }
// }

// void print_back_RBtree(NODE *node){    //same
//     if (node){
//         print_back_RBtree(node->left);
//         print_back_RBtree(node->right);
//         printf("%d ",node->key);
//     }
// }

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
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL){
        root->node = y;
    }else{
        if (x == x->parent->right){
            x->parent->right = y;
        }else {
            x->parent->left = y;
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
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL){
        root->node = y;
    }else{
        if (x == x->parent->left){
            x->parent->left = y;
        }else{
            x->parent->right = y;
        }
    }
    y->left = x;
    x->parent = y;
}
