#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct{
    int* val;
    int dim;
    int* shape;
    int size;
}NeuArray;

NeuArray* create_NeuArray(const int* shape, int dim){
    NeuArray* narr=(NeuArray*)malloc(sizeof(NeuArray));
    if(narr==NULL){
        printf("DMA Failed | NeuArray\n");
    }
    narr->shape=(int*)malloc(dim*sizeof(int));
    if(narr->shape==NULL){
        printf("DMA Failed | NeuArray Shape\n");
    }
    narr->dim=dim;
    narr->size=1;
    for(int i=0;i<dim;i++){
        narr->shape[i]=shape[i];
        narr->size*=shape[i];
    }
    narr->val=(int*)malloc(narr->size*sizeof(int));
    if(narr->shape==NULL){
        printf("DMA Failed | NeuArray Values\n");
    }
    return narr;
}

int len(const int* shape,int dim){
    int s=1;
    for(int i=0;i<dim;i++){
        s*=shape[i];
    }
    return s;
}

void print_NeuArray(const NeuArray* narr){
    if(narr==NULL){
        printf("Empty Array\n");
        return;
    }
    printf("NeuArray |  Shape : (");
    for(int i=0;i<narr->dim;i++){
        printf("%d",narr->shape[i]);
        if(i<narr->dim-1){
            printf(", ");
        }
    }
    printf(") |  Size : %d\n\n",narr->size);
    for(int i=0;i<narr->size;i++){
        printf("%d",narr->val[i]);
        if((i+1)%narr->shape[narr->dim-1]==0){
            printf("\n");
        }
        else{
            printf(" ");
        }
    }
}

void free_NeuArray(NeuArray* narr){{
    if(narr!=NULL){
        free(narr->shape);
        free(narr->val);
        free(narr);
    }
}}

NeuArray* zeros(const int* shape, int dim){
    NeuArray *narr = create_NeuArray(shape,dim);
    for (int i = 0; i < narr->size; i++) {
        narr->val[i] = 0;
    }
    return narr;
}

NeuArray* ones(const int* shape, int dim){
    NeuArray *narr = create_NeuArray(shape,dim);
    for (int i = 0; i < narr->size; i++) {
        narr->val[i] = 1;
    }
    return narr;
}

NeuArray* eye(const int* shape, int dim){
    NeuArray *narr = create_NeuArray(shape,dim);
    int total_size=len(shape,dim);
    int diagonal_step=1+shape[dim-1],diagonal=0;
    for(int i=0;i<total_size;i++){
        if(i==diagonal && diagonal<total_size){
            narr->val[i]=1;
            diagonal+=diagonal_step;
        }else{
            narr->val[i]=0;
        }
    }
    return narr;
}

int check_shape(const NeuArray* n1,const NeuArray* n2){
    if(n1->dim != n2->dim || n1->size!=n2->size){
        return 0;
    }
    for(int i=0;i<n1->dim;i++){
        if(n1->shape[i]!=n2->shape[i]){
            return 0;
        }
    }
    return 1;
}

NeuArray* add(const NeuArray* n1, const NeuArray* n2){
    if(!check_shape(n1,n2)){
        fprintf(stderr,"Error : Shape Mismatch\n");
        return NULL;
    }
    NeuArray* res= create_NeuArray(n1->shape,n1->dim);
    if(res==NULL){
        printf("DMA Failed | Result NeuArray doesn't exist\n");
    }
    for(int i=0;i<n1->size;i++){
        res->val[i]=n1->val[i]+n2->val[i];
    }
    return res;
}