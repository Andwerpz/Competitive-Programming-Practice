#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1849C

//for each range sort, we want to find the minimum 'effective range'. 

//note that for a given range, if a[l] == '0', then it doesn't move. So we want to increment l until a[l] == '1'. 
//similar for r, if a[r] == '1', then we want to decrement r until a[r] == '0'. 

//we can increment and decrement faster if we just store for each '0', what's the nearest '1', and for each '1'
//the nearest '0'. 

//then we can keep a set of these minimum 'effective ranges'. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        string st;
        cin >> st;
        vector<int> lrev(n, -1);
        int ind = -1;
        for(int i = 1; i < n; i++){
            if(st[i - 1] == '0' && st[i] == '1') {
                ind = i;
            }
            lrev[i] = ind;
        }
        vector<int> rrev(n, -1);
        ind = -1;
        for(int i = n - 2; i >= 0; i--){
            if(st[i] == '0' && st[i + 1] == '1') {
                ind = i;
            }
            rrev[i] = ind;
        }
        // for(int i = 0; i < n; i++){
        //     cout << lrev[i] << " \n"[i == n - 1];
        // }
        // for(int i = 0; i < n; i++){
        //     cout << rrev[i] << " \n"[i == n - 1];
        // }
        int ans = 0;
        bool found = false;
        set<pair<int, int>> s;
        while(q--){
            int l, r;
            cin >> l >> r;
            l --;
            if(st[l] != '1') {
                if(rrev[l] == -1){
                    l = n;
                }
                else {
                    l = rrev[l] + 1;
                }
            }
            if(st[r - 1] != '0') {
                if(lrev[r - 1] == -1){
                    r = 0;
                }
                else {
                    r = lrev[r - 1];
                }
            }
            //cout << "LR : " << l << " " << r << "\n";
            if(r - l <= 0){
                //cout << "NOCHANGE" << endl;
                if(!found) {
                    ans ++;
                }
                found = true;
            }
            else {
                //cout << "CHANGE : " << l << " " << r << endl;
                pair<int, int> p = {l, r};
                s.insert(p);
            }
        }
        ans += s.size();
        cout << ans << "\n";
    }
    
    return 0;
}
