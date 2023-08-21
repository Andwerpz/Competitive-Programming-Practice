#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1849B

//we can first use the skill as many times without killing any of the monsters. 
//Then, if a monster was of health a[i], it will now be of health a[i] % k, and if a[i] % k == 0, then k. 

//then, since we kill all monsters in 1 hit now, we can just sort the monsters, by health, then index, and fill 
//out the answer. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
            a[i].second = i;
            a[i].first %= k;
            if(a[i].first == 0){
                a[i].first = k;
            }
        }
        sort(a.begin(), a.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
            if(a.first != b.first) {
                return a.first > b.first;
            }
            return a.second < b.second;
        });
        vector<int> ans(n);
        for(int i = 0; i < n; i++){
            //cout << a[i].first << " " << a[i].second << "\n";
            ans[i] = a[i].second + 1;
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
