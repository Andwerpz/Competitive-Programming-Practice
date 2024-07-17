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
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 1988C

//first, enumerate the bits of n. I claim that the length of the maximum sequence is the number of bits in n + 1. 
//the ith element in the sequence is just n, with the ith most significant bit of n turned off. The last element
//of the sequence is just n. 

//there is one exception, if n only has 1 bit, then the sequence is just [n]. This is because if we turn off the most 
//significant bit in this case, we'll get 0, which is out of the range of acceptable values. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        vi bits(0);
        int ptr = 0;
        ll tmp = n;
        while(n != 0){
            if(n % 2 == 1){
                bits.push_back(ptr);
            }
            n /= 2;
            ptr ++;
        }
        n = tmp;
        reverse(bits.begin(), bits.end());
        vl ans(0);
        if(bits.size() > 1){
            for(int i = 0; i < bits.size(); i++){
                ans.push_back(n ^ (1ll << bits[i]));
            }
        }
        ans.push_back(n);
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " \n"[i == ans.size() - 1];
        }
    }
    
    return 0;
}