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

//AtCoder - ARC84E

//very constructive, interpret as finding some base k integer of length n. 

//It seems like there might be a constructive solution for this problem, so let's enumerate some testcases to see what's going on. 
//Also, instead of having numbers in range [1, k], I'll have numbers in range [0, k), as then we can interpret it as making numbers in base-k. 
//Starting with n = 3, k = 3. We'll enumerate on columns left to right. 

//```
//0       1       2
//0 0     1 0     2 0
//0 0 0   1 0 0   2 0 0
//0 0 1   1 0 1   2 0 1
//0 0 2   1 0 2   2 0 2
//0 1     1 1     2 1
//0 1 0   1 1 0   2 1 0
//0 1 1   1 1 1   2 1 1
//0 1 2   1 1 2   2 1 2
//0 2     1 2     2 2
//0 2 0   1 2 0   2 2 0
//0 2 1   1 2 1   2 2 1
//0 2 2   1 2 2   2 2 2
//```

//Note that the number of columns is controlled by k, so if k is even, then we'd always pick the last element of the k / 2th column. 
//The last element of a column is easy to construct, so let's focus on the case where k is odd. 

//Let's find the middle element by doing some 'balancing' which means I'll identify some equal amount on the left and right and 
//mark them both as impossible to have the middle element. First, note that the first and third columns cancel each other out. 
//Next, within the first column, let's disregard the sequence '1' and note that the rest is composed of 3 equal groups, two of which
//we can cancel out. Keep doing this until we arrive at our final answer '1 1 1'. However, we didn't account for the elements that  
//we skipped over, so get that amount, divide by 2, and move that many sequences backwards, giving us '1 1 0'. 

//First, observe that for any odd k, the sequence we first arrive at is always going to be n entries of k / 2. And, the amount
//skipped is always going to be n - 1. Therefore, we can just generate the array, and count backwards (n - 1) / 2 times to get the 
//answer. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> k >> n;
    if(k % 2 == 0) {
        cout << k / 2 << " ";
        for(int i = 0; i < n - 1; i++){
            cout << k << " ";
        }
        cout << "\n";
        return 0;
    }
    vi ans(n, k / 2);
    int ptr = n;
    for(int i = 0; i < n / 2; i++){
        if(ans[ptr - 1] == 0) {
            ptr --;
        }
        else if(ptr != n && ans[ptr - 1] != 0){
            for(int j = ptr; j < n; j++){
                ans[j] = k - 1;
            }
            ans[ptr - 1] --;
            ptr = n;
        }
        else {
            ans[n - 1] --;
        }
    }
    for(int i = 0; i < ptr; i++){
        cout << ans[i] + 1 << " ";
    }
    cout << "\n";
    
    return 0;
}