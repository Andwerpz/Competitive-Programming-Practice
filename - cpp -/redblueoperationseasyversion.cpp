#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1832D

//doesn't work

bool isValid(vector<ll> a, int k, ll val) {
    //cout << "TEST : " << k << " " << val << "\n";
    if(a[0] >= val) {
        //cout << "AUTO" << "\n";
        return true;
    }
    
    int r = 0;
    while(r < a.size() && a[r] < val){
        r++;
    }
    if(r > k){
        //cout << "TOO MANY\n";
        return false;
    }
    ll i = 1;
    if(k % 2 == 1){
        a[0] --;
        i ++;
    }
    for(int j = r - 1; j >= 0; j--){
        a[j] += i;
        i ++;
    }
    ll sum = 0;
    for(int j = 0; j < r; j++){
        if(a[j] >= val){
            continue;
        }
        sum += val - a[j];
    }
    //cout << (sum * 2 + r) << "\n";
    return k >= (sum * 2 + r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<ll> a(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    while(q-- > 0){
        int k;
        cin >> k;
        ll low = 0;
        ll high = 1e18;
        ll mid = low + (high - low) / 2;
        ll ans = low;
        while(low <= high) {
            if(isValid(a, k, mid)) {
                ans = max(ans, mid);
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << " ";
    }
    
    return 0;
}
