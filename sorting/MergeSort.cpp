//
// Created by Crystina on 30/9/2020.
//

#include <stdio.h>
#include <assert.h>
#include <cstring>

#include "MergeSort.h"


MergeSort::MergeSort(): Sort{} {}

MergeSort::MergeSort(int *arr, int arrSize): Sort{arr, arrSize} {}

void MergeSort::merge(int *arr, int l, int mid, int r) {
    int tmp[r-l];
    int left_i = l, right_i = mid, sort_i = 0;
    while (left_i < mid or right_i < r) {
        if ((right_i >= r) || (left_i < mid && arr[left_i] < arr[right_i])) {
            tmp[sort_i] = arr[left_i];
            left_i += 1;
        } else {
            assert(right_i < r); // , "Right index exceeding the right boundary");
            tmp[sort_i] = arr[right_i];
            right_i += 1;
        } // if
        sort_i += 1;
    } // while
    for (int i = 0; i < (r - l); i++) { arr[l+i] = tmp[i]; }
}

void MergeSort::sort() {
    sort(arr, arrSize);
}

void MergeSort::sort(int *arr, int arrSize, int l, int r) {
    if (arrSize < 2) return;

    if (l == -1) { l = 0; }
    if (r == -1) { r = arrSize; }

    int mid = (l + r) / 2;
    sort(arr, mid - l, l, mid);
    sort(arr, r - mid, mid, r);
    merge(arr, l, mid, r);
}


//int main() {
//    printf("::SORT::\n");
//    int test[] = {2, 33, 5, 77, 100, 9, 10, 8, 99};
//    MergeSort obj(test, 9);
//
//    printf("Before sorting: \n");
//    obj.print();
//    obj.sort();
//
//    printf("After sorting: \n");
//    obj.print();
//}
