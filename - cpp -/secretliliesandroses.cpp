#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//2025 ICPC Asia Pacific Championship - H

//main takeaway: need to do more interactive problems
//also, try to describe the solution and find something convenient about it. 

//some notes:

// k roses
// n - k lilies
// prove that nr lilies in first k flowers = nr roses in last n - k flowers
// suppose there are a lilies in the first k flowers, a <= k. Then, there are k - a roses in the first k flowers, which means that 
// there must be k - (k - a) = a roses in the last n - k flowers.
// the intuition is that any lily in the first k flowers will push a rose into the last n - k flowers. 

// how to find the number of roses??
// if i can find a non-zero multiply, then I can find the number of roses. Idea is to know the number of lilies in the prefix and 
// roses in the suffix, the lilies in the prefix gives the roses in the prefix. 

// let's just query any value, If we get something non-zero, then great. However, if we don't then we need to figure out in which 
// direction there are non-zero things. how can we determine whether or not there are lilies 

// LL, then there cannot be roses to the right, therefore need to move left
// RR, then there cannot be lilies to the left, therefore need to move right
// LR, if our query is 0, this is impossible
// RL, actually need to spend an extra query, so query one over to the right. 

// even if we know in which direction to move, how can we efficiently find some non-zero multiply?
// in some cases, there doesn't exist a non-zero multiply

// Let's say we found some 'LL'. Then, we move left and find a 'RR'. However, since we know it's a 0 multiply, we only need to query 
// the right character and see that it's 'R' to know that. If we query the right and find 'L', then the left still could be 'R'. 

// ah, so find one occurrence of RL, then query two times. To find, if we see an 'R', move right and if we see an 'L', move left. 
// We'll maintain that our range has an 'R' on the left and 'L' on the right. Put an imaginary rose on the leftmost side and an 
// imaginary lily on the rightmost side. 

// l_x * r_x = a
// l_{x - 1} * r_{x - 1} = l_x * (r_x + 1) = b

// l_x * r_x + l_x = b
// l_x * r_x = b - l_x = a
// l_x = b - a

// if l_x == 0, all flowers to the left of x are roses, wait but we can just query l_{x + 1} * r_{x + 1}

// l_{x + 1} * r_{x + 1} = (l_x + 1) * r_x = c
// l_x * r_x + r_x = c
// l_x * r_x = c - r_x = a
// r_x = c - a

// 2^7 = 128, so we should have enough queries to find within 7 queries

int n, qcnt;
string s;
string qtype(int x) {
    // qcnt ++;
    // return s[x] == 'R'? "R" : "L";
    cout << "type " << x + 1 << endl;
    string type;
    cin >> type;
    return type == "rose"? "R" : "L";
}

int qmult(int x) {
    // qcnt ++;
    // int l = 0, r = 0;
    // for(int i = 0; i < n; i++){
    //     l += i < x && s[i] == 'L';
    //     r += i >= x && s[i] == 'R';
    // }
    // return l * r;
    if(x < 0 || x > n) return 0;
    cout << "multi " << x << endl;
    int ans;
    cin >> ans;
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        // cin >> s;
        // n = s.size();
        // qcnt = 0;
        //find 'RL'. Maintain that s[low] = 'R', s[high] = 'L'
        int low = -1, high = n;
        while(high - low > 1){
            int mid = low + (high - low) / 2;
            if(qtype(mid) == "R") low = mid;
            else high = mid;
        }
        //compute nr roses
        int a = qmult(low + 1), b = qmult(low), c = qmult(low + 2);
        int lx = b - a, rx = c - a;
        int rcnt = rx + (low + 1) - lx;
        //yay
        cout << "answer " << rcnt << endl;
        // cout << "QUERIES : " << qcnt << "\n";
    }
    
    return 0;
}