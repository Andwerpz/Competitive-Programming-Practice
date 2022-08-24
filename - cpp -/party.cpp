#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1711B

//the idea is to invite everyone, and remove people until the amount of cakes is even. 

//notice that if m is even, then you don't need to remove anyone. 

//if m is odd, then you need to remove someone. The most obvious choice is to remove someone
//with an odd amount of connections, so that the remaining connections is even. 

//the less obvious choice is to remove someone with an even amount of connections, so that someone else
//with an even amount of connections now has an odd amount of connections, so you can remove them. 

//both can be brute force tested in linear time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        vector<int> cnt(n);
        vector<int> minEven(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            minEven[i] = 1e9;
        }
        vector<pair<int, int>> c(m);
        for(int i = 0; i < m; i++){
            cin >> c[i].first >> c[i].second;
            cnt[--c[i].first] ++;
            cnt[--c[i].second] ++;
        }
        int ans = 1e9;
        for(int i = 0; i < m; i++){
            if(cnt[c[i].first] % 2 == 0){
                minEven[c[i].second] = min(minEven[c[i].second], a[c[i].first]);
            }
            if(cnt[c[i].second] % 2 == 0){
                minEven[c[i].first] = min(minEven[c[i].first], a[c[i].second]);
            }
        }
        if(m % 2 == 0){
            ans = 0;
        }
        for(int i = 0; i < n; i++){
            if(cnt[i] % 2 == 1){
                ans = min(ans, a[i]);
            }
            else{
                ans = min(ans, a[i] + minEven[i]);
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
