//
// Created by Crystina on 26/9/2020.
//

#include <math>
#include "VanEmdeBoas.h"

VanEmdeBoas::VanEmdeBoas(int size): universe_size(size) {
    min = -1;
    max = -1;

    if (size <= 2) {
        summary = nullptr;
        clusters = vector<VanEmdeBoas*>(0, nullptr);
        return;
    }

    int sqrt_size = ceil(sqrt(size));  // == no_clusters and sub_size
    summary = new VanEmdeBoas(sqrt_size);
    clusters = vector<VanEmdeBoas*>(sqrt_size, nullptr);
    for (int i = 0; i < sqrt_size; i++) {
        clusters[i] = new VanEmdeBoas(sqrt_size);
    }
}

int VanEmdeBoas::high(int x) { return x / ceil(sqrt(universe_size)); }

int VanEmdeBoas::low(int x) { return x % ceil(sqrt(universe_size)); }

int VanEmdeBoas::generate_index(int x, int y) { return x * ceil(sqrt(universe_size)) + y; }

void VanEmdeBoas::insert(int key) {
    if (min == -1) { min = key; max = key; return; }    // if the tree was empty

    if (key < min) { swap(min, key); }  // ??

    if (universe_size > 2) {
        int cluster_id= high(key), subkey = low(key);
        if (clusters[cluster_id].min == -1) {
            insert(summary, cluster_id);
            clusters[cluster_id].min = subkey;
            clusters[cluster_id].max = subkey;
        } else {
            clusters[cluster_id].insert(subkey);
        }
    }

    if (key > max) { max = key; }  // ??
}

bool VanEmdeBoas::isMember(int key) {
    if (universe_size < key) { return false; }
    if (min == key || max == key) { return true; }
    if (universe_size == 2) { return false; }

    return clusters[high(key)].isMember(low(key));
}
