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

int NeuArray_len(const int* shape,int dim){
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
