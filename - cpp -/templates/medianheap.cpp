#include <bits/stdc++.h>
using namespace std;

//not really tested apart from 1 leetcode problem. 
//multiset is pretty slow i think, replace with map to make faster?

template <typename T>
struct MedianHeap {
    //left.size() >= right.size()
    multiset<T> left;   //below and equal to median
    multiset<T> right;  //above median

    void balance() {
        while(right.size() < left.size()) right.insert(*left.rbegin()), left.erase(left.find(*left.rbegin()));
        while(left.size() < right.size()) left.insert(*right.begin()), right.erase(right.begin());
    }

    void insert(T x) {
        if (size() == 0 || x <= *left.rbegin()) left.insert(x);
        else right.insert(x);
        balance();
    }

    void remove(T x) {
        if (left.count(x)) left.erase(left.find(x));
        else if (right.count(x)) right.erase(right.find(x));
        balance();
    }

    size_t size() {
        return left.size() + right.size();
    }

    T getMedian() {
        if(size() == 0) return 0;
        return *left.rbegin();
    }
};