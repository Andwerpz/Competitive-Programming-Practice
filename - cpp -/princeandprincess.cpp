#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 12 E

//classic longest common subsequence 
//turn it into longest increasing subsequence to get O(nlog(n)) complexity. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    int caseCnt = 0;
    while(t-- > 0){
        caseCnt ++;
        int n, p, q;
        cin >> n >> p >> q;
        p ++;
        q ++;
        vector<int> a(p);
        vector<int> b(q);
        for(int i = 0; i < p; i++){
            cin >> a[i];
        }
        for(int i = 0; i < q; i++){
            cin >> b[i];
        }
        map<int, int> m;
        for(int i = 0; i < p; i++){
            m.insert({a[i], i});
            //cout << "INS : " << a[i] << " " << i << "\n";
        }
        vector<ll> lis(q + 1, 1e9);
        lis[0] = -1e9;
        int ans = 0;
        for(int i = 0; i < q; i++){
            if(m.find(b[i]) == m.end()) {
                //cout << "CANT FIND : " << b[i] << "\n";
                continue;
            }
            ll next = m.find(b[i])->second;
            //cout << next << "\n";
            int ind = q;
            int low = 0;
            int high = q - 1;
            int mid = low + (high - low) / 2;
            while(low <= high) {
                if(lis[mid] >= next) {
                    ind = min(ind, mid);
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
                mid = low + (high - low) / 2;
            }
            //cout << "IND : " << ind << "\n";
            ans = max(ans, ind);
            lis[ind] = min(lis[ind], next);
        }
        cout << "Case " << caseCnt << ": " << ans << "\n";
    }
    
    return 0;
}
