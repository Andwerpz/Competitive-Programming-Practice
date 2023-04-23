#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest H

//the criteria for making a polygon is that no side should be longer than the sum of all other sides. If the sides don't 
//meet this, then it's impossible. 

//otherwise, it is always possible. To make creating the polygon simpler, we can make a triangle. 

//from there it's just implementation. 

pair<ld, ld> lerp(pair<ld, ld>& a, pair<ld, ld>& b, ld lo, ld hi, ld val) {
    return {a.first + (b.first - a.first) / (hi - lo) * (val - lo), a.second + (b.second - a.second) / (hi - lo) * (val - lo)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ld> a(n);
    ld sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    if(n == 2){
        if(abs(a[0] - a[1]) < 1e-6) {
            cout << "0 0\n";
            cout << a[0] << " 0\n";
            cout << "0 0\n";
        }
        else {
            cout << "impossible\n";
        }
        return 0;
    }
    ld max = 0;
    int maxInd = -1;
    for(int i = 0; i < n; i++){
        if(sum - a[i] < a[i]) {
            cout << "impossible\n";
            return 0;
        }
        if(max < a[i]) {
            max = a[i];
            maxInd = i;
        }
    }
    ld sideA = max;
    ld sideB = 0;
    ld sideC = sum - max;
    vector<int> whichSide(n, 3);
    whichSide[maxInd] = 1;
    for(int i = 1; i < n; i++){
        sideB += a[(maxInd + i) % n];
        sideC -= a[(maxInd + i) % n];
        whichSide[(maxInd + i) % n] = 2;
        if(sideA - 1e-6 < sideC + sideB && sideB - 1e-6 < sideA + sideC && sideC - 1e-6 < sideA + sideB) {
            break;
        }
    }
    pair<ld, ld> va = {0, 0};
    pair<ld, ld> vb = {sideA, 0};
    ld theta = acos((sideA * sideA + sideC * sideC - sideB * sideB) / (2 * sideA * sideC));
    pair<ld, ld> vc = {cos(theta) * sideC, sin(theta) * sideC};
    vector<pair<ld, ld>> wStart(n, {0, 0});
    wStart[maxInd] = va;
    ld ptr = 0;
    bool onSideC = false;
    for(int i = 1; i < n; i++){
        if(whichSide[(i - 1 + maxInd + n) % n] == 2 && whichSide[(i + maxInd) % n] == 3){
            onSideC = true;
            ptr = 0;
        }
        if(!onSideC) {
            wStart[(i + maxInd) % n] = lerp(vb, vc, 0, sideB, ptr);
        }
        else {
            wStart[(i + maxInd) % n] = lerp(vc, va, 0, sideC, ptr);
        }
        ptr += a[(i + maxInd) % n];
    }
    pair<ld, ld> offset = {wStart[0].first, wStart[0].second};
    for(int i = 0; i < n; i++){
        wStart[i].first -= offset.first;
        wStart[i].second -= offset.second;
    }
    for(int i = 0; i < n + 1; i++){
        cout << fixed << setprecision(10) << wStart[i % n].first << " " << wStart[i % n].second << "\n";
    }
    
    return 0;
}
