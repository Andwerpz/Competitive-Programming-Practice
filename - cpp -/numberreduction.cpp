#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//M(IT)^2 Winter 2025 Advanced Round 1 - P1

//note that any number that is reducible cannot have prime factors larger than 9, so we're restricted to 
//numbers of the form 2^a * 3^b * 5^c * 7^d. 

//There aren't actually that many numbers of that form under 10^18, a quick estimation puts the upper
//bound at around 12 million (60^4) but the actual amount is probably much less. 

//We can just go through all the numbers in ascending order, and see if they can go to a lower reducible
//number. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    ll n;
    cin >> n;
    priority_queue<ll> q;
    set<ll> anss, v;
    anss.insert(1);
    q.push(-1);
    while(q.size() != 0){
        ll cur = -q.top();
        q.pop();
        if(cur > n || v.count(cur)) continue;
        // cout << "CUR : " << cur << endl;
        v.insert(cur);
        q.push(-cur * 2), q.push(-cur * 3), q.push(-cur * 5), q.push(-cur * 7);
        ll tmp = cur;
        bool cvalid = false;
        while(tmp != 0){
            ll dig = tmp % 10;
            tmp /= 10;
            if(dig != 0 && cur % dig == 0 && anss.count(cur / dig)) cvalid = true;
        }
        if(cvalid) anss.insert(cur);
    }
    cout << anss.size() << "\n";
    
    return 0;
}