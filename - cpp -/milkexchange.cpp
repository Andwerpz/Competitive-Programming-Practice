#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    //rotate so that minimum element is last
    {
        int min_ind = 0;
        for(int i = 1; i < n; i++){
            if(a[i] < a[min_ind]) {
                min_ind = i;
            }
        }
        vector<ll> tmp(n);
        for(int i = 0; i < n; i++){
            tmp[i] = a[(min_ind + 1 + i) % n];
        }
        a = tmp;
    }
    //for each element, find the first element to it's right that is less than it
    vector<int> p(n);
    {   
        stack<pair<int, int>> s;    //{value, index}
        for(int i = n - 1; i >= 0; i--){
            while(s.size() != 0 && s.top().first >= a[i]) {
                s.pop();
            }
            p[i] = s.size() == 0? -1 : s.top().second;
            s.push({a[i], i});
        }
    }
    //this is O(n^2).
    //going backwards, figure out contribution from each element individually
    for(int i = n - 1; i >= 0; i--){

    }
    
    return 0;
}
