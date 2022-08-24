#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1697B

//since the y cheapest items from your purchase are free, it's always optimal to purchase the x most
//expensive items, so that you can maximize the value of your free stuff. 

//if you sort the items in descending value, then you'll find that the value of free stuff
//is equal to the subarray sum from x - y to x inclusive. Use pfx sums to quickly compute. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<ll> pfx(n + 1);
    sort(a.begin(), a.end(), [](int a, int b) {return a > b;});
    for(int i = 0; i < n; i++){
        pfx[i + 1] = pfx[i] + (ll) a[i];
    }
    while(q-- > 0){
        int x, y;
        cin >> x >> y;
        cout << (pfx[x] - pfx[x - y]) << "\n";
    }
    
    return 0;
}
