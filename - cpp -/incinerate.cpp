#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1763B

//just simulate the problem statement. 

//to make it easier, sort the monsters in order of health in ascending order, and construct
//a sfx min array for the powers of the monsters. 

ll damage(ll k, ll reduction, ll n) {
    ll totalReduction = (n * (n - 1) / 2ll) * reduction;
    ll ans = k * n - totalReduction;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        ll k;
        cin >> n >> k;
        vector<vector<ll>> a(n, vector<ll>(2));
        for(int i = 0; i < n; i++) {
            cin >> a[i][0];
        }
        for(int i = 0; i < n; i++){
            cin >> a[i][1];
        }
        sort(a.begin(), a.end(), [] (vector<ll>& a, vector<ll>& b) {return a[0] < b[0];});
        vector<ll> sfxMin(n + 1);
        sfxMin[n - 1] = a[n - 1][1];
        for(int i = n - 2; i >= 0; i--){
            sfxMin[i] = min(sfxMin[i + 1], a[i][1]);
        }
        // for(vector<ll> i : a) {
        //     cout << i[0] << " " << i[1] << endl;
        // }
        ll dmg = 0;
        bool isValid = true;
        for(int i = 0; i < n; i++){
            //cout << "I : " << i << " " << dmg << " " << k << endl;
            //cout << a[i][0] << endl;
            if(dmg >= a[i][0]){ //already killed the ith monster
                continue;
            }
            if(k <= 0){
                isValid = false;
                break;
            }
            ll healthLeft = a[i][0] - dmg;
            ll minP = sfxMin[i];
            ll maxIncinerate = k / minP + (k % minP == 0? 0 : 1);
            if(damage(k, minP, maxIncinerate) < healthLeft) {
                isValid = false;
                break;
            }
            ll low = 1;
            ll high = maxIncinerate;
            ll mid = low + (high - low) / 2;
            ll atkAmt = maxIncinerate;
            while(low <= high) {
                if(damage(k, minP, mid) >= healthLeft) {
                    atkAmt = min(atkAmt, mid);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
                mid = low + (high - low) / 2;
            }
            dmg += damage(k, minP, atkAmt);
            ll nextP = 0;
            for(int j = i + 1; j < n; j++){
                if(a[j][0] > dmg) {
                    nextP = sfxMin[j];
                    break;
                }
            }
            k -= (atkAmt - 1) * minP + nextP;
            //cout << atkAmt << endl;
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
