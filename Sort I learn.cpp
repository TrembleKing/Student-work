#include<iostream>
#include<string.h>
#include<time.h>
#define SWAP(a,b){int tmp; tmp = a; a = b; b = tmp;}
#define MaxSize 10  //change the value and test efficiency

void Insert_array(int ar[]);
//Insert sort 插入排序
void Insert_Sort(int ar[]);
void printf_list(int ar[],int,int);
//Select sort 选择排序
void Select_Sort(int ar[]);
//Bubble sort 冒泡排序
void Bubble_Sort(int ar[],int);
//Shell's sort希尔排序
void Shell_Sort(int ar[]);
//Heap sort   堆排序
void Build_Heap_Sort(int ar[]);
void Heap_Sort(int ar[],int,int);
//Quick sort  快速排序
int Quick_Sort(int ar[],int,int);
void Build_Quick_Sort(int ar[],int,int);
//Quick sort  用qsort函数 快速排序
int compare_1(const void *,const void *);
//Merge sort  归并排序
void Return_Sort(int ar[],int,int);
void Merge(int ar[],int,int,int);
//Count sort  计数排序
void Count_Sort(int ar[]);

int main(){
    int array[MaxSize+1];
    srand(time(NULL));

    time_t start,end; 
    Insert_array(array);
    start = time(NULL);
    Insert_Sort(array);
    end = time(NULL);
    printf_list(array,end,start);

    Insert_array(array);
    start = time(NULL);
    Select_Sort(array);
    end = time(NULL);
    printf_list(array,end,start);

    Insert_array(array);
    start = time(NULL);
    Shell_Sort(array);
    end = time(NULL);
    printf_list(array,end,start);

    Insert_array(array);
    start = time(NULL);
    Build_Heap_Sort(array);
    end = time(NULL);
    printf_list(array,end,start);
    
    Insert_array(array);
    start = time(NULL);
    Build_Quick_Sort(array,0,MaxSize-1);
    end = time(NULL);
    printf_list(array,end,start);
    
    Insert_array(array);
    start = time(NULL);
    qsort(array,MaxSize,sizeof(int),compare_1);
    end = time(NULL);
    printf_list(array,end,start);

    Insert_array(array);
    start = time(NULL);
    Return_Sort(array,0,MaxSize-1);
    end = time(NULL);
    printf_list(array,end,start);

    Insert_array(array);
    start = time(NULL);
    Bubble_Sort(array,MaxSize);
    end = time(NULL);
    printf_list(array,end,start);

    Insert_array(array);
    start = time(NULL);
    Count_Sort(array);
    end = time(NULL);
    printf_list(array,end,start);

    system("pause");
}

void Insert_array(int ar[]){
    for (int i = 0; i < MaxSize; ++i)
        ar[i] = rand()%100;
}

void Return_Sort(int ar[],int low,int high){
    if (low < high){
        int mid;
        mid = (low+high)/2;
        Return_Sort(ar,low,mid);
        Return_Sort(ar,mid+1,high);
        Merge(ar,low,mid,high);
    }
}

void Merge(int ar[],int low,int mid,int high){
    int b[MaxSize];
    int i,j,k;
    for (i = low; i <= high; ++i){
        b[i] = ar[i];
    }
    for (i = k = low,j = mid+1; i <= mid && j <= high;k++){
        if (b[i] < b[j]){
            ar[k] = b[i];
            ++i;
        }else{
            ar[k] = b[j];
            ++j;
        }
    }
    while (i <= mid){
        ar[k] = b[i];
        ++k;++i;
    }
    while (j <= high){
        ar[k] = b[j];
        ++k;++j;
    }
}

int compare_1(const void *left,const void *right){
    int *p1 = (int *)left;
    int *p2 = (int *)right;
    if(*p1 > *p2){
        return 1;
    }else if (*p1 < *p2){
        return -1;
    }else{
        return 0;
    }
}

void printf_list(int ar[],int end,int start){
    for (int i = 0; i < MaxSize; ++i)
        printf("%d ",ar[i]);
    printf("use time is %d.",end-start);
    printf("\n------------------------------------\n");
}

void Insert_Sort(int ar[]){
    int i,j,key;
    for (i = 1; i < MaxSize; ++i){
        j = i - 1;
        key = ar[i];
        while (j>=0 && key < ar[j]){
            ar[j+1] = ar[j];
            j = j - 1;
        }
        ar[j+1] = key;
    }
}

void Select_Sort(int ar[]){
    int i,j;
    for (i = 0; i < MaxSize-1; ++i){
        j = i;
        for (int k = i+1; k < MaxSize; ++k){
            if (ar[j] > ar[k]){
                j = k;
            }
        }
        if (j != i){
            SWAP(ar[j],ar[i]);
        }
    }
}

void Bubble_Sort(int ar[],int Size){
    int i,j;
    bool change;
    for (i = Size-1,change = true; i>0 && change == true; --i){
        change = false;
        for (j = 0; j < i ; ++j){
            if (ar[j]>ar[j+1]){
                SWAP(ar[j],ar[j+1]);
                change = true;
            }
        }
    }
}

void Shell_Sort(int ar[]){
    int i,j,gep,key;
    for (gep = MaxSize>>1; gep>0; gep>>=1){
        for (i = gep; i < MaxSize; ++i){
            key = ar[i];
            for (j = i - gep; j >= 0 ; j = j-gep){
                if (key < ar[j]){
                    ar[j + gep] = ar[j];
                }else{
                    break;
                }
            }
            ar[j + gep] = key;
        }
    }
}

void Heap_Sort(int ar[],int asort,int Length){
    int dad = asort;
    int son = dad*2+1;
    while(son < Length){    
        if (son+1 < Length && ar[son] < ar[son+1]){
            son++;
        }
        if (ar[son] > ar[dad]){
            SWAP(ar[son],ar[dad]);
            dad = son;
            son = dad*2+1;
        }else{
            break;
        }
    }
}

void Build_Heap_Sort(int ar[]){
    for (int i = MaxSize>>1-1; i >=0 ; --i){
        Heap_Sort(ar,i,MaxSize);
    }
    SWAP(ar[0],ar[MaxSize-1]);
    for (int i = MaxSize-1; i > 0 ; --i){
        Heap_Sort(ar,0,i);
        SWAP(ar[0],ar[i-1]);
    }
}

void Build_Quick_Sort(int ar[],int left,int right){
    int Qsort;
    if (right > left){
        Qsort = Quick_Sort(ar,left,right);
        Build_Quick_Sort(ar,left,Qsort-1);
        Build_Quick_Sort(ar,Qsort+1,right);
    }
}

int Quick_Sort(int ar[],int left,int right){
    int i,k;
    for(i = k = left; i < right; ++i){
        if (ar[i] < ar[right]){
            SWAP(ar[i],ar[k]);
            k++;
        }
    }
    SWAP(ar[k],ar[right]);
    return k;   
}

void Count_Sort(int ar[]){
    int ar2[MaxSize],C[100];
    int i;
    memset(C,0,sizeof(C));     //not int
    for (i = 0; i < MaxSize; ++i){
        ar2[i] = ar[i];
    }
    for (i = 0; i < MaxSize; ++i){
        C[ar2[i]]++;
    }
    for (i = 1; i < 100; ++i){
        C[i] = C[i] + C[i-1];
    }

    for (i = MaxSize-1; i >= 0 ; --i){
        ar[C[ar2[i]]-1] = ar2[i];
        C[ar2[i]]--; 
    }
}































