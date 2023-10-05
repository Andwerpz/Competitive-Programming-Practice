#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2012 - C

//once you integrate the polynomial, you can just binary search for the locations. 

ld pi = acos(-1);

vector<ld> poly_square(vector<ld>& a) {
    vector<ld> ans(a.size() * 2, 0);
    for(int i = 0; i < a.size() * 2; i++){
        for(int j = 0; j <= i; j++){
            if(max(j, i - j) >= a.size()) {
                continue;
            }
            ans[i] += a[j] * a[i - j];
        }
    }
    return ans;
}

vector<ld> integrate(vector<ld>& a) {
    a = poly_square(a);
    for(int i = 0; i < a.size(); i++){
        a[i] *= pi;
    }
    a.push_back(0);
    for(int i = a.size() - 1; i >= 1; i--){
        a[i] = a[i - 1] * (1.0 / i);
    }
    a[0] = 0;
    return a;
}

ld calc_val(ld x, vector<ld>& a) {
    ld ans = 0;
    for(int i = 0; i < a.size(); i++){
        ans += a[i] * pow(x, i);
    }
    return ans;
}

ld calc_vol(ld low, ld high, vector<ld>& a) {
    //cout << "CALC VOL : " << calc_val(high, a) << " " << calc_val(low, a) << "\n";
    return calc_val(high, a) - calc_val(low, a);
}

ld my_round(ld x) {
    return round(x * 100) / 100.0;
}

ld epsilon = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int tind = 0;
    cout << fixed << setprecision(2);
    while(!cin.eof() && n != -1){
        tind ++;
        vector<ld> a(n + 1);
        for(int i = 0; i <= n; i++){
            cin >> a[i];
        }
        ld x_low, x_high;
        cin >> x_low >> x_high;
        ld inc;
        cin >> inc;
        a = integrate(a);
        ld full_vol = calc_vol(x_low, x_high, a);
        cout << "Case " << tind << ": " << my_round(full_vol) << "\n";
        if(full_vol < inc) {
            cout << "insufficient volume" << "\n";
            cin >> n;
            continue;
        }
        int cnt = 0;
        ld lptr = x_low;
        while(full_vol > inc && cnt != 8) {
            cnt ++;
            ld low = lptr;
            ld high = x_high;
            while(high - low > epsilon) {
                ld mid = low + (high - low) / 2.0;
                if(calc_vol(lptr, mid, a) < inc) {
                    low = mid;
                }
                else {
                    high = mid;
                }
            }
            lptr = low;
            cout << my_round(lptr - x_low) << " ";
            full_vol -= inc;
        }
        cout << "\n";
        cin >> n;
    }
    
    return 0;
}
