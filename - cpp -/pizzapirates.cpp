#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest P

//in the case where ethan can beat all the pirates in one day, then the answer is n * d. 

//else, he can only beat less than n pirates in one day. We can see that the pirates appear in a circular fashion, as 
//the beaten pirates circle around to the back of the queue. 

//For each pirate starting, we need to find what pirate will start the next day. In at most n days, there will be some loop, where
//we can quickly calculate the total pirates beaten. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll e, d;
    cin >> n >> e >> d;
    vector<ll> a(n);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum += a[i];
    }
    if(e >= sum) {
        cout << d * n << "\n";
        return 0;
    }
    vector<int> c(n);
    vector<ll> amt(n);
    vector<ll> pfx(3 * n + 1);
    pfx[0] = 0;
    for(int i = 1; i < 3 * n; i++){
        pfx[i] = pfx[i - 1] + a[(i - 1) % n];
    }
    for(int i = 0; i < n; i++){
        if(a[i] > e) {
            c[i] = i;
            amt[i] = 0;
            continue;
        }
        int low = i;
        int high = low + n - 1;
        int mid = low + (high - low) / 2;
        int ind = low;
        while(low <= high) {
            ll tot = pfx[mid + 1] - pfx[i];
            //cout << "TOT : " << tot << " " << mid << " " << i << "\n";
            if(e >= tot) {
                low = mid + 1;
                ind = max(ind, mid);
            }
            else {
                high = mid - 1;
            }
            mid = low + (high - low) / 2;
        }
        c[i] = (ind + 1) % n;
        amt[i] = (ind + 1) - i;
    }
    // for(int i = 0; i < n; i++){
    //     cout << c[i] << " ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n; i++){
    //     cout << amt[i] << " ";
    // }
    // cout << "\n";
    set<int> s;
    vector<int> l;
    int ptr = 0;
    while(s.find(ptr) == s.end() && s.size() < d) {
        s.insert(ptr);
        l.push_back(ptr);
        ptr = c[ptr];
    }
    ll ans = 0;
    if(s.size() == d){
        for(int i = 0; i < d; i++){
            ans += amt[l[i]];
        }
    }
    else {
        vector<int> loop(0);
        bool found = false;
        for(int i = 0; i < l.size(); i++){
            if(ptr == l[i]){
                found = true;
            }
            if(found) {
                loop.push_back(l[i]);
            }
            else {
                ans += amt[l[i]];
                d --;
            }
        }
        ll numLoops = d / loop.size();
        for(int i = 0; i < loop.size(); i++){
            ans += numLoops * amt[loop[i]];
            if(i < d % loop.size()) {
                ans += amt[loop[i]];
            }
        }
    }
    cout << ans << "\n";
    
    return 0;
}
