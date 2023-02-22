#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1795E

//lets say that you want to place the explosion on index i; what is the minimum cost of doing so?

//well, you have the cost of the explosion, which is a[i], and the cost of making the segment 
//a[0] to a[i] strictly increasing, and a[i] to a[n - 1] strictly decreasing. Lets denote these two as pfx[i]
//and sfx[i]. 

//so the answer for placing the explosion at i is a[i] + pfx[i] + sfx[i]. The answer is simply min(a[i] + pfx[i] + sfx[i]). 

//but how to calculate these values? notice that if we can calculate pfx, then we can just reverse a to calculate sfx. 

//so to calculate pfx[i], we want to find the greatest j where a[j] - j <= a[i] - i. To simplify, it means we want to find the
//greatest j where we don't have to change a[j] to make a[0] to a[i] strictly increasing. 

//once we have j, we assume that we already know pfx[j]. Thus, pfx[i] = pfx[j] + x, where x is the minimum operations to 
//make a[j] to a[i] strictly increasing. We can calculate x using prefix sums and arithmetic sequences. 

vector<ll> solve(vector<ll> a, int n) {
    ll sum = 0;
    vector<ll> pfx(n, 0);
    stack<pair<ll, ll>> s;  //index, sum
    s.push({-1, 0});
    for(int i = 0; i < n; i++){
        while(s.top().first != -1 && a[s.top().first] - s.top().first > a[i] - i) {
            s.pop();
        }
        int j = s.top().first;
        ll nextAns = j == -1? 0 : pfx[j];
        ll amt = i - (j + 1);
        ll psum = sum - s.top().second;
        ll r = a[i] - 1;
        ll l = r - amt + 1;
        if(l < 0){
            ll diff = 1 - l;
            amt -= diff;
            l = 1;
        }
        ll nsum = amt * (l - 1) + amt * (amt + 1) / 2;
        nextAns += psum - nsum;
        pfx[i] = nextAns;
        sum += a[i];
        s.push({i, sum});
        //cout << pfx[i] << " ";
    }
    //cout << "\n";
    return pfx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n, 0);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }  
        vector<ll> pfx = solve(a, n);
        reverse(a.begin(), a.end());
        vector<ll> sfx = solve(a, n);
        reverse(a.begin(), a.end());
        reverse(sfx.begin(), sfx.end());
        ll ans = 1e12;
        for(int i = 0; i < n; i++){
            ll nextAns = a[i] + pfx[i] + sfx[i];
            ans = min(ans, nextAns);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
