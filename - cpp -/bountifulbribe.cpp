#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//ACPC 2024 Spring Contest - B

//greedily take the toppings with the maximum happiness. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, pair<string, int>>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].second.first >> a[i].first >> a[i].second.second;
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < n; j++){
            if(a[j].second.second != 0){
                cout << a[j].second.first << "\n";
                a[j].second.second --;
                break;
            }
        }
    }
    
    return 0;
}
