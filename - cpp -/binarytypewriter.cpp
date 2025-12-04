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

//Codeforces - 2103B

//the total cost of writing the string is n + number of switches between 0 and 1. Keep in mind that if the string initially
//starts at 1, that's an extra switch. If you have 2 switches, you can always swap a substring to reduce that to 1. If you have 3
//or more switches, you can always swap to decrease that by 2. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int cnt = 0;
        char prev = '0';
        for(int i = 0; i < n; i++) {
            if(s[i] != prev) cnt ++;
            prev = s[i];
        }
        if(cnt == 2) cnt = 1;
        else if(cnt >= 3) cnt -= 2;
        cout << n + cnt << "\n";
    }
    
    return 0;
}