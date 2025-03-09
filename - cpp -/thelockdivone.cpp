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

//Topcoder - 10514

//patternforces. First make some guesses:
// - changing n will not change the contents of the sequence. 
// - the sequence will resemble some sort of gray code

//then, generate the first few elements of the sequence. Here are the first 32, but the first 16 should be good
//enough to get a feel for it. 
/*
00000
00001
00011
00010
00110
00100
00101
00111
01111
01000
01001
01011
01010
01110
01100
01101
11101
10000
10001
10011
10010
10110
10100
10101
10111
11111
11000
11001
11011
11010
11110
11100
*/

//observe that when we go up a power of 2, we always introduce the next most significant bit, then immediately set the
//rest of the bits to 0, and then repeat the sequence on the n - 1 bits. 


ll get_pass(int n, ll k){
    if(n == -1) return 0;  
    if(!(k & (1ll << n))) return get_pass(n - 1, k); //doesn't have the nth bit
    if(k == (1ll << n)) return get_pass(n - 1, k - 1) + (1ll << n);    //right on the border
    return get_pass(n - 1, k - (1ll << n) - 1) + (1ll << n);
}

ll solve(int n, ll k){
    if(n == -1) return 0;  
    if(!(k & (1ll << n))) return solve(n - 1, k); //doesn't have the nth bit
    if(k == (1ll << n)) return get_pass(n - 1, k - 1) + (1ll << n);    //right on the border
    //has nth bit, best is either on the border or max of stuff not on border
    return max(solve(n, (1ll << n)), solve(n - 1, k - (1ll << n) - 1) + (1ll << n));
}

string to_bin(int n, ll x) {
    string ret = "";
    for(int i = n - 1; i >= 0; i--){
        ret.push_back((x & (1ll << i))? '1' : '0');
    }
    return ret;
}

class TheLockDivOne {
public:
    string password(int n, long long k) {
        return to_bin(n, solve(n - 1, k - 1));
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    long long arg1;
    cin >> arg1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = TheLockDivOne();
    string ret = c.password(arg0, arg1);
    cout << ret;
}