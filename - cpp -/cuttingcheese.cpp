#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2015 D

//we can do a binary search to find the widths of each slice. 

//since the spheres don't intersect the edges of the cheese, and don't intersect with each other, it's pretty easy to do so. 

int n, s;
vector<vector<ld>> a;   //r, x, y, z

ld pi = 3.1415926535;

ld calc_circle_volume(int i, ld z) {
    ld r = a[i][0];
    ld x_0 = -r;
    ld x_1 = z - a[i][3];
    x_1 = clamp(x_1, -r, r);
    //cout << "X1 : " << x_1 << "\n";
    ld low = pi * (x_0 * r * r - x_0 * x_0 * x_0 / 3.0);
    ld high = pi * (x_1 * r * r - x_1 * x_1 * x_1 / 3.0);
    return high - low;
}

//calculates the area in the prefix [0, z);
ld calc_volume(ld z) {
    //cout << "CALCULATING VOLUME : " << z << "\n";
    ld volume = (ld) 100000 * (ld) 100000 * z;
    for(int i = 0; i < a.size(); i++){
        volume -= calc_circle_volume(i, z);
    }
    return volume;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> s;
    a = vector<vector<ld>>(n, vector<ld>(4, 0));
    for(int i = 0; i < n; i++){
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
    }
    vector<ld> ans(0);
    ld z_0 = 0;
    ld tgt_vol = calc_volume(100000) / (ld) s;
    //cout << "TGT : " << tgt_vol << "\n";
    //ld total_volume = 0;
    for(int i = 0; i < s - 1; i++){
        //cout << z_0 << "\n";
        ld vol_0 = calc_volume(z_0);
        ld low = z_0;
        ld high = 100000;
        while(high - low > 1e-9) {
            ld mid = low + (high - low) / 2;
            ld mid_vol = calc_volume(mid) - vol_0;
            if(mid_vol < tgt_vol) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        //cout << "NEXT SLICE VOLUME : " << (calc_volume(low) - vol_0) << "\n";
        //total_volume += calc_volume(low) - vol_0;
        ans.push_back(low - z_0);
        z_0 = low;
    }
    //cout << "NEXT SLICE VOLUME : " << (calc_volume(100000) - calc_volume(z_0)) << "\n";
    //total_volume += calc_volume(100000) - calc_volume(z_0);
    //cout << "TOTAL VOLUME : " << total_volume << " " << calc_volume(100000) << "\n";
    ans.push_back((ld) 100000 - z_0);
    cout << fixed << setprecision(10);
    for(int i = 0; i < ans.size(); i++){
        cout << (ans[i] / 1000.0) << "\n";
    }
    
    return 0;
}
