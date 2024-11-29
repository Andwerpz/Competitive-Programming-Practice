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

//UTPC Contest 11-20-24 Div1 - G

//naively, answer is just equal to the amount of unique elements present in the array. 
//however cycles of length 2 or greater that are completely isolated all remove 1 from the answer, as
//you can't kill the last guy in the cycle. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vi a(n), indeg(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
        indeg[a[i]] ++;
    }
    set<int> s;
    for(int i = 0; i < n; i++){
        s.insert(a[i]);
    }
    int ans = s.size();
    vi v(n, -1);
    for(int i = 0; i < n; i++){
        if(v[i] != -1){
            continue;
        }
        stack<int> st;
        int ptr = i;
        v[i] = i;
        while(v[a[ptr]] == -1){
            v[a[ptr]] = i;
            ptr = a[ptr];
            st.push(ptr);
        }
        if(v[a[ptr]] == i && ptr != a[ptr]) {
            //found some cycle
            bool subt = true;
            while(st.size() != 0){
                if(indeg[st.top()] != 1){
                    subt = false;
                }
                st.pop();
            }
            ans -= subt;
        }
    }
    cout << ans << "\n";
    
    return 0;
}