#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int *arr = malloc(SIZE * sizeof(int));


    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand();
    }

    arr[SIZE] = 42;  

    qsort(arr, SIZE, sizeof(int), compare);

    printf("Sorted first element: %d\n", arr[0]);

    free(arr);
    return 0;
}
