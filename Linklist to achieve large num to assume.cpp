#include "storage.h"

//Using linklist to achieve large num to assume.  
int main(){
    int a,b;
    node phead = NULL,ptail = NULL;
    node phead_two = NULL,ptail_two = NULL;
    node pnewhead = NULL,pnewtail = NULL;

    std::cout << "Please enter your first num:";
    while (scanf("%d",&a)!=EOF){
        First_insert_node(&phead,&ptail,a);
    };
    std::cout << "Please enter your next num:";
    while (scanf("%d",&b)!=EOF){
        Second_insert_node(&phead_two,&ptail_two,b);
    };
    //printf_Lnode(phead);
    //printf_Lnode(phead_two);
    Result_node(&phead,&phead_two,&pnewhead,&pnewtail); 
    printf("\n-------------------------------\n");
    printf("Well the result is:");
    printf_Lnode(pnewhead);
    printf("\n-------------------------------\n");
    
    system("pause");
}

void First_insert_node(node *pphead,node *pptail,int vals){ 
    node pnew = (node)calloc(1,sizeof(Lnode));
    pnew->data = vals;
    if (*pphead == NULL){
        *pphead = pnew;
        *pptail = pnew;
    }else{
        pnew->pNext = *pphead;
        *pphead = pnew;
    }
}

void Second_insert_node(node *pphead_two,node *pptail_two,int vals){  //计数时进行逆置采用头插法
    node pnew= (node)calloc(1,sizeof(Lnode));
    pnew->data = vals;
    if (*pphead_two == NULL){
        *pphead_two = pnew;
        *pptail_two = pnew;
    }else{
        pnew->pNext = *pphead_two;
        *pphead_two = pnew;
    }
}

void printf_Lnode(node phead){
    while (phead){
        printf("%d",phead->data);
        phead = phead->pNext;
    }
}

void Result_node(node *pphead,node *pphead_two,node *ppRhead,node *ppRtail){
    int jin;
    node pp = *pphead; node pp2 = *pphead_two;  
    while (pp || pp2){                                        
        node pnew = (node)calloc(1,sizeof(Lnode));            
        if (*ppRhead == NULL){                               
            jin = ((pp)->data + (pp2)->data)/10;              
            pnew->data = ((pp)->data + (pp2)->data)%10;       
            *ppRhead = pnew;                                  
            *ppRtail = pnew;
            *pphead = pp->pNext; *pphead_two = pp2->pNext;    
            pp = *pphead; pp2 = *pphead_two;                  
        }else{
            if (pp && pp2){                                   
                pnew->data = ((pp)->data + (pp2)->data + jin)%10;   
                jin = ((pp)->data + (pp2)->data + jin)/10;          
                *pphead = pp->pNext; *pphead_two = pp2->pNext;     
                pp = *pphead; pp2 = *pphead_two;  
            }else{
                if (pp){
                    pnew->data = (jin!=0) ? (pp->data+jin)%10:(pp->data)%10;  
                    jin = ((pp->data) + jin)/10;
                    *pphead = pp->pNext;
                    free(pp);                                 
                    pp = *pphead;                            
                }else if(pp2){
                    pp2->data = (jin!=0) ? (pp2->data+jin):(pp2->data);        
                    pnew->data = pp2->data;
                    jin = ((pp2->data) + jin)/10;
                    *pphead_two = pp2->pNext; 
                    free(pp2);
                    pp2 = *pphead_two;
                }
            }
            pnew->pNext = *ppRhead;
            *ppRhead = pnew;
        }
    }
    if (jin != 0){
        node pnew = (node)calloc(1,sizeof(Lnode));                                           
        pnew->data = jin;
        pnew->pNext = *ppRhead;
        *ppRhead = pnew;
    }
}