#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 G

//once a number is in it's correct place, it isn't swapped with any other number. 

//so, we can use a segtree to keep track of which numbers are sorted, and which numbers have not been. 
//then, the number of swaps is either the number of unsorted numbers in the prefix, or suffix from the number being sorted. 

const int N = 1e6;  //limit for segtree size
int n;
int t[2 * N];

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
    
    cin >> n;
    for(int i = 0; i < n; i++){
        modify(i, 1);
    }
    vector<int> a(n);
    vector<int> loc(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
        loc[a[i]] = i;
    }
    int l = 0;
    int r = n - 1;
    for(int i = 0; i < n; i++){
        int next = -1;
        if(i % 2 == 0){
            next = l ++;
        }
        else{
            next = r --;
        }
        //cout << "LOC : " << loc[next] << "\n";
        modify(loc[next], 0);
        if(i % 2 == 0){
            cout << query(0, loc[next]);
        }   
        else {
            cout << query(loc[next] + 1, n);
        }
        cout << "\n";
    }
    
    return 0;
}
