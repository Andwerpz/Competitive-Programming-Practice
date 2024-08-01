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

int solve(string& s, int nr_diff, string& retstring) {
    int n = s.size();
    if(n % nr_diff != 0){
        return 1e9;
    }
    vi freq(26, 0);
    for(int i = 0; i < s.size(); i++){
        freq[s[i] - 'a'] ++;
    }
    vector<pii> arr(0);
    for(int i = 0; i < 26; i++){
        arr.push_back({freq[i], i});
    }
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    vi exp(26, 0);
    stack<pii> need;
    for(int i = 0; i < nr_diff; i++){
        // cout << "CHOOSE : " << (char) (arr[i].second + 'a') << "\n";
        exp[arr[i].second] = n / nr_diff;
        if(n / nr_diff > freq[arr[i].second]) {
            need.push({arr[i].second, (n / nr_diff) - freq[arr[i].second]});
        }
    }
    retstring = string(n, ' ');
    int cnt = 0;
    freq = vi(26, 0);
    for(int i = 0; i < n; i++){
        int c = s[i] - 'a';
        if(freq[c] < exp[c]) {
            retstring[i] = s[i];
            freq[c] ++;
        }
        else {
            cnt ++;
            c = need.top().first;
            retstring[i] = c + 'a';
            need.top().second --;
            if(need.top().second == 0){
                need.pop();
            }
        }
    }
    return cnt;
}   

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
        string ans;
        int bpos = 1e6;
        for(int i = 1; i <= 26; i++){
            string ret;
            int cpos = solve(s, i, ret);
            if(cpos < bpos){
                bpos = cpos;
                ans = ret;
            }
        }
        cout << bpos << "\n" << ans << "\n";
    }
    
    return 0;
}