//
// Created by Crystina on 30/9/2020.
//

#include <stdio.h>
#include "SortBase.h"

Sort::Sort():arr(nullptr), arrSize(0) {}

Sort::Sort(int *arr, int arrSize): arr(arr), arrSize(arrSize) {}

void Sort::print() {
    print(arr, arrSize);
}

void Sort::print(int* arr, int size) {
    for (int i = 0; i < size; i += 1) { printf("%d ", arr[i]); }
    printf("\n");
}


void Sort::sort() {}