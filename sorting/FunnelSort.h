//
// Created by Crystina on 30/9/2020.
//

#ifndef CODEBASE_FUNNELSORT_H
#define CODEBASE_FUNNELSORT_H

#include <vector>
#include "MergeSort.h"

class KMerger {
private:
    int k;
    std::vector<int*> buffers;  // each with size 2 * (k)^(3/2)
    std::vector<KMerger*> submergers;   // a list of (k)^(1/2) mergers

public:
    KMerger(int k);
    void merge();
};


class FunnelSort: public MergeSort {
private:
    int k;

public:
    virtual void sort();
    void sort(int *arr, int arrSize);
};


#endif //CODEBASE_FUNNELSORT_H
