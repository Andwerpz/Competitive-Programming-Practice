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

//Topcoder - 8238

//first observe that the two sets need to be the same size since there is a one to one correspondence 
//going on. 

//Between every pair of points that correspond between the two sets, they need to also be rotated the
//same amount. 

//So, we can just try every possible rotation, and take the one that grants the maximum. 

//Be careful about when the angle loops around. 

int test(vi& a, int val) {
    int n = a.size();
    vvi c(n);
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            int diff = min({abs(a[i] - a[j]), abs((a[i] + 360) - a[j]), abs((a[i] - 360) - a[j])});
            if(diff == val) {
                c[i].push_back(j);
                c[j].push_back(i);
            }
        }
    }
    vb v(n, false);
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(v[i]) continue;
        int sz = 0;
        queue<int> q;
        q.push(i);
        v[i] = true;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            sz ++;
            for(int x : c[cur]) if(!v[x]) q.push(x), v[x] = true;
        }
        ans += sz / 2;
    }
    return ans;
}

class PointsOnACircle {
public:
    int color(vector<string> inpt) {
        vi a;
        {
            string s;
            for(string x : inpt) s += x;
            int ptr = 0;
            while(ptr < s.size()) {
                int l = ptr;
                while(ptr != s.size() && s[ptr] != ' ') ptr ++;
                a.push_back(stoi(s.substr(l, ptr - l)));
                ptr ++;
            }
        }
        int ans = 0;
        for(int i = 1; i < 360; i++){
            ans = max(ans, test(a, i));
        }
        return ans * 2;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    // int n;
    // cin >> n;
    // string line;
    // getline(cin, line);
    // vector<string> lines;
    // for(int i = 0; i < n; i++){
    //     getline(cin, line);
    //     lines.push_back(line);
    // }
    // cout << solve(lines) << "\n";
    
    return 0;
}