//
// Created by Crystina on 26/9/2020.
// reference: https://www.geeksforgeeks.org/van-emde-boas-tree-set-3-successor-and-predecessor
//
#ifndef CODEBASE_VANEMDEBOAS_H
#define CODEBASE_VANEMDEBOAS_H

#include <vector>
//#include <bits/stdc++.h>
using namespace std;

class VanEmdeBoas {
public:
    int universe_size;
    int max;
    int min;
    VanEmdeBoas* summary;
    vector<VanEmdeBoas*> clusters;

    int high(int x);    // return cluster id
    int low(int x);     // return pos of x in its cluster
    int generate_index(int x, int y);   // return the value from cluster number and position

    VanEmdeBoas(int size);
    int minimum();
    int maximum();
    void insert(int key);
    bool isMember(int key);
    int successor(int key);
    int predecessor(int key);
    void remove(int key);
};


#endif //CODEBASE_VANEMDEBOAS_H
