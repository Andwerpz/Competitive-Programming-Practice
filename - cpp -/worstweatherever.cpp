#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 04 D

//i think i have the solution, i'm just missing some casework. 

const int N = 1e6;  //limit for segtree size
int n;
int t[2 * N];

void modify(int p, int value) { // set value at position p
    p += n;
    t[p] = value;
    for (p /= 2; p > 0; p /= 2) {
        t[p] = max(t[p * 2], t[p * 2 + 1]);
    }
}

int query(int l, int r) { // max on interval [l, r)
    int res = -1;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res = max(res, t[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res = max(res, t[r]);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    while(n != 0){
        n += 2;
        map<int, int> m;
        for(int i = 0; i < n - 2; i++){
            int y, r;
            cin >> y >> r;
            m.insert({y, i + 1});
            modify(i + 1, r);
        }
        m.insert({-1e9 - 1, 0});
        m.insert({1e9 + 1, n - 1});
        modify(0, 1e9 + 1);
        modify(n - 1, 1e9 + 1);
        int q;
        cin >> q;
        for(int i = 0; i < q; i++){
            int l, r;
            cin >> l >> r;
            if(m.find(r) == m.end()) {
                cout << "maybe\n";
                continue;
            }
            int lVal = -1;
            int rVal = -1;
            bool adjacent = l == r - 1;
            bool missingBetween = true;
            if(m.find(l) != m.end()) {
                int lInd = m.find(l) -> second;
                lVal = t[lInd + n];
            }
            if(m.find(r) != m.end()) {
                int rInd = m.find(r) -> second;
                rVal = t[rInd + n];
            }
            int lrInd = m.upper_bound(l) -> second;
            int rrInd = m.lower_bound(r) -> second;
            if(rrInd - lrInd == r - l - 1) {
                missingBetween = false;
            }
            int maxBetween = -1;
            if(lrInd < rrInd) {
                maxBetween = query(lrInd, rrInd);
            }
            // cout << "START INFO" << "\n";
            // cout << l << " " << r << "\n";
            // cout << adjacent << " " << missingBetween << "\n";
            // cout << lVal << " " << rVal << "\n";
            // cout << lrInd << " " << rrInd << "\n";
            // cout << maxBetween << "\n";
            // cout << "END INFO" << "\n";

            // bool isValid = false;
            // if(lVal >= rVal && rVal > maxBetween) {
            //     isValid = true;
            // }
            // if(isValid && !missingBetween && lVal >= 0 && rVal >= 0) {
            //     cout << "true\n";
            // }
            // else if(isValid){
            //     cout << "maybe\n";
            // }
            // else {
            //     cout << "false\n";
            // }

            bool isValid = false;
            if((rVal > maxBetween || rVal == -1) && (lVal >= rVal || lVal == -1)) {
                isValid = true;
            }
            // if((lVal <= rVal || rVal == -1) && maxBetween < rVal) {
            //     isValid = true;
            // }
            if(isValid && !missingBetween && lVal != -1 && rVal != -1) {
                cout << "true\n";
            }
            else if(isValid){
                cout << "maybe\n";
            }
            else {
                cout << "false\n";
            }
        }
        cout << "\n";
        cin >> n;
    }

    return 0;
}
