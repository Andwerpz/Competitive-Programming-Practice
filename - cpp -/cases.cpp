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

//Codeforces - 1995D

//first, if we choose a letter to be a case, then we can make any occurrence of that letter into an ending point. 
//then, we can reword the maximum length of word as k constraint to say that for any contiguous substring of k characters, 
//there must be at least one letter which is a case. There is one exception, it's that the last letter of the string 
//must be a case. 

//For each substring of length k, we can create a bitset to represent which characters are in that substring. Then, we
//just have to find some bitset with minimal characters which shares a character with every bitset, and which contains
//the last character of the string. 

//It might be useful to identify which bitsets are bad. A bitset a is bad if for some substring bitset b, a & !b = 0. 
//In other words, a is a subset of !b, which means that a does not share any bits with b. 

//after computing all the bad bitsets, we can simply iterate through all of them, and take the one with the least amount
//of bits. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, c, k;
        cin >> n >> c >> k;
        string s;
        cin >> s;
        vvi pfx(c, vi(n + 1, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < c; j++){
                pfx[j][i + 1] = pfx[j][i];
            }
            pfx[s[i] - 'A'][i + 1] ++;
        }
        //if a bitset is a subset of a 'bad' bitset, then it's also bad. 
        //a bad bitset is one that completely misses at least one of the k-subarray bitsets. 
        vb bad((1 << c), false);
        for(int i = k; i <= n; i++){
            int bits = 0;
            for(int j = 0; j < c; j++){
                if(pfx[j][i - k] != pfx[j][i]) {
                    bits = bits | (1 << j);
                }
            }
            bad[((1 << c) - 1) - bits] = true;
        }
        int last = s[s.size() - 1] - 'A';
        int ans = c;
        for(int i = (1 << c) - 1; i >= 0; i--){
            if(!bad[i]) {
                if((i & (1 << last))) { //answer has to include the last character in the string. 
                    ans = min(ans, __builtin_popcount(i));
                }
                continue;
            }
            for(int j = 0; j < c; j++){
                if(i & (1 << j)) {
                    bad[i ^ (1 << j)] = true;
                }
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}