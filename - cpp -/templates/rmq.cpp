#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//RMQ from josh
struct RMQ  {
    vector<int> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    int *mask, *sparse_table;
    int op(int x, int y) { //update this method to determine what value we are trying to find. Currently set to minimum (return index of minimum element)
        return elements[x] < elements[y] ? x : y;
    }
    int lsb(int x) {return x & -x;}
    int msbi(int x) {return 31 - __builtin_clz(x);}
    int small_query(int r, int size = block_size) {return r - msbi(mask[r] & ((1<<size)-1));}
    RMQ() {} //need this to satisfy master goon's requirements
    RMQ (const vector<int>& input) {build(input);}
    void build (const vector<int>& input) {
        elements = input;
        n = input.size();
        mask = new int[n];
        sparse_table = new int[n];
        memset(mask, 0, n);
        memset(sparse_table, 0, n);
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            while(curr_mask > 0 && op(i, i - msbi(lsb(curr_mask))) == i) curr_mask ^= lsb(curr_mask);
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        for(int i = 0; i < n/block_size; i++) sparse_table[i] = small_query(block_size * i + block_size - 1);
        for(int j = 1; (1<<j) <= n/block_size; j++) for(int i = 0; i + (1<<j) <= n / block_size; i++) sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
    }
    int _query(int l, int r) {  //queries range [l, r]
        if(r - l + 1 <= block_size) {
            return small_query(r, r - l + 1);
        }
        int ans = op(small_query(l + block_size - 1), small_query(r)); 
        int x = l / block_size + 1;
        int y = r / block_size - 1;
        if(x <= y) {
            int j = msbi(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }
        return ans;
    }
    int query(int l, int r) {   //queries range [l, r)
        r --;
        // return _query(l, r);              //return the index with minimum value
        return elements[_query(l, r)];      //return the minimum value
    }
};