#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1691D

//lets say that for each a_i, we know the maximum size subarray where a_i is the maximum value. The starting point
//is j, and the ending is k. 

//we only need to check subarrays (j, i), (j + 1, i) ... (i - 1, i), (i, i + 1) ... (i, k - 1), (i, k). 
//we only need to check one side at a time. 

//if we only consider one side, then getting the maximum sum subarray can be done in log(n) time with segment tree
//as we can query the maximum pfx sum over a range. 

//if at any point, the subarray sum is greater than a_i, then the input is invalid. 

vector<ll> pfxTree;
vector<ll> sfxTree;

void modify(vector<ll> &t, int i, ll val, int n){
    i += n;
    for(t[i] = val, i /= 2; i > 0; i /= 2){
        t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
}

ll query(vector<ll> &t, int l, int r, int n) {
    ll ans = t[l + n];
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1)
        {
            ans = max(ans, t[l]);
            l++;
        }
        if (r % 2 == 1)
        {
            r--;
            ans = max(ans, t[r]);
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        //construct pfx and sfx
        pfxTree = vector<ll>(n * 2);
        sfxTree = vector<ll>(n * 2);
        ll sum = 0;
        for(int i = 0; i < n; i++){
            sum += a[i];
            modify(pfxTree, i, sum, n);
        }
        sum = 0;
        for(int i = n - 1; i >= 0; i--){
            sum += a[i];
            modify(sfxTree, i, sum, n);
        }
        stack<pair<int, ll>> s;
        bool isValid = true;
        for(int i = 0; i < n; i++){
            int firstGreater = i;
            while(s.size() != 0 && s.top().second <= a[i]){
                firstGreater = s.top().first;
                s.pop();
            }
            if(s.size() == 0){
                firstGreater = 0;
            }
            ll curSfx = i == n - 1? 0 : sfxTree[i + n + 1];
            ll maxSfx = query(sfxTree, firstGreater, i, n);
            if(maxSfx - curSfx > a[i]){
                isValid = false;
            }
            s.push({i, a[i]});
        }
        s = stack<pair<int, ll>>();
        for(int i = n - 1; i >= 0; i--){
            int lastGreater = i;
            while(s.size() != 0 && s.top().second <= a[i]){
                lastGreater = s.top().first;
                s.pop();
            }
            if(s.size() == 0){
                lastGreater = n - 1;
            }
            ll curPfx = i == 0? 0 : pfxTree[i + n - 1];
            ll maxPfx = query(pfxTree, i, lastGreater + 1, n);
            if(maxPfx - curPfx > a[i]){
                isValid = false;
            }
            s.push({i, a[i]});
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
