#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1923D

//for each slime, it either has to be eaten from the left, or from the right. If it's eaten 
//from the left, then it's best to 'power up' one slime to it's left such that it can come and
//eat the slime in question. 

//given the subarray of slimes to the left of slime i, it's possible to only use slimes in this subarray
//to eat i if the subarray sum is greater than the size of i, and there is more than 1 distinct value
//or the maximum value is greater than the size of i. We can binary search for the minimum possible size 
//of subarray to the left and right. 

template<typename T>
struct RMQ  {
    vector<T> elements;
    int n;
    static const int block_size = 30; // block size. adjust accordingly
    vector<int> mask;
    vector<int> sparse_table;

    //type of function the table is storing. Currently, it stores the minimum because it returns the minimum index 
    int op(int x, int y) { 
        return elements[x] < elements[y] ? x : y;
    }

    int least_significant_bit(int x) {
        return x & -x;
    }
    
    int most_significant_bit_index(int x) {
        return 31 - __builtin_clz(x);
    }

    // answers the smaller queries given size is <= b. elements[r-size+1..r] using masks
    int small_query(int r, int size = block_size) {
        //get only the 'size' least significant bits from the mask
        //with that, get the most significant set bit
        int dist_from_r = most_significant_bit_index(mask[r] & ((1<<size)-1));
        return r - dist_from_r;
    }

    RMQ() {} //need this to satisfy master goon's requirements

    //constructor
    RMQ (const vector<T>& input): elements(input), n(input.size()), mask(n), sparse_table(n) {
        //construct masks for all elements
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            //shift mask by 1, keeping only the 'b' least significant bits
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            //while the current value is smaller than the value least significant bit of curr_mask
            //update that 0 into a 1. 
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
                curr_mask ^= least_significant_bit(curr_mask);
            }
            //the least bit will always be minimum in that small bit
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        //construct sparse table for the n / b blocks
        //lower level
        for(int i = 0; i < n/block_size; i++) {
            sparse_table[i] = small_query(block_size * i + block_size - 1);
        }
        //rest of the levels
        for(int j = 1; (1<<j) <= n/block_size; j++) {
            for(int i = 0; i + (1<<j) <= n / block_size; i++) {
                sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
            }
        }

    }

    //query(l,r) returns the element from the minimum of v[l..r)
    //can be updated to return index by changing what we are returning
    T query(int l, int r) {
        //make it exclusive :)
        r --;

        //query size <= b
        if(r - l + 1 <= block_size) {
            return elements[small_query(r, r - l + 1)];
            // return small_query(r, r- l + 1);
        }

        //work out the small parts of the answer
        //it's ok for it to overlap and because size > b, we can freely let size of both sides be b
        int ans = op(small_query(l + block_size - 1), small_query(r)); 

        //blocks to query over
        int x = l / block_size + 1;
        int y = r / block_size - 1;

        if(x <= y) {
            int j = most_significant_bit_index(y - x + 1);
            ans = op(ans, op(sparse_table[n / block_size * j + x], sparse_table[n / block_size * j + y - (1 << j) + 1]));
        }

        return elements[ans];
        // return ans;
    }

    //alternative way to build if can't easily do with constructor or want to reuse
    void build (const vector<T>& input) {
        elements = input;
        n = input.size();
        mask.assign(n,0);
        sparse_table.assign(n,0);
        
        //construct masks for all elements
        int curr_mask = 0;
        for(int i = 0; i < n; i++) {
            //shift mask by 1, keeping only the 'b' least significant bits
            curr_mask = (curr_mask<<1) & ((1<<block_size)-1);
            //while the current value is smaller than the value least significant bit of curr_mask
            //update that 0 into a 1. 
            while(curr_mask > 0 && op(i, i - most_significant_bit_index(least_significant_bit(curr_mask))) == i) {
                curr_mask ^= least_significant_bit(curr_mask);
            }
            //the least bit will always be minimum in that small bit
            curr_mask |= 1;
            mask[i] = curr_mask;
        }
        //construct sparse table for the n / b blocks
        //lower level
        for(int i = 0; i < n/block_size; i++) {
            sparse_table[i] = small_query(block_size * i + block_size - 1);
        }
        //rest of the levels
        for(int j = 1; (1<<j) <= n/block_size; j++) {
            for(int i = 0; i + (1<<j) <= n / block_size; i++) {
                sparse_table[n / block_size * j + i] = op(sparse_table[n / block_size * (j - 1) + i], sparse_table[n / block_size * (j - 1) + i + (1<<(j-1))]);
            }
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<ll> pfx(n + 1, 0);
        vector<int> a(n);
        vector<int> a_neg(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a_neg[i] = -a[i];
            pfx[i + 1] = a[i] + pfx[i];
        }
        RMQ<int> q_min(a);
        RMQ<int> q_max(a_neg);
        for(int i = 0; i < n; i++){
            int a_left = 1e9;
            int a_right = 1e9;
            //eaten from left
            if(i != 0){
                int low = 0;
                int high = i;
                int ans = -1;
                while(low <= high) {
                    int mid = low + (high - low) / 2;
                    int smin = q_min.query(mid, i);
                    int smax = -q_max.query(mid, i);
                    if(pfx[i] - pfx[mid] > a[i] && (smax > a[i] || smin != smax)) {
                        ans = max(ans, mid);
                        low = mid + 1;
                    }
                    else {
                        high = mid - 1;
                    }
                }
                if(ans != -1) a_left = i - ans;
            }
            //eaten from right
            if(i != n - 1){
                int low = i + 2;
                int high = n;
                int ans = n + 1;
                while(low <= high) {
                    int mid = low + (high - low) / 2;
                    int smin = q_min.query(i + 1, mid);
                    int smax = -q_max.query(i + 1, mid);
                    if(pfx[mid] - pfx[i + 1] > a[i] && (smax > a[i] || smin != smax)) {
                        ans = min(ans, mid);
                        high = mid - 1;
                    }
                    else {
                        low = mid + 1;
                    }
                }
                if(ans != n + 1) a_right = ans - i - 1;
            }
            int ans = min(a_left, a_right);
            // cout << "I : " << i << " " << a_left << " " << a_right << "\n";
            cout << (ans == 1e9? -1 : ans) << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
