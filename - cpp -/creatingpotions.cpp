#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//HackerRank - Creating Potions

//binary search across possible amounts of potions. 

//if you create x potions, it means that you can only use a maximum of x of each ingredient. 
//from there, validating is just greedy. 

bool isValid(vector<int>& a, int val, int g) {
    ll tgt = (ll) g * (ll) val;
    ll sum = 0;
    for(int i = 0; i < a.size(); i++){
        sum += min(a[i], val);
    }
    return sum >= tgt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, g;
    cin >> n >> g;
    vector<int> a(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int low = 0;
    int high = 1e9;
    int mid = low + (high - low) / 2;
    int ans = 0;
    while(low <= high) {
        if(isValid(a, mid, g)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << ans << "\n";
    
    return 0;
}