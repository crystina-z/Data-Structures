//
// Created by Crystina on 30/9/2020.
//

#ifndef CODEBASE_SORT_H
#define CODEBASE_SORT_H


class Sort {
protected:
    int *arr;
    int arrSize;

public:
    Sort();
    Sort(int *arr, int arrSize);

    virtual void sort();
    void print();
    void print(int *arr, int arrSize);
};


#endif //CODEBASE_SORT_H
