#include <stdio.h>
#include "neuarray.h"


int main() {
    printf("\n\n\n");
    int shape[2] = {4, 3};
    NeuArray *array = create_NeuArray(shape,2);
    for (int i = 0; i < array->size; i++) {
        array->val[i] = i + 1;
    }
    printf("Array created and printed:\n");
    print_NeuArray(array);
    free_NeuArray(array);
    printf("\n\n");
    return 0;
}