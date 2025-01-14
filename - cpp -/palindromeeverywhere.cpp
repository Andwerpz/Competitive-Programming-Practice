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

//Codeforces - 2029F

//observationforces. Probably wouldn't get this one during contest

//first, let's build a good model for what's going on in the problem. Lets say you want to get from a -> b with a
//palindrome path. Put pointer i at a, and pointer j at b. Then, whatever move you make to pointer i, you must follow 
//along with the same color edge with pointer j. If you can eventually make i and j point to the same or adjacent nodes
//then you can derive the palindrome path by considering the path from a -> i and j -> b. Any palindrome path can be made
//this way, so if it's impossible this way, then a palindrome path is impossible. 

//first observation is that a sequence that has 'RR' and 'BB' is not good, as if we start in the middle of 'RR' and want
//to go to middle of 'BB', then anywhere we move pointer i, pointer j can't follow. 

//second, if it's just alternating 'R' and 'B', then it's impossible, as wherever we move the i pointer, the j pointer only 
//has one option to move. So we can conclude that either R or B must have some connected component of size > 1. 

//third, if we have two even sized connected components of the same color, then it's impossible. This is because we can start
//one pointer in one component, and the other pointer in the other component, and make it so that it requires an odd amount of 
//steps to leave the first component and an even amount of steps for the other one. Therefore, only one even sized component can 
//exist. 

//Finally, observe that unless it's the trivial case, any even n will not work. This is for some parity reasons. 

//any sequence that gets past these rules will work. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int rcnt = 0, bcnt = 0;
        for(int i = 0; i < s.size(); i++){
            rcnt += s[i] == 'R';
            bcnt += s[i] == 'B';
        }
        if(rcnt >= n - 1 || bcnt >= n - 1) {
            cout << "YES\n";
            continue;
        }
        if(n % 2 == 0) {
            cout << "NO\n";
            continue;
        }
        int rec = 0, roc = 0, bec = 0, boc = 0;
        rcnt = 0, bcnt = 0;
        int ptr = 0;
        while(s[ptr] != 'B') ptr = (ptr + 1) % n;
        for(int i = 0; i < n; i++){
            if(s[(ptr + i) % n] == 'B') continue;
            int ccnt = 0;
            while(s[(ptr + i) % n] == 'R') ccnt ++, i ++;
            if(ccnt > 1) rec += (ccnt % 2) == 0, roc += ccnt % 2;
            rcnt += ccnt > 1;
        }
        while(s[ptr] != 'R') ptr = (ptr + 1) % n;
        for(int i = 0; i < n; i++){
            if(s[(ptr + i) % n] == 'R') continue;
            int ccnt = 0;
            while(s[(ptr + i) % n] == 'B') ccnt ++, i ++;
            if(ccnt > 1) bec += (ccnt % 2) == 0, boc += ccnt % 2;
            bcnt += ccnt > 1;
        }
        if(bcnt == 0 && rec <= 1) {
            cout << "YES\n";
            continue;
        }
        if(rcnt == 0 && bec <= 1) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }
    
    return 0;
}