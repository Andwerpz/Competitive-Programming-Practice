#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1856D

//if the number of inversions in the segment [l, r] is equal to the number of inversions in the segment [l, r + 1], 
//then we know that a[r + 1] is greater than every element in the range [l, r]. 

//then, we can do a divide and conquer algorithm. 

int solve(int l, int r) {
    if(r - l == 1) {
        return l;
    }
    int mid = l + (r - l) / 2;
    //cout << l << " " << mid << " " << r << endl;
    int lmax = solve(l, mid);
    int rmax = solve(mid, r);
    int a, b;
    if(lmax + 1 == rmax) {
        a = 0;
    }
    else {
        cout << "? " << (lmax + 1) << " " << (rmax) << endl;
        cin >> a;
    }
    cout << "? " << (lmax + 1) << " " << (rmax + 1) << endl;
    cin >> b;
    return (a == b? rmax : lmax);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int ans = solve(0, n);
        cout << "! " << (ans + 1) << endl;
    }
    
    return 0;
}
