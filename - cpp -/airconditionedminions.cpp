#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 05 A

//for each room, try to satisfy the largest prefix of minions possible. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    int ans = 0;
    int temp = -1;
    for(int i = 0; i < n; i++){
        if(temp < a[i].first) {
            temp = a[i].second;
            ans ++;
        }
        temp = min(temp, a[i].second);
    }
    cout << ans << "\n";
    
    return 0;
}
