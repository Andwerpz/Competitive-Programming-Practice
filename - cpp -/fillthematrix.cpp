#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1841E

//given a matrix, can we figure out the maximum beauty with a certain m?
//for example (this is the matrix for sample test case 2): 
/*
. . . .
. . # .
# . # .
# . # #
*/

//with limited m, we want to start filling in the maximum sized contiguous row sections first. We can actually just fill in the 
//row segments from longest to smallest, and that will produce the maximum beauty. 

//the problem is that we can't just go and tabulate and sort all of the segments, since there might be around n^2 of them. 
//so, we'll have to find a way to speed this up. 

//If we consider the rows from top down, we can treat the grid as a tree. Each contiguous segment along a row is a node, and the children
//of that node are the contiguous segments that it touches to it's bottom. 

//due to the structure of the grid, each node will have no more than 1 parent, which makes it a tree. 
//tree representation of above grid. The value of the node indicates the size of the segment. 
/*
   ┌─┐
 ┌─┤4├─┐
 │ └─┘ │
 │     │
┌▼┐   ┌▼┐
│2│   │1│
└┬┘   └┬┘
 │     │
┌▼┐   ┌▼┐
│1│   │1│
└┬┘   └─┘
 │
┌▼┐
│1│
└─┘
*/

//we can find this tree structure on the fly by querying the maximum value in a segment using segment tree, 
//and use a priority queue to greedily use all the longest segments first. 
//this works because a node of value x will never have children of value greater than x. 

//a necessary optimization is in the case where there are multiple nodes of the same length in a chain; we want to merge them, 
//since it's too expensive to deal with them one at a time. 

const int N = 3e5;  //limit for segtree size
int n;
int t[2 * N];
int id[2 * N];

void build() { // build the tree
    for(int i = 0; i < n; i++){
        id[i + n] = i;
    }
    for (int i = n - 1; i > 0; i--) {   
        if(t[i * 2] > t[i * 2 + 1]) {
            id[i] = id[i * 2];
        }
        else {
            id[i] = id[i * 2 + 1];
        }
        t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
}

void modify(int p, int value) { // set value at position p
    p += n;
    t[p] = value;
    for (p /= 2; p > 0; p /= 2) {
        if(t[p * 2] > t[p * 2 + 1]) {
            id[p] = id[p * 2];
        }
        else {
            id[p] = id[p * 2 + 1];
        }
        t[p] = max(t[p * 2], t[p * 2 + 1]);
    }
}

int query(int l, int r, int& ind) { // max on interval [l, r)
    int res = -1;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            if(t[l] > res) {
                ind = id[l];
            }
            res = max(res, t[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            if(t[r] > res) {
                ind = id[r];
            }
            res = max(res, t[r]);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tc;
    cin >> tc;
    while(tc--) {
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> t[i + n];
        }
        build();
        ll m;
        cin >> m;
        priority_queue<vector<int>> q;  //segment length, row, l, r
        q.push({n, n, 0, n});
        ll ans = 0;
        while(m != 0 && q.size() != 0){
            vector<int> cur = q.top();
            q.pop();
            ll len = cur[0];
            int row = cur[1];
            int l = cur[2];
            int r = cur[3];
            //cout << "SEG : " << len << " " << row << " " << l << " " << r << "\n";
            int mxInd = 0;
            int mx = query(l, r, mxInd);
            //cout << "MAX : " << mx << " " << mxInd << "\n";
            ll nr = row - mx;
            ll maxCon = nr * len;
            if(m > maxCon) {
                ans += nr * (len - 1);
                m -= maxCon;
                if(mxInd - l > 0){
                    q.push({mxInd - l, (int) (row - nr), l, mxInd});
                }
                if(r - (mxInd + 1) > 0){
                    q.push({r - (mxInd + 1), (int) (row - nr), mxInd + 1, r});
                }
                continue;
            }
            while(m >= len){
                ans += len - 1;
                m -= len;
            }
            if(m != 0){
                ans += m - 1;
                m = 0;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
