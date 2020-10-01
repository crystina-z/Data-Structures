//
// Created by Crystina on 26/9/2020.
//

#include <math.h>
#include <assert.h>
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

int VanEmdeBoas::high(int x) { return x / (int)ceil(sqrt(universe_size)); }

int VanEmdeBoas::low(int x) { return x % (int)ceil(sqrt(universe_size)); }

int VanEmdeBoas::generate_index(int x, int y) {
    assert(x >= 0 && y >= 0);
    int i = x * (int)ceil(sqrt(universe_size)) + y;
    return i;
}

void VanEmdeBoas::insert(int key) {
    if (min == -1) { min = key; max = key; return; }    // if the tree was empty

    if (key < min) { swap(min, key); }  // lazy propagation
    // temporarily store the new min here, and continue with the old key

    if (universe_size > 2) {
        int cluster_id = high(key), subkey = low(key);  // recursively go deep
        if (clusters[cluster_id]->min == -1) {  // the cluster was empty
            summary->insert(cluster_id);
            clusters[cluster_id]->min = subkey;
            clusters[cluster_id]->max = subkey;
        } else {    // the cluster was not empty
            clusters[cluster_id]->insert(subkey);
        }
    }

    if (key > max) { max = key; }
    // CASE 1: current node is not leaf: max value is always already stored in sub-trees;
    // CASE 2: current node is leaf: if such condition holds, then max must be equal to the min before
}

bool VanEmdeBoas::isMember(int key) {
    if (universe_size < key) { return false; }
    if (min == key || max == key) { return true; }
    if (universe_size == 2) { return false; }

    return clusters[high(key)]->isMember(low(key));
}

int VanEmdeBoas::successor(int key) {
    // base cases
    if (universe_size == 2) {
        if (key == 0 && max == 1) { return 1; }
        return -1;
    }
    if (min != -1 && key < min) { return min; } // TODO: when would we reach here?
    // Crystina: if (key > max) { return -1; } ?

    // if the key falls in the range (min, max): find its cluster and then search there
    int cluster_id = high(key), subkey = low(key);

    int max_in_cluster = clusters[cluster_id]->max;
    if (max_in_cluster != -1 && subkey < max_in_cluster) { // if the cluster which the KEY belongs to is not empty
        int offset = clusters[cluster_id]->successor(subkey);
        return generate_index(cluster_id, offset);
    }

    // if not found: the key is not in current cluster
    // BUT THEN WHY WOULD IT BE ASSIGNED TO THIS CLUSTER?
    int succ_cluster_id = summary->successor(cluster_id);  // check next cluster
    if (succ_cluster_id == -1) { return -1; }   // no next cluster

    int offset = clusters[succ_cluster_id]->min;
    return generate_index(succ_cluster_id, offset);
}

int VanEmdeBoas::predecessor(int key) {
    if (universe_size == 2) {
        if (key == 1 && min == 0) { return 0; }
        return -1;
    }
    if (max != -1 && key > max) { return max; }

    int cluster_id = high(key), subkey = low(key);

    int min_cluster = clusters[cluster_id]->min;
    if (min_cluster != -1 && subkey > min_cluster) {
        int offset = clusters[cluster_id]->predecessor(subkey);
        return generate_index(cluster_id, offset);
    }

    int pred_cluster = summary->predecessor(cluster_id);
    if (pred_cluster == -1) {
        if (min != -1 && key > min) { return min; }
        return -1;
    }

    int offset = clusters[pred_cluster]->max;
    return generate_index(pred_cluster, offset);
}

void VanEmdeBoas::remove(int key) {
    if (min == max) { min = -1; max = -1; return; }
    if (universe_size == 2) {
        if (key == 0) { min = 1; }
        else { min = 0; }
        max = min;
        return;
    }

    if (key == min) {
        int first_cluster_id = summary->min;
        // but we havn't remove anything? and won't key be overwritten??
        key = generate_index(first_cluster_id, clusters[first_cluster_id]->min);
        min = key;
    }

    int cluster_id = high(key), subkey = low(key);
    clusters[cluster_id]->remove(subkey);

    if (clusters[cluster_id]->min == -1) {
        summary->remove(cluster_id);
        if (key == max) {
            int max_in_summary = summary->max;
            if (max_in_summary == -1) { max = min; }
            else {
                max = generate_index(max_in_summary, clusters[cluster_id]->max);
            }
        }
        return;
    }

    if (key == max) {
        max = generate_index(cluster_id, clusters[cluster_id]->max);
    }
}

void VanEmdeBoas::print() {
    if (min == -1) return;

    printf("[MIN: %i MAX: %i]\t", min, max);

    printf("%i ", min);
    int cur = min;
    while ((cur = successor(cur)) != -1) {
        printf("%i ", cur);
    }
    printf("\n");
}

int main() {
    printf("::VEB::\n");
    VanEmdeBoas veb(10);

    veb.insert(10);
    veb.insert(4);
    veb.insert(8);
    veb.insert(3);
    veb.insert(2);

    veb.insert(6);
    veb.insert(1);
    veb.insert(7);
    veb.insert(5);
    veb.insert(9);

    veb.print();
}