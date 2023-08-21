#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1849E

//we can solve using divide and conquer. 

//1: find the index of the maximum element in our subarray, [l, r). 
//2: figure out how many subarrays there are such that the maximum element in our subarray is the maximum element, and maxpos > minpos. 
//3: solve for the answers for subarrays [l, maxpos), and [maxpos + 1, r). 

//we can do step 1 in log(n) time using a segment tree. 

//step 2 can be done in O(n) time, but the crucial detail is that it usually takes around O(n / 2). This allows the
//entire complexity of the algorithm to be O(n * log(n)). (i actually don't really know why it doesnt TLE). 

//UPDATE: solution got hacked. Seems like the two pointer solution does TLE. 

//instead of using pointers, and searching linearly, we can just binary search the next minimum element to the left, and then binary
//search for the maximum index 'rptr' where the minimum on the segment [maxpos, rptr) is greater than that of the segment [lptr, maxpos). 

//range max query
struct Segtree {
    //note that t[0] is not used
    int n;
    int* tmax;
    int* tmin;
    int* ind;   //which index is the max

    Segtree(int n) {
        this->n = n;
        tmax = new int[2 * n];
        tmin = new int[2 * n];
        ind = new int[2 * n];
        
        for(int i = 0; i < 2 * n; i++){
            tmax[i] = 0;
            tmin[i] = 1e9;
            ind[i] = 0;
        }

        for(int i = 0; i < n; i++){
            ind[i + n] = i;
        }
    }

    ~Segtree() {
        delete tmax;
        delete tmin;
        delete ind;
    }

    void build() { // build the tree
        for (int i = n - 1; i > 0; i--) {
            ind[i] = (tmax[i * 2] >= tmax[i * 2 + 1])? ind[i * 2] : ind[i * 2 + 1];
            tmax[i] = max(tmax[i * 2], tmax[i * 2 + 1]);
            tmin[i] = min(tmin[i * 2], tmin[i * 2 + 1]);
        }
    }

    int queryMaxInd(int l, int r) { // max on interval [l, r), gets the index
        int res = -1;
        int wind = -1;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                if(tmax[l] > res) {
                    res = tmax[l];
                    wind = ind[l];
                }
                l++;
            }
            if (r % 2 == 1) {
                r--;
                if(tmax[r] > res) {
                    res = tmax[r];
                    wind = ind[r];
                }
            }
        }
        return wind;
    }

    int queryMin(int l, int r) {    // min on interval [l, r). 
        int res = 1e9;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) {
                res = min(res, tmin[l]);
                l++;
            }
            if (r % 2 == 1) {
                r--;
                res = min(res, tmin[r]);
            }
        }
        return res;
    }
};

ll solve(vector<int>& a, Segtree& tree, int l, int r) {
    //cout << "SOLVE : " << l << " " << r << endl;
    if(l >= r){
        return 0;
    }
    int maxind = tree.queryMaxInd(l, r);
    //cout << "MAXIND : " << maxind << " " << a[maxind] << endl;
    if(maxind == l) {
        return solve(a, tree, l + 1, r);
    }
    int lptr = maxind;
    int rptr = maxind + 1;
    ll ans = 0;
    while(lptr != l) {
        //search for left bound
        {
            int low = l;
            int high = lptr;
            int nlptr = low;
            while(low <= high) {
                int mid = low + (high - low) / 2;
                if(tree.queryMin(mid, maxind + 1) < a[lptr]) {
                    nlptr = max(nlptr, mid);
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            ans += (ll) (lptr - nlptr) * (ll) (rptr - maxind);
            lptr = nlptr;
        }
        //search for right bound
        {
            int low = rptr;
            int high = r;
            int nrptr = rptr;
            while(low <= high){
                int mid = low + (high - low) / 2;
                if(tree.queryMin(maxind, mid) > a[lptr]) {
                    nrptr = max(nrptr, mid);
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            ans += nrptr - rptr;
            rptr = nrptr;
        }
        if(rptr == r) {
            ans += (ll) (lptr - l) * (ll) (rptr - maxind);
            break;
        }
    }
    ans += solve(a, tree, l, maxind);
    ans += solve(a, tree, maxind + 1, r);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    Segtree tree(n);
    for(int i = 0; i < n; i++){
        tree.tmax[i + n] = a[i];
        tree.tmin[i + n] = a[i];
    }
    tree.build();
    // for(int i = 0; i < 2 * n; i++){
    //     cout << tree.ind[i] << " ";
    // }
    // cout << "\n";
    //cout << tree.query(0, n) << endl;
    //cout << "FINISHED BUILDING TREE" << endl;
    cout << solve(a, tree, 0, n) << "\n";
    
    return 0;
}
