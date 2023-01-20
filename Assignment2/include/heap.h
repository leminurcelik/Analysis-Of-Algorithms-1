//BLG 335E ANALYSIS OF ALGORITHMS 1 HOMEWORK 2
//Leminur Çelik
//150190085
#ifndef _H
#define _H

#include <string>
#include <vector>

using namespace std;

class Heap{
    private:
        vector<double> heap;
        int maxSize;
        int size;
        int left;
        int right;
        int parent;

    public:
        Heap();
        void max_heapify(int);
        void build_max_heap();
        void heap_sort();
        void heap_increase_key(int);
        void heap_insert(double);
        double calculate_mean();
        double calculate_std();
        double minimum();
        double calculate_firstq();
        double calculate_median();
        double calculate_thirdq();
        double maximum();
        void setSize();
        int getSize();
};
#endif