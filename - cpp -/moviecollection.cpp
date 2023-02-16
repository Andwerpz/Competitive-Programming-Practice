#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 04 B

//since you can only have up to 10^5 queries, we can just allocate a big array to 'simulate' the stack. 
//every time you take a dvd from the middle and move it to the top, you just erase it from where it was, and
//put it at the end, no need to move the ones in the middle down to fill the empty space. 

//with this in mind, we can use segment tree to do fast range queries of how many dvds are after the one in question. 

const int N = 1e6;  //limit for segtree size
int n;
int t[2 * N];

void build() { // build the tree
    for (int i = n - 1; i > 0; i--) {   
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

void modify(int p, int value) { // set value at position p
    p += n;
    t[p] = value;
    for (p /= 2; p > 0; p /= 2) {
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
}

int query(int l, int r) { // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res += t[l];
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res += t[r];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int mov, r;
        cin >> mov >> r;
        n = mov + r;
        map<int, int> m;
        for(int i = 0; i < mov; i++){
            m.insert({mov - i - 1, i});
            modify(i, 1);
        }
        for(int i = mov; i < n; i++){
            modify(i, 0);
        }
        for(int i = 0; i < r; i++){
            int a;
            cin >> a;
            a--;
            int ind = m.find(a) -> second;
            int nextInd = mov + i;
            cout << query(ind + 1, n) << " ";
            modify(ind, 0);
            modify(nextInd, 1);
            m.find(a) -> second = nextInd;
        }
        cout << "\n";
    }
    
    return 0;
}
