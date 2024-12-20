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

//AtCoder - ABC108D

//We are tasked with creating a graph that will result in exactly L edges from node 1 to N, 
//with all unique path lengths being in range [0, L). However, the challenge is that the amount 
//of nodes and edges allowed for our graph is very small, with only 20 nodes and 60 edges. 

//Conveniently, note that 2^20 is around 10^6, which hints at a solution using powers of 2. 
//Actually, for an L equal to a power of 2, L = 2^p, the answer is very simple. We can just have 
//p + 1 nodes and connect nodes i and i + 1 with edges of weight 0 and 2^{p - i}. 

//To extend this solution to L that is not a power of 2, we can just add extra edges to this graph. 
//We'll initially build as if L was lowered to the nearest power of 2, then add in the extra edges 
//to cover the extra bit that we didn't initially cover. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int l;
    cin >> l;
    l --;
    vector<array<int, 3>> e;
    int n = 2;
    {
        int ptr = 2;
        while(ptr * 2 <= l){
            n ++;
            ptr *= 2;
        }   
    }
    for(int i = 0; i < n - 1; i++){
        e.push_back({i, i + 1, 0});
        e.push_back({i, i + 1, (1 << (n - i - 2))});
    }
    int ptr = (1 << (n - 1)) - 1;
    while(ptr != l){
        int inc = 1;
        int pow = 0;
        while(ptr + inc * 2 <= l && (n - 1 - pow - 1) > 0) {
            inc *= 2;
            pow ++;
        }
        e.push_back({0, n - 1 - pow, ptr + 1});
        ptr += inc;
    }
    cout << n << " " << e.size() << "\n";
    for(int i = 0; i < e.size(); i++){
        cout << e[i][0] + 1 << " " << e[i][1] + 1 << " " << e[i][2] << "\n";
    }
    
    return 0;
}