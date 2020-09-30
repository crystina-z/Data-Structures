//
// Created by Crystina on 30/9/2020.
// https://www.geeksforgeeks.org/merge-sort/
//

#ifndef CODEBASE_MERGESORT_H
#define CODEBASE_MERGESORT_H

#include "SortBase.h"

class MergeSort: public Sort{
private:
    void merge(int *arr, int l, int mid, int r);

public:
    MergeSort();
    MergeSort(int *arr, int arrSize);

    void sort();    // parent's virtual function
    void sort(int *arr, int arrSize, int l = -1, int r = -1);
};


#endif //CODEBASE_MERGESORT_H
