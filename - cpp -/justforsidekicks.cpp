#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 04 A

//just keep 6 parallel segment trees, one for each type of gem. 

const int N = 1e6;  //limit for segtree size
int n;
int t[6][2 * N];

void modify(int i, int p, int value) { // set value at position p
    p += n;
    t[i][p] = value;
    for (p /= 2; p > 0; p /= 2) {
        t[i][p] = t[i][p * 2] + t[i][p * 2 + 1];
    }
}

int query(int i, int l, int r) { // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res += t[i][l];
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res += t[i][r];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> n >> q;
    vector<ll> v(6);
    for(int i = 0; i < 6; i++){
        cin >> v[i];
    }
    string s;
    cin >> s;
    for(int i = 0; i < n; i++){
        int type = s[i] - '1';
        modify(type, i, 1);
    }
    while(q-- > 0){
        int t;
        cin >> t;
        if(t == 1){
            int k, p;
            cin >> k >> p;
            k --;
            p --;
            for(int i = 0; i < 6; i++){
                if(i == p){
                    modify(i, k, 1);
                }
                else {
                    modify(i, k, 0);
                }
            }
        }
        else if(t == 2){
            int p, val;
            cin >> p >> val;
            p --;
            v[p] = val;
        }
        else if(t == 3){
            int l, r;
            cin >> l >> r;
            l --;
            ll sum = 0;
            for(int i = 0; i < 6; i++){
                ll next = query(i, l, r);
                sum += next * v[i];
            }
            cout << sum << "\n";
        }
    }
    
    return 0;
}
