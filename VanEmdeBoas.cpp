//
// Created by Crystina on 26/9/2020.
//

#include <math.h>
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

int VanEmdeBoas::generate_index(int x, int y) { return x * (int)ceil(sqrt(universe_size)) + y; }

void VanEmdeBoas::insert(int key) {
    if (min == -1) { min = key; max = key; return; }    // if the tree was empty

    if (key < min) { swap(min, key); }  // ??

    if (universe_size > 2) {
        int cluster_id = high(key), subkey = low(key);
        if (clusters[cluster_id]->min == -1) {
            summary->insert(cluster_id);
            clusters[cluster_id]->min = subkey;
            clusters[cluster_id]->max = subkey;
        } else {
            clusters[cluster_id]->insert(subkey);
        }
    }

    if (key > max) { max = key; }  // ??
}

bool VanEmdeBoas::isMember(int key) {
    if (universe_size < key) { return false; }
    if (min == key || max == key) { return true; }
    if (universe_size == 2) { return false; }

    return clusters[high(key)]->isMember(low(key));
}

int VanEmdeBoas::successor(int key) {
    if (universe_size == 2) {
        if (key == 0 && max == 1) { return 1; }
        return -1;
    }

    if (min != -1 && key < min) { return min; }

    int cluster_id = high(key), subkey = low(key);

    int max_in_cluster = clusters[cluster_id]->max;
    if (max_in_cluster != -1 && subkey < max_in_cluster) {
        int offset = clusters[cluster_id]->successor(subkey);
        return generate_index(cluster_id, offset);
    }

    // why would we need to check the next cluster?
    int succ_cluster_id = summary->successor(cluster_id);  // check next cluster
    if (succ_cluster_id == -1) { return -1; }   // no next cluster

    int offset = clusters[cluster_id]->min;
    return generate_index(succ_cluster_id, offset);
}

int VanEmdeBoas::predecessor(int key) { return false; }

void VanEmdeBoas::remove(int key) {
    if (min == max) { min = -1; max = -1; return }
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

    int cluster_id, subkey = high(key), low(key);
    clusters[cluster_id)]->remove(subkey);

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